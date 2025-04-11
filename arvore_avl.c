#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore_avl.h"

/*
Criação de nó
Parâmetro: recebe a chave que estara no nó
Funcionamento: aloca espaço para o conteudo do nó e os inicializa caso o nó seja de fato criado
*/

NO *criar_no(int chave)
{
    NO *no = (NO *)malloc(sizeof(NO));
    if (no)
    {
        no->direita = no->esquerda = NULL;
        no->altura = 0;
        no->chave = chave;
    }
    return no;
}

/*
Criação de arvore
Parametro: //
Funcionamento: aloca espaço para o conteudo da arvore e os inicializa caso a arvore seja de fato criada
*/
ArvoreAVL *criar_arvore_avl()
{
    ArvoreAVL *arv = (ArvoreAVL *)malloc(sizeof(ArvoreAVL));
    if (arv)
        arv->raiz = NULL;
    return arv;
}

/*
Altura de um nó
Parametro: nó a ser verificado
Funcionamento: retorna a altura armazenada do nó ou retorna -1 caso seja um nó nulo
*/
static int altura(NO *no)
{
    return no ? no->altura : -1; // nó nulo tem como padrão altura -1
}
/*
Atualização da altura de um nó
Parametro: nó a ser atualizado
Funcionamento: atualiza a altura armazenada de um nó com base na altura dos filhos, verificando o de maior altura e adicionando mais 1
*/
static void atualizar_altura(NO *no)
{
    if (no)
    {
        int altura_esq = altura(no->esquerda);
        int altura_dir = altura(no->direita);
        no->altura = 1 + (altura_esq > altura_dir ? altura_esq : altura_dir);
    }
}

/*
Calcular fator de balanceamento
Parametro: nó a ser verificado
Funcionamento: verifica a diferença de altura entre nós filhos, fornecendo parametro para saber se tal subárvore está balanceada
*/
static int fator_balanceamento(NO *no)
{
    return no ? altura(no->esquerda) - altura(no->direita) : 0; // Diferença entre as alturas dos filhos
}

/*
Rotação direita
Parametro: nó raiz da subárvore a ser rotacionada
Funcionamento: o nó a esquerda será a nova raiz. O filho direito do nó esquerdo se torna filho esquerdo do antido nó raiz. Além disso, é necessário atualizar as alturas dado que a estrutura foi alterada
*/
static NO *rotacao_direita(NO *y)
{
    NO *x = y->esquerda;      // O novo no raiz sera o filho á esquerda
    y->esquerda = x->direita; // o filho direito de x se torna o filho esuqerdo de y
    x->direita = y;           // y se torna filho direito de x

    atualizar_altura(y);
    atualizar_altura(x);

    return x;
}

/*
Rotação esquerda
Parametro: nó raiz da subárvore a ser rotacionada
Funcionamento: o nó a direita será a nova raiz. O filho esquerdo do nó direito se torna filho direito do antido nó raiz. Além disso, é necessário atualizar as alturas dado que a estrutura foi alterada
*/
static NO *rotacao_esquerda(NO *x)
{
    NO *y = x->direita;       // O novo no sera o filho a direita
    x->direita = y->esquerda; // o filjo esquerdo de y se torna o filho direito
    y->esquerda = x;          // x se torna o filho esquerdo de y

    atualizar_altura(x);
    atualizar_altura(y);

    return y;
}

