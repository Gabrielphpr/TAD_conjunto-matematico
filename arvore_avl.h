#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H
#include <stdbool.h>
typedef struct ArvoreAVL ArvoreAVL;


/*
Struct No: representa o elemento da arvore, guardando consigo suas conexões a outros elementos, além da sua altura e do conteudo (a chave)
Possui uma referencia ao nó direito, nó esquerdo, seu conteudo (chave) e a altura relativa ao nó folha conexos a esse nó
*/

typedef struct No
{
    int chave;
    struct No *esquerda;
    struct No *direita;
    int altura;
} NO;

/*
Struct Arvore AVL: Com o sistema de nós, esquivale a uma arvore binaria de busca com sistema rebalanceamento da AVL
A principio, é somente uma referênia ao nó raiz, com arestas para outros nós, que levam aos outros nós e assim por diante
*/

struct ArvoreAVL
{
    NO *raiz;
};
// Cria uma árvore AVL
ArvoreAVL *criar_arvore_avl();

// Apaga a árvore AVL
void apagar_arvore_avl(ArvoreAVL **raiz);

// Insere um elemento na árvore AVL

bool inserir_arvore_avl(ArvoreAVL *arv, int elemento);

// Remove um elemento da árvore AVL
bool remover_arvore_avl(ArvoreAVL *arv, int elemento);

// Verifica se um elemento pertence à árvore AVL
bool pertence_arvore_avl(ArvoreAVL *raiz, int elemento);

// Imprime os elementos da árvore AVL
void imprimir_arvore_avl(ArvoreAVL *raiz);

// Realiza a união de duas árvores AVL
ArvoreAVL *uniao_arvores_avl(ArvoreAVL *raiz1, ArvoreAVL *raiz2);

// Realiza a interseção de duas árvores AVL
ArvoreAVL *intersecao_arvores_avl(ArvoreAVL *raiz1, ArvoreAVL *raiz2);

#endif
