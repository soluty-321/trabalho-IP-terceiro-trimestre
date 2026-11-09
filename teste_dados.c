#include <stdio.h>
#include <stdlib.h>
#include "dados.h"

int main(void) {
    int qtd = 0;
    int qtd_biologia = 0;
    Carta *cartas = carregar_cartas_txt("teste_cartas.txt", &qtd);
    Carta *biologia;
    int i;

    printf("qtd=%d\n", qtd);
    if (cartas == NULL) {
        printf("erro\n");
        return 1;
    }

    listar_temas(cartas, qtd);
    biologia = filtrar_cartas_por_tema(cartas, "Biologia", qtd, &qtd_biologia);
    printf("biologia=%d\n", qtd_biologia);

    for (i = 0; i < qtd_biologia; i++) {
        printf("%d|%s|%s|%s|%s|%d|%d|%d|%d|%d\n",
               biologia[i].id,
               biologia[i].tema,
               biologia[i].nome,
               biologia[i].grupo,
               biologia[i].categoria,
               biologia[i].atri1,
               biologia[i].atri2,
               biologia[i].atri3,
               biologia[i].atri4,
               biologia[i].especial);
    }

    free(biologia);
    free(cartas);
    return 0;
}
