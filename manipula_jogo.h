#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"


// Struct necess�ria para constru��o do hist�rico de pontua��o do usu�rio
typedef struct pontuacao
{
    int rodada;         // Rodada
    int movimentacoes;  // Movimenta��es em uma rodada
    int n;              // N�mero de tubos em uma rodada
} Pontuacao;

Pontuacao* inicia_pontuacao(void);

void executa_jogo(Pontuacao *pont, int rodada);                                  // Fun��o principal para execu��o do jogo
void menu_pontuacoes(Pontuacao* pont, int rodada);                               // Menu interativo do jogo para mostrar o hist�rico de pontua��o
void imprime_tubos(Pilha *p, int n);                                             // Mostra os tubos
void info_jogo(void);                                                            // Mostra algumas informa��es do jogo para o usu�rio
int menu(void);                                                                  // Menu interativo
void config_inicial_tubo(Pilha *p, int n);                                       // Gera as bolas com cores aleat�rias nos tubos
int verificador_tubo_completo(Pilha *p, int n);                                  // Verifica todas as cores do tubo
int verificador_cor_origem_destino(Pilha *p, int tubo_origem, int tubo_destino); // Verifica se a cor do tubo origem � igual ao destino



