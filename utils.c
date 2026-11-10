#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int validar_entrada_numerica(int max, int min) {
    int entrada = -1;
    scanf("%d", &entrada);
    while(entrada < min || entrada > max) {
        printf("Ei, isso não é valido, repita!\n");
        while(getchar() != '\n');
        scanf("%d", &entrada);
    }
    while(getchar() != '\n');
    return entrada;
}

void aperte_enter() {
    printf("aperte enter para o proximo momento\n");
    while(getchar() != '\n');
}

void limpar_tela() {
    system("clear");
}
