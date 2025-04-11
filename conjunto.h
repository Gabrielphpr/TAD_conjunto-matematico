#ifndef CONJUNTO_H
#define CONJUNTO_H

typedef struct Conjunto Conjunto;

// Cria um conjunto com a estrutura que for escolhida ( 1: avl, 2: (a q vcs decidirem :
Conjunto *criar_conjunto(int tipo, int tam); // int tam caso a lista seja dinamica
// Apaga o conjunto
void apagar_conjunto(Conjunto *conjunto);

// Insere um elemento
bool inserir_elemento(Conjunto *conjunto, int elemento);

// Remove um elemento
bool remover_elemento(Conjunto *conjunto, int elemento);

// Verifica se o elemento pertence ao conjunto
bool pertence_conjunto(Conjunto *conjunto, int elemento);

// Imprime o conjunto
void imprimir_conjunto(Conjunto *conjunto);

// uni dois conjuntos
Conjunto *uniao_conjuntos(Conjunto *conjunto1, Conjunto *conjunto2);

// intersecção de conjuntos
Conjunto *intersecao_conjuntos(Conjunto *conjunto1, Conjunto *conjunto2);

#endif