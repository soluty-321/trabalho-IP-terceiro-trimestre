#include <stdio.h>
#include "carta.h"
#include "monte.h"

int enfileirar(Monte *m, Carta entrada) {
    if(m->tam >= MAX_CARTAS) {
        return 1;
    }
    m->monte[m->tam] = entrada;
    m->tam++;
    return 0;
}

int desenfileirar(Monte *m, Carta *saida) {
    if(m->tam <= 0) {
        return 1;
    }
    *saida = m->monte[0];
    for(int i = 0; i < m->tam - 1; i++) {
        m->monte[i] = m->monte[i + 1];
    }
    m->tam--;
    return 0;
    
}
