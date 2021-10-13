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


// Struct necessária para construção do histórico de pontuação do usuário
typedef struct pontuacao
{
    int rodada;         // Rodada
    int movimentacoes;  // Movimentações em uma rodada
    int n;              // Número de tubos em uma rodada
} Pontuacao;

Pontuacao* inicia_pontuacao(void);

void executa_jogo(Pontuacao *pont, int rodada);                                  // Função principal para execução do jogo
void menu_pontuacoes(Pontuacao* pont, int rodada);                               // Menu interativo do jogo para mostrar o histórico de pontuação
void imprime_tubos(Pilha *p, int n);                                             // Mostra os tubos
void info_jogo(void);                                                            // Mostra algumas informações do jogo para o usuário
int menu(void);                                                                  // Menu interativo
void config_inicial_tubo(Pilha *p, int n);                                       // Gera as bolas com cores aleatórias nos tubos
int verificador_tubo_completo(Pilha *p, int n);                                  // Verifica todas as cores do tubo
int verificador_cor_origem_destino(Pilha *p, int tubo_origem, int tubo_destino); // Verifica se a cor do tubo origem é igual ao destino