/*
Balancear subarvore
Parametro: nó raiz da subárvore
Funcionamento: verifica-se o fator de balanceamento da arvore. Caso o fator ultrapasse 1 ou -1, significa que a arvore está desbalanceada.
Para balancear, as rotações são utilizadas a fim de equilibrar a diferença de altura entre a subarvore esquerda e direita.
*/
static NO *balancear(NO *no)
{
    if (!no) return no;

    int fb = fator_balanceamento(no); // Calcula o fator de balanceamento

    // Caso de desbalanceamento à esquerda
    if (fb > 1)
    {
        if (fator_balanceamento(no->esquerda) < 0) // Caso de rotação dupla (LR)
        {
            no->esquerda = rotacao_esquerda(no->esquerda); // Rotação adicional para rotação dupla
        }
        return rotacao_direita(no); // Rotação simples à direita
    }

    // Caso de desbalanceamento à direita
    if (fb < -1)
    {
        if (fator_balanceamento(no->direita) > 0) // Caso de rotação dupla (RL)
        {
            no->direita = rotacao_direita(no->direita); // Rotação adicional para rotação dupla
        }
        return rotacao_esquerda(no); // Rotação simples à esquerda
    }

    return no; // Retorna o nó balanceado
}

/*
Apagar arvore (apagar_arvore_avl e apagar_no)
Parametro: arvore a ser apagada
Funcionamento: antes de apagar a arvore, é necessário verificar se tem elemento, os quais precisam ser apagados.
Caso tenha, a função auxiliar percorre a arvore apagando os elementos de baixo para cima (percurso pós-ordem).
Após isso, enfim apaga-se a arvore.
*/

void apagar_no(NO **raiz)
{
    if (*raiz)
    {
        apagar_no(&((*raiz)->esquerda)); // apaga os nos a esquerda
        apagar_no(&((*raiz)->direita));  // apaga os nos a direita
        free(*raiz);
        *raiz = NULL; // Libera o no atual
    }
}

void apagar_arvore_avl(ArvoreAVL **arv)
{
    if (*arv) //se a arvore não tem espaço alocado, então se faz necessário desalocar
    {
        if ((*arv)->raiz) // se a arvore não tiver nós, o algorimto pula o processo de apagar nós
        {
            apagar_no(&((*arv)->raiz));
        }
        free(*arv);
        *arv = NULL;
    }
}

/*Imprimir nó
Parâmetro: raiz do nó que será impresso
Funcionamento: percorre a subárvore de maneira in-order (ordem simétrica), ou seja:
Chama recursivamente a função para o nó filho esquerdo.
Imprime a chave do nó atual.
Chama recursivamente a função para o nó filho direito. Dessa forma, os elementos são exibidos em ordem crescente. */

void imprimir_no(NO *raiz)
{
    if (raiz)
    {
        imprimir_no(raiz->esquerda);
        printf("%d ", raiz->chave);
        imprimir_no(raiz->direita);
    }
}

/*imprimir_arvore_avl
Parâmetros: Recebe a árvore AVL (arv).
Funcionamento:
Imprime os elementos da árvore em ordem crescente.
Utiliza a função auxiliar imprimir_no para percorrer a árvore em ordem simétrica.*/

void imprimir_arvore_avl(ArvoreAVL *arv)
{
    printf("{");
    imprimir_no(arv->raiz);
    printf("}");
}

/*
Inserção de elemento (inserir_arvore_avl e inserir_no)
Parametro: A arvore que receberá um elemento e o elemento
Funcionamento: após verificar se a árvore existe, o nó com o elemento é criado e assim busca-se a posição em que será colocado o nó.
Caso o elemento for maior que a chave da raiz atual, compara-se o elemento com o filho direito;
Caso o elemento for menor que a chave da raiz atual, compara-se o elemento com o filho esquerdo;
Caso a raiz atual for nula, esta será a posição do nó. Após isso, pela volta da recursão, todos os nós acessados são redefinidos.
*/

NO *inserir_no(NO *raiz, NO *no)
{
    // Inserção recursiva á esquerda ou a direita
    if (!raiz)
        raiz = no;

    if (no->chave < raiz->chave)
        raiz->esquerda = inserir_no(raiz->esquerda, no);
    else if (no->chave > raiz->chave)
        raiz->direita = inserir_no(raiz->direita, no);
    else
        return raiz;

    atualizar_altura(no); // Atualiza a altura do nó atual
    return balancear(raiz); // Balanceia a arvore apos a inserção
}

