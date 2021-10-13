#include "manipula_pilha.h"
#include "manipula_jogo.h"

// Executador do jogo
void executa_jogo(Pontuacao *pont, int rodada)
{
    Pilha *p;

    int n;                  // Número de tubos
    int tubo_origem;        // Tubo de origem do movimento
    int tubo_destino;       // Tubo de destino do movimento

    int val_empilhar;       // Armazenará o retorno da função verifica_pilha_cheia()
    int val_desempilhar;    // Armazenará o retorno da função verifica_pilha_vazia()

    int verif_venceu = 0;   // Verifica se o usuário venceu

    char cor_origem;        // Ao desempilhar, a função retornará para esta variável o cor do tubo origem


    for(;;)
    {

        // Escolha do numero de tubos
        do
        {
            system("cls");
            printf(RED"Escolha:\n\n"RESET);
            printf("Escolha um número de tubos de 6 a 12\n> ");
            scanf("%d",&n);
            fflush(stdin);
        }
        while(n < 6 || n > 12);


        //Cria os tubos e recria em caso de tubo perfeito

        p = cria_pilha(n);          // Cria os tubos
        config_inicial_tubo(p, n);  // Realiza a configuração inicial da posição das bolas nos tubos

        pont[rodada - 1].n = n;     // Insere no histórico de pontuação o número de tubos da rodada atual

        pont[rodada - 1].movimentacoes = 0;


        // Realização da jovagada
        for(;;)
        {
            system("cls");                          // Limpa a tela antes da nova impressão

            printf(RED" Ball Sort Puzzle\n"RESET);  // Imprime o Titulo

            imprime_tubos(p, n);                    // Invoca a função de Impressão


            // Verifica se o Usuario venceu
            if(verif_venceu == 1)
            {
                pont[rodada - 1].rodada = rodada;   // Enfia as rodadas atauis para o struct de historico

                verif_venceu = 0;                   // Verfica se o usuario venceu para finalizar rodada

                printf(GREEN"Você venceu a rodada!\n\n"RESET);
                printf("Número de movimentações realizadas: %d\n\n", pont[rodada - 1].movimentacoes);
                system("pause");

                return; // Volta para o MENU
            }


            // Pontuação
            printf(YELLOW"Movimentos Realizados:"RESET" %d\n\n",pont[rodada - 1].movimentacoes);

            // Sair para o menu
            printf("(0) Terminar rodada.\n\n");


            // Tubo ORIGEM
            do
            {
                // Captura o tubo de origem
                printf("Escolha um tubo para "RED"PEGAR"RESET" a bola:\n> ");
                scanf("%d", &tubo_origem);
                fflush(stdin);

                //Se valor inserido == 0, retorna ao menu e atualiza a rodada.
                if(tubo_origem == 0)
                {
                    pont[rodada - 1].rodada = rodada; // Atualiza a rodada

                    return; // Volta para o MENU
                }
            }
            while(tubo_origem < 1 || tubo_origem > n);


            // Tubo DESTINO
            do
            {
                // Captura o tubo de destino
                printf("Escolha um tubo para "RED"COLOCAR"RESET" a bola\n> ");
                scanf("%d", &tubo_destino);
                fflush(stdin);

                //Se valor inserido == 0, retorna ao menu e atualiza a rodada.
                if(tubo_destino == 0)
                {
                    pont[rodada - 1].rodada = rodada; // Atualiza a rodada

                    return; // Volta para o MENU
                }
            }
            while(tubo_destino < 1 || tubo_destino > n);


            // Primeiro, é preciso verificar se existe bola no tubo que o usuário solicitou
            val_desempilhar = verifica_pilha_vazia(p, tubo_origem - 1);


            // Caso sim, poderá entrar nesta condicional
            if(val_desempilhar == 1)
            {
                val_empilhar = verifica_pilha_cheia(p, tubo_destino - 1); // Verifica se poderá empilhar no tubo

                // Se sim, esta linha irá verificar se poderá colocar a bola no tubo de destino (pois o tubo pode estar cheio)
                if(val_empilhar == 1)
                {

                    // Temos também que verificar se as cores do tubo origem e destino são iguais (Caso o tubo destino esteja vazio, não entrará no 'if')
                    if(verificador_cor_origem_destino(p, tubo_origem - 1, tubo_destino - 1) != 0)
                    {
                        printf("\nA cor do tubo origem não é igual ao tubo destino! Tente novamente\n\n");
                        system("pause");
                        continue; // Volta para a escolha de tubos e não realiza nenhuma alteração
                    }

                    // Tudo certo então para desempilhar, empilhar e somar +1 ao movimento realizado

                    cor_origem = desempilhar(p, tubo_origem - 1);   // Desempilhando do tubo origem

                    empilhar(p, cor_origem, tubo_destino - 1);      // Empilhando no tubo destino

                    if(tubo_origem != tubo_destino)
                    {
                        pont[rodada - 1].movimentacoes++;               // Incremeta o movimento realizado
                    }

                    verif_venceu = verificador_tubo_completo(p, n);   // Verfica se o usuario venceu

                    continue;                                       // Continua o looping
                }

                // Caso tubo CHEIO
                printf("\nTubo cheio! Tente de novo.\n\n");
                system("pause");
                continue;                                           // Continua o looping
            }

            // Caso tubo VAZIO
            else
            {
                printf("\nTubo vazio! Selecione outro tubo.\n\n");
                system("pause");
                continue;                                           // Continua o looping
            }
        }
    }
}


