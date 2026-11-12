#!/usr/bin/env bash
set -eu

for comando in node npm mosquitto curl; do
    if ! command -v "$comando" >/dev/null; then
        printf 'Instale %s para executar a demonstração local.\n' "$comando" >&2
        exit 1
    fi
done

apps_dir=$(cd "$(dirname "$0")/.." && pwd)
demo_dir=$(mktemp -d "${TMPDIR:-/tmp}/grupo3-demo.XXXXXX")
mqtt_pid=
node_red_pid=

limpar() {
    if [ -n "$node_red_pid" ]; then kill "$node_red_pid" 2>/dev/null || true; fi
    if [ -n "$mqtt_pid" ]; then kill "$mqtt_pid" 2>/dev/null || true; fi
    wait 2>/dev/null || true
    rm -rf "$demo_dir"
}
trap limpar EXIT
trap 'exit 130' INT
trap 'exit 143' TERM

npm install --prefix "$demo_dir" --no-audit --no-fund node-red@4.1.12
node - "$apps_dir" "$demo_dir" <<'JS'
const fs = require('node:fs');
const path = require('node:path');
const [apps, demo] = process.argv.slice(2);
const settings = require(path.join(apps, 'node-red/settings.js'));
const flows = require(path.join(apps, 'node-red/flows.json'));
const broker = flows.find(node => node.type === 'mqtt-broker');

broker.broker = '127.0.0.1';
broker.port = '33883';
settings.uiHost = '127.0.0.1';
settings.uiPort = 33880;
settings.httpStatic = path.join(apps, 'frontend');

fs.writeFileSync(path.join(demo, 'settings.js'), 'module.exports = ' + JSON.stringify(settings));
fs.writeFileSync(path.join(demo, 'flows.json'), JSON.stringify(flows));
JS
sed 's/^listener 1883$/listener 33883 127.0.0.1/' "$apps_dir/mosquitto/mosquitto.conf" > "$demo_dir/mosquitto.conf"
mosquitto -c "$demo_dir/mosquitto.conf" > "$demo_dir/mosquitto.log" 2>&1 &
mqtt_pid=$!
"$demo_dir/node_modules/.bin/node-red" --userDir "$demo_dir/data" --settings "$demo_dir/settings.js" "$demo_dir/flows.json" > "$demo_dir/node-red.log" 2>&1 &
node_red_pid=$!

pronto=false
for tentativa in {1..20}; do
    if ! kill -0 "$mqtt_pid" "$node_red_pid" 2>/dev/null; then break; fi
    if curl --max-time 1 -fsS http://127.0.0.1:33880/api/estado >/dev/null 2>&1; then
        pronto=true
        break
    fi
    sleep 1
done

if [ "$pronto" != true ]; then
    cat "$demo_dir/mosquitto.log" "$demo_dir/node-red.log" >&2
    exit 1
fi

printf '\nPainel de demonstração: http://127.0.0.1:33880/painel/\n'
NODE_PATH="$demo_dir/node_modules" GRUPO3_DEMO_BROKER=mqtt://127.0.0.1:33883 node "$apps_dir/testes/cliente-mqtt.cjs"
