#ifndef DADOS_H
#define DADOS_H

#include "carta.h"


int contar_linhas_txt(char *nome_arquivo);
Carta *carregar_cartas_txt(char *nome_arquivo, int *qtd_cartas);
int listar_temas(Carta *cartas, int tamanho, char retorno_temas[6][50]);
Carta *filtrar_cartas_por_tema(Carta *cartas, char tema[], int tamanho, int *qtd_filtradas);

#endif
