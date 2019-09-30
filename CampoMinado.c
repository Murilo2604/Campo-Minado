 /***************************************************************/
/**                                                           **/
/**   NOME: Murilo Viana Teixeira Alvares----------11261548   **/
/**   EXERCICIO-PROGRAMA: 03                                  **/
/**   PROFESSOR: Ernesto Birgin                               **/
/**   TURMA: (02)                                             **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MMAX 90
#define NMAX 90
#define true 1
#define false 0
#define aberto -2                /*                                                                                                                                       */
#define fechado_marcado -3       /*Definicoes de valores arbitrarios que serao usadas para atriuir à matriz de verificacao o estado que cada casa do tabuleiro se encontra*/
#define fechado_desmarcado -4    /*                                                                                                                                       */

void abrir_casas(int i, int j, int tab[MMAX + 2][NMAX + 2], int tab_ver[MMAX + 2][NMAX + 2], int linhas, int colunas){ /*Funcao que recebe as coordenadas da casa, as matrizes da funcao principal, o numero de linhas e de colunas do tabuleiro e abre as casas ao redor da casa indicada*/

    int m,
    n;

    tab_ver[i][j] = aberto;


    for(m = i - 1; m <= i + 1; m = m + 1){       /*Loop que tem a funcao de abrir todas as casas ao redor daquela que tem valor zero(0)*/
        for(n = j - 1; n <= j + 1; n = n + 1){
            if (tab_ver[m][n] != aberto && (m >= 1 && m <= linhas) && (n >= 1 && n <= colunas)){       /*Como foi estabelecida uma "borda" ao tabuleiro, essa condicional verificara se a casa verificada nao pertence a borda, alem de verificar se a casa ja esta aberta*/
                tab_ver[m][n] = aberto;
                if(tab[m][n] == 0)
                    abrir_casas(m, n, tab, tab_ver, linhas, colunas);
            }
        }
    }
}

void matriz_aberta (int m, int n, int z, int seed, int tab[MMAX + 2][NMAX + 2]){   /*Funcao que recebe o numero de linhas, colunas e bombas, alem de receber as matrizes da funcao principal. Ela atribuira às casas os seus respectivos valores*/

    int minas[NMAX * MMAX];      /*Vetor que armazenará os valores atribuido as bombas pela geracao aleatoria*/

    int bombas, i, j;

    srand(seed);                 /*Inicializacao do gerador aleatorio atraves da semente*/

    for (i = 0; i <= z - 1; i = i + 1)   /*Loop que atribui os valores das bombas aos espacos do vetor minas*/
        minas[i] = rand();

    for (i = 0; i <= z - 1; i = i + 1)     /*Loop que usa os valores aleatoriamente gerados para posicionar as bombas no tabuleiro*/
        tab[minas[i] % m + 1][(minas[i] / m) % n + 1] = -1;

    for (i = 0; i <= m + 1; i = i + 1){
        for (j = 0; j <= n + 1; j = j + 1){
            bombas = 0;
            if (tab[i][j - 1] == -1 && (i >= 1 && j >= 1))           /******************************************************************************************************************************************************************/
                bombas = bombas + 1;                                 /**                                                                                                                                                               */
            if (tab[i][j + 1] == -1 && (i >= 1 && j >= 1))           /**                                                                                                                                                               */
                bombas = bombas + 1;                                 /**                                                                                                                                                               */
            if (tab[i + 1][j + 1] == -1 && (i >= 1 && j >= 1))       /**                                                                                                                                                               */
                bombas = bombas + 1;                                 /**                                                                                                                                                               */
            if (tab[i + 1][j - 1] == -1 && (i >= 1 && j >= 1))       /**                                                                                                                                                               */
                bombas = bombas + 1;                                 /**  Nesse bloco, sera atribuida as casas seus respectivos valores, somando-se um(1) a casa, caso seja verificada uma bomba em uma das oito casas que a envolvem  */
            if (tab[i + 1][j] == -1 && (i >= 1 && j >= 1))           /**                                                                                                                                                               */
                bombas = bombas + 1;                                 /**                                                                                                                                                               */
            if (tab[i - 1][j - 1] == -1 && (i >= 1 && j >= 1))       /**                                                                                                                                                               */
                bombas = bombas + 1;                                 /**                                                                                                                                                               */
            if (tab[i - 1][j] == -1 && (i >= 1 && j >= 1))           /**                                                                                                                                                               */
                bombas = bombas + 1;                                 /**                                                                                                                                                               */
            if (tab[i - 1][j + 1] == -1 && (i >= 1 && j >= 1))       /**                                                                                                                                                               */
                bombas = bombas + 1;                                 /******************************************************************************************************************************************************************/
            if (tab[i][j] != -1)         /*Condicional que verificara se a casa analisada nao armazena uma bomba. Caso a condicao seja atendida, sera armazenada nela a quantidade de bombas ao seu redor*/
                tab[i][j] = bombas;
        }
    }
}

