#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

/*
Struct Lista: equivale a uma Lista Linear Sequencial Ordenada e Dinamicamente Alocada
Possui um indicador para início, fim , o tamanho atual da lista e o tamanho máximo que ela suporta, além da própria lista em formato de vetor
*/
struct lista_
{
    int *lista;
    int inicio;
    int fim;
    int tamanho_atual;
    int tamanho_maximo;
};
typedef struct lista_ LISTA;
//////CRIAÇÃO /////////
/*
Criação da lista
Parâmetro: Recebe o parâmetro "n", tamanho máximo da lista
Ideia: Tenta alocar espaço para a struct lista e para a própria lista dentro da struct, se conseguir, define os parâmetros iniciais
*/
LISTA *lista_criar(int n)
{
    /*Pré-condição: existir espaço na memória*/
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    // Aloca dinamicamente o espaço necessário para a lista (equivale ao tamanho do conjunto, que é dado)
    lista->lista = (int *)malloc(n * sizeof(int));

    if (lista != NULL && lista->lista != NULL)
    {
        lista->inicio = 0;
        lista->fim = lista->inicio; /// lista vazia
        lista->tamanho_atual = 0;
        lista->tamanho_maximo = n;
    }
    return lista;
}

///// INSERÇÃO ////////
/*
    Inserção em posição específica, função auxiliar da Inserção
    Parâmetros: lista, posição a ser inserido e o item a ser inserido
    Ideia: dada a posição, realiza shift right dos elementos maiores que o elemento na posição "pos"
*/
bool lista_inserir_posicao(LISTA *l, int pos, int item)
{
    // verifica se existe espaço e se a posição está na lista
    if ((pos != ERRO && !lista_cheia(l)) && (pos <= l->fim))
    {
        // percorre a lista começando do fim até a posição
        for (int i = (l->fim - 1); i >= pos; i--)
        {
            // desloca para direita cada um dos elementos depois da posição
            l->lista[i + 1] = l->lista[i];
        }
        // insere o número na posição correta
        l->lista[pos] = item;
        l->fim++;
        l->tamanho_atual++;
        return true;
    }
    // se as condições não forem corretas, não insere na lista
    return false;
}
/*
    Busca Binária de posição para inserção, função auxiliar para Inserção
    Parâmetros:  lista e elemento a ser inserido
    Ideia: por meio de uma busca binária adaptada, divide sucessivamente o vetor ao meio,
    procurando a posição ou na metade inferior ou superior, e retorna uma posição atrás do elemento exatamente maior que o elemento a ser inserido
*/
int lista_busca_binaria_insercao(LISTA *l, int elemento_inserido)
{
    if (l == NULL)
    {
        return ERRO;
    }
    int inf = 0;
    int sup = l->fim - 1;
    int meio, valor;

    while (inf <= sup)
    {
        meio = (inf + sup) / 2;
        valor = l->lista[meio];
        if (valor == elemento_inserido)
        {
            return ERRO; /// note que aqui o elemento já existe, por o conjunto tratar elementos únicos, não deve ser inserido
        }
        else if (valor > elemento_inserido)
        {
            sup = meio - 1;
        }
        else
        {
            inf = meio + 1;
        }
    }
    // retorna indice de onde o elemento deve ser inserido
    return inf;
}

/*
Inserir na Lista
Parâmetros: Recebe a lista e o elemento a ser inserido
Ideia: acha a posicao do elemento a ser inserido e insere naquela posição específica
*/
bool lista_inserir(LISTA *l, int elemento_procurado)
{
    // Acha a posição do elemento a ser inserido
    int posicao = lista_busca_binaria_insercao(l, elemento_procurado);
    // se o elemento já existe no conjunto, não pode ser inserido 2 vezes
    if (posicao == ERRO)
    {
        return false;
    }
    return (lista_inserir_posicao(l, posicao, elemento_procurado));
}

