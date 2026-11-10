#include <cassert>
#include <iostream>
#include "../iluminacao/iluminacao.ino"

void verificarLeitura(int leitura, int esperado) {
    leituraSimulada = leitura;
    loop();
    assert(saidaLed == esperado);
}

int main() {
    setup();
    assert(saidaLed == LOW);
    verificarLeitura(4095, LOW);
    verificarLeitura(1501, LOW);
    verificarLeitura(1500, HIGH);
    verificarLeitura(1600, HIGH);
    verificarLeitura(1799, HIGH);
    verificarLeitura(1800, LOW);
    verificarLeitura(1600, LOW);
    verificarLeitura(0, HIGH);
    verificarLeitura(4095, LOW);
    std::cout << "Limites e manutenção do estado verificados.\n";
}
