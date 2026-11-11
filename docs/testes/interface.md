# Testes do protótipo visual

Responsável — Rafael (@rafaelcf29).

| Ação | Resultado esperado | Registro |
| --- | --- | --- |
| Abrir index.html | Aviso de simulação e valor inicial 2200 | Passou em 2026-11-11 (HTML conferido e carga inicial em DOM simulado via `jsc`; conferência visual no navegador pendente) |
| Automático e leitura 1000 | Luz simulada ligada | Passou em 2026-11-11 (DOM simulado em `jsc`) |
| Aumentar para 1600 | Mantém ligada | Passou em 2026-11-11 (DOM simulado em `jsc`) |
| Aumentar para 2000 | Desliga | Passou em 2026-11-11 (DOM simulado em `jsc`) |
| Forçar desligada com leitura 1000 | Mantém desligada | Passou em 2026-11-11 (DOM simulado em `jsc`) |
| Forçar ligada com leitura 3000 | Mantém ligada | Passou em 2026-11-11 (DOM simulado em `jsc`) |
| Voltar ao automático | Retoma a regra do sensor | Passou em 2026-11-11 (DOM simulado em `jsc`) |
| Alterar mais de 20 vezes | Mantém as últimas 20 linhas | Passou em 2026-11-11 (DOM simulado em `jsc`: 25 alterações mantiveram 20 linhas) |
| Recarregar | Reinicia a simulação e o histórico | Passou em 2026-11-11 (nova carga do script em `jsc` retornou a 2200 e 1 linha); confirmar F5 no navegador |

Execução de 2026-11-11 — Rafael (@rafaelcf29). Os 9 cenários funcionais de `applications/frontend/app.js` foram executados em JavaScriptCore (`jsc`) com DOM simulado, e os IDs/atributos de `applications/frontend/index.html` foram validados. A abertura direta no navegador (renderização visual, navegação por teclado e largura de tela pequena até 680 px) e a revisão de paginação do `.docx` no Word permanecem pendentes de conferência manual. Os testes desta interface usam dados simulados. A confirmação de estados reais e a integração MQTT serão verificadas após implementação.
