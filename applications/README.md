# Serviços e comunicação MQTT

Responsável — Raul Vila Nova (@raulvnc).

Com Docker em execução, rode os comandos nesta pasta.

```sh
docker compose config --quiet
docker compose up -d
docker compose ps
```

O painel abre em http://localhost:1880/painel/ e o editor de diagnóstico em http://localhost:1880/admin/. O Node-RED carrega `node-red/flows.json` automaticamente. O fluxo fica no repositório e é montado em modo de leitura. Depois de editar o arquivo, aplique a alteração com `docker compose restart node-red`.

O Node-RED usa `mqtt:1883` na rede do Docker. No firmware, configure o IPv4 do computador na rede local. O broker aceita conexões anônimas na bancada. A API e o editor do Node-RED ficam vinculados ao endereço local do computador.

## Diagnóstico

Com o ESP32 conectado, acompanhe telemetria e status:

```sh
docker compose exec mqtt mosquitto_sub -h localhost -t 'grupo3/iluminacao/#' -v
```

O editor oferece três botões Inject para verificar comandos MQTT. O contrato dos tópicos está em [PROTOCOLO_MQTT.md](../docs/PROTOCOLO_MQTT.md).

```sh
docker compose logs --tail=80
docker compose down
```

## Demonstração sem o ESP32

Este roteiro usa um cliente MQTT de teste com leituras simuladas. Ele recebe os mesmos comandos que o firmware e devolve uma confirmação com o identificador correspondente. O broker da demonstração roda separado do broker da bancada.

A partir de `applications/`, inicie os serviços de demonstração e deixe o cliente rodando.

```sh
GRUPO3_HTTP_PORT=18880 GRUPO3_MQTT_PORT=18830 GRUPO3_MQTT_BIND=127.0.0.1 \
  docker compose -p grupo3-demonstracao up -d
docker compose -p grupo3-demonstracao exec -T node-red node < testes/cliente-mqtt.cjs
```

Abra [o painel de demonstração](http://127.0.0.1:18880/painel/). No modo automático, observe a luz ligar com leitura de 1200, manter o estado em 1600 e desligar em 2200. Clique em **Forçar ligada**, **Forçar desligada** e **Automático**. Aguarde a confirmação após cada clique. Encerre o cliente com Ctrl+C para verificar o estado offline. Ao terminar, rode `docker compose -p grupo3-demonstracao down -v` para remover os recursos da demonstração.

### Alternativa quando o Colima não encaminha a porta

Com Node.js, npm e Mosquitto instalados, execute na pasta `applications/`:

```sh
bash testes/demo-local.sh
```

Abra [o painel local de demonstração](http://127.0.0.1:33880/painel/) e repita os passos acima. O script usa o mesmo painel e o mesmo fluxo, com Node-RED e Mosquitto executados no computador. Ele usa portas próprias e encerra os serviços de teste com Ctrl+C.
