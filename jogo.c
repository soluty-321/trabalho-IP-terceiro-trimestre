#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"
#include "utils.h"

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

int escolher_atributo(Monte *m, char *tema) {
    Carta carta = m->monte[0];
    int escolha;

    printf("\nSua carta: %s (%s, %s)\n", carta.nome, carta.grupo, carta.categoria);

    if (strcmp(tema, "Astronomia") == 0) {
        printf("1) Diametro: %d km\n", carta.atri1);
        printf("2) Distancia do Sol: %d milhoes de km\n", carta.atri2);
        printf("3) Numero de luas: %d\n", carta.atri3);
        printf("4) Duracao do dia: %d horas\n", carta.atri4);
    } else if (strcmp(tema, "Quimica") == 0) {
        printf("1) Numero atomico: %d\n", carta.atri1);
        printf("2) Massa atomica: %d u\n", carta.atri2);
        printf("3) Ponto de fusao: %d graus C\n", carta.atri3);
        printf("4) Ponto de ebulicao: %d graus C\n", carta.atri4);
    } else if (strcmp(tema, "Geografia") == 0) {
        printf("1) Area: %d mil km2\n", carta.atri1);
        printf("2) Populacao: %d milhoes de habitantes\n", carta.atri2);
        printf("3) Densidade demografica: %d hab/km2\n", carta.atri3);
        printf("4) Numero de municipios: %d\n", carta.atri4);
    } else if (strcmp(tema, "Historia") == 0) {
        printf("1) Altura: %d m\n", carta.atri1);
        printf("2) Idade: %d anos\n", carta.atri2);
        printf("3) Tempo de construcao: %d anos\n", carta.atri3);
        printf("4) Visitantes por ano: %d milhoes\n", carta.atri4);
    } else {
        printf("1) Atributo 1: %d\n", carta.atri1);
        printf("2) Atributo 2: %d\n", carta.atri2);
        printf("3) Atributo 3: %d\n", carta.atri3);
        printf("4) Atributo 4: %d\n", carta.atri4);
    }

    printf("\nEscolha o atributo: ");
    escolha = validar_entrada_numerica(4, 1);
    limpar_tela();

    return escolha;
}

static int valor_atributo(Carta *c, int atributo) {
    if (atributo == 1) {
        return c->atri1;
    } else if (atributo == 2) {
        return c->atri2;
    } else if (atributo == 3) {
        return c->atri3;
    } else if (atributo == 4) {
        return c->atri4;
    }

    return 0;
}

int comparar_cartas(Carta *c1, Carta *c2, int atributo) {
    int valor1;
    int valor2;

    if (c1->especial == 1 && c2->especial == 1) {
        return 0;
    }

    if (c1->especial == 1) {
        return 1;
    }

    if (c2->especial == 1) {
        return 2;
    }

    valor1 = valor_atributo(c1, atributo);
    valor2 = valor_atributo(c2, atributo);

    if (valor1 > valor2) {
        return 1;
    }

    if (valor2 > valor1) {
        return 2;
    }

    return 0;
}
