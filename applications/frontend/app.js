'use strict';
let modo = 'automatico';
let luzLigada = false;
const nomes = { automatico: 'Automático', ligada: 'Forçar ligada', desligada: 'Forçar desligada' };
const sensor = document.getElementById('sensor');
const historico = document.getElementById('history');

function atualizar() {
    const leitura = Number(sensor.value);
    if (modo === 'automatico') {
        if (leitura <= 1500) luzLigada = true;
        else if (leitura >= 1800) luzLigada = false;
    } else {
        luzLigada = modo === 'ligada';
    }
    const estado = luzLigada ? 'Ligada' : 'Desligada';
    document.getElementById('reading').textContent = leitura;
    document.getElementById('light').textContent = estado;
    document.getElementById('mode').textContent = nomes[modo];
    document.querySelectorAll('[data-mode]').forEach(botao => {
        botao.setAttribute('aria-pressed', String(botao.dataset.mode === modo));
    });
    const linha = document.createElement('tr');
    [new Date().toLocaleTimeString('pt-BR'), leitura, estado, nomes[modo]].forEach(valor => {
        const celula = document.createElement('td');
        celula.textContent = valor;
        linha.appendChild(celula);
    });
    historico.prepend(linha);
    if (historico.children.length > 20) historico.lastElementChild.remove();
}

sensor.addEventListener('input', atualizar);
document.querySelectorAll('[data-mode]').forEach(botao => {
    botao.addEventListener('click', () => {
        modo = botao.dataset.mode;
        atualizar();
    });
});
atualizar();