// Mini-menu do histórico de pontuação de todas as rodadas feitas pelo usuário
void menu_pontuacoes(Pontuacao* pont, int rodada)
{
    system("cls");

    printf(RED" Histórico de Jogadas\n\n"RESET);

    // Imprime o historico das rodadas
    for(int i = 0; i < rodada; i++)
    {
        printf(YELLOW" Rodada: "RESET RED"%d\n"RESET, pont[i].rodada);
        printf(YELLOW" Número de Tubos: "RESET "%d\n", pont[i].n);
        printf(YELLOW" Movimentações: "RESET "%d\n", pont[i].movimentacoes);
        printf("--------------------\n\n");
    }

    if(rodada == 0)
    {
        printf(YELLOW"Você ainda não jogou."RESET "\n\n");
    }

    system("pause");
}


// Realiza a verificação de cores do tubo origem em comparação com o de destino
int verificador_cor_origem_destino(Pilha *p, int tubo_origem, int tubo_destino)
{
    No* ptr_1;                  // Nó referente ao tubo de origem
    No* ptr_2;                  // Nó referente ao tubo de destino

    char cor_1;                 // Cor do tubo origem
    char cor_2;                 // Cor do tubo destino

    ptr_1 = p[tubo_origem].topo;     // Nó do tubo origem
    ptr_2 = p[tubo_destino].topo;     // Nó do tubo destino


    // Faça a verificação somente se o tubo estiver com alguma cor
    if(ptr_1 != NULL && ptr_2 != NULL)
    {
        cor_1 = ptr_1->valor;   // Valor da cor do tubo origem
        cor_2 = ptr_2->valor;   // Valor da cor do tubo destino

        // Verifica se a cor deles são iguais
        if(cor_1 == cor_2)
        {
            return 0;   // Cor do tubo de origem igual a cor do tubo de destino
        }
        else
        {
            return 1;   // Cores desiguais
        }
    }

    return 0; // Pode passar! O tubo está vazio, não há o que comparar aqui..
}

// Realiza a primeira ordenação das bolas nos tubos
void config_inicial_tubo(Pilha *p, int n)
{
    srand(time(NULL));  //

    //Repete ate os valores dos tubos deixarem de ser uma combinação perfeita
    for(;;)
    {
        int x = 0;
        char cor;                   // cor escolhida pelo programa
        int sorteio, limite;        // random e limite
        char vet[40] = {'A','A','A','A','B','B','B','B','C','C','C','C','D','D','D','D','E','E','E','E','F','F','F','F','G','G','G','G','H','H','H','H','I','I','I','I','J','J','J','J'};
        char verif[4];
        limite = (n - 2) * 4;       // Lógica para o limite de bolas somadas em todos os tubos
        int i = 0;


        // Estrutura que irá percorrer todos os tubos
        while(i < n)
        {

            if(i < n - 2) // Não entrará nos dois últimos tubos (Pois os dois últimos precisam estar vazios)
            {
                for(int j = 0; j < 4;)      // Achou um tubo que esteja vazio ? Pronto, agora encha-o até o topo.
                {
                    sorteio = rand() % (limite);    // randomiza a escolha da letra(feita pelo programa)

                    if(vet[sorteio] != 'Z')
                    {
                        p[i].cod_tubo = i + 1;      // código do tubo (id) para identificação

                        cor = vet[sorteio];         // Essa variável recebe a cor escolhida pelo programa

                        verif[j] = cor;             // Acumula as 4 letras para verificação

                        vet[sorteio] = 'Z';         // A cor escolhida recebe um identificador 'Z' de que ja foi utilizada

                        empilhar(p, cor, i);        // Agora é colocado no tubo a cor e isso se repete até o tubo encher

                        j++;
                    }
                }

                //Verifica se uma pilha  por acaso foi gerada de forma identica
                if((verif[0] == verif[1]) && (verif[0] == verif[2]) && (verif[0] == verif[3]))
                {
                    x = 1;
                }

                // Tubo encheu ? Ok, agora o programa irá escolher outro tubo.
                i++;
                continue;                           // Continua o looping..
            }


            // Entra somente nos dois últimos tubos
            if(i < n)
            {
                p[i].cod_tubo = i + 1;          //
                p[i].tamanho = 0;               // Adiciona tamanho = 0
                i++;
                continue;                       // Continua o looping..
            }
        }

        //Se x == 1 limpa toda caso uma elas seja perfeita
        if(x == 1)
        {
            limpa_pilha(p, n);
            p = cria_pilha(n);
        }
        else
        {
            break;
        }
    }
}

