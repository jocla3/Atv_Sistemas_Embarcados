'use strict';

const mqtt = require('mqtt');

const topicos = 'grupo3/iluminacao/';
const modos = ['automatico', 'ligada', 'desligada'];
const leituras = [2200, 1200, 1600, 2200];
const broker = process.env.GRUPO3_DEMO_BROKER || 'mqtt://mqtt:1883';

let modo = 'automatico';
let luz = false;
let indice = 0;
let intervalo;
let encerrando = false;

const cliente = mqtt.connect(broker, {
    connectTimeout: 5000,
    reconnectPeriod: 0,
    will: { topic: topicos + 'status', payload: 'offline', qos: 1, retain: true }
});

function publicarLeitura(confirmacao) {
    const ldr = leituras[indice];
    if (modo === 'automatico') {
        if (ldr <= 1500) luz = true;
        else if (ldr >= 1800) luz = false;
    } else {
        luz = modo === 'ligada';
    }

    const leitura = { ldr, luz, modo, simulado: true };
    if (confirmacao) leitura.confirmacao = confirmacao;
    cliente.publish(topicos + 'telemetria', JSON.stringify(leitura));
    console.log(leitura);
}

async function encerrar(erro) {
    if (encerrando) return;
    encerrando = true;
    clearInterval(intervalo);
    if (erro) {
        console.error(erro.message);
        process.exitCode = 1;
    }
    try {
        if (cliente.connected) {
            await cliente.publishAsync(topicos + 'status', 'offline', { qos: 1, retain: true });
        }
    } catch (falha) {
        console.error(falha.message);
        process.exitCode = 1;
    } finally {
        await cliente.endAsync();
    }
}

cliente.on('connect', async () => {
    try {
        await cliente.subscribeAsync(topicos + 'comando');
        await cliente.publishAsync(topicos + 'status', 'online', { qos: 1, retain: true });
        publicarLeitura();
        intervalo = setInterval(() => {
            indice = (indice + 1) % leituras.length;
            publicarLeitura();
        }, 2500);
    } catch (erro) {
        void encerrar(erro);
    }
});

cliente.on('message', (topico, payload) => {
    if (encerrando || topico !== topicos + 'comando') return;

    const texto = payload.toString();
    let comando = { modo: texto };
    if (texto.startsWith('{')) {
        try {
            comando = JSON.parse(texto);
        } catch {
            return;
        }
    }
    if (!comando || !modos.includes(comando.modo)) return;
    modo = comando.modo;
    publicarLeitura(comando.id);
});

cliente.on('error', erro => void encerrar(erro));
cliente.on('close', () => void encerrar(new Error('A conexão com o broker foi encerrada.')));
process.once('SIGINT', () => void encerrar());
process.once('SIGTERM', () => void encerrar());

console.log('Demonstração com leituras simuladas. Use um broker separado da bancada.');
