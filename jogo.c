#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"
#include "dados.h"
#include "ranking.h"
#include "utils.h"

#define ARQUIVO_CARTAS "cartas.txt"
#define MIN_CARTAS_PARTIDA 10

Carta *embaralhar(Carta *filtradas, int quant) {
    Carta *embaralhado = malloc(quant * sizeof(Carta));
    int indices[quant];
    int sentinela;
    int valor;
    memset(indices, -1, sizeof(indices));
    for(int i = 0; i < quant; i++) {
        do {
            sentinela = 0;
            valor = rand() % quant; 
            for(int j = 0; j < quant; j++) {
                if(indices[j] == valor) sentinela = 1;
            }
        } while(sentinela == 1);
        indices[i] = valor;
    }
    for(int i = 0; i < quant; i++) {
        embaralhado[i] = filtradas[indices[i]];
    }
    return embaralhado;
}

void distribuir_cartas(Carta *cartas, Monte *jogador1, Monte *jogador2) {
    for (int i = 0; i < 5; i++) {
        enfileirar(jogador1, cartas[i]);
        enfileirar(jogador2, cartas[i + 5]);
    }

}

int escolher_atributo(Monte *m, char *tema) {
    Carta carta = m->monte[0];
    int escolha;

    printf("\nSua carta: %s (%s, %s)\n", carta.nome, carta.grupo, carta.categoria);

    if (strcmp(tema, "Astronomia") == 0) {
        printf("1) Diametro: %d km\n", carta.atri1);
        printf("2) Distancia do Sol: %d milhoes de km\n", carta.atri2);
        printf("3) Numero de luas: %d\n", carta.atri3);
        printf("4) Duracao do dia: %d horas\n", carta.atri4);
    } else if (strcmp(tema, "Quimica") == 0) {
        printf("1) Numero atomico: %d\n", carta.atri1);
        printf("2) Massa atomica: %d u\n", carta.atri2);
        printf("3) Ponto de fusao: %d graus C\n", carta.atri3);
        printf("4) Ponto de ebulicao: %d graus C\n", carta.atri4);
    } else if (strcmp(tema, "Geografia") == 0) {
        printf("1) Area: %d mil km2\n", carta.atri1);
        printf("2) Populacao: %d milhoes de habitantes\n", carta.atri2);
        printf("3) Densidade demografica: %d hab/km2\n", carta.atri3);
        printf("4) Numero de municipios: %d\n", carta.atri4);
    } else if (strcmp(tema, "Historia") == 0) {
        printf("1) Altura: %d m\n", carta.atri1);
        printf("2) Idade: %d anos\n", carta.atri2);
        printf("3) Tempo de construcao: %d anos\n", carta.atri3);
        printf("4) Visitantes por ano: %d milhoes\n", carta.atri4);
    } else {
        printf("1) Atributo 1: %d\n", carta.atri1);
        printf("2) Atributo 2: %d\n", carta.atri2);
        printf("3) Atributo 3: %d\n", carta.atri3);
        printf("4) Atributo 4: %d\n", carta.atri4);
    }

    printf("\nEscolha o atributo: ");
    escolha = validar_entrada_numerica(4, 1);
    limpar_tela();

    return escolha;
}

static int valor_atributo(Carta *c, int atributo) {
    if (atributo == 1) {
        return c->atri1;
    } else if (atributo == 2) {
        return c->atri2;
    } else if (atributo == 3) {
        return c->atri3;
    } else if (atributo == 4) {
        return c->atri4;
    }

    return 0;
}

int comparar_cartas(Carta *c1, Carta *c2, int atributo) {
    int valor1;
    int valor2;

    if (c1->especial == 2 || c2->especial == 2) {
        printf("\n>> QUASAR! O disco de acrecao cega os dois jogadores.\n");
        printf(">> Rodada anulada.\n");
        return 0;
    }

    if (c1->especial == 1 && c2->especial == 1) {
        return 0;
    }

    if (c1->especial == 1) {
        return 1;
    }

    if (c2->especial == 1) {
        return 2;
    }

    valor1 = valor_atributo(c1, atributo);
    valor2 = valor_atributo(c2, atributo);

    if (valor1 > valor2) {
        return 1;
    }

    if (valor2 > valor1) {
        return 2;
    }

    return 0;
}

