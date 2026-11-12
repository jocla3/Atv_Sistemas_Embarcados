# Firmware do ESP32

Responsável — João Cláudio Cavalcanti Beltrão Filho (@jocla3).

O ESP32 lê o LDR no GPIO34 e controla o LED no GPIO23. No automático, o LED liga com leitura de até 1500 e desliga a partir de 1800. Entre os limites, mantém o estado anterior. Os valores iniciais estão em `iluminacao/controle.h` e devem ser calibrados na montagem.

## Configurar e gravar

1. No Arduino IDE, instale o pacote de placas **esp32** da Espressif e as bibliotecas **PubSubClient** e **ArduinoJson 7**.
2. Copie `iluminacao/configuracao.exemplo.h` para `iluminacao/configuracao.h`. Preencha o nome e a senha da rede Wi-Fi de 2,4 GHz e o IPv4 do computador que executa o Docker. O arquivo local com as credenciais está no `.gitignore`.
3. Abra `iluminacao/iluminacao.ino`, selecione **ESP32 Dev Module**, escolha a porta e grave pelo USB.
4. Abra o monitor serial a **115200 baud** e compare as leituras com o LDR coberto e iluminado. Se necessário, ajuste os limites em `controle.h` e grave novamente.
5. Abra o [painel](http://localhost:1880/painel/) e confira a telemetria e o acionamento pelo navegador.

Com a configuração de rede vazia, o firmware roda em modo automático local. A perda de Wi-Fi ou do broker mantém o controle local no modo atual. O modo automático volta ao reiniciar a placa. A placa tenta se reconectar sem interromper a leitura do sensor.

Se o LED não responder, confira polaridade, resistor, GPIO e o GND comum. Posicione o LED para que ele não ilumine diretamente o sensor.

[Roteiro de testes](../docs/testes/firmware.md) · [Contrato MQTT](../docs/PROTOCOLO_MQTT.md)