/*inserir_arvore_avl
Parâmetros: Recebe um ponteiro para uma árvore AVL (arv) e um inteiro (elemento) que será inserido.
Funcionamento:
Verifica se a árvore AVL existe (arv não é nula).
Cria um nó com o valor fornecido (criar_no).
Insere o nó na árvore utilizando a função auxiliar inserir_no, que executa a lógica de inserção balanceada.
Retorna true se o nó foi inserido com sucesso, ou false se houve falha na criação do nó.*/

bool inserir_arvore_avl(ArvoreAVL *arv, int elemento)
{
    if (arv)
    {
        NO *no = criar_no(elemento);
        if (no)
        {
            arv->raiz = inserir_no(arv->raiz, no);
            return true;
        }
        return false;
    }
}

/*remover_no
Parâmetros: Recebe a raiz de uma subárvore (raiz) e o elemento a ser removido.
Funcionamento:
Procura o nó a ser removido comparando a chave do elemento com a chave da raiz.
Se o elemento não tem filhos ou tem apenas um, remove-o e retorna o filho restante (ou NULL).
Se o nó tem dois filhos, substitui a chave pela do menor elemento da subárvore direita e remove este elemento.
Após a remoção, balanceia a subárvore.*/

NO *remover_no(NO *raiz, int elemento)
{
    if (!raiz)
        return NULL; /// o elemento não foi encontrado

    if (elemento < raiz->chave)
    {
        raiz->esquerda = remover_no(raiz->esquerda, elemento);
    }
    else if (elemento > raiz->chave)
    {
        raiz->direita = remover_no(raiz->direita, elemento);
    }
    else
    {
        // no encontrado
        if (!raiz->esquerda || !raiz->direita)
        {
            NO *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            free(raiz);
            return temp; // Retorna o único filho (ou NULL)
        }
        else
        {
            // Nó com dois filhos: substitui pelo menor elemento da subárvore direita
            NO *temp = raiz->direita;
            while (temp->esquerda)
                temp = temp->esquerda;
            raiz->chave = temp->chave;
            raiz->direita = remover_no(raiz->direita, temp->chave);
        }
    }

    return balancear(raiz); // Balanceia a árvore após a remoção
}

/*remover_arvore_avl
Parâmetros: Recebe um ponteiro para uma árvore AVL (arv) e o elemento a ser removido.
Funcionamento:
Utiliza a função remover_no para encontrar e remover o elemento da árvore.
Retorna true se a remoção foi bem-sucedida ou false se o elemento não foi encontrado.*/

bool remover_arvore_avl(ArvoreAVL *arv, int elemento)
{
    if (pertence_arvore_avl(arv, elemento))
    {
        arv->raiz = remover_no(arv->raiz, elemento);
        return true;
    }
    return false;
}

/*Pertence nó
Parâmetro: nó raiz da subárvore e o elemento a ser buscado.
Funcionamento: verifica se um elemento está presente na subárvore iniciada pelo nó dado.
Caso o nó seja nulo, retorna 0, indicando que o elemento não foi encontrado.
Caso o elemento seja igual à chave do nó atual, retorna 1, indicando que o elemento foi encontrado.
Caso o elemento seja menor que a chave do nó atual, a busca continua recursivamente no filho esquerdo.
Caso o elemento seja maior que a chave do nó atual, a busca continua recursivamente no filho direito.*/

bool pertence_no(NO *raiz, int elemento)
{
    if (!raiz)
        return 0; // Elemento não encontrado
    if (elemento == raiz->chave)
        return 1; // Elemento encontrado
    if (elemento < raiz->chave)
        return pertence_no(raiz->esquerda, elemento);
    return pertence_no(raiz->direita, elemento);
}

