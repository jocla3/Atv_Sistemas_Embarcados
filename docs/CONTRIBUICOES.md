# Contribuições do Grupo 3

Preparamos quatro entregas do mesmo estágio de protótipo inicial. Cada integrante terá dois commits, com arquivos exclusivos e responsabilidade por revisar, testar e explicar sua parte. O esforço foi distribuído por área; as quantidades de linhas e arquivos variam porque circuito, documentação e software têm naturezas diferentes.

| Integrante | Responsabilidade | Commits |
| --- | --- | --- |
| João (@jocla3) | Firmware e integração | 2 |
| Raul (@raulvnc) | MQTT e back-end | 2 |
| Caio (@Caiosenas2101) | Circuito e testes físicos | 2 |
| Rafael (@rafaelcf29) | Interface e documentação | 2 |

Os ZIPs individuais estão na pasta `entregas/` do repositório. Cada ZIP contém uma pasta `arquivos/` com a estrutura que deve ser copiada para a raiz do repositório, um manifesto e instruções específicas. O pacote completo serve para conferir a integração local. Para distribuir os commits, cada integrante deve copiar somente seu pacote individual.

## Como trabalhar juntos

1. Baixe e extraia seu pacote. Leia e revise os arquivos antes do commit.
2. João trabalha no repositório original. Os demais podem clicar em **Fork** na página do projeto e clonar o fork na própria conta. Isso permite contribuir mesmo sem acesso de escrita ao repositório original.
3. Crie a branch indicada no seu pacote e copie o conteúdo de `arquivos/` para a raiz do clone. Não substitua a pasta `.git`.
4. Confira `git status` e `git diff`. Execute os testes da sua área e registre somente os resultados que você realmente obteve.
5. Faça os dois commits indicados e envie sua branch para sua conta.
6. Abra um Pull Request para `jocla3/Atv_Sistemas_Embarcados`, branch `main`. Descreva o que fez, como testou e o que ficou pendente.
7. Após revisar os quatro PRs, João deve usar **Create a merge commit**. Assim, os dois commits de cada integrante permanecem no histórico. A base comum e os commits de merge são administrativos e não entram na divisão de duas entregas por pessoa.

Os quatro pacotes usam caminhos distintos e podem ser publicados na mesma rodada. A validação integrada deve acontecer depois que todos forem incorporados. Se alguém alterar contratos, pinagem ou limites, combine a mudança com os responsáveis pelas áreas afetadas.

## Critério de conclusão desta rodada

Cada pessoa terá publicado os arquivos da sua área, realizado os testes disponíveis e descrito as pendências. Esta rodada entrega firmware local, desenho do circuito, infraestrutura e diagnóstico MQTT, protótipo simulado e relatório. A integração real ESP32–MQTT–painel será a próxima rodada.

## Verificações realizadas na preparação

- Teste da lógica do firmware com chamadas Arduino simuladas passou, incluindo os limites 1500 e 1800 e a manutenção do estado.
- A sintaxe JavaScript passou. Os modos automático/manual e o limite de 20 registros passaram em um DOM simulado.
- `docker compose config --quiet` aceitou a configuração.
- O download das imagens Docker falhou por timeout de DNS em `auth.docker.io`. Os serviços e o fluxo Node-RED ainda precisam ser executados e testados.
- A compilação com o core ESP32, a gravação e os testes físicos ainda precisam de registro.
- O DOCX foi conferido estruturalmente; a paginação deve ser revisada no Word antes da entrega.
