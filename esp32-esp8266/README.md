# Firmware do ESP32

Responsável — João Cláudio Cavalcanti Beltrão Filho (@jocla3).

## O que esta versão faz

Lê o LDR pelo GPIO34 e aciona um LED pelo GPIO23. A leitura usa 12 bits, de 0 a 4095. Com o divisor proposto, a leitura cai no escuro. O LED liga em valores menores ou iguais a 1500 e desliga em valores maiores ou iguais a 1800. Dentro desse intervalo, mantém o estado anterior. Os limites são iniciais e precisam de calibração no ambiente real.

## Como gravar

1. Instale o Arduino IDE e o suporte de placas `esp32` da Espressif pelo gerenciador de placas.
2. Abra `iluminacao/iluminacao.ino`.
3. Selecione ESP32 Dev Module e a porta da placa.
4. Compile e grave com um cabo USB de dados.
5. Abra o monitor serial a 115200 baud.
6. Compare os valores com o LDR iluminado e coberto. Ajuste `LIMIAR_LIGAR` e `LIMIAR_DESLIGAR`, mantendo o primeiro menor que o segundo.

Se o LED não responder, confira polaridade, resistor, GPIO e o GND comum. Posicione o LED para que ele não ilumine diretamente o sensor.

## Integração seguinte

Wi-Fi, MQTT e os comandos manuais ainda precisam ser implementados. O contrato das mensagens estará em `docs/PROTOCOLO_MQTT.md`. A automação local desta versão serve como base para essa integração.

A compilação com o core ESP32 e a validação física ainda precisam ser registradas. O teste de lógica com funções Arduino simuladas pode ser executado em computador com C++17 conforme o roteiro de testes.

Documentação de referência — https://docs.espressif.com/projects/arduino-esp32/en/latest/api/adc.html
