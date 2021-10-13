#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct no
{
    char valor;         // "bola"
    struct no *prox;    // pr�ximo n�
}No;

typedef struct
{
    No *topo;       // topo da pilha
    int tamanho;    // tamanho total de bolas dentro do tubo
    int cod_tubo;   // c�digo �nico do tubo, para facilitar sua identifica��o na hora de manipul�-lo
}Pilha;

Pilha* cria_pilha(int n);

int empilhar(Pilha *p, char elem, int i);   // Insere algum elemento na pilha
char desempilhar(Pilha *p, int i);          // Retira elemento da pilha
int verifica_pilha_vazia(Pilha *p, int i);  // Verifica se a pilha est� vazia
int verifica_pilha_cheia(Pilha *p, int i);  // Verifica se a pilha est� cheia
void limpa_pilha(Pilha *p, int n);          // Libera pilha
