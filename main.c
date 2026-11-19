#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jogo.h"
#include "ranking.h"
#include "utils.h"

static void mostrar_como_jogar() {
    printf("\n==================== COMO JOGAR ====================\n");
    printf("A HISTORIA\n");
    printf("Dois pesquisadores chegam a um campo de estudo para catalogar os\n");
    printf("elementos mais impressionantes do tema escolhido. Cada um leva seu\n");
    printf("caderno de campo e um baralho de especies. Para decidir quem publica\n");
    printf("a grande descoberta, os dois fazem um duelo de dados cientificos:\n");
    printf("vence quem ficar com todos os especimes do rival.\n\n");

    printf("OBJETIVO\n");
    printf("Terminar a partida com mais cartas que o adversario. Se um jogador\n");
    printf("ficar sem cartas, o outro vence imediatamente.\n\n");

    printf("PREPARACAO\n");
    printf("1. Escolha um dos temas disponiveis no arquivo de cartas.\n");
    printf("2. Informe o nome dos dois jogadores.\n");
    printf("3. As cartas do tema sao embaralhadas e divididas: 5 para cada um.\n\n");

    printf("UMA RODADA\n");
    printf("1. O jogador da vez ve apenas a propria carta do topo.\n");
    printf("2. Ele escolhe um dos quatro atributos numericos dessa carta.\n");
    printf("3. O valor escolhido e comparado com o mesmo atributo da carta do rival.\n");
    printf("4. Quem tiver o maior valor vence a rodada e leva as duas cartas.\n");
    printf("5. Em caso de empate, cada um mantem a sua carta.\n");
    printf("6. O vencedor da rodada escolhe o atributo na rodada seguinte.\n");
    printf("   Na primeira rodada, quem escolhe e o jogador 1.\n\n");

    printf("CARTAS ESPECIAIS\n");
    printf("- Carta Trunfo: vence qualquer carta comum, independentemente do atributo.\n");
    printf("  No confronto entre duas cartas Trunfo, a rodada empata.\n");
    printf("- Carta de evento Quasar (tema Astronomia): empata automaticamente\n");
    printf("  a rodada, sendo superior ate mesmo a uma carta Trunfo.\n\n");

    printf("FIM DA PARTIDA\n");
    printf("A partida termina quando um dos jogadores fica sem cartas ou quando\n");
    printf("sao atingidas 20 rodadas. Vence quem tiver mais cartas; se os dois\n");
    printf("tiverem a mesma quantidade, a partida termina empatada.\n\n");

    printf("RANKING\n");
    printf("Ao final, o resultado e gravado no ranking com vitorias, derrotas,\n");
    printf("empates e total de partidas. O ranking e ordenado por vitorias.\n");
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
