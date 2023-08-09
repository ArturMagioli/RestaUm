#include <stdio.h>
#include <conio.h>
#define TAM 7

///Alunos: Victor Hugo Froes Vianna
///        Artur de Paula Pereira Magioli


//define o struct Tabuleiro7x7 que recebe uma matriz7x7 como valor do parâmetro
typedef struct
{
    int data[TAM][TAM];
} Tabuleiro7x7;

///retorna struct tabuleiro que serve para chamá-lo no main
Tabuleiro7x7 getTabuleiro()
{
    Tabuleiro7x7 tabuleiro =
    {
        .data = {
            0, 0, 1, 1, 1, 0, 0,
            0, 0, 1, 1, 1, 0, 0,
            1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 2, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1,
            0, 0, 1, 1, 1, 0, 0,
            0, 0, 1, 1, 1, 0, 0,
        }
    };

    return tabuleiro;
}

///printa o tabuleiro que for passado como parâmetro
void printTabuleiro(Tabuleiro7x7 tabuleiro, int p1, int p2)
{
    printf("\nSEJA BEM VINDO AO RESTA UM! :D\n");
    printf("\nControles:\n \nSetas: MOVIMENTE O CURSOR 'X'(ESQUERDA, DIREITA, CIMA E BAIXO). \nEnter: SELECIONA A PECA DESEJADA OU CANCELA A SELECAO.\n\n");
    printf("\n\n");

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            if ( (p1 == i) && (p2 == j))
                printf("\tX ");

            else if(tabuleiro.data[i][j] == 1)
                printf("\tO  ");

            else if (tabuleiro.data[i][j] == 2)
                printf("\t  ");

            else
                printf("\t  ");
        }
        printf("\n\n");
    }
}

///retorna 1 se o jogo do usuário tiver movimentos possíves e 0 caso não.
int canPlay(Tabuleiro7x7 tab)
{
    for(int i = 0; i < TAM; i++)

        for(int j = 0; j < TAM; j++)

            if ((tab.data[i][j] == 1) && (hasValidMove(tab, i, j) == 1))

                return 1;

    return 0;
}

///retorna a quantidade de peças ativas no jogo
int contaPecas(Tabuleiro7x7 tab)
{
    int qtd = 0;

    for(int i = 0; i < TAM; i++)

        for(int j = 0; j < TAM; j++)

            if (tab.data[i][j] == 1)
                qtd++;

    return qtd;
}

///retorna 1 se o número for uma peça e 0 se for outra coisa
int isValid(Tabuleiro7x7 tab,int linhaAtual, int colunaAtual)
{
    return tab.data[linhaAtual][colunaAtual] == 1
           ? 1
           : 0;
}

///retorna 1 se a peça tiver movimentos válidos e 0 se não
int hasValidMove(Tabuleiro7x7 tab, int linhaAtual, int colunaAtual)
{
    if((tab.data[linhaAtual - 1][colunaAtual] == 1) && (tab.data[linhaAtual - 2][colunaAtual] == 2))
        return 1;

    else if((tab.data[linhaAtual + 1][colunaAtual] == 1) && (tab.data[linhaAtual + 2][colunaAtual] == 2))
        return 1;

    else if((tab.data[linhaAtual][colunaAtual - 1] == 1) && (tab.data[linhaAtual][colunaAtual - 2] == 2))
        return 1;

    else if((tab.data[linhaAtual][colunaAtual + 1] == 1) && (tab.data[linhaAtual][colunaAtual + 2] == 2))
        return 1;

    else
        return 0;

}

int moveBack(int move)
{
    return move - 1;
}

int moveForward(int move)
{
    return move + 1;
}

///Incrementa a posição de uma linha ou coluna do cursor
int moveForwardOnActionMode (int move)
{
    return move + 2;
}

///Decresce a posição de uma linha ou coluna do cursor
int moveBackOnActionMode(int move)
{
    ///Decresce a posição de uma linha ou coluna do cursor
    return move - 2;
}

