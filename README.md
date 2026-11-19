# Super Trunfo Temático

Trabalho Final de Introdução à Programação  
Professora: Camille Braga  
Aluno: Eduardo

## Sobre o jogo

Dois pesquisadores chegam a um campo de estudo para catalogar os elementos mais impressionantes do tema escolhido. Cada um leva seu caderno de campo e um baralho de espécies. Para decidir quem publica a grande descoberta, os dois fazem um duelo de dados científicos: vence quem ficar com todos os espécimes do rival.

No jogo, cada jogador recebe cinco cartas. Em cada rodada, o jogador da vez escolhe um dos quatro atributos da sua carta e compara esse valor com o mesmo atributo da carta do adversário. Quem tiver o maior valor leva as duas cartas. A partida termina quando um jogador fica sem cartas ou quando são atingidas 20 rodadas.

Tema escolhido: **Tema 2 — Super Trunfo Temático**.

## Funcionalidades

- Menu principal com as opções Jogar, Ver Ranking, Como Jogar e Sair.
- Leitura e validação do arquivo `cartas.txt`.
- Quatro temas: Astronomia, Geografia, História e Química.
- Embaralhamento e distribuição de cinco cartas para cada jogador.
- Partidas de até 20 rodadas.
- Escolha de atributos pelo jogador da vez.
- Vencedor da rodada escolhe o atributo na rodada seguinte.
- Em caso de empate, a escolha passa para o outro jogador.
- Cartas Trunfo e carta de evento Quasar.
- Ranking binário com atualização ao final de cada partida.
- Ranking ordenado por número de vitórias.
- Validação de entradas inválidas no menu e na escolha de atributos.
- Limpeza de tela e pausa com Enter entre as etapas.

## Como compilar e executar

Execute os comandos a partir da pasta raiz do projeto, pois o programa abre `cartas.txt` e `ranking.bin` por caminho relativo.

### Opção 1 — compilação direta com gcc

```bash
gcc -std=c11 -Wall -Wextra -o super_trunfo \
    main.c jogo.c dados.c ranking.c utils.c monte.c
./super_trunfo
```

### Opção 2 — CMake

```bash
cmake -S . -B build
cmake --build build
./build/trabalhoIP3t
```

O projeto usa C11 e não depende de bibliotecas externas.

## Arquivos do projeto

| Arquivo | Responsabilidade |
|---|---|
| `main.c` | Menu principal, carregamento do ranking e controle geral do programa. |
| `jogo.c` / `jogo.h` | Regras da partida, escolha de atributos, comparação de cartas, Trunfo, evento e fluxo de uma partida completa. |
| `dados.c` / `dados.h` | Leitura, contagem e validação das cartas do arquivo `cartas.txt`, descoberta dos temas e filtragem por tema. |
| `ranking.c` / `ranking.h` | Carregamento, atualização, ordenação, exibição e gravação binária do ranking. |
| `utils.c` / `utils.h` | Entrada numérica validada, limpeza de tela e pausa com Enter. |
| `carta.h` | Estrutura `Carta`. |
| `monte.c` / `monte.h` | Estrutura `Monte` e operações de fila (`enfileirar` e `desenfileirar`). |
| `cartas.txt` | Banco de cartas do jogo. |
| `ranking.bin` | Ranking binário gerado automaticamente pelo programa. |

## Formato do arquivo cartas.txt

Cada linha representa uma carta, com um campo por coluna:

```text
id;tema;nome;grupo;categoria;atributo1;atributo2;atributo3;atributo4;especial
```

Exemplo:

```text
1;Astronomia;Mercurio;Planeta;Rochoso;4879;58;0;4222;0
```

O campo `especial` indica o tipo da carta:

- `0` — carta comum;
- `1` — carta Trunfo;
- `2` — carta de evento.

O arquivo entregue possui 60 cartas, sendo 15 de cada tema, com os registros misturados entre os temas. Os atributos são interpretados de acordo com o tema:

