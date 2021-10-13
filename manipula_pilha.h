#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct no
{
    char valor;         // "bola"
    struct no *prox;    // próximo nó
}No;

typedef struct
{
    No *topo;       // topo da pilha
    int tamanho;    // tamanho total de bolas dentro do tubo
    int cod_tubo;   // código único do tubo, para facilitar sua identificação na hora de manipulá-lo
}Pilha;

Pilha* cria_pilha(int n);

int empilhar(Pilha *p, char elem, int i);   // Insere algum elemento na pilha
char desempilhar(Pilha *p, int i);          // Retira elemento da pilha
int verifica_pilha_vazia(Pilha *p, int i);  // Verifica se a pilha está vazia
int verifica_pilha_cheia(Pilha *p, int i);  // Verifica se a pilha está cheia
void limpa_pilha(Pilha *p, int n);          // Libera pilha
