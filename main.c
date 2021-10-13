#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "manipula_pilha.h"
#include "manipula_jogo.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao;                  // Armazena a escolha do usuário
    int static rodada = 0;      // Armazena de modo estático, a rodada atual do usuário no jogo

    Pontuacao *pont;

    pont = inicia_pontuacao();  // Cria um ponteiro de struct para pontuação

    for(;;)
    {
        opcao = menu();         // Retorna a escolha do usuário

        switch(opcao)
        {

        // Executa o Jogo
        case 1:
            rodada++;

            // Se rodada for maior que 1 será necessário alocar mais memória para o histórico de pontuações do usuário
            if(rodada > 1)
            {
                pont = (Pontuacao*)realloc(pont, rodada * sizeof(Pontuacao));

                if(pont == NULL)
                {
                    printf("Memória insuficiente\n");
                    exit(0);
                }
            }

            executa_jogo(pont, rodada);
            break;

        // Historico de pontuação
        case 2:
            menu_pontuacoes(pont, rodada);
            break;

        // Informações do Jogo
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

// Impressão Menu Principal
int menu()
{
    int opcao;  // Variável do menu


    //Impressão
    do
    {
        system("cls");

        opcao = 0; // Reinicia variavel para evitar travamentos por characteres

        // Menu pré-jogo
        printf("*------------ "RED"MENU"RESET" ------------*\n");
        printf("|                              |\n");
        printf("| (1)"YELLOW" Jogar/Continuar rodada   "RESET"|\n");
        printf("| (2)"YELLOW" Ver pontuações           "RESET"|\n");
        printf("| (3)"YELLOW" Informações              "RESET"|\n");
        printf("| (4)"YELLOW" Sair                     "RESET"|\n");
        printf("|______________________________|\n\n");
        printf("> ");
        scanf("%d", &opcao);
        fflush(stdin);
    }
    while(opcao < 1 || opcao > 4);

    return opcao;
}


// Informações do Jogo
void info_jogo()
{
    system("cls");

    printf(">> O jogo possui como 'bolas' as letras/cores (A, B, C, D etc).\n\n");
    printf(">> Será gerado um número abaixo de cada tubo para facilitar na hora da escolha.\n\n");

    printf(">> Não existe um limite máximo de movimentações.\n\n");
    printf(">> Você poderá parar uma rodada se desejar e seu histórico de pontuação será mantido.\n\n");

    printf(">> Você poderá escolher de 6 a 12 tubos, onde será gerado as bolas com cores aleatórias para cada um.\n\n\n");

    system("pause");
}
