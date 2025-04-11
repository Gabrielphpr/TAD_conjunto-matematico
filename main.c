#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "conjunto.h"
int main(int argc, char *argv[])
{
  Conjunto *A, *B;
  int n_a, n_b, x;
  int op;
  int tipo;

  scanf("%d", &tipo); // 0 -> ED1, 1 -> ED2

  scanf(" %d %d", &n_a, &n_b);

  A = criar_conjunto(tipo, n_a);
  B = criar_conjunto(tipo, n_b);

  for (int i = 0; i < n_a; i++)
  {
    scanf("%d", &x);
    inserir_elemento(A, x);
  }

  for (int i = 0; i < n_b; i++)
  {
    scanf("%d", &x);  
    inserir_elemento(B, x);
  }

  printf("\ninsercoes feitas!\n");
  imprimir_conjunto(A);
  printf("\n");
  imprimir_conjunto(B);
  printf("\n");

  scanf("%d", &op);

  switch (op)
  {
  case 1:
  {
    // pertence
    int elemento_procurado;
    scanf("%d", &elemento_procurado);
    
    if (pertence_conjunto(A, elemento_procurado))
    {
      printf("Pertence.");
    }
    else
    {
      printf("Nao pertence.");
    }
    break;
  }
  case 2:
  {
    // união
    Conjunto *uniao = uniao_conjuntos(A, B);
    imprimir_conjunto(uniao);
    break;
  }
  case 3:
  {
    // intersecção
    Conjunto *intersecao = intersecao_conjuntos(A, B);
    imprimir_conjunto(intersecao);
    break;
  }
  case 4:
  {
    // remoção (considerando-se apenas do conjunto A)
    int elemento_removido;
    scanf(" %d", &elemento_removido);
    if(!remover_elemento(A, elemento_removido)) printf("elemento nao esta no conjunto\n");
    imprimir_conjunto(A);
  }
  }
  apagar_conjunto(A);
  apagar_conjunto(B);
  return 0;
}