// Realiza a impressão dos tubos na tela
void imprime_tubos(Pilha *p, int n)
{
    No* ptr;                        // Ponteiro pro Nó

    Pilha* _pi;                     // Ponteiro de Pilha auxiliador. Armazena dados da pilha original sem altera-los originalmente

    _pi = cria_pilha(n);            // Retorna a Pilha já criada com malloc

    printf("\n");


    // Percorro todos os índices para realizar a cópia da pilha original para a pilha auxiliar
    for(int i = 0; i < n; i++)
    {
        _pi[i] = p[i];
    }


    // Percorro no número máximo de bolas é possível ter em um tubo
    for(int i = 0; i < 4; i++)
    {
        // Percorro todos os tubos
        for(int j = 0; j < n; j++)
        {
            ptr = _pi[j].topo; // Armazeno o topo da pilha no Nó


            // Verifico se não está vazio
            if(ptr != NULL)
            {
                // Parte importante para fazer com que a bola fique no fundo do tubo ao passar de um tubo para o outro.
                if(_pi[j].tamanho < 4)
                {
                    printf(YELLOW"|   |   "RESET);
                    ++_pi[j].tamanho;

                    // Aqui quer dizer que chegou no último tubo (n - 1). Obs: É n - 1 pois o usuário digitará como exemplo o tubo numero 1, e o vetor começa na posição 0
                    if(j == n - 1)
                    {
                        printf("\n");
                        break;
                    }

                    continue;
                }

                printf(YELLOW"|"RESET" %c "YELLOW"|   "RESET, ptr->valor); // Imprime com o valor

                _pi[j].topo = ptr->prox; // Pega o próximo

                if(j == n - 1)
                {
                    printf("\n");
                }

                continue;
            }

            printf(YELLOW"|   |   "RESET);

            if(j == n - 1)
            {
                printf("\n");
            }
        }
    }

    // Imprime, em baixo dos tubos, um número para auxiliar o usuário na hora de escolher o tubo que desejar
    for(int i = 1; i <= n; i++)
    {
        printf(YELLOW"- %-2d-   "RESET, i);
    }

    printf("\n\n");

    free(_pi);  // Libera
}

// Realiza a verificação de vitória do usuário
int verificador_tubo_completo(Pilha *p, int n)
{
    No *ptr;

    int i = 0;
    int aux;
    int qtd_tubos_cores_iguais = 0;

    char cor;

    char cor_1;
    char cor_2;
    char cor_3;
    char cor_4;

    // Percorre todos os tubos
    while(i < n)
    {
        aux = 0;            // Auxilia na contagem para passar para a próxima cor do tubo

        if(p[i].tamanho == 0) // Tubo vazio
        {
            i++; // Ir para o próximo tubo
            continue;
        }

        ptr = p[i].topo;    // Caso o tamanho != 0

        // Se o tubo estiver cheio, haverá uma verificação das cores no tubo
        if(verifica_pilha_cheia(p, i) == 0)
        {
            while(ptr != NULL)
            {
                cor = ptr->valor;

                if(aux == 0)
                {
                    cor_1 = cor;
                    ptr = ptr->prox;
                    aux++;

                    continue;
                }

                if(aux == 1)
                {
                    cor_2 = cor;
                    ptr = ptr->prox;
                    aux++;

                    continue;
                }

                if(aux == 2)
                {
                    cor_3 = cor;
                    ptr = ptr->prox;
                    aux++;

                    continue;
                }

                if(aux == 3)
                {
                    cor_4 = cor;
                    ptr = ptr->prox;
                    aux++;

                    continue;
                }

                ptr = ptr->prox;
            }

            // Parte importante! Verifica se todas as cores do tubo são iguais
            if(cor_1 == cor_2 && cor_1 == cor_3 && cor_1 == cor_4 && cor_2 == cor_3 && cor_2 == cor_4 && cor_3 == cor_4)
            {
                qtd_tubos_cores_iguais++;
            }

        }

        // Caso o usuário tenha a quantidade de N - 2 tubos iguais
        if(qtd_tubos_cores_iguais == n - 2)
        {
            return 1; // O usuário venceu !!
        }

        i++;
        continue;
    }

    return 0; // O usuário ainda não venceu!
}


// Realiza a montagem do ponteiro de struct para criação de histórico do usuário
Pontuacao* inicia_pontuacao()
{
    Pontuacao *pont = (Pontuacao*)malloc(sizeof(Pontuacao));

    if(pont == NULL)
    {
        printf("Memória insuficiente.\n");
        exit(0);
    }

    pont->movimentacoes = 0;    // Armazena o número de movimentações realizada

    pont->rodada = 0;           // Armazena a rodada do usuário

    pont->n = 0;                // Armazena a quantidade de tubos na rodada, escolhido pelo usuário

    return pont;                 // Retorna o ponteiro para struct
}

