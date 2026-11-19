#ifndef JOGO_H
#define JOGO_H

#include "carta.h"
#include "monte.h"
#include "ranking.h"

Carta *embaralhar(Carta *filtradas, int quant);
void distribuir_cartas(Carta *cartas, Monte *jogador1, Monte *jogador2);
int escolher_atributo(Monte *m, char *tema);
int comparar_cartas(Carta *c1, Carta *c2, int atributo);
int simular_rodada(Monte *m1, Monte *m2, int jogador_escolhe);
int jogar_partida_completa(Monte *jogador1, Monte *jogador2, char *nome1, char *nome2);
void jogar(Ranking **ranking, int *qtd_jogadores);

#endif
