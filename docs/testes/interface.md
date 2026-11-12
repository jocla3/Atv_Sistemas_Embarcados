# Testes do painel

Responsável — Rafael (@rafaelcf29).

Abra http://localhost:1880/painel/ com os serviços em execução.

| Ação | Resultado esperado |
| --- | --- |
| Abrir sem ESP32 conectado | Estado offline, indicadores sem leitura e comandos desabilitados |
| Receber telemetria válida | Leitura, estado do LED e modo aparecem no painel |
| Enviar cada um dos três comandos | A interface aguarda a confirmação do identificador correspondente |
| Receber uma confirmação com outro identificador | O comando em andamento continua aguardando |
| Ficar sem confirmação | O painel avisa e permite tentar de novo quando o ESP32 está disponível |
| Parar de receber telemetria por mais de 7 segundos | O painel informa que os dados estão desatualizados |
| Receber offline e depois nova telemetria | Os controles são desabilitados e voltam quando há leitura recente |
| Receber mais de 20 mudanças de estado | Apenas as últimas 20 aparecem no histórico |
| Abrir em tela pequena | A tabela pode rolar sem alargar a página |

Registre uma captura com dados da placa para a entrega.

Em 12/11/2026, testamos o painel em Chrome com viewport de 390 px, Node-RED, Mosquitto e um cliente MQTT de teste. Passaram os três modos, a confirmação por identificador, o timeout e a volta da telemetria após desconexão.

Para repetir a demonstração sem a placa, siga o [roteiro do cliente MQTT de teste](../../applications/README.md#demonstração-sem-o-esp32).
