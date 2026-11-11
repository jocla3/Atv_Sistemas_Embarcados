# Serviços e diagnóstico MQTT

Responsável — Raul Vila Nova (@raulvnc).

## Inicialização

Com Docker em execução, entre nesta pasta e rode:

```sh
docker compose config --quiet
docker compose up -d
docker compose ps
```

Abra http://localhost:1880. No menu do Node-RED, escolha Import, selecione o conteúdo de `node-red/flows.json`, confirme e clique em Deploy. O fluxo assina a telemetria e o status, mostra os dados no painel Debug e oferece três botões Inject para testar comandos.

O cliente do Node-RED usa o broker `mqtt:1883`. Um ESP32 na rede deve usar o IP local do computador. Os tópicos estão documentados em `../docs/PROTOCOLO_MQTT.md`.

## Teste do broker

Em um terminal, a partir desta pasta:

```sh
docker compose exec mqtt mosquitto_sub -h localhost -t grupo3/iluminacao/telemetria -C 1 -W 10
```

Em outro terminal, publique uma mensagem de teste:

```sh
docker compose exec mqtt mosquitto_pub -h localhost -t grupo3/iluminacao/telemetria -m '{"ldr":1200,"luz":true,"modo":"automatico"}'
```

O assinante deve imprimir o JSON. Com o fluxo implantado, a mensagem também deve aparecer no Debug do Node-RED. Esse teste usa uma publicação manual e não comprova comunicação com a placa.

## Operação

```sh
docker compose logs --tail=80
docker compose down
```

O volume `node_red_data` guarda os fluxos configurados no editor. O broker desta etapa usa memória e acesso anônimo para bancada em rede confiável. Antes de usar uma rede compartilhada, configurar autenticação e restringir acesso. Não publique credenciais no repositório.

A integração MQTT no firmware e a conexão do protótipo visual aos serviços ainda estão pendentes.