void print_tab (int m, int n, int tab[MMAX + 2][NMAX + 2], int tab_ver[MMAX + 2][NMAX + 2]){   /*Funcao que recebe o numero de linhas e colunas, alem das matrizes da funcao principal, sendo responsavel por imprimir o tabuleiro*/

    int cont1,
    cont2;

    printf("\n     ");

    for (cont1 = 1; cont1 <= n; cont1 = cont1 + 1){
        if (cont1 <= 9)
            printf("  %d", cont1);
        else
            printf(" %d", cont1);
    }

    printf("\n    +");

    for (cont1 = 1; cont1 <= n; cont1 = cont1 + 1)
        printf("---");

    printf("-+");

    for(cont1 = 1; cont1 <= m; cont1 = cont1 + 1){
        if(cont1 < 10)
            printf("\n  %d", cont1);
        else
            printf("\n %d", cont1);
        printf(" |");
        for(cont2 = 1; cont2 <= n; cont2 = cont2 + 1){
            if(tab_ver[cont1][cont2] == aberto){
                if (tab[cont1][cont2] == -1)
                    printf("  @");
                else
                    printf("  %d", tab[cont1][cont2]);
            }
            if(tab_ver[cont1][cont2] == fechado_marcado)
                printf("  *");
            if(tab_ver[cont1][cont2] == fechado_desmarcado)
                printf("  .");
        }
        printf(" | %d", cont1);
    }
    printf("\n    +");

    for(cont1 = 1; cont1 <= n; cont1 = cont1 + 1)
            printf("---");

    printf("-+\n     ");

    for (cont1 = 1; cont1 <= n; cont1 = cont1 + 1){
        if(cont1 <= 9)
            printf("  %d", cont1);
        else
            printf(" %d", cont1);
    }

}

