#include "manipula_pilha.h"

// Cria a Pilha
Pilha* cria_pilha(int n)
{
    Pilha *tubos = (Pilha*)malloc(n * sizeof(Pilha));

    if(tubos == NULL)
    {
        printf("Memória insuficiente.");
        exit(0);
    }

    for(int i = 0; i < n; i++)
    {
        tubos[i].topo = NULL;
        tubos[i].tamanho = 0;
    }

    return tubos;
}


// Armazena elemento na pilha
int empilhar(Pilha *p, char elem, int i)
{

    // Cria uma bola no tubo
    No *no = (No*)malloc(sizeof(No));
    no->valor = elem;
    no->prox = p[i].topo;
    p[i].topo = no;
    p[i].tamanho++;

    return 1;
}

// Retira elemento da pilha
char desempilhar(Pilha *p, int i)
{
    No *ptr = p[i].topo;
    char cor;

    // Retirar a bola do tubo se realmente existe uma bola lá.
    if(ptr != NULL)
    {
        p[i].topo = ptr->prox;
        ptr->prox = NULL;
        cor = ptr->valor;
        free(ptr);
        p[i].tamanho--;

        return cor; // Bola retirada
    }

    return 'X'; // Não foi possível retirar uma bola do tubo, pois o mesmo encontra-se vazio.
}

int verifica_pilha_cheia(Pilha *p, int i)
{

    if(p[i].tamanho == 4)
    {
        return 0; // Atingiu o máximo de bolas no tubo
    }

    return 1; // Há espaço disponível no tubo
}

int verifica_pilha_vazia(Pilha *p, int i)
{
    No *ptr = p[i].topo;

    if(ptr != NULL)
    {
        return 1; // Tubo não está vazio
    }

    return 0; // Tubo vazio

}

void limpa_pilha(Pilha *p,int n)
{
    No *aux;                        // Cria nó auxiliar
    No *aux2;                       // Cria nó auxiliar

    for(int y = 0; y < (n-2); y++)
    {
        aux = p[y].topo;            //Auxiliar 1 recebe topo
        aux2 = p[y].topo;           //Auxiliar 2 recebe topo

        while(aux2 != NULL)
        {
            aux = aux2->prox;        // Topo da pilha agora aponta para o proximo elemento
            free(aux2);              // Libero o nó
            aux2 = aux;
        }
    }
    free(p);                        // Libera a pilha
}