int jogar_partida_completa(Monte *jogador1, Monte *jogador2, char *nome1, char *nome2) {
    int rodada;
    int vencedor;
    int resultado;
    int jogador_escolhe = 1;

    if (jogador1 == NULL || jogador2 == NULL || nome1 == NULL || nome2 == NULL) {
        return -1;
    }

    for (rodada = 1; rodada <= 20; rodada++) {
        if (jogador1->tam <= 0 || jogador2->tam <= 0) {
            break;
        }
        if (jogador1->tam >= MAX_CARTAS || jogador2->tam >= MAX_CARTAS) {
            break;
        }

        limpar_tela();
        printf("==================== SUPER TRUNFO ====================\n");
        printf("Rodada %d de 20\n", rodada);
        printf("%s: %d carta(s) | %s: %d carta(s)\n", nome1, jogador1->tam, nome2, jogador2->tam);
        printf("=======================================================\n");
        printf("%s escolhe o atributo.\n", (jogador_escolhe == 1) ? nome1 : nome2);

        vencedor = simular_rodada(jogador1, jogador2, jogador_escolhe);
        if (vencedor == -1) {
            break;
        }

        if (vencedor == 1) {
            printf("\n>> %s venceu a rodada!\n", nome1);
            jogador_escolhe = 1;
        } else if (vencedor == 2) {
            printf("\n>> %s venceu a rodada!\n", nome2);
            jogador_escolhe = 2;
        } else {
            printf("\n>> A rodada terminou empatada.\n");
            jogador_escolhe = 3 - jogador_escolhe;
        }

        aperte_enter();
    }

    limpar_tela();
    printf("==================== FIM DE JOGO ====================\n");
    printf("%s: %d carta(s) | %s: %d carta(s)\n", nome1, jogador1->tam, nome2, jogador2->tam);

    if (jogador1->tam > jogador2->tam) {
        printf(">> %s venceu a partida!\n", nome1);
        resultado = 1;
    } else if (jogador2->tam > jogador1->tam) {
        printf(">> %s venceu a partida!\n", nome2);
        resultado = 2;
    } else {
        printf(">> A partida terminou empatada!\n");
        resultado = 0;
    }
    printf("=====================================================\n");
    aperte_enter();

    return resultado;
}

int simular_rodada(Monte *m1, Monte *m2, int jogador_escolhe) {
    Carta c1;
    Carta c2;
    Monte *escolhedor;
    int atributo;
    int vencedor;

    if (m1 == NULL || m2 == NULL) {
        return -1;
    }

    if (m1->tam <= 0 || m2->tam <= 0) {
        return -1;
    }

    if (jogador_escolhe != 2) {
        jogador_escolhe = 1;
    }

    c1 = m1->monte[0];
    c2 = m2->monte[0];

    escolhedor = (jogador_escolhe == 2) ? m2 : m1;
    atributo = escolher_atributo(escolhedor, escolhedor->monte[0].tema);
    vencedor = comparar_cartas(&c1, &c2, atributo);

    desenfileirar(m1, &c1);
    desenfileirar(m2, &c2);

    if (vencedor == 1) {
        enfileirar(m1, c1);
        enfileirar(m1, c2);
    } else if (vencedor == 2) {
        enfileirar(m2, c1);
        enfileirar(m2, c2);
    } else {
        enfileirar(m1, c1);
        enfileirar(m2, c2);
    }

    return vencedor;
}

static void liberar_memoria(Carta *cartas, Carta *filtradas, Carta *embaralhadas) {
    free(cartas);
    free(filtradas);
    free(embaralhadas);
}

static void ler_nome(char *rotulo, char *destino, int tamanho) {
    printf("%s: ", rotulo);
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = '\0';
}