| Tema | Atributo 1 | Atributo 2 | Atributo 3 | Atributo 4 |
|---|---|---|---|---|
| Astronomia | Diâmetro (km) | Distância do Sol (milhões de km) | Número de luas | Duração do dia (horas) |
| Geografia | Área (mil km²) | População (milhões) | Densidade demográfica (hab/km²) | Número de municípios |
| História | Altura (m) | Idade desde a conclusão (anos) | Tempo de construção (anos) | Visitantes por ano (milhões) |
| Química | Número atômico | Massa atômica (u) | Ponto de fusão (°C) | Ponto de ebulição (°C) |

Os nomes de cartas foram escritos sem espaços e sem acentos para simplificar a leitura com `strtok`. Os valores foram arredondados para inteiros porque os atributos da estrutura `Carta` são do tipo `int`.

## Regras implementadas

### Objetivo

Terminar a partida com mais cartas que o adversário. Se um jogador ficar sem cartas, o outro vence imediatamente.

### Preparação

1. O jogador escolhe um dos temas disponíveis.
2. São informados os nomes dos dois jogadores.
3. As cartas do tema são filtradas, embaralhadas e distribuídas: cinco para cada jogador.

### Rodada

1. O jogador da vez vê apenas a própria carta do topo.
2. Ele escolhe um dos quatro atributos numéricos da carta.
3. O atributo escolhido é comparado com o mesmo atributo da carta do adversário.
4. Quem tiver o maior valor vence a rodada e recebe as duas cartas.
5. Em caso de empate, cada jogador mantém a sua carta.
6. O vencedor da rodada escolhe o atributo na rodada seguinte.
7. Em caso de empate, a escolha passa para o outro jogador.
8. Na primeira rodada, o jogador 1 escolhe.

### Cartas especiais

- **Carta Trunfo:** vence qualquer carta comum, independentemente do atributo escolhido. No confronto entre duas cartas Trunfo, a rodada empata.
- **Carta de evento Quasar:** carta do tema Astronomia que empata automaticamente a rodada, sendo superior até mesmo a uma carta Trunfo.
- Como a Quasar é a única carta de evento do jogo, qualquer carta com `especial = 2` empata a rodada.

### Fim da partida

A partida termina quando um dos montes fica vazio, quando um jogador chega a 10 cartas ou quando são atingidas 20 rodadas. Vence quem tiver mais cartas; se os dois tiverem a mesma quantidade, a partida termina empatada.

### Ranking

Ao final de cada partida, os dois jogadores são atualizados no ranking:

- vencedor recebe uma vitória;
- perdedor recebe uma derrota;
- em caso de empate, os dois recebem um empate.

O ranking é ordenado por número de vitórias em ordem decrescente. A ordenação é feita com um algoritmo estável do tipo bubble sort, preservando a ordem anterior dos jogadores com o mesmo número de vitórias. A classificação é gravada em `ranking.bin` usando `fwrite` e lida com `fread`. Caso o arquivo não exista, o programa o cria automaticamente.

## Estruturas de dados

### `Carta`

Representa uma carta do jogo, com identificador, tema, nome, grupo, categoria, quatro atributos numéricos e o campo `especial`.

### `Monte`

Representa o caderno de cartas de um jogador. As cartas são armazenadas em um vetor de capacidade máxima 10 e controladas como uma fila:

- `enfileirar` insere no final;
- `desenfileirar` remove do início.

O topo do monte é sempre a posição `0`, que é a carta usada na rodada.

### `Ranking`

Representa um registro de jogador, com nome, vitórias, derrotas e empates. O total de partidas é calculado como a soma desses três valores na exibição.

## Alocação dinâmica de memória

A quantidade de cartas não é fixada no código:

- `contar_linhas_txt` conta os registros do arquivo;
- `carregar_cartas_txt` aloca um vetor de `Carta` com `malloc` do tamanho exato;
- `filtrar_cartas_por_tema` conta as cartas do tema escolhido e aloca outro vetor com `malloc`;
- `embaralhar` aloca o vetor embaralhado com `malloc`;
- `atualizar_ranking` usa `realloc` para acrescentar jogadores ou reaproveita um registro vazio;
- todos os vetores temporários são liberados com `free` ao final da preparação da partida e o ranking é liberado ao sair do programa.

O ranking é gravado e lido em modo binário, respeitando o tamanho da estrutura `Ranking`.

## Decisões e limitações