////// BUSCA E PERTENCIMENTO ////
/*
    Busca
    Parâmetros: lista e elemento a ser procurado (x)
    Ideia: divide o vetor ao meio sucessivamente e procura o elemento ou na metade superior ou inferior
*/
int lista_busca_binaria(LISTA *l, int x)
{
    if (l == NULL || lista_vazia(l))
    {
        return ERRO;
    }

    int inf = 0;
    int sup = l->fim - 1;
    int meio, valor;
    while (inf <= sup)
    {
        meio = (inf + sup) / 2;
        valor = l->lista[meio];

        if (valor == x)
        {
            return meio;
        }
        else if (valor > x)
        {
            sup = meio - 1;
        }
        else
        {
            inf = meio + 1;
        }
    }
    return ERRO;
}
/*
    Pertencimento ao conjunto: retorna true caso pertence, caso contrário false
    Parâmetros: lista e elemento a ser procurado
*/
bool lista_pertence(LISTA *l, int chave)
{
    if (lista_busca_binaria(l, chave) != ERRO)
    {
        return true;
    }
    return false;
}

//////// UNIÃO /////////////

/*
    União
    Parâmetros: duas listas a serem unidas
    Ideia: percorrer as duas listas paralelamente (objetivo é criar uma complexidade O(n)).
    Vai adicionando cada elemento do conjunto sempre verificando se os elementos não são iguais, se são iguais, printa-se só uma vez.
    A mesma ideia é usada para intersecção, só que printa-se apenas os elementos que pertencem aos dois conjuntos.
    Quando uma lista acaba de ser percorrida, printa-se os elementos da outra (que serão maiores que o maior elemento da lista x)
    A ideia advém da propriedade: A união B = A + B - (A intersecção B)
*/
LISTA *lista_uniao(LISTA *lista1, LISTA *lista2)
{
    if (lista1 == NULL && lista2 == NULL)
    {
        return NULL;
    }
    if (lista1 == NULL)
    {
        return lista2;
    }
    if (lista2 == NULL)
    {
        return lista1;
    }

    LISTA *lista_resultado;
    // cria-se uma lista com o maior tamanho das 2, dado que esse é o maior tamanho para interseccao
    lista_resultado = lista_criar(lista1->tamanho_atual + lista2->tamanho_atual);

    int i = 0, j = 0;
    while (i < lista1->tamanho_atual && j < lista2->tamanho_atual)
    {
        if (lista1->lista[i] == lista2->lista[j])
        {
            lista_inserir(lista_resultado, lista1->lista[i]);
            i++;
            j++;
        }
        else if (lista1->lista[i] > lista2->lista[j])
        {
            lista_inserir(lista_resultado, lista2->lista[j]);
            j++;
        }
        else
        {
            lista_inserir(lista_resultado, lista1->lista[i]);
            i++;
        }
    }

    // adiciona os elementos restantes de lista1, se existirem
    while (i < lista1->tamanho_atual)
    {
        lista_inserir(lista_resultado, lista1->lista[i]);
        i++;
    }

    // adiciona os elementos restantes de lista2, se existirem
    while (j < lista2->tamanho_atual)
    {
        lista_inserir(lista_resultado, lista2->lista[j]);
        j++;
    }
    // para usar apenas o espaço de memória desejado, vamos utilizar a função "realloc"
    if (lista_resultado->tamanho_atual != 0)
    {
        lista_realocar(lista_resultado);
    }
    return lista_resultado;
}

