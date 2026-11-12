'use strict';

const nomes = { automatico: 'Automático', ligada: 'Forçar ligada', desligada: 'Forçar desligada' };
const conexoes = { online: 'Online', offline: 'Offline', desatualizada: 'Dados desatualizados' };
const leitura = document.getElementById('reading');
const luz = document.getElementById('light');
const origemLuz = document.getElementById('light-source');
const modo = document.getElementById('mode');
const conexao = document.getElementById('connection');
const aviso = document.getElementById('command-status');
const historico = document.getElementById('history');
const botoes = [...document.querySelectorAll('[data-mode]')];

let placaDisponivel = false;
let enviando = false;
let pendente = null;

function atualizarBotoes() {
    for (const botao of botoes) {
        botao.disabled = !placaDisponivel || enviando || pendente !== null;
    }
}

function textoLuz(ligada) {
    return ligada ? 'Ligada' : 'Desligada';
}

function mostrarHistorico(registros) {
    const linhas = registros.map(registro => {
        const linha = document.createElement('tr');
        const hora = new Date(registro.recebidoEm).toLocaleTimeString('pt-BR');
        for (const valor of [hora, registro.ldr, textoLuz(registro.luz), nomes[registro.modo]]) {
            const celula = document.createElement('td');
            celula.textContent = valor;
            linha.appendChild(celula);
        }
        return linha;
    });
    historico.replaceChildren(...linhas);
}

function mostrarEstado(dados) {
    placaDisponivel = dados.conexao === 'online';
    const estado = placaDisponivel ? dados.estado : null;
    conexao.textContent = estado?.simulado ? 'Online · teste MQTT' : conexoes[dados.conexao];
    origemLuz.textContent = estado?.simulado ? 'Estado informado pelo cliente de teste' : 'Estado informado pelo ESP32';
    leitura.textContent = estado?.ldr ?? '—';
    luz.textContent = estado ? textoLuz(estado.luz) : '—';
    modo.textContent = estado ? nomes[estado.modo] : '—';
    for (const botao of botoes) {
        botao.setAttribute('aria-pressed', String(botao.dataset.mode === estado?.modo));
    }
    mostrarHistorico(dados.historico);

    const confirmacao = pendente && dados.confirmacoes.find(item => item.id === pendente.id && item.modo === pendente.modo);
    if (confirmacao) {
        aviso.textContent = confirmacao.simulado ?
            'Comando confirmado pelo cliente MQTT de teste.' : 'Comando confirmado pelo ESP32.';
        pendente = null;
    }
}

async function atualizar() {
    try {
        const resposta = await fetch('/api/estado', { cache: 'no-store', signal: AbortSignal.timeout(3000) });
        if (!resposta.ok) throw new Error('Painel indisponível');
        mostrarEstado(await resposta.json());
    } catch {
        placaDisponivel = false;
        conexao.textContent = 'Sem conexão com o servidor';
        leitura.textContent = luz.textContent = modo.textContent = '—';
        for (const botao of botoes) {
            botao.setAttribute('aria-pressed', 'false');
        }
    }

    if (pendente && Date.now() >= pendente.expiraEm) {
        aviso.textContent = 'O ESP32 não confirmou o comando. Confira a conexão e tente novamente.';
        pendente = null;
    }
    atualizarBotoes();
    setTimeout(atualizar, 750);
}

async function enviar(novoModo) {
    if (!placaDisponivel || enviando || pendente) return;

    enviando = true;
    atualizarBotoes();
    aviso.textContent = 'Enviando comando…';

    try {
        const resposta = await fetch('/api/comando', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ modo: novoModo }),
            signal: AbortSignal.timeout(3000)
        });
        const dados = await resposta.json();
        if (!resposta.ok) throw new Error(dados.erro);
        pendente = { id: dados.id, modo: novoModo, expiraEm: Date.now() + 6000 };
        aviso.textContent = 'Aguardando confirmação do ESP32…';
    } catch (erro) {
        aviso.textContent = erro.message.startsWith('ESP32') ? erro.message : 'Falha ao enviar o comando. Tente novamente.';
    } finally {
        enviando = false;
        atualizarBotoes();
    }
}

for (const botao of botoes) {
    botao.addEventListener('click', () => enviar(botao.dataset.mode));
}
atualizar();
