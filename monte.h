#ifndef MONTE_H

#define MONTE_H
#include "carta.h"
#define MAX_CARTAS 10

typedef struct {
    Carta monte[MAX_CARTAS];
    int tam;
} Monte;

int enfileirar(Monte *m, Carta entrada);
int desenfileirar(Monte *m, Carta *saida);

#endif