///// INTERSECÇÃO ///////
/*
    Intersecção
    Parâmetros: duas listas a serem achados os elementos em comum
    Ideia: mesma ideia para união, de percorrer os vetores paralelamente, (para Big Oh de O(n)), mas apenas printa-se os elementos em comum (A intersecção B)
*/
LISTA *lista_intersecao(LISTA *lista1, LISTA *lista2)
{
    if (lista1 == NULL || lista2 == NULL)
    {
        return NULL;
    }
    LISTA *lista_resultado;
    // cria-se uma lista com o menor tamanho das 2, dado que esse é o maior tamanho para interseccao
    if (lista1->tamanho_atual >= lista2->tamanho_atual)
    {
        lista_resultado = lista_criar(lista2->tamanho_atual);
    }
    else
    {
        lista_resultado = lista_criar(lista1->tamanho_atual);
    }
    int i = 0, j = 0;
    while (i < lista1->tamanho_atual && j < lista2->tamanho_atual)
    {
        if (lista1->lista[i] == lista2->lista[j])
        {
            lista_inserir(lista_resultado, lista1->lista[i]);
            i++;
            j++;
        }
        else if (lista1->lista[i] > lista2->lista[j])
        {
            j++;
        }
        else
        {
            i++;
        }
    }
    // para usar apenas o espaço de memória desejado, vamos utilizar a função "realloc"
    if (lista_resultado->tamanho_atual != 0)
    {
        lista_realocar(lista_resultado);
    }
    return lista_resultado;
}
////// REMOÇÃO ////////
/*
    Remover
    Parâmetros: lista e elemento a ser removido
    Ideia: utiliza-se a função de "Busca", por busca binária, para achar a posição do elemento.
    A partir disso, se encontrado, o elemento é retirado e realiza-se shift left dos elementos à direita do elemento removido
*/
bool lista_remover(LISTA *l, int x)
{
    /* if(l == NULL || !lista_vazia(l)){
         return ERRO;
     }*/
    int posicao;
    posicao = lista_busca_binaria(l, x);
    if (posicao == ERRO)
    {
        return false;
    }
    // Shift para a esquerda
    for (int i = posicao; i < (l->fim); i++)
    {
        l->lista[i] = l->lista[i + 1];
    }
    if (l->lista[l->fim] != -1)
    {
        // Apenas libere memória se os elementos forem ponteiros alocados
        l->lista[l->fim] = -1;
    }
    l->lista[l->fim] = -1;
    l->fim--;
    l->tamanho_atual--;
    return true;
}
///// APAGAR ///////
/*
    Apagar
    Parâmetro: lista
    Ideia: se a lista não for nula, desaloca dinamicamente a memória do vetor dinamico que representa a lista
*/
bool lista_apagar(LISTA **l)
{
    if (l == NULL || *l == NULL)
    {
        return false;
    }

    if ((*l)->lista != NULL)
    {
        free((*l)->lista);
    }

    free(*l);
    *l = NULL;

    return true;
}

/////// IMPRIMIR ////////
/*
    Imprimir
    Parâmetro: lista
    Ideia: percorre a lista da posição 0 até o tamanho atual dela
*/
void lista_imprimir(LISTA *l)
{
    printf("{");
    if (l == NULL || lista_vazia(l))
    {
        printf("}");
        return;
    }
    for (int i = 0; i < l->tamanho_atual; i++)
    {
        printf("%d ", l->lista[i]);
    }
    printf("}");
}

/////// Funções Auxiliares ////////

/*
    Tamanho da Lista
    Parâmetro: lista
    Ideia: retorna o tamanho da lista
*/
int lista_tamanho(LISTA *l)
{
    if (l != NULL)
    {
        return l->tamanho_atual;
    }
    return ERRO;
}
/*
    Realocar memória para a Lista
    Parâmetro: lista
    Ideia: tem o objetivo de não disperdiçar espaço de memória. Funções como intersecção e união utilizam memória a mais para realizar seus processos,
    e precisam de um "realloc" ao final desse processo. Para isso, a função realoca memória para o "tamanho atual" da lista
*/
bool lista_realocar(LISTA *l)
{
    if (l == NULL)
    {
        printf("Erro ao realocar, L nulo");
        return false;
    }
    int *nova_lista = (int *)realloc(l->lista, l->tamanho_atual * sizeof(int));
    if (nova_lista == NULL)
    {
        printf("Erro ao realocar");
        return false;
    }
    l->lista = nova_lista;
    l->fim = l->tamanho_atual;
    // printf("\n Realocar deu sucesso!!");
    return true;
}
/*
    Lista Vazia
    Parâmetro: lista
    Ideia: se o tamanho atual da lista é 0, ela está vazia
*/
bool lista_vazia(LISTA *l)
{
    if (l != NULL)
    {
        if (l->tamanho_atual == 0)
        {
            return true;
        }
        return false;
    }
    return true;
}

/*
    Lista Cheia
    Parâmetro: lista
    Ideia: se o tamanho máximo da lista é igual ao tamanho máximo da lista, ela está cheia
*/
bool lista_cheia(LISTA *l)
{
    if (l != NULL)
    {
        if (l->tamanho_atual == l->tamanho_maximo)
        {
            return true;
        }
    }
    return false;
}
