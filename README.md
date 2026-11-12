# Monitoramento e Iluminação Automática Inteligente

Projeto do Grupo 3 de Sistemas Embarcados da CESAR School. O ESP32 lê a luminosidade pelo LDR, controla um LED e envia o estado para um painel web via MQTT. O painel permite manter o controle automático ou forçar a luz ligada ou desligada.

| Integrante | GitHub | Responsabilidade |
| --- | --- | --- |
| João Cláudio Cavalcanti Beltrão Filho | [jocla3](https://github.com/jocla3) | Firmware, integração e representação |
| Raul Vila Nova | [raulvnc](https://github.com/raulvnc) | Broker MQTT, back-end e comunicação |
| Caio Sena | [Caiosenas2101](https://github.com/Caiosenas2101) | Circuito, sensores e testes de hardware |
| Rafael Fernandes | [rafaelcf29](https://github.com/rafaelcf29) | Interface, documentação e apresentação |

## Executar

1. Monte o circuito do [esquemático](schematics/README.md). A junção do LDR com o resistor de 10 kΩ vai ao GPIO34. O GPIO23 aciona o LED por um resistor de 220 Ω ou 330 Ω.
2. Na pasta `applications/`, rode `docker compose up -d`. O Node-RED carrega o fluxo automaticamente.
3. Configure o Wi-Fi e o endereço do broker no [firmware](esp32-esp8266/README.md). Grave o sketch no ESP32 e conecte a placa à mesma rede do computador.
4. Abra [o painel](http://localhost:1880/painel/) no computador que executa o Docker. Quando o ESP32 ficar online, cubra e ilumine o LDR. Em seguida, teste os três modos pelo painel.

O broker usa a porta 1883 e aceita conexões anônimas para a bancada. Use uma rede local confiável. O painel e o editor do Node-RED ficam disponíveis no computador que executa o Docker.

## Demonstração sem a placa

O [roteiro de demonstração](applications/README.md#demonstração-sem-o-esp32) mostra como repetir o fluxo com um cliente MQTT de teste, inclusive se o Colima apresentar problemas de acesso ao painel.

## Documentação

- [Arquitetura](docs/ARQUITETURA.md) e [contrato MQTT](docs/PROTOCOLO_MQTT.md)
- [Serviços](applications/README.md), [firmware](esp32-esp8266/README.md) e [painel](applications/frontend/README.md)
- Roteiros de testes de [hardware](docs/testes/hardware.md), [firmware](docs/testes/firmware.md), [MQTT](docs/testes/mqtt.md) e [interface](docs/testes/interface.md)
- [Contribuições do checkpoint](docs/CONTRIBUICOES.md) e [relatório](docs/Relatorio_CheckPoint_Grupo_3.docx)
