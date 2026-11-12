# Contrato MQTT

Responsável — Raul Vila Nova (@raulvnc).

O firmware, o Node-RED e o painel seguem os tópicos abaixo.

Broker local Mosquitto na porta 1883. No Node-RED em Docker, configure o host `mqtt`. No ESP32, use o endereço IPv4 do computador na mesma rede Wi-Fi. Cada cliente deve ter um identificador diferente.

| Tópico | Publicador | Assinante | Conteúdo |
| --- | --- | --- | --- |
| grupo3/iluminacao/telemetria | ESP32 | Node-RED | JSON com ldr, luz e modo |
| grupo3/iluminacao/comando | Node-RED | ESP32 | Modo em texto ou JSON com modo e id |
| grupo3/iluminacao/status | ESP32/broker | Node-RED | online ou offline |

Exemplo de telemetria:

```json
{"ldr":1200,"luz":true,"modo":"automatico"}
```

`ldr` é inteiro entre 0 e 4095. `luz` é booleano. `modo` assume `automatico`, `ligada` ou `desligada`. A leitura é bruta, sem unidade lux. O dispositivo deve enviar telemetria periodicamente e após aplicar um comando válido.

Comandos usam QoS 0 e `retain=false`. O ESP32 deve ignorar mensagens desconhecidas. Repetir um comando válido deve manter o mesmo estado. O status deve usar retenção e Last Will `offline`. Ao conectar, o dispositivo publica `online` e seu estado atual.

Os botões de diagnóstico do Node-RED enviam os modos em texto. O painel envia um comando identificado, como `{"modo":"ligada","id":"e81d3f17cfc387a8"}`. Depois de atualizar o GPIO, o ESP32 inclui o campo `confirmacao` com esse identificador na próxima telemetria do comando. O painel aguarda o identificador recebido para informar que o firmware aplicou o comando.

O Node-RED fornece `GET /api/estado` e `POST /api/comando`. Para enviar um comando, use o tipo `application/json` e o campo `modo`. A API responde com HTTP 202 e um identificador quando encaminha o comando ao broker. Sem telemetria recente ou conexão ativa, responde com HTTP 503.

O cliente da demonstração usa o campo opcional `simulado: true` na telemetria. Assim, o painel identifica as leituras e confirmações do teste.
