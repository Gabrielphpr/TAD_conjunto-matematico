#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore_avl.h"
#include "lista.h"
#include "conjunto.h"

struct Conjunto
{
    int tipo;        // 0 -> AVL, 1 -> Lista Linear Sequencial
    int tam;         // Tamanho do conjunto
    void *estrutura; // A partir desse ponteiro void, é possível escolher qual estrutura de dados será utilizada
};

/*
    As funções desse arquivo possuem um padrão comum:
        - Dada a definição do tipo, de estrutura a ser utilizada, por meio de um "if",
         o algoritmo redireciona a chamada para uma função específica ou do TAD arvore_avl ou do TAD lista
         - Exceto o União e Intersecção, que tem alguns detalhes específicos, todos seguem esse padrão
*/

Conjunto *criar_conjunto(int tipo, int tam)
{
    Conjunto *conjunto = (Conjunto *)malloc(sizeof(Conjunto));
    if (!conjunto)
    {
        printf("Erro: falha ao alocar memória para o conjunto.\n");
        exit(EXIT_FAILURE);
    }

    conjunto->tipo = tipo;
    conjunto->tam = tam;

    if (tipo == 0)
    {
        conjunto->estrutura = criar_arvore_avl();
        if (!conjunto->estrutura)
        {
            printf("Erro: falha ao criar a árvore AVL.\n");
            free(conjunto);
            exit(EXIT_FAILURE);
        }
    }
    else if (tipo == 1)
    {
        conjunto->estrutura = lista_criar(tam);
        if (!conjunto->estrutura)
        {
            printf("Erro: falha ao criar a lista.\n");
            free(conjunto);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("Erro: tipo de estrutura inválido.\n");
        free(conjunto);
        exit(EXIT_FAILURE);
    }

    return conjunto;
}

void apagar_conjunto(Conjunto *conjunto)
{
    if (!conjunto || !conjunto->estrutura)
        return;

    if (conjunto->estrutura)
    {
        if (conjunto->tipo == 0)
        {
            apagar_arvore_avl((ArvoreAVL **)(&(conjunto->estrutura)));
        }
        else if (conjunto->tipo == 1)
        {
            lista_apagar((LISTA **)&(conjunto->estrutura));
        }
    }

    free(conjunto);
}

bool inserir_elemento(Conjunto *conjunto, int elemento)
{
    if (conjunto->tipo == 0)
    {
        return inserir_arvore_avl((ArvoreAVL *)conjunto->estrutura, elemento);
    }
    else if (conjunto->tipo == 1)
    {
        return lista_inserir((LISTA *)conjunto->estrutura, elemento);
    }
}

bool remover_elemento(Conjunto *conjunto, int elemento)
{
    if (conjunto->tipo == 0)
    {
        return remover_arvore_avl((ArvoreAVL *)conjunto->estrutura, elemento);
    }
    else if (conjunto->tipo == 1)
    {
        return lista_remover((LISTA *)conjunto->estrutura, elemento);
    }
}

bool pertence_conjunto(Conjunto *conjunto, int elemento)
{
    if (conjunto->tipo == 0)
    {
        return pertence_arvore_avl((ArvoreAVL *)conjunto->estrutura, elemento);
    }
    else if (conjunto->tipo == 1)
    {
        return lista_pertence((LISTA *)conjunto->estrutura, elemento);
    }
}

void imprimir_conjunto(Conjunto *conjunto)
{
    if (conjunto->tipo == 0)
    {
        imprimir_arvore_avl((ArvoreAVL *)conjunto->estrutura);
    }
    else if (conjunto->tipo == 1)
    {
        lista_imprimir((LISTA *)conjunto->estrutura);
    }
    printf("\n");
}

/*
    Ideia de Alocação de Memória para Lista:
        - Para união de conjuntos, o pior caso de uso de memória é quando todos os elementos de A são diferentes dos elementos de B
        - Nota-se isso pela relação: A união B = A + B - A intersecção B, o que fica A união B = A + B, Dado A intesecção B = 0
        - Portanto, aloca-se espaço para o número de elementos de A + os de B
*/
Conjunto *uniao_conjuntos(Conjunto *conjunto1, Conjunto *conjunto2)
{
    Conjunto *resultado;

    if (conjunto1->tipo == 0)
    {
        resultado = criar_conjunto(conjunto1->tipo, 0);
        resultado->estrutura = uniao_arvores_avl((ArvoreAVL *)conjunto1->estrutura, (ArvoreAVL *)conjunto2->estrutura);
    }
    else if (conjunto1->tipo == 1)
    {
        resultado = criar_conjunto(conjunto1->tipo, conjunto1->tam + conjunto2->tam);
        resultado->estrutura = lista_uniao((LISTA *)conjunto1->estrutura, (LISTA *)conjunto2->estrutura);
    }
    return resultado;
}
/*
    Ideia de Alocação de Memória:
        - Para interseção de conjuntos, no que tange pior caso de memória, o pior caso é quando todos os elementos de um conjunto pertencem ao outro
        - Portanto, aloca-se espaço para o número de elementos do menor conjunto
*/
Conjunto *intersecao_conjuntos(Conjunto *conjunto1, Conjunto *conjunto2)
{
    Conjunto *resultado;

    if (conjunto1->tipo == 0)
    {
        resultado = criar_conjunto(conjunto1->tipo, 0);
        if (conjunto1->tam >= conjunto2->tam)
        {
            resultado->estrutura = intersecao_arvores_avl((ArvoreAVL *)conjunto2->estrutura, (ArvoreAVL *)conjunto1->estrutura);
        }
        else
        {
            resultado->estrutura = intersecao_arvores_avl((ArvoreAVL *)conjunto1->estrutura, (ArvoreAVL *)conjunto2->estrutura);
        }
    }
    else if (conjunto1->tipo == 1)
    {
        if (conjunto1->tam >= conjunto2->tam)
        {
            resultado = criar_conjunto(conjunto1->tipo, conjunto2->tam);
        }
        else
        {
            resultado = criar_conjunto(conjunto1->tipo, conjunto1->tam);
        }
        resultado->estrutura = lista_intersecao((LISTA *)conjunto1->estrutura, (LISTA *)conjunto2->estrutura);
    }
    return resultado;
}