# Testes da comunicação

Responsável — Raul (@raulvnc).

| Teste | Resultado esperado | Situação |
| --- | --- | --- |
| Validar Compose | Configuração aceita sem erros | Passou em 2026-11-11 (`docker compose config --quiet`) |
| Iniciar serviços | Mosquitto e Node-RED ativos | Passou em 2026-11-11 com `nodered/node-red:4.1`; a tag `4` não existe no Docker Hub |
| Publicação manual | JSON recebido pelo assinante | Passou em 2026-11-11 (mensagem de teste) |
| Importar fluxo | Telemetria aparece no Debug | Passou em 2026-11-11; telemetria e status apareceram no Debug |
| Enviar comando | Assinante recebe automatico/ligada/desligada | Passou em 2026-11-11; os três comandos foram recebidos |
| Integrar ESP32 | Telemetria vem da placa e comando altera saída | Pendente de implementação |
| Reconectar placa | Recupera conexão sem repetir comando antigo | Pendente de implementação |

Use os comandos do README de `applications/`. Para testar comandos, assine `grupo3/iluminacao/comando` e use um botão Inject no Node-RED. Registre data, responsável, mensagem, resultado e logs. Mensagens manuais devem ser identificadas como teste.

Execução de 2026-11-11 — Raul (@raulvnc). Testes em bancada com Docker Desktop e mensagens manuais identificadas com `"teste":true`. O fluxo foi implantado pela API do Node-RED e os botões Inject foram acionados. Nenhum teste envolveu a placa.
