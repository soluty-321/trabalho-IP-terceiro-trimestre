#ifndef RANKING_H
#define RANKING_H

#define ARQUIVO_RANKING "ranking.dat"
#define TAM_NOME 50

#define VITORIA 1
#define DERROTA 2
#define EMPATE 3

typedef struct {
    char nome[TAM_NOME];
    int vitorias;
    int derrotas;
    int empates;
} Ranking;

Ranking *carregar_ranking(char *nome_arquivo, int *qtd_jogadores);
Ranking *atualizar_ranking(Ranking *ranking, char *nome, int resultado, int *qtd_jogadores);
int salvar_ranking(char *nome_arquivo, Ranking *ranking, int qtd_jogadores);

#endif