- Foram implementados quatro temas: Astronomia, Geografia, História e Química. Biologia e Paleontologia não possuem cartas neste banco de dados.
- O banco possui 15 cartas por tema, mas a partida usa as 10 primeiras cartas do vetor embaralhado, cinco para cada jogador.
- A Quasar possui atributos zerados no arquivo porque a regra de evento não realiza comparação numérica; ela sempre empata a rodada.
- Os nomes dos jogadores devem ser diferentes para evitar que os dois resultados sejam gravados no mesmo registro do ranking.
- O programa deve ser executado na pasta que contém `cartas.txt`.
- A carta de evento é o recurso especial obrigatório do Tema 2. Não foi implementado nenhum recurso extra opcional além dela.

## Fontes dos dados

Os valores das cartas são aproximados e foram arredondados para inteiros. As principais fontes consultadas foram:

- NASA — Planetary Fact Sheet: <https://nssdc.gsfc.nasa.gov/planetary/factsheet/>
- IBGE — Censo Demográfico 2022: <https://sidra.ibge.gov.br/pesquisa/censo-demografico/demografico-2022/primeiros-resultados-populacao-e-domicilios>
- IBGE — Número de municípios por unidade da federação: <https://anuario.ibge.gov.br/images/aeb/2023/s2/2_pdf/s2t7102.pdf>
- Guinness World Records — Pirâmides de Gizé: <https://www.guinnessworldrecords.com/world-records/780560-most-visited-pyramid-complex>
- Coliseu: <https://it.m.wikipedia.org/wiki/Colosseo>
- Torre Eiffel: <https://sete.toureiffel.paris/fr/presse/communiques/63-millions-de-visiteurs-la-tour-eiffel-en-2023>
- Estátua da Liberdade: <https://home.nps.gov/stli/learn/statue-of-liberty-facts.htm>
- Taj Mahal: <http://www.china.org.cn/world/Off_the_Wire/2025-09/27/content_118101159.shtml>
- Machu Picchu: <https://andina.pe/agencia/noticia-machu-picchu-informe-sobre-carga-visitantes-a-santuario-estara-listo-setiembre-1058966.aspx>
- Partenon: <https://plus.inquirer.net/news/parthenon-new-look-in-220-years/>
- Versalhes: <https://beta.rtbf.be/article/hausse-record-de-visiteurs-au-louvre-et-dans-les-monuments-emblematiques-de-france-en-2025-11656661>
- Angkor Wat: <https://aa.com.tr/ar/%d8%a7%d9%84%d8%ab%d9%82%d8%a7%d9%81%d8%a9-%d9%88%d8%a7%d9%84%d9%81%d9%86%d9%88%d9%86/%d9%85%d8%b9%d8%a8%d8%af-%d8%a3%d9%86%d8%ba%d9%83%d9%88%d8%b1-%d9%88%d8%a7%d8%aa-%d8%a7%d9%84%d9%85%d8%b9%d9%84%d9%85-%d8%a7%d9%84%d9%83%d9%85%d8%a8%d9%88%d8%af%d9%8a-%d8%a7%d9%84%d8%aa%d8%a7%d8%b1%d9%8a%d8%ae%d9%8a-%d9%88%d9%85%d8%ad%d8%b1%d9%83%d9%87%d8%a7-%d8%a7%d9%84%d8%b3%d9%8a%d8%a7%d8%ad%d9%8a-%d8%aa%d9%82%d8%b1%d9%8a%d8%b1/3954853>
- Petra: <https://petra.gov.jo/en/news/petra-visitors-rise-27-in-2025-foreign-arrivals-up-45-pdtra>
- Stonehenge: <https://www.the-independent.com/news/uk/home-news/stonehenge-tickets-english-heritage-alone-b3023531.html>
- Torre de Pisa: <https://activities.easyjet.com/pt/pisa/torre-de-pisa-v>
- Big Ben: <https://eresources.nlb.gov.sg/webarchives/wayback/20130918183807/http://en.wikipedia.org/wiki/Big_Ben>
- Muralha da China: <https://commons.wikimedia.org/wiki/Category:Great_Wall_of_China?uselang=pt>
- Catedral de Colônia: <https://en.wikipedia.org/wiki/Cologne_Cathedral>
- Tabela periódica — Royal Society of Chemistry: <https://www.rsc.org/periodic-table>
