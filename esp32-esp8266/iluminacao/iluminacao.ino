#include <Arduino.h>
#include "controle.h"

#ifdef ARDUINO_ARCH_ESP32
#include "rede.h"
#endif

constexpr int PINO_LDR = 34;
constexpr int PINO_LED = 23;

bool luzLigada = false;
Modo modoAtual = Modo::Automatico;

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
  digitalWrite(PINO_LED, LOW);
  analogReadResolution(12);

#ifdef ARDUINO_ARCH_ESP32
  iniciarRede();
#endif
}

void loop() {
  const int leitura = analogRead(PINO_LDR);

#ifdef ARDUINO_ARCH_ESP32
  Comando comando{};
  if (receberComando(comando)) {
    modoAtual = comando.modo;
  }
#endif

  luzLigada = calcularLuz(modoAtual, leitura, luzLigada);
  digitalWrite(PINO_LED, luzLigada ? HIGH : LOW);

#ifdef ARDUINO_ARCH_ESP32
  registrarLeitura(leitura, luzLigada, modoAtual, comando.id);
#endif

  Serial.printf("LDR: %d | LED: %s\n", leitura, luzLigada ? "ligado" : "desligado");
  delay(250);
}
