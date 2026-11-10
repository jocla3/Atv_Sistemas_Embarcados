# Montagem do circuito

Responsável — Caio Sena (@Caiosenas2101).

Consulte `circuito.svg` e `circuito.txt`. O desenho representa as conexões elétricas, sem fixar posições na protoboard.

| Componente | Ligação |
| --- | --- |
| ESP32 DevKit | Alimentação por USB |
| LDR, terminal 1 | 3V3 |
| LDR, terminal 2 | Junção de leitura e GPIO34 (D34) |
| Resistor 10 kΩ | Entre a junção de leitura e GND |
| Resistor 220 Ω ou 330 Ω | Entre GPIO23 (D23) e ânodo do LED |
| Cátodo do LED | GND |

Monte com a placa desconectada. Use 3V3 no divisor e GND comum. Confira o valor dos resistores disponíveis antes de energizar. Verifique o ânodo e o cátodo do LED; normalmente a perna longa indica o ânodo e o lado chato indica o cátodo.

Deixe o LED afastado do LDR para evitar que a própria luz altere a decisão de acionamento. Faça os testes de `docs/testes/hardware.md` e inclua uma foto real da montagem após a verificação.

Referência de GPIO — https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html