///Executa a ação de "comer" uma peça, verifica qual foi o movimento e substitui os valores das peças
Tabuleiro7x7 eatPiece(Tabuleiro7x7 tab3, int p1, int p2, int move)
{
    tab3.data[p1][p2] = 1;
    if (move == 72)
    {
        tab3.data[p1 + 1][p2] = 2;
        tab3.data[p1 + 2][p2] = 2;
        system("cls");
        printTabuleiro(tab3, p1, p2);
        return tab3;
    }
    else if (move == 80)
    {
        tab3.data[p1 - 1][p2] = 2;
        tab3.data[p1 - 2][p2] = 2;
        system("cls");
        printTabuleiro(tab3, p1, p2);
        return tab3;

    }
    else if (move == 75)
    {
        tab3.data[p1][p2 + 1] = 2;
        tab3.data[p1][p2 + 2] = 2;
        system("cls");
        printTabuleiro(tab3, p1, p2);
        return tab3;
    }
    else if (move == 77)
    {
        tab3.data[p1][p2 - 1] = 2;
        tab3.data[p1][p2 - 2] = 2;
        system("cls");
        printTabuleiro(tab3, p1, p2);
        return tab3;
    }

}

///Executa a movimentação do cursor entre as peças disponíveis após a seleção.
Tabuleiro7x7 actionMode(Tabuleiro7x7 tab2, int p1, int p2, int *p1Main, int *p2Main, char *direction)
{
    int input = 0, registerMove = 0;
    int cursorParalelo[2];
    cursorParalelo[0] = p1;
    cursorParalelo[1] = p2;
    int resetLinha = p1;
    int resetColuna = p2;

    do
    {
        input = _getch();
        if ( (input == 13) && ( (resetLinha != p1) || (resetColuna != p2) ) )
        {
            tab2 = eatPiece(tab2, p1, p2, registerMove); //Ativa a ação de "comer" a peça
        }

        else if (input == 0 || input == 224) //Movimentação do cursor que seleciona a para qual direção a peça selecionada será movida.
        {
            input = _getch();
            cursorParalelo[0] = resetLinha;
            cursorParalelo[1] = resetColuna;
            p1 = resetLinha;
            p2 = resetColuna;
            *p1Main = p1;
            *p2Main = p2;
            system("cls");
            printTabuleiro(tab2, cursorParalelo[0], cursorParalelo[1]);

            switch (input)
            {
            case 72:
                if ( (tab2.data[resetLinha - 1][resetColuna] == 1) && (tab2.data[resetLinha - 2][resetColuna] == 2) && (resetLinha <= p1) )
                {
                    registerMove = 72;
                    system("cls");
                    p1 = moveBackOnActionMode(p1);
                    cursorParalelo[0] = p1;
                    *p1Main = p1;
                    *direction = 'u';
                    printTabuleiro(tab2, cursorParalelo[0], cursorParalelo[1]);
                }
                break;
            case 80:
                if ((tab2.data[resetLinha + 1][resetColuna] == 1) && (tab2.data[resetLinha + 2][resetColuna] == 2) && (resetLinha >= p1))
                {
                    registerMove = 80;
                    system("cls");
                    p1 = moveForwardOnActionMode(p1);
                    cursorParalelo[0] = p1;
                    *p1Main = p1;
                    *direction = 'd';
                    printTabuleiro(tab2, cursorParalelo[0], cursorParalelo[1]);
                }
                break;
            case 75:
                if ( (tab2.data[resetLinha][resetColuna - 1] == 1) && (tab2.data[resetLinha][resetColuna - 2] == 2) && (resetColuna <= p2) )
                {
                    registerMove = 75;
                    system("cls");
                    p2 = moveBackOnActionMode(p2);
                    cursorParalelo[1] = p2;
                    *p2Main = p2;
                    *direction = 'l';
                    printTabuleiro(tab2, cursorParalelo[0], cursorParalelo[1]);
                }
                break;
            case 77:
                if ( (tab2.data[resetLinha][resetColuna + 1] == 1) && (tab2.data[resetLinha][resetColuna + 2] == 2) && (resetColuna >= p2))
                {
                    registerMove = 77;
                    system("cls");
                    p2 = moveForwardOnActionMode(p2);
                    cursorParalelo[1] = p2;
                    *p2Main = p2;
                    *direction = 'r';
                    printTabuleiro(tab2, cursorParalelo[0], cursorParalelo[1]);
                }
                break;
            }
        }
    }
    while (input != 13);
    return tab2;
}

