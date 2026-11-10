#pragma once
constexpr int OUTPUT = 1;
constexpr int LOW = 0;
constexpr int HIGH = 1;
struct SerialSimulado {
    void begin(int) {}
    void printf(const char*, ...) {}
};
inline SerialSimulado Serial;
inline int leituraSimulada = 0;
inline int saidaLed = LOW;
inline void pinMode(int, int) {}
inline void digitalWrite(int, int valor) { saidaLed = valor; }
inline void analogReadResolution(int) {}
inline int analogRead(int) { return leituraSimulada; }
inline void delay(int) {}
