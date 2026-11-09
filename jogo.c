#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jogo.h"

Carta *embaralhar(Carta *filtradas, int quant) {
    Carta *embaralhado = malloc(quant * sizeof(Carta));
    int indices[quant];
    int sentinela;
    int valor;
    memset(indices, -1, sizeof(indices));
    for(int i = 0; i < quant; i++) {
        do {
            sentinela = 0;
            valor = rand() % quant; 
            for(int j = 0; j < quant; j++) {
                if(indices[j] == valor) sentinela = 1;
            }
        } while(sentinela == 1);
        indices[i] = valor;
    }
    for(int i = 0; i < quant; i++) {
        embaralhado[i] = filtradas[indices[i]];
    }
    return embaralhado;
}

void distribuir_cartas(Carta *cartas, Monte *jogador1, Monte *jogador2) {
    for (int i = 0; i < 5; i++) {
        enfileirar(jogador1, cartas[i]);
        enfileirar(jogador2, cartas[i + 5]);
    }

}
