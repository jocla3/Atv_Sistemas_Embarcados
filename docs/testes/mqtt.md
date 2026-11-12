# Testes da comunicação

Responsável — Raul (@raulvnc).

Em `applications/`, rode `docker compose up -d` e use os comandos do [guia dos serviços](../../applications/README.md).

| Teste | Resultado esperado |
| --- | --- |
| Carregar o fluxo e iniciar os serviços | Mosquitto e Node-RED ativos, com o painel servido em `/painel/` |
| Conectar a placa | O broker recebe status online e telemetria com leitura, modo e estado do LED |
| Testar os três comandos pelo painel | O ESP32 aplica o modo e devolve a confirmação com o identificador do comando |
| Desconectar o Wi-Fi do ESP32 | O painel deixa de aceitar comandos e o controle local continua |
| Reconectar o ESP32 | O painel recebe a leitura atual e nenhum comando antigo é reaplicado |
| Reiniciar a placa em modo manual | A placa volta no modo automático |
| Desligar o broker | O controle local continua e a placa volta a publicar quando o broker retornar |

Registre as mensagens e os logs. Identifique os resultados obtidos com cliente MQTT de teste e os obtidos com a placa física.

Em 12/11/2026, um cliente MQTT de teste confirmou telemetria, envio de comando e retorno da confirmação no Docker Compose. Os testes com o ESP32 físico devem ser registrados na bancada.
