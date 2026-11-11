# Contrato MQTT

Responsável — Raul (@raulvnc). Este contrato orienta a integração ainda pendente no firmware e no painel.

Broker local Mosquitto na porta 1883. No Node-RED em Docker, configure o host `mqtt`. No ESP32, use o endereço IPv4 do computador na mesma rede Wi-Fi. Cada cliente deve ter um identificador diferente.

| Tópico | Publicador | Assinante | Conteúdo |
| --- | --- | --- | --- |
| grupo3/iluminacao/telemetria | ESP32 | Node-RED | JSON com ldr, luz e modo |
| grupo3/iluminacao/comando | Node-RED | ESP32 | automatico, ligada ou desligada |
| grupo3/iluminacao/status | ESP32/broker | Node-RED | online ou offline |

Exemplo de telemetria:

```json
{"ldr":1200,"luz":true,"modo":"automatico"}
```

`ldr` é inteiro entre 0 e 4095. `luz` é booleano. `modo` assume `automatico`, `ligada` ou `desligada`. A leitura é bruta, sem unidade lux. O dispositivo deve enviar telemetria periodicamente e após aplicar um comando válido.

Comandos usam QoS 0 e `retain=false`. O ESP32 deve ignorar mensagens desconhecidas. Repetir um comando válido deve manter o mesmo estado. O status deve usar retenção e Last Will `offline`. Ao conectar, o dispositivo publica `online` e seu estado atual.

A confirmação de publicação no broker não confirma o acionamento físico. A interface deverá aguardar telemetria nova para exibir o resultado do comando.
