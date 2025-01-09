/**
 * Implementação de Árvore Binária em C
 * 
 * Este código implementa uma árvore binária básica com as seguintes funcionalidades:
 * - Inserir nós na árvore
 * - Navegar em ordem (in-order traversal)
 * - Imprimir os nós da árvore
 * 
 * Conceito:
 * A árvore binária organiza os nós de forma que:
 * - Os valores menores que o nó raiz ficam à esquerda.
 * - Os valores maiores que o nó raiz ficam à direita.
 */

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore binária
struct No {
    int numero;
    struct No *esquerda;
    struct No *direita;
};

/**
 * Insere um novo nó na árvore binária
 * @param raiz Ponteiro para a raiz da árvore
 * @param numero Valor a ser inserido
 * @return Ponteiro atualizado da raiz
 */
struct No* inserirArvore(struct No* raiz, int numero) {
    if (!raiz) {
        raiz = (struct No*)malloc(sizeof(struct No));
        if (!raiz) {
            fprintf(stderr, "Erro ao alocar memória.\n");
            exit(EXIT_FAILURE);
        }
        raiz->numero = numero;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
        return raiz;
    }
    if (numero < raiz->numero)
        raiz->esquerda = inserirArvore(raiz->esquerda, numero);
    else
        raiz->direita = inserirArvore(raiz->direita, numero);
    return raiz;
}

/**
 * Navegação em ordem (in-order traversal)
 * @param raiz Ponteiro para a raiz da árvore
 */
void navegarInOrdem(struct No* raiz) {
    if (!raiz) return;
    navegarInOrdem(raiz->esquerda);
    printf("%d ", raiz->numero);
    navegarInOrdem(raiz->direita);
}

/**
 * Função principal para testar a implementação
 */
int main() {
    struct No* raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80};

    // Inserindo valores na árvore
    for (int i = 0; i < 7; i++) {
        raiz = inserirArvore(raiz, valores[i]);
    }

    // Navegando e imprimindo a árvore em ordem
    printf("Árvore Binária em Ordem: ");
    navegarInOrdem(raiz);
    printf("\n");

    return 0;
}