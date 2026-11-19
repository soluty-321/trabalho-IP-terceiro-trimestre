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

static int slot_vazio(Ranking *registro) {
    return registro->nome[0] == '\0'
        && registro->vitorias == 0
        && registro->derrotas == 0
        && registro->empates == 0;
}

Ranking *atualizar_ranking(Ranking *ranking, char *nome, int resultado, int *qtd_jogadores) {
    Ranking *novo;
    int indice = -1;
    int vazio = -1;

    if (nome == NULL || qtd_jogadores == NULL) {
        return NULL;
    }

    if (ranking == NULL && *qtd_jogadores > 0) {
        return NULL;
    }

    for (int i = 0; i < *qtd_jogadores; i++) {
        if (strcmp(ranking[i].nome, nome) == 0) {
            indice = i;
            break;
        }
        if (vazio == -1 && slot_vazio(&ranking[i])) {
            vazio = i;
        }
    }

    if (indice == -1 && vazio != -1) {
        indice = vazio;
        strncpy(ranking[indice].nome, nome, TAM_NOME - 1);
        ranking[indice].nome[TAM_NOME - 1] = '\0';
    }

    if (indice == -1) {
        novo = realloc(ranking, (*qtd_jogadores + 1) * sizeof(Ranking));
        if (novo == NULL) {
            return NULL;
        }
        ranking = novo;
        indice = *qtd_jogadores;
        (*qtd_jogadores)++;

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

void ordenar_ranking(Ranking *ranking, int qtd_jogadores) {
    int trocou;
    Ranking aux;

    if (ranking == NULL || qtd_jogadores <= 1) {
        return;
    }

    for (int i = 0; i < qtd_jogadores - 1; i++) {
        trocou = 0;
        for (int j = 0; j < qtd_jogadores - i - 1; j++) {
            if (ranking[j].vitorias < ranking[j + 1].vitorias) {
                aux = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = aux;
                trocou = 1;
            }
        }
        if (trocou == 0) {
            break;
        }
    }
}

void exibir_ranking(Ranking *ranking, int qtd_jogadores) {
    int exibidos = 0;
    int posicao = 1;

    if (ranking == NULL || qtd_jogadores <= 0) {
        printf("Nenhum jogador cadastrado ainda.\n");
        return;
    }

    printf("\n==================== RANKING ====================\n");
    printf("%-3s %-20s %-9s %-9s %-8s %-6s\n", "#", "Nome", "Vitorias", "Derrotas", "Empates", "Total");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < qtd_jogadores; i++) {
        if (ranking[i].nome[0] == '\0' && ranking[i].vitorias == 0 && ranking[i].derrotas == 0 && ranking[i].empates == 0) {
            continue;
        }

        printf("%-3d %-20.20s %-9d %-9d %-8d %-6d\n",
               posicao++,
               ranking[i].nome,
               ranking[i].vitorias,
               ranking[i].derrotas,
               ranking[i].empates,
               ranking[i].vitorias + ranking[i].derrotas + ranking[i].empates);
        exibidos++;
    }

    if (exibidos == 0) {
        printf("Nenhum jogador cadastrado ainda.\n");
    }

    printf("=================================================\n");
}

void salvar_ranking(char *nome_arquivo, Ranking *ranking, int qtd_jogadores) {
    FILE *arq;
    int escritos;

    arq = fopen(nome_arquivo, "wb");
    if (arq == NULL) {
        return;
    }

    escritos = fwrite(ranking, sizeof(Ranking), qtd_jogadores, arq);
    fclose(arq);

    if (escritos != qtd_jogadores) {
        return;
    }
}
