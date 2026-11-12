# Testes do firmware

Responsável — João (@jocla3).

## Verificação da lógica em computador

Execute da raiz, com um compilador C++17 instalado:

```sh
c++ -std=c++17 -I esp32-esp8266/testes esp32-esp8266/testes/teste_logica.cpp -o /tmp/teste-iluminacao
/tmp/teste-iluminacao
```

O teste usa o firmware real com chamadas Arduino simuladas para conferir os limites, a manutenção do estado entre eles, os modos manuais e o retorno ao automático. Não valida eletrônica, compilação para ESP32 ou conectividade.

Em 12/11/2026, o sketch compilou para ESP32 Dev Module com o core Espressif 3.3.12, incluindo Wi-Fi e MQTT. O build com configuração de rede ocupou 915.400 bytes (69% da partição de aplicação).

## Testes na placa

| Teste | Resultado esperado | Registro |
| --- | --- | --- |
| Inicialização | LED começa desligado e o serial inicia | A executar e registrar |
| Cobrir LDR | Leitura cai e LED liga ao atingir o limite | A executar e registrar |
| Iluminar LDR | Leitura sobe e LED desliga no limite superior | A executar e registrar |
| Luz próxima ao limite | LED mantém estado dentro da faixa intermediária | A executar e registrar |
| Forçar ligada com o LDR iluminado | LED fica ligado | A executar e registrar |
| Forçar desligada com o LDR coberto | LED fica desligado | A executar e registrar |
| Voltar ao automático | LED volta a responder ao sensor | A executar e registrar |
| Reiniciar a placa em modo manual | Placa retorna ao automático | A executar e registrar |
| Interromper o Wi-Fi | Controle local continua no modo atual | A executar e registrar |

Para cada execução, anote data, responsável, versão do firmware, leituras observadas e resultado. O grupo informou que executou o código inicial; as evidências detalhadas ainda precisam ser reunidas.
