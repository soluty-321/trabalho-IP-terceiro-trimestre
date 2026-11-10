#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "utils.h"

#define LINHA_MAX 512

int contar_linhas_txt(char *nome_arquivo) {
    FILE *arq;
    char linha[LINHA_MAX];
    int linhas = 0;

    arq = fopen(nome_arquivo, "r");
    if (arq == NULL) {
        return -1;
    }

    while (fgets(linha, LINHA_MAX, arq) != NULL) {
        if (linha[0] != '\n' && linha[0] != '\r' && linha[0] != '\0') {
            linhas++;
        }
    }

    fclose(arq);
    return linhas;
}

Carta *carregar_cartas_txt(char *nome_arquivo, int *qtd_cartas) {
    FILE *arq;
    Carta *cartas;
    char linha[LINHA_MAX];
    char *token;
    int total;
    int indice = 0;

    if (qtd_cartas == NULL) {
        return NULL;
    }

    total = contar_linhas_txt(nome_arquivo);
    if (total <= 0) {
        *qtd_cartas = 0;
        return NULL;
    }

    cartas = malloc(total * sizeof(Carta));
    if (cartas == NULL) {
        *qtd_cartas = 0;
        return NULL;
    }

    arq = fopen(nome_arquivo, "r");
    if (arq == NULL) {
        free(cartas);
        *qtd_cartas = 0;
        return NULL;
    }

    while (fgets(linha, LINHA_MAX, arq) != NULL && indice < total) {
        if (linha[0] == '\n' || linha[0] == '\r' || linha[0] == '\0') {
            continue;
        }

        token = strtok(linha, ";\r\n");
        cartas[indice].id = atoi(token);

        token = strtok(NULL, ";\r\n");
        strcpy(cartas[indice].tema, token);

        token = strtok(NULL, ";\r\n");
        strcpy(cartas[indice].nome, token);

        token = strtok(NULL, ";\r\n");
        strcpy(cartas[indice].grupo, token);

        token = strtok(NULL, ";\r\n");
        strcpy(cartas[indice].categoria, token);

        token = strtok(NULL, ";\r\n");
        cartas[indice].atri1 = atoi(token);

        token = strtok(NULL, ";\r\n");
        cartas[indice].atri2 = atoi(token);

        token = strtok(NULL, ";\r\n");
        cartas[indice].atri3 = atoi(token);

        token = strtok(NULL, ";\r\n");
        cartas[indice].atri4 = atoi(token);

        token = strtok(NULL, ";\r\n");
        cartas[indice].especial = atoi(token);

        indice++;
    }

    fclose(arq);
    *qtd_cartas = indice;
    return cartas;
}

int contar_temas(Carta *cartas, int tamanho, char retorno_temas[6][50]) {
    int quant_temas = 0;
    int repetido;

    for (int i = 0; i < tamanho; i++) {
        repetido = 0;
        for (int j = 0; j < quant_temas; j++) {
            if (strcmp(cartas[i].tema, retorno_temas[j]) == 0) {
                repetido = 1;
            }
        }
        if (repetido == 0 && quant_temas < 6) {
            strcpy(retorno_temas[quant_temas], cartas[i].tema);
            quant_temas++;
        }
    }

    return quant_temas;
}

void escolher_tema(char temas[6][50], int qtd_temas, char tema_escolhido[50]) {
    int opcao;

    printf("\nEscolha um tema:\n");
    for (int i = 0; i < qtd_temas; i++) {
        printf("[%d] %s\n", i + 1, temas[i]);
    }

    printf("Opcao: ");
    opcao = validar_entrada_numerica(qtd_temas, 1);
    strcpy(tema_escolhido, temas[opcao - 1]);
}

Carta *filtrar_cartas_por_tema(Carta *cartas, char tema[], int tamanho, int *quant_filtradas) {
    Carta *filtradas;
    int total = 0;
    int indice_filtradas = 0;

    for (int i = 0; i < tamanho; i++) {
        if (strcmp(cartas[i].tema, tema) == 0) {
            total++;
        }
    }

    if (total == 0) {
        *quant_filtradas = 0;
        printf("nao foi achado correspondencia\n");
        return NULL;
    }

    filtradas = malloc(total * sizeof(Carta));

    for (int i = 0; i < tamanho; i++) {
        if (strcmp(cartas[i].tema, tema) == 0) {
            filtradas[indice_filtradas] = cartas[i];
            indice_filtradas++;
        }
    }

    *quant_filtradas = total;
    return filtradas;
}