static int preparar_partida(char *nome1, char *nome2, Monte *jogador1, Monte *jogador2) {
    Carta *cartas = NULL;
    Carta *filtradas = NULL;
    Carta *embaralhadas = NULL;
    char temas[6][50];
    char tema[50];
    int qtd_cartas;
    int qtd_temas;
    int qtd_filtradas;

    qtd_cartas = contar_linhas_txt(ARQUIVO_CARTAS);
    if (qtd_cartas <= 0) {
        printf("Nao foi possivel ler o arquivo %s.\n", ARQUIVO_CARTAS);
        return 0;
    }

    cartas = carregar_cartas_txt(ARQUIVO_CARTAS, &qtd_cartas);
    if (qtd_cartas <= 0) {
        printf("Erro ao carregar as cartas de %s.\n", ARQUIVO_CARTAS);
        liberar_memoria(cartas, filtradas, embaralhadas);
        return 0;
    }

    qtd_temas = contar_temas(cartas, qtd_cartas, temas);
    if (qtd_temas <= 0) {
        printf("Nenhum tema encontrado em %s.\n", ARQUIVO_CARTAS);
        liberar_memoria(cartas, filtradas, embaralhadas);
        return 0;
    }

    ler_nome("Nome do jogador 1", nome1, TAM_NOME);
    ler_nome("Nome do jogador 2", nome2, TAM_NOME);

    if (strcmp(nome1, nome2) == 0) {
        printf("Os dois jogadores precisam ter nomes diferentes.\n");
        liberar_memoria(cartas, filtradas, embaralhadas);
        return 0;
    }

    limpar_tela();
    printf("Jogadores: %s x %s\n", nome1, nome2);
    escolher_tema(temas, qtd_temas, tema);
    limpar_tela();

    filtradas = filtrar_cartas_por_tema(cartas, tema, qtd_cartas, &qtd_filtradas);
    if (qtd_filtradas < MIN_CARTAS_PARTIDA) {
        printf("O tema escolhido precisa ter pelo menos %d cartas.\n", MIN_CARTAS_PARTIDA);
        liberar_memoria(cartas, filtradas, embaralhadas);
        return 0;
    }

    embaralhadas = embaralhar(filtradas, qtd_filtradas);
    distribuir_cartas(embaralhadas, jogador1, jogador2);
    liberar_memoria(cartas, filtradas, embaralhadas);
    return 1;
}

static int atualizar_jogadores(Ranking **ranking, int *qtd_jogadores, char *nome1, char *nome2, int resultado) {
    int res1;
    int res2;

    if (resultado == 1) {
        res1 = VITORIA;
        res2 = DERROTA;
    } else if (resultado == 2) {
        res1 = DERROTA;
        res2 = VITORIA;
    } else {
        res1 = EMPATE;
        res2 = EMPATE;
    }

    *ranking = atualizar_ranking(*ranking, nome1, res1, qtd_jogadores);
    *ranking = atualizar_ranking(*ranking, nome2, res2, qtd_jogadores);

    return 1;
}

void jogar(Ranking **ranking, int *qtd_jogadores) {
    Monte jogador1 = {0};
    Monte jogador2 = {0};
    char nome1[TAM_NOME] = "";
    char nome2[TAM_NOME] = "";
    int resultado;

    if (ranking == NULL || qtd_jogadores == NULL) {
        return;
    }

    if (0 == preparar_partida(nome1, nome2, &jogador1, &jogador2)) {
        aperte_enter();
        return;
    }

    resultado = jogar_partida_completa(&jogador1, &jogador2, nome1, nome2);
    if (resultado == -1) {
        printf("Erro ao executar a partida.\n");
        aperte_enter();
        return;
    }

    if (0 == atualizar_jogadores(ranking, qtd_jogadores, nome1, nome2, resultado)) {
        printf("Erro ao atualizar o ranking.\n");
        aperte_enter();
        return;
    }

    ordenar_ranking(*ranking, *qtd_jogadores);
    salvar_ranking(ARQUIVO_RANKING, *ranking, *qtd_jogadores);

    limpar_tela();
    exibir_ranking(*ranking, *qtd_jogadores);
    aperte_enter();
}
