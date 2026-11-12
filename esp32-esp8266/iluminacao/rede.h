#pragma once
#include "controle.h"

struct Comando {
  Modo modo;
  char id[33];
};

void iniciarRede();
bool receberComando(Comando &comando);
void registrarLeitura(int leitura, bool luzLigada, Modo modo, const char *confirmacao);