/*pertence_arvore_avl
Parâmetros: Recebe a árvore AVL (arv) e o elemento a ser verificado.
Funcionamento:
Utiliza a função auxiliar pertence_no para percorrer a árvore recursivamente.
Retorna true se o elemento estiver na árvore e false caso contrário.
*/
bool pertence_arvore_avl(ArvoreAVL *arv, int elemento)
{
    return pertence_no(arv->raiz, elemento);
}

/*Uniao_no
Parâmetros: dois nós raiz (raiz1 e raiz2) representando as subárvores a serem unidas.
Funcionamento: combina os elementos das subárvores enraizadas em raiz1 e raiz2 em uma única árvore.

Se raiz1 for nulo, retorna raiz2, pois não há elementos em raiz1.
Se raiz2 for nulo, retorna raiz1, pois não há elementos em raiz2.
Caso contrário, insere o elemento do nó raiz de raiz2 na subárvore de raiz1.
Recursivamente aplica a união para os filhos esquerdo e direito de raiz2 com raiz1.
Retorna raiz1, que agora contém os elementos das duas subárvores combinadas.*/

NO *uniao_no(NO *raiz1, NO *raiz2)
{
    if (!raiz1)
        return raiz2;
    if (!raiz2)
        return raiz1;

    // Adiciona todos os elementos de raiz2 em raiz1
    raiz1 = inserir_no(raiz1, criar_no(raiz2->chave));
    raiz1 = uniao_no(raiz1, raiz2->esquerda);
    raiz1 = uniao_no(raiz1, raiz2->direita);

    return raiz1;
}

/*uniao_arvores_avl
Parâmetros: Duas árvores AVL (arv1 e arv2).
Funcionamento:
Combina os elementos de arv2 na árvore arv1.
Utiliza a função auxiliar uniao_no para percorrer e inserir os elementos de arv2 em arv1.*/

ArvoreAVL *uniao_arvores_avl(ArvoreAVL *arv1, ArvoreAVL *arv2)
{
    if (!arv1 || !arv2)
        return arv1 ? arv1 : arv2;
    arv1->raiz = uniao_no(arv1->raiz, arv2->raiz);
    return arv1;
}

/*intersecao_no
Parâmetros: dois nós raiz (raiz1 e raiz2) das arvores e a raiz do resultado (intersecao).
Funcionamento: verifica os elementos repetidos presentes nas subárvores enraizadas em raiz1 e raiz2 e os armazena.

Se raiz1 ou raiz2 for nulo, não modifica a intersecao.
Caso contrário, busca-se o elemento de raiz1 na arvore de raiz2. Caso estiver, insere o elemento na arvore intersecao.
Recursivamente, o algoritmo acessa outros elementos por meio de raiz1 e verifica se estão na arvore de raiz2. 
Retorna intersecao quando acessar toda raiz1.*/

// Realiza a interseção de duas árvores AVL
NO *intersecao_no(NO *intersecao, NO *raiz1, NO *raiz2) {
    if (!raiz1 || !raiz2) 
        return intersecao;  // Retorna a árvore atual, não NULL
    
    if (pertence_no(raiz2, raiz1->chave)) {
        intersecao = inserir_no(intersecao, criar_no(raiz1->chave));
    }
    
    intersecao = intersecao_no(intersecao, raiz1->esquerda, raiz2);
    intersecao = intersecao_no(intersecao, raiz1->direita, raiz2);
    
    return intersecao;
}

/*intersecao_arvores_avl
Parâmetros: Duas árvores AVL (arv1 e arv2).
Funcionamento:
Identifica os elementos que estão presentes em ambas as árvores.
Utiliza a função intersecao_no para construir uma nova árvore com os elementos comuns.*/

ArvoreAVL *intersecao_arvores_avl(ArvoreAVL *arv1, ArvoreAVL *arv2) {
    ArvoreAVL *intersecao = criar_arvore_avl();
    if (!arv1 || !arv2) return intersecao;
    
    intersecao->raiz = intersecao_no(intersecao->raiz, arv1->raiz, arv2->raiz);
    return intersecao;
}
