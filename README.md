# Monitoramento e Iluminação Automática Inteligente

Projeto do Grupo 3 da disciplina de Sistemas Embarcados da CESAR School. Nosso objetivo é usar um ESP32 para medir a luminosidade e acender a iluminação quando escurece. Estamos preparando o monitoramento e o controle manual por MQTT.

## Equipe

| Integrante | GitHub | Responsabilidade |
| --- | --- | --- |
| João Cláudio Cavalcanti Beltrão Filho | [jocla3](https://github.com/jocla3) | Firmware, integração e representação do grupo |
| Raul Vila Nova | [raulvnc](https://github.com/raulvnc) | Broker MQTT, back-end e comunicação |
| Caio Sena | [Caiosenas2101](https://github.com/Caiosenas2101) | Circuito, sensores e testes de hardware |
| Rafael Fernandes | [rafaelcf29](https://github.com/rafaelcf29) | Interface, documentação e apresentação |

## Estágio do projeto

Estamos no protótipo inicial para o check point de 17/11/2026. Temos um firmware de automação local, uma proposta de circuito, a configuração inicial de Mosquitto/Node-RED e um protótipo visual com dados simulados. O grupo informou a execução do firmware e está aprimorando os testes. A integração ESP32–MQTT–painel e os testes físicos documentados ainda estão pendentes.

A publicação está dividida em quatro pacotes na seção **Releases**, para que cada integrante revise e faça os próprios commits. As pastas abaixo estarão completas na branch principal após a integração dos quatro pacotes. O roteiro está em [docs/CONTRIBUICOES.md](docs/CONTRIBUICOES.md).

## Organização

```text
esp32-esp8266/   Firmware e instruções de gravação
schematics/     Ligações e desenho do circuito
docs/           Arquitetura, relatório e roteiros de testes
applications/   Docker, broker MQTT e protótipo da interface
```

## Montagem e firmware

Utilizamos um ESP32 DevKit, LDR, LED, resistor de 10 kΩ para o divisor do sensor, resistor de 220 Ω ou 330 Ω para o LED, protoboard e jumpers. Os valores dos resistores devem ser conferidos na montagem.

O LDR é ligado entre 3V3 e a junção de leitura; a junção vai ao GPIO34 e ao resistor de 10 kΩ, que segue até GND. O GPIO23 aciona o LED através do resistor limitador. Alimente a placa por USB.

Após integrar o pacote de João, abra `esp32-esp8266/iluminacao/iluminacao.ino` no Arduino IDE com o pacote de placas ESP32 da Espressif, selecione **ESP32 Dev Module**, escolha a porta e grave. Use o monitor serial a **115200 baud**. Consulte as instruções da pasta do firmware para calibrar os limites.

## Serviços locais

Com Docker e Docker Compose disponíveis e após integrar o pacote de Raul, execute a partir da raiz:

```sh
cd applications
docker compose config --quiet
docker compose up -d
docker compose ps
```

O editor do Node-RED estará em http://localhost:1880. Importe o arquivo `applications/node-red/flows.json` e clique em Deploy. Ele contém um fluxo inicial de diagnóstico MQTT, com recepção de telemetria e envio manual de comandos. O broker fica na porta 1883. Dentro do Node-RED, o endereço é `mqtt`; no futuro firmware MQTT, use o IP do computador na rede local.

O broker de bancada permite conexões sem senha. Utilize uma rede local confiável e configure autenticação antes de expor o serviço em redes compartilhadas. Para parar os serviços, use `docker compose down`.

## Protótipo visual

Após integrar o pacote de Rafael, abra `applications/frontend/index.html` no navegador. A interface identifica os dados como simulados e permite demonstrar os modos automático e manual. Os botões ainda não enviam comandos ao ESP32.

## Comunicação planejada

| Tópico | Origem | Destino |
| --- | --- | --- |
| `grupo3/iluminacao/telemetria` | ESP32 | Node-RED |
| `grupo3/iluminacao/comando` | Node-RED | ESP32 |
| `grupo3/iluminacao/status` | ESP32 e broker | Node-RED |

O controle automático deve continuar localmente mesmo sem rede. Na integração futura, o modo manual deve permanecer até a seleção de Automático e o painel deve mostrar o estado confirmado pelo dispositivo.

## Verificação e próximos passos

Cada área inclui um roteiro de testes. Registre data, responsável, ambiente, resultado e evidência ao executar cada teste. Os exemplos e as simulações não substituem a validação na placa.

Precisamos calibrar o LDR, fotografar o circuito, implementar MQTT no firmware, integrar o painel e registrar os testes de reconexão e controle manual. O histórico nesta versão do protótipo é mantido somente na memória do navegador.
