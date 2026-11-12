#include "rede.h"

#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <initializer_list>

#if __has_include("configuracao.h")
#include "configuracao.h"
#else
#include "configuracao.exemplo.h"
#endif

namespace {
constexpr char TOPICO_TELEMETRIA[] = "grupo3/iluminacao/telemetria";
constexpr char TOPICO_COMANDO[] = "grupo3/iluminacao/comando";
constexpr char TOPICO_STATUS[] = "grupo3/iluminacao/status";
constexpr uint32_t INTERVALO_TELEMETRIA = 2000;
constexpr uint32_t INTERVALO_RECONEXAO = 5000;

struct Leitura {
  int ldr;
  bool luz;
  Modo modo;
  char confirmacao[33];
};

WiFiClient wifi;
PubSubClient mqtt(wifi);
QueueHandle_t comandos = nullptr;
QueueHandle_t ultimaLeitura = nullptr;
QueueHandle_t confirmacoes = nullptr;

const char *nomeModo(Modo modo) {
  switch (modo) {
    case Modo::Ligada: return "ligada";
    case Modo::Desligada: return "desligada";
    case Modo::Automatico: return "automatico";
  }
  return "automatico";
}

bool lerModo(const char *nome, Modo &modo) {
  for (const auto candidato : {Modo::Automatico, Modo::Ligada, Modo::Desligada}) {
    if (strcmp(nome, nomeModo(candidato)) == 0) {
      modo = candidato;
      return true;
    }
  }
  return false;
}

void aoReceber(char *, byte *dados, unsigned int tamanho) {
  if (tamanho == 0 || tamanho >= 128 || memchr(dados, '\0', tamanho)) {
    return;
  }

  char texto[128];
  memcpy(texto, dados, tamanho);
  texto[tamanho] = '\0';
  Comando comando{};

  if (texto[0] == '{') {
    JsonDocument json;
    if (deserializeJson(json, texto, tamanho)) {
      return;
    }
    const char *id = json["id"] | "";
    const size_t comprimento = strlen(id);
    if (comprimento == 0 || comprimento >= sizeof(comando.id) ||
        strspn(id, "0123456789abcdef") != comprimento ||
        !lerModo(json["modo"] | "", comando.modo)) {
      return;
    }
    memcpy(comando.id, id, comprimento + 1);
  } else if (!lerModo(texto, comando.modo)) {
    return;
  }

  xQueueSend(comandos, &comando, 0);
}

bool publicar(const Leitura &leitura) {
  JsonDocument json;
  json["ldr"] = leitura.ldr;
  json["luz"] = leitura.luz;
  json["modo"] = nomeModo(leitura.modo);
  if (leitura.confirmacao[0] != '\0') {
    json["confirmacao"] = leitura.confirmacao;
  }

  char mensagem[128];
  const size_t tamanho = serializeJson(json, mensagem, sizeof(mensagem));
  return mqtt.publish(TOPICO_TELEMETRIA, reinterpret_cast<const uint8_t *>(mensagem), tamanho);
}

void executarRede(void *) {
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_SENHA);

  char id[32];
  snprintf(id, sizeof(id), "grupo3-%012llx", static_cast<unsigned long long>(ESP.getEfuseMac()));
  mqtt.setServer(MQTT_HOST, MQTT_PORTA);
  mqtt.setCallback(aoReceber);
  mqtt.setSocketTimeout(2);
  mqtt.setKeepAlive(10);

  uint32_t ultimaTentativa = millis() - INTERVALO_RECONEXAO;
  uint32_t ultimaPublicacao = 0;
  Leitura publicada{};
  bool precisaPublicar = true;

  while (true) {
    const uint32_t agora = millis();
    if (WiFi.status() != WL_CONNECTED) {
      wifi.stop();
    } else if (!mqtt.connected()) {
      if (agora - ultimaTentativa >= INTERVALO_RECONEXAO) {
        ultimaTentativa = agora;
        if (mqtt.connect(id, TOPICO_STATUS, 1, true, "offline")) {
          if (!mqtt.subscribe(TOPICO_COMANDO) || !mqtt.publish(TOPICO_STATUS, "online", true)) {
            wifi.stop();
          }
          precisaPublicar = true;
        }
      }
    } else if (mqtt.loop()) {
      Leitura leitura{};
      while (xQueuePeek(confirmacoes, &leitura, 0) == pdTRUE) {
        if (!publicar(leitura)) {
          break;
        }
        xQueueReceive(confirmacoes, &leitura, 0);
        precisaPublicar = true;
      }

      if (xQueuePeek(ultimaLeitura, &leitura, 0) == pdTRUE &&
          (precisaPublicar || leitura.luz != publicada.luz || leitura.modo != publicada.modo ||
           agora - ultimaPublicacao >= INTERVALO_TELEMETRIA) &&
          publicar(leitura)) {
        publicada = leitura;
        ultimaPublicacao = agora;
        precisaPublicar = false;
      }
    }

    vTaskDelay(pdMS_TO_TICKS(25));
  }
}
}

void iniciarRede() {
  if (WIFI_SSID[0] == '\0' || MQTT_HOST[0] == '\0') {
    Serial.println("Wi-Fi/MQTT sem configuração. Automação local ativa.");
    return;
  }

  comandos = xQueueCreate(8, sizeof(Comando));
  ultimaLeitura = xQueueCreate(1, sizeof(Leitura));
  confirmacoes = xQueueCreate(8, sizeof(Leitura));
  if (comandos && ultimaLeitura && confirmacoes &&
      xTaskCreate(executarRede, "rede", 6144, nullptr, 1, nullptr) == pdPASS) {
    return;
  }

  if (comandos) vQueueDelete(comandos);
  if (ultimaLeitura) vQueueDelete(ultimaLeitura);
  if (confirmacoes) vQueueDelete(confirmacoes);
  comandos = ultimaLeitura = confirmacoes = nullptr;
  Serial.println("Rede indisponível. Automação local ativa.");
}

bool receberComando(Comando &comando) {
  return comandos && xQueueReceive(comandos, &comando, 0) == pdTRUE;
}

void registrarLeitura(int leitura, bool luzLigada, Modo modo, const char *confirmacao) {
  if (!ultimaLeitura) {
    return;
  }

  Leitura estado{leitura, luzLigada, modo, {}};
  xQueueOverwrite(ultimaLeitura, &estado);
  if (confirmacao[0] != '\0') {
    strcpy(estado.confirmacao, confirmacao);
    xQueueSend(confirmacoes, &estado, 0);
  }
}
