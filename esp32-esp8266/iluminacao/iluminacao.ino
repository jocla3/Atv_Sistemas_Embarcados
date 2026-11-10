#include <Arduino.h>

constexpr int PINO_LDR = 34;
constexpr int PINO_LED = 23;
constexpr int LIMIAR_LIGAR = 1500;
constexpr int LIMIAR_DESLIGAR = 1800;

bool luzLigada = false;

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
  digitalWrite(PINO_LED, LOW);
  analogReadResolution(12);
}

void loop() {
  const int leitura = analogRead(PINO_LDR);

  if (leitura <= LIMIAR_LIGAR) {
    luzLigada = true;
  } else if (leitura >= LIMIAR_DESLIGAR) {
    luzLigada = false;
  }

  digitalWrite(PINO_LED, luzLigada ? HIGH : LOW);
  Serial.printf("LDR: %d | LED: %s\n", leitura, luzLigada ? "ligado" : "desligado");
  delay(250);
}
