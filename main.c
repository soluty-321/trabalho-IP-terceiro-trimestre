#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jogo.h"
#include "ranking.h"
#include "utils.h"

static void mostrar_como_jogar() {
    printf("\n==================== COMO JOGAR ====================\n");
    printf("Este programa segue o menu principal descrito no enunciado:\n");
    printf("[1] Jogar\n");
    printf("[2] Ver Ranking\n");
    printf("[3] Como Jogar\n");
    printf("[4] Sair\n\n");

    printf("Fluxo geral do jogo tematico:\n");
    printf("1. O jogo carrega os dados do arquivo externo e organiza as informacoes.\n");
    printf("2. O jogador escolhe um tema disponivel antes da partida.\n");
    printf("3. A partida ocorre em rodadas, com escolha de atributos e comparacao entre cartas.\n");
    printf("4. Ao final, o ranking e atualizado e ordenado por numero de vitorias.\n\n");

    printf("No Super Trunfo Tematico, a ideia e comparar os atributos das cartas e vencer\n");
    printf("o maior numero de rodadas possivel. O ranking mostra nome, vitorias, derrotas,\n");
    printf("empates e total de partidas.\n");
    printf("====================================================\n");
}

static void mostrar_menu() {
    printf("==================== MENU ====================\n");
    printf("[1] Jogar\n");
    printf("[2] Ver Ranking\n");
    printf("[3] Como Jogar\n");
    printf("[4] Sair\n");
    printf("==============================================\n");
    printf("Escolha uma opcao: ");
}

int main(void) {
    Ranking *ranking = NULL;
    int qtd_jogadores = 0;
    int opcao;

    srand((unsigned int)time(NULL));

    ranking = carregar_ranking(ARQUIVO_RANKING, &qtd_jogadores);
    if (ranking == NULL) {
        printf("Erro ao carregar o ranking.\n");
        return 1;
    }

    do {
        limpar_tela();
        mostrar_menu();
        opcao = validar_entrada_numerica(4, 1);

        switch (opcao) {
            case 1:
                limpar_tela();
                jogar(&ranking, &qtd_jogadores);
                break;

            case 2:
                limpar_tela();
                ordenar_ranking(ranking, qtd_jogadores);
                exibir_ranking(ranking, qtd_jogadores);
                aperte_enter();
                break;

            case 3:
                limpar_tela();
                mostrar_como_jogar();
                aperte_enter();
                break;

            case 4:
                break;
        }
    } while (opcao != 4);

    free(ranking);
    printf("Saindo do programa...\n");
    return 0;
}
