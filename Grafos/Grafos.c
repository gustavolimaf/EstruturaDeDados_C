/**
 * Implementação de Grafos em C
 * 
 * Este código implementa um grafo básico utilizando matriz de adjacência.
 * - Permite construir o grafo com base na entrada do usuário.
 * - Imprime a matriz de adjacência do grafo.
 */

#include <stdio.h>

#define TAMANHO 5

/**
 * Constrói o grafo com base na entrada do usuário
 * @param grafo Matriz de adjacência
 */
void construirGrafo(int grafo[TAMANHO][TAMANHO]) {
    int i, j, adjacencia;
    for (i = 0; i < TAMANHO; i++)
        for (j = 0; j < TAMANHO; j++)
            grafo[i][j] = 0;

    for (i = 0; i < TAMANHO; i++) {
        for (j = 0; j < TAMANHO; j++) {
            if (i != j) {
                printf("Digite 1 se %d é adjacente a %d: ", i, j);
                scanf("%d", &adjacencia);
                grafo[i][j] = adjacencia;
            }
        }
    }
}

/**
 * Imprime a matriz de adjacência do grafo
 * @param grafo Matriz de adjacência
 */
void imprimirGrafo(int grafo[TAMANHO][TAMANHO]) {
    printf("Grafo:\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", grafo[i][j]);
        }
        printf("\n");
    }
}

/**
 * Função principal para testar o grafo
 */
int main() {
    int grafo[TAMANHO][TAMANHO];
    construirGrafo(grafo);
    imprimirGrafo(grafo);
    return 0;
}