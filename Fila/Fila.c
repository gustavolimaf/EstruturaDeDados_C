/**
 * Implementação de Fila (Queue) em C
 * 
 * Este código implementa uma fila usando lista encadeada, onde:
 * - Novos elementos são inseridos no início (para eficiência)
 * - Remoções ocorrem no final (FIFO - First In, First Out)
 * - Mantém apenas uma referência para o início da fila
 */

#include <stdio.h>
#include <stdlib.h>

struct no {
    int numero;
    struct no *proximo;
};

/**
 * Insere um novo número no início da fila
 * @param inicio Ponteiro para o início da fila
 * @param numero Valor a ser inserido
 * @return Novo ponteiro para o início da fila
 */
struct no *entrar(struct no *inicio, int numero) {
    struct no *novoNo = (struct no *) malloc(sizeof(struct no));
    novoNo->numero = numero;
    novoNo->proximo = inicio;
    return novoNo;
}

/**
 * Remove e retorna o último elemento da fila
 * @param inicio Ponteiro para o início da fila
 * @return Novo ponteiro para o início da fila
 */
struct no *sair(struct no *inicio) {
    // Fila vazia
    if (inicio == NULL) {
        printf("Fila vazia!\n");
        return NULL;
    }

    // Fila com um único elemento
    if (inicio->proximo == NULL) {
        printf("Removido: %d\n", inicio->numero);
        free(inicio);
        return NULL;
    }

    // Encontra o penúltimo elemento
    struct no *penultimo = inicio;
    while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
    }

    // Remove o último elemento
    printf("Removido: %d\n", penultimo->proximo->numero);
    free(penultimo->proximo);
    penultimo->proximo = NULL;
    return inicio;
}

/**
 * Imprime todos os elementos da fila
 * @param inicio Ponteiro para o início da fila
 */
void imprimir(struct no *inicio) {
    struct no *atual = inicio;
    printf("Fila: ");
    while (atual != NULL) {
        printf("%d ", atual->numero);
        atual = atual->proximo;
    }
    printf("\n");
}

/**
 * Exibe menu de opções e retorna a escolha do usuário
 * @return Opção escolhida
 */
int menu() {
    int opcao;
    printf("\n1 - Entrar na fila\n");
    printf("2 - Sair da fila\n");
    printf("3 - Imprimir fila\n");
    printf("4 - Sair do programa\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

int main() {
    struct no *fila = NULL;
    int opcao = 0;
    int numero;

    while (opcao != 4) {
        opcao = menu();
        switch(opcao) {
            case 1:
                printf("Digite o numero: ");
                scanf("%d", &numero);
                fila = entrar(fila, numero);
                break;
            case 2:
                fila = sair(fila);
                break;
            case 3:
                imprimir(fila);
                break;
        }
    }
    return 0;
}