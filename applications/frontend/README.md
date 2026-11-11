# Protótipo do painel

Responsável — Rafael Fernandes (@rafaelcf29).

Abra `index.html` diretamente no navegador. Os arquivos são locais e não exigem instalação de bibliotecas.

A interface simula a leitura do LDR com um controle deslizante, mostra o estado da luz e permite selecionar Automático, Forçar ligada e Forçar desligada. A simulação usa os mesmos limites iniciais do firmware. O histórico guarda até 20 alterações na memória e é apagado ao recarregar a página.

Todos os dados são demonstrativos. MQTT e comunicação com a placa serão integrados posteriormente. Os testes estão em `docs/testes/interface.md`, na raiz do repositório.
