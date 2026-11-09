#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dados.h"
#include "jogo.h"

static void imprimir_monte(const char *nome, Monte *m) {
    int i;
    printf("%s tam=%d\n", nome, m->tam);
    for (i = 0; i < m->tam; i++) {
        printf("  %d|%s|%s\n", m->monte[i].id, m->monte[i].tema, m->monte[i].nome);
    }
}

int main(void) {
    int total = 0;
    int qtd_filtradas = 0;
    int qtd_temas = 0;
    int i;
    Carta *cartas;
    Carta *filtradas;
    Carta *embaralhadas;
    Monte j1 = {0};
    Monte j2 = {0};
    char temas[6][50];

    srand(1234);

    total = contar_linhas_txt("teste_cartas.txt");
    printf("linhas=%d\n", total);

    cartas = carregar_cartas_txt("teste_cartas.txt", &total);
    if (cartas == NULL) {
        printf("falha_carregar\n");
        return 1;
    }
    printf("carregadas=%d\n", total);

    qtd_temas = listar_temas(cartas, total, temas);
    printf("temas=%d\n", qtd_temas);
    for (i = 0; i < qtd_temas; i++) {
        printf("tema[%d]=%s\n", i, temas[i]);
    }

    filtradas = filtrar_cartas_por_tema(cartas, "Biologia", total, &qtd_filtradas);
    printf("biologia=%d\n", qtd_filtradas);
    if (filtradas == NULL) {
        free(cartas);
        return 2;
    }

    embaralhadas = embaralhar(filtradas, qtd_filtradas);
    printf("embaralhadas=%d\n", qtd_filtradas);
    for (i = 0; i < qtd_filtradas; i++) {
        printf("%d|%s|%s\n", embaralhadas[i].id, embaralhadas[i].tema, embaralhadas[i].nome);
    }

    distribuir_cartas(embaralhadas, &j1, &j2);
    imprimir_monte("j1", &j1);
    imprimir_monte("j2", &j2);

    if (j1.tam != 5 || j2.tam != 5) {
        printf("erro_tam_monte\n");
        free(cartas);
        free(filtradas);
        free(embaralhadas);
        return 3;
    }

    free(cartas);
    free(filtradas);
    free(embaralhadas);
    printf("ok\n");
    return 0;
}
