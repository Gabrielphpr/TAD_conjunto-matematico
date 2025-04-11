
#ifndef LISTA_H
#define LISTA_H
#define TAM_MAX 100
// #define inicial 0
#define ERRO -1

typedef struct lista_ LISTA;
LISTA *lista_criar(int n);
bool lista_inserir(LISTA *lista, int item);
bool lista_remover(LISTA *lista, int chave);
int lista_busca_binaria(LISTA *lista, int chave);
int lista_tamanho(LISTA *lista);
bool lista_pertence(LISTA *lista, int chave);
bool lista_vazia(LISTA *lista);
bool lista_cheia(LISTA *lista);
void lista_imprimir(LISTA *lista);
bool lista_apagar(LISTA **lista);
LISTA *lista_uniao(LISTA *lista1, LISTA *lista2);
LISTA *lista_intersecao(LISTA *lista1, LISTA *lista2);
bool lista_realocar(LISTA *lista);
#endif
