#pragma once

enum class Modo { Automatico, Ligada, Desligada };

constexpr int LIMIAR_LIGAR = 1500;
constexpr int LIMIAR_DESLIGAR = 1800;

inline bool calcularLuz(Modo modo, int leitura, bool luzLigada) {
  if (modo != Modo::Automatico) {
    return modo == Modo::Ligada;
  }
  if (leitura <= LIMIAR_LIGAR) {
    return true;
  }
  if (leitura >= LIMIAR_DESLIGAR) {
    return false;
  }
  return luzLigada;
}