int main(){

    int tabuleiro_print[MMAX + 2][NMAX + 2],       /*Tabuleiro que guardara o valor de cada casa, ou seja, quantas bombas vizinhas existem ao redor dela*/
        tabuleiro_verificacao[MMAX + 2][NMAX + 2]; /*Tabuleiro que guardara o estado de cada casa: aberto, fechado e marcado ou fechado e desmarcado*/

    int m,                 /*Numero de linhas*/
    n,                     /*Numero de colunas*/
    z,                     /*Numero de bombas*/
    linhas_no_limite,
    colunas_no_limite,     /*Variaveis que verificarao se as condicoes pedidas no enunciado para as entradas m, n e z froam atendidas*/
    minas_no_limite,
    semente,
    vitoria,               /*Variavel que armazena se o jogador ja ganhou ou nao*/
    derrota,               /*Variavel que armazena se o jogador ja perdeu ou nao*/
    bombas_marcadas,
    i,
    j,
    conti,
    contj,
    casas_abertas,
    casas_livres;

    char jogada;           /*Variavel que armazena o tipo de jogada feita pelo jogador*/

    linhas_no_limite = false;
    colunas_no_limite = false;
    minas_no_limite = false;

    vitoria = false;   /*Por enquanto, nao se pode afirmar se o jogador venceu ou perdeu, entao ambas serao estabelecidas como falsas*/
    derrota = false;   /*                                                                                                            */

    while (linhas_no_limite == false){    /*Loop que nao se enerrara ate que as condicoes estabelecidas para a quantidade de linhas seja atendida*/
        printf("Entre com um valor para o numero de linhas (3 <= m <= 90): ");
        scanf("%d", &m);
        if (m <= MMAX && m >= 3)
            linhas_no_limite = true;
    }
    while(colunas_no_limite == false){    /*Loop que nao se enerrara ate que as condicoes estabelecidas para a quantidade de colunas seja atendida*/
        printf("Entre com um valor para o numero de colunas (3 <= m <= 90): ");
        scanf("%d", &n);
        if (n <= NMAX && n >= 3)
            colunas_no_limite = true;
    }
    while(minas_no_limite == false){    /*Loop que nao se enerrara ate que as condicoes estabelecidas para a quantidade de bombas seja atendida*/
        printf("Entre com um valor para o numero de minas (1 <= z <= %d): ", m*n-1);
        scanf("%d", &z);
        if (z <= m*n-1 && z >= 1)
            minas_no_limite = true;
    }

    printf("Entre com a semente:");
    scanf("%d", &semente);

    for (i = 1; i <= m; i = i + 1){                           /*Nesse loop, a matriz de verificacao fechara e desmarcara todas as casas do tabuleiro*/
        for (j = 1; j <= n; j = j + 1){
            tabuleiro_verificacao[i][j] = fechado_desmarcado;
        }
    }

    matriz_aberta(m, n, z, semente, tabuleiro_print);         /*Nessa passagem, a funcao matriz_aberta definira o valor de cada casa*/

    printf("Bem vindo ao Caca-Minas!\n");
    print_tab(m, n, tabuleiro_print, tabuleiro_verificacao);   /*Primeira impressao do tabuleiro, o qual sera impresso completamente fechado e desmarcado*/

    bombas_marcadas = 0;
    casas_livres = m*n - z;

    while(derrota == false && vitoria == false){               /*Loop que englobara todo o jogo. Enquanto o jogador nao perder ou nao vencer, ele permanecera em acao*/

        printf("\n\nProxima jogada: ");
        scanf(" %c %d %d", &jogada, &i, &j);

        if(jogada == 'a' || jogada == 'A'){            /*Condicional que verifica se a jogada pretendida pelo jogador e 'abrir'*/
            if(tabuleiro_print[i][j] == -1){           /*Condicional que verifica se a casa aberta armazena uma bomba*/
                printf("\nBOOOOM! Voce acaba de pisar numa mina!\n");
                derrota = true;                        /*Se o jogador abrir uma casa que armazena uma mina, entao ele perde o jogo*/
                for(i = 1; i <= m; i = i + 1){         /*Loop que abre todo o tabuleiro, o qual sera impresso apos o anuncico da derrota*/
                    for(j = 1; j <= n; j = j + 1){
                        tabuleiro_verificacao[i][j] = aberto;
                    }
                }
                print_tab(m , n, tabuleiro_print,tabuleiro_verificacao);
            }
            else if(tabuleiro_print[i][j] == 0){       /*Loop que verificara se casa aberta nao possui nenhuma bomba em sua vizinhanca*/
                if(tabuleiro_verificacao[i][j] == aberto)   /*Caso a casa ja esteja aberta, a jogada nao surtira efeito*/
                    printf("Sem efeito");
                else{
                    abrir_casas(i, j, tabuleiro_print, tabuleiro_verificacao, m, n);
                    casas_abertas = 0;
                    for (conti = 1; conti <= m; conti = conti + 1){   /*Loop que fara a contagem de quantas casas livres restantes ha*/
                        for (contj = 1; contj <= n; contj = contj + 1){
                            if(tabuleiro_verificacao[conti][contj] == aberto)
                                casas_abertas = casas_abertas + 1;
                        }
                    }
                    casas_livres = m*n-z - casas_abertas;
                    print_tab(m , n, tabuleiro_print,tabuleiro_verificacao);
                    printf("\n\nPor enquanto: %d/%d marcadas, %d livres", bombas_marcadas, z, casas_livres);
                }
            }
            else {
                if(tabuleiro_verificacao[i][j] == aberto)     /*Caso a casa ja esteja aberta, a jogada nao surtira efeito*/
                    printf("Sem efeito");
                else{
                    tabuleiro_verificacao[i][j] = aberto;
                    casas_livres = casas_livres - 1;
                    print_tab(m, n, tabuleiro_print, tabuleiro_verificacao);
                    printf("\n\nPor enquanto: %d/%d marcadas, %d livres", bombas_marcadas, z, casas_livres);
                }
            }
        }
        if(jogada == 'm' || jogada == 'M'){         /*Condicional que verifica se a jogada pretendida pelo jogador e 'marcar'*/
            if(tabuleiro_verificacao[i][j] == fechado_marcado)   /*Caso a casa ja esteja marcada, a jogada nao surtira efeito*/
                printf("Sem efeito");
            else if(tabuleiro_verificacao[i][j] == aberto)       /*Caso a casa ja esteja aberta, o jogo continua sem alteracoes*/
                printf("A casa ja estava previamente aberta");
            else{
                tabuleiro_verificacao[i][j] = fechado_marcado;
                if(tabuleiro_print[i][j] == -1)      /*Condicional que verifica se a casa marcada e uma bomba. Caso seja, o numero de bombas marcadas aumentara no valor de um (1)*/
                    bombas_marcadas = bombas_marcadas + 1;
                print_tab(m, n, tabuleiro_print, tabuleiro_verificacao);
                printf("\n\nPor enquanto: %d/%d marcadas, %d livres", bombas_marcadas, z, casas_livres);
            }
        }

        if(jogada == 'd' || jogada == 'D'){         /*Condicional que verifica se a jogada pretendida pelo jogador e 'desmarcar'*/
            if(tabuleiro_verificacao[i][j] == fechado_desmarcado)     /*Caso a casa ja esteja desmarcada, a jogada nao surtira efeito*/
                printf("Sem efeito");
            else{
                tabuleiro_verificacao[i][j] = fechado_desmarcado;
                if(tabuleiro_print[i][j] == -1 && tabuleiro_verificacao[i][j] == fechado_marcado)      /*Condicional que verifica se a casa desmarcada e uma bomba e ja estava previamente marcada. Caso seja, o numero de bombas marcadas reduzira no valor de um (1)*/
                    bombas_marcadas = bombas_marcadas - 1;
                print_tab(m, n, tabuleiro_print, tabuleiro_verificacao);
                printf("\n\nPor enquanto: %d/%d marcadas, %d livres", bombas_marcadas, z, casas_livres);
            }
        }
        if (casas_livres == 0){      /*Condicional que verifica se todas as casas possiveis de abrir ja foram abertas*/
            vitoria = true;          /*Caso a condiconal seja atendida, entao jogador vende a partida*/
            printf("\n\nParabens, voce venceu!\n");
            for(i = 1; i <= m; i = i + 1){         /*Loop que abre todo o tabuleiro, o qual sera impresso apos o anuncico da derrota*/
                for(j = 1; j <= n; j = j + 1){
                    tabuleiro_verificacao[i][j] = aberto;
                }
            }
            print_tab(m , n, tabuleiro_print,tabuleiro_verificacao);
        }
    }

    return 0;

}
