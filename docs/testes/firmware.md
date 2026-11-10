# Testes do firmware

Responsável — João (@jocla3).

## Verificação da lógica em computador

Execute da raiz, com um compilador C++17 instalado:

```sh
c++ -std=c++17 -I esp32-esp8266/testes esp32-esp8266/testes/teste_logica.cpp -o /tmp/teste-iluminacao
/tmp/teste-iluminacao
```

O teste usa o firmware real com chamadas Arduino simuladas para conferir os limites e a manutenção do estado entre eles. Não valida eletrônica, compilação para ESP32 ou conectividade.

## Testes na placa

| Teste | Resultado esperado | Registro |
| --- | --- | --- |
| Inicialização | LED começa desligado e o serial inicia | A executar e registrar |
| Cobrir LDR | Leitura cai e LED liga ao atingir o limite | A executar e registrar |
| Iluminar LDR | Leitura sobe e LED desliga no limite superior | A executar e registrar |
| Luz próxima ao limite | LED mantém estado dentro da faixa intermediária | A executar e registrar |
| Reiniciar a placa | Automação volta a responder ao ambiente | A executar e registrar |

Para cada execução, anote data, responsável, versão do firmware, leituras observadas e resultado. O grupo informou que executou o código inicial; as evidências detalhadas ainda precisam ser reunidas.
