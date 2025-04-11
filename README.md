# Tipo Abstrato de Dado: Conjunto (Implementação com Árvore AVL e Lista Sequencial Ordenada)

Este projeto implementa um Tipo Abstrato de Dados (TAD) Conjunto utilizando duas estruturas de dados distintas: Árvores AVL e Listas Sequenciais Ordenadas. A escolha dessas estruturas foi baseada em suas características de busca eficiente, que são fundamentais para operações em conjuntos.

As principais operações implementadas são:
- Inserção e remoção de elementos
- Função pertece (busca)
- União e Interseção

## Árvore AVL

A Árvore AVL foi escolhida por oferecer um balanceamento automático, garantindo que as operações básicas tenham complexidade O(log n) mesmo no pior caso. A altura média de uma árvore AVL é de aproximadamente 1.44*log(n), o que a torna mais eficiente que árvores rubro-negras para buscas.

## Lista Sequencial Ordenada

A lista sequencial ordenada utiliza um vetor dinâmico com elementos sempre mantidos em ordem. Apesar de inserções e remoções terem complexidade O(n) no caso médio, a busca binária proporciona operações de pertence com O(log n). As vantagens da lista aparecem especialmente quando os elementos são inseridos em ordem crescente (inserção O(1)) e quando observa-se que a maioria das remoções ocorre no final da lista (remoção O(1))

## Complexidade das Operações

### Operações Básicas

Para a Árvore AVL:
- Busca: O(log n)
- Inserção: O(log n)
- Remoção: O(log n)

Para a Lista Sequencial:
- Busca: O(log n) (busca binária)
- Inserção: O(n) (busca + deslocamento)
- Remoção: O(n) (busca + deslocamento)

### Operações de Conjunto

A implementação das operações de conjunto difere entre as estruturas:

**União:**
- AVL: O(n log n) - Insere todos elementos de uma árvore na outra
- Lista: O(n+m) - Percorre ambas listas em paralelo

**Interseção:**
- AVL: O(n log n) - Busca cada elemento de uma árvore na outra
- Lista: O(n+m) - Percorre ambas listas em paralelo

## Detalhes de Implementação

O projeto utiliza um sistema flexível onde o usuário pode escolher qual estrutura deseja utilizar (0 para AVL, 1 para Lista) no momento da criação do conjunto. A estrutura `Conjunto` contém um ponteiro void que pode apontar para qualquer uma das duas implementações.

## Casos testes

Foi desenvolvido vários casos teste que testam as funcionalidades de ambas as implementações. Para saber mais, leia o `README.txt` dentro da pasta `casos`

## Considerações Finais

Este projeto demonstra como diferentes estruturas de dados podem ser utilizadas para implementar o mesmo TAD, cada uma com suas vantagens e desvantagens. A Árvore AVL se mostra superior para conjuntos dinâmicos com muitas operações de inserção/remoção, enquanto a Lista Sequencial é mais eficiente para conjuntos estáticos ou quando os elementos são inseridos em ordem.

## Licença
Este projeto está licenciado sob a licença MIT - veja o arquivo [LICENSE](LICENSE) para detalhes.
