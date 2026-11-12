# Painel de iluminação

Responsável — Rafael Fernandes (@rafaelcf29).

Inicie os serviços conforme [o guia do Docker](../README.md) e abra http://localhost:1880/painel/.

O painel mostra a leitura do LDR, o estado do LED, o modo de operação e a disponibilidade do ESP32. Os botões ficam disponíveis quando há telemetria recente. A confirmação do comando aparece depois que o firmware informa que o aplicou. O histórico mostra as últimas 20 mudanças de leitura, luz ou modo e fica na memória do Node-RED até o serviço reiniciar.

O [roteiro da interface](../../docs/testes/interface.md) descreve os cenários de teste.
