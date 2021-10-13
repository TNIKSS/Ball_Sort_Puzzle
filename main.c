#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "manipula_pilha.h"
#include "manipula_jogo.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao;                  // Armazena a escolha do usu�rio
    int static rodada = 0;      // Armazena de modo est�tico, a rodada atual do usu�rio no jogo

    Pontuacao *pont;

    pont = inicia_pontuacao();  // Cria um ponteiro de struct para pontua��o

    for(;;)
    {
        opcao = menu();         // Retorna a escolha do usu�rio

        switch(opcao)
        {

        // Executa o Jogo
        case 1:
            rodada++;

            // Se rodada for maior que 1 ser� necess�rio alocar mais mem�ria para o hist�rico de pontua��es do usu�rio
            if(rodada > 1)
            {
                pont = (Pontuacao*)realloc(pont, rodada * sizeof(Pontuacao));

                if(pont == NULL)
                {
                    printf("Mem�ria insuficiente\n");
                    exit(0);
                }
            }

            executa_jogo(pont, rodada);
            break;

        // Historico de pontua��o
        case 2:
            menu_pontuacoes(pont, rodada);
            break;

        // Informa��es do Jogo
        case 3:
            info_jogo();
            break;

        // Saida
        case 4:
            exit(0);

        // Valor default
        default:
            printf("Valor inexistente");
        }
    }
    return 0;
}

// Impress�o Menu Principal
int menu()
{
    int opcao;  // Vari�vel do menu


    //Impress�o
    do
    {
        system("cls");

        opcao = 0; // Reinicia variavel para evitar travamentos por characteres

        // Menu pr�-jogo
        printf("*------------ "RED"MENU"RESET" ------------*\n");
        printf("|                              |\n");
        printf("| (1)"YELLOW" Jogar/Continuar rodada   "RESET"|\n");
        printf("| (2)"YELLOW" Ver pontua��es           "RESET"|\n");
        printf("| (3)"YELLOW" Informa��es              "RESET"|\n");
        printf("| (4)"YELLOW" Sair                     "RESET"|\n");
        printf("|______________________________|\n\n");
        printf("> ");
        scanf("%d", &opcao);
        fflush(stdin);
    }
    while(opcao < 1 || opcao > 4);

    return opcao;
}


// Informa��es do Jogo
void info_jogo()
{
    system("cls");

    printf(">> O jogo possui como 'bolas' as letras/cores (A, B, C, D etc).\n\n");
    printf(">> Ser� gerado um n�mero abaixo de cada tubo para facilitar na hora da escolha.\n\n");

    printf(">> N�o existe um limite m�ximo de movimenta��es.\n\n");
    printf(">> Voc� poder� parar uma rodada se desejar e seu hist�rico de pontua��o ser� mantido.\n\n");

    printf(">> Voc� poder� escolher de 6 a 12 tubos, onde ser� gerado as bolas com cores aleat�rias para cada um.\n\n\n");

    system("pause");
}
