#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"

static Ranking *criar_ranking_zerado(char *nome_arquivo, int *qtd_jogadores) {
    FILE *arq;
    Ranking *ranking;
    int escritos;

    ranking = malloc(sizeof(Ranking));
    if (ranking == NULL) {
        *qtd_jogadores = 0;
        return NULL;
    }

    memset(ranking, 0, sizeof(Ranking));

    arq = fopen(nome_arquivo, "wb");
    if (arq == NULL) {
        free(ranking);
        *qtd_jogadores = 0;
        return NULL;
    }

    escritos = fwrite(ranking, sizeof(Ranking), 1, arq);
    fclose(arq);

    if (escritos != 1) {
        free(ranking);
        *qtd_jogadores = 0;
        return NULL;
    }

    *qtd_jogadores = 1;
    return ranking;
}

Ranking *carregar_ranking(char *nome_arquivo, int *qtd_jogadores) {
    FILE *arq;
    Ranking *ranking;
    long tamanho;
    int total;

    if (qtd_jogadores == NULL) {
        return NULL;
    }

    arq = fopen(nome_arquivo, "rb");
    if (arq == NULL) {
        return criar_ranking_zerado(nome_arquivo, qtd_jogadores);
    }

    fseek(arq, 0, SEEK_END);
    tamanho = ftell(arq);
    rewind(arq);

    total = tamanho / sizeof(Ranking);
    if (total <= 0) {
        fclose(arq);
        return criar_ranking_zerado(nome_arquivo, qtd_jogadores);
    }

    ranking = malloc(total * sizeof(Ranking));
    if (ranking == NULL) {
        fclose(arq);
        *qtd_jogadores = 0;
        return NULL;
    }

    total = fread(ranking, sizeof(Ranking), total, arq);
    fclose(arq);

    if (total <= 0) {
        free(ranking);
        *qtd_jogadores = 0;
        return NULL;
    }

    *qtd_jogadores = total;
    return ranking;
}

Ranking *atualizar_ranking(Ranking *ranking, char *nome, int resultado, int *qtd_jogadores) {
    Ranking *novo;
    int indice = -1;
    int vazio = -1;

    if (nome == NULL || qtd_jogadores == NULL) {
        return NULL;
    }

    if (nome[0] == '\0' || resultado < VITORIA || resultado > EMPATE) {
        return NULL;
    }

    if (ranking == NULL && *qtd_jogadores > 0) {
        return NULL;
    }

    for (int i = 0; i < *qtd_jogadores; i++) {
        if (ranking[i].nome[0] == '\0') {
            if (vazio == -1) {
                vazio = i;
            }
        } else if (strcmp(ranking[i].nome, nome) == 0) {
            indice = i;
        }
    }

    if (indice == -1) {
        if (vazio != -1) {
            indice = vazio;
        } else {
            novo = realloc(ranking, (*qtd_jogadores + 1) * sizeof(Ranking));
            if (novo == NULL) {
                return NULL;
            }

            ranking = novo;
            indice = *qtd_jogadores;
            (*qtd_jogadores)++;
        }

        memset(&ranking[indice], 0, sizeof(Ranking));
        strncpy(ranking[indice].nome, nome, TAM_NOME - 1);
        ranking[indice].nome[TAM_NOME - 1] = '\0';
    }

    if (resultado == VITORIA) {
        ranking[indice].vitorias++;
    } else if (resultado == DERROTA) {
        ranking[indice].derrotas++;
    } else {
        ranking[indice].empates++;
    }

    return ranking;
}

int salvar_ranking(char *nome_arquivo, Ranking *ranking, int qtd_jogadores) {
    FILE *arq;
    int escritos;

    if (ranking == NULL || qtd_jogadores <= 0) {
        return 1;
    }

    arq = fopen(nome_arquivo, "wb");
    if (arq == NULL) {
        return 1;
    }

    escritos = fwrite(ranking, sizeof(Ranking), qtd_jogadores, arq);
    fclose(arq);

    if (escritos != qtd_jogadores) {
        return 1;
    }

    return 0;
}
