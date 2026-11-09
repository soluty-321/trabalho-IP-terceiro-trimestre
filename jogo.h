#ifndef JOGO_H
#define JOGO_H

#include "carta.h"
#include "monte.h"

Carta *embaralhar(Carta *filtradas, int quant);
void distribuir_cartas(Carta *cartas, Monte *jogador1, Monte *jogador2);

#endif