int main()
{
    Tabuleiro7x7 tabuleiro = getTabuleiro();

    int qtdPecas = contaPecas(tabuleiro);

    int input = 0;

    int linhaAtual = 3;
    int colunaAtual = 3;

    int cursor[2];
    cursor[0] = linhaAtual;
    cursor[1] = colunaAtual;

    char direction = 'a';

    printTabuleiro(tabuleiro, cursor[0], cursor[1]);

    while((qtdPecas >= 2) && (canPlay(tabuleiro) == 1))
    {
        qtdPecas = contaPecas(tabuleiro);

        input = _getch();

        if (input == 13)
        {
            int peca = isValid(tabuleiro, linhaAtual, colunaAtual);
            int movimento = hasValidMove(tabuleiro, linhaAtual, colunaAtual);
            if (movimento + peca == 2)
            {
                tabuleiro = actionMode(tabuleiro, linhaAtual, colunaAtual, &linhaAtual, &colunaAtual, &direction);
            }
            else
                printf("Movimento invalido!\n");
        }

        else if (input == 0 || input == 224)
        {
            input = _getch();
            switch (input)
            {
            case 72: //impede linha < 0
                if ((cursor[0] > 0) && ((cursor[0] > 2 || cursor[1] > 1) && (cursor[0] > 2 || cursor[1] < 5)))   //Garante que não extrapole do tabuleiro
                {
                    system("cls");
                    linhaAtual = moveBack(linhaAtual);
                    cursor[0] = linhaAtual;
                    //conserta direita pra esquerda e virar para baixo
                    if (direction == 'r')
                        cursor[1] += 2;

                    //conserta direita pra esquerda e virar para cima
                    else if(direction == 'l')
                        cursor[1] -= 2;

                    printTabuleiro(tabuleiro, cursor[0], cursor[1]);
                    direction = 'a';
                }
                break;
            case 80://impede linha > 6
                if (cursor[0] < 6 && ((cursor[0] < 4 || cursor[1] > 1) && (cursor[0] < 4 || cursor[1] < 5)))
                {
                    system("cls");
                    linhaAtual = moveForward(linhaAtual);
                    cursor[0] = linhaAtual;
                    //conserta esquerda pra direita e virar para cima
                    if(direction == 'l')
                        cursor[1] -= 2;

                    //conserta esquerda pra direita e virar para baixo
                    else if(direction == 'r')
                        cursor[1] += 2;

                    printTabuleiro(tabuleiro, cursor[0], cursor[1]);
                    direction = 'a';
                }
                break;
            case 75://impede coluna < 0
                if ((cursor[1] > 0) && ((cursor[0] > 1 || cursor[1] > 2) && (cursor[0] < 5 || cursor[1] > 2)))
                {
                    system("cls");
                    colunaAtual = moveBack(colunaAtual);
                    cursor[1] = colunaAtual;
                    //conserta baixo pra cima e virar para direita
                    if(direction == 'd')
                        cursor[0] += 2;

                    //conserta baixo pra cima e virar para esquerda
                    else if(direction == 'u')
                        cursor[0] -= 2;

                    printTabuleiro(tabuleiro, cursor[0], cursor[1]);
                    direction = 'a';
                }
                break;
            case 77://impede coluna > 6
                if ((cursor[1] < 6) && ((cursor[0] > 1 || cursor[1] < 4) && (cursor[0] < 5 || cursor[1] < 4)))
                {
                    system("cls");
                    colunaAtual = moveForward(colunaAtual);
                    cursor[1] = colunaAtual;
                    //conserta cima pra baixo e virar para esquerda
                    if(direction == 'u')
                        cursor[0] -= 2;

                    //conserta cima pra baixo e virar para esquerda
                    else if(direction == 'd')
                        cursor[0] += 2;

                    printTabuleiro(tabuleiro, cursor[0], cursor[1]);
                    direction = 'a';
                }
                break;
            }
        }
    }

    qtdPecas--;
    qtdPecas == 1
    ? printf("\t\t\tVOCE GANHOU!!!!\n")
    : printf("\t\t\tVOCE PERDEU!! D:\n")
    ;

    printf("\nQUANTIDADE DE PECAS RESTANTES: %i\n", qtdPecas);

    return 0;
}
