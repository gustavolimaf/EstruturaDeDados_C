/**
 * Implementação de Pilha (Stack) em C
 * 
 * Este código implementa uma pilha usando lista encadeada, onde:
 * - Inserções e remoções ocorrem no início (topo) da pilha
 * - Segue o princípio LIFO (Last In, First Out)
 * - Todas as operações têm complexidade O(1)
 */

#include <stdio.h>
#include <stdlib.h>

struct no {
    int numero;
    struct no *proximo;
};

/**
 * Insere um novo número no topo da pilha (push)
 * @param topo Ponteiro para o topo da pilha
 * @param numero Valor a ser inserido
 * @return Novo ponteiro para o topo da pilha
 */
struct no *push(struct no *topo, int numero) {
    struct no *novoNo = (struct no *) malloc(sizeof(struct no));
    
    // Verifica se a alocação foi bem sucedida
    if (novoNo == NULL) {
        fprintf(stderr, "Erro na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    
    novoNo->numero = numero;
    novoNo->proximo = topo;
    return novoNo;
}

/**
 * Remove e retorna o elemento do topo da pilha (pop)
 * @param topo Ponteiro para o topo da pilha
 * @return Novo ponteiro para o topo da pilha
 */
struct no *pop(struct no *topo) {
    // Pilha vazia
    if (topo == NULL) {
        printf("Pilha vazia!\n");
        return NULL;
    }

    // Remove o elemento do topo
    struct no *remover = topo;
    topo = topo->proximo;
    printf("Removido: %d\n", remover->numero);
    free(remover);
    return topo;
}

/**
 * Imprime todos os elementos da pilha (do topo para a base)
 * @param topo Ponteiro para o topo da pilha
 */
void imprimir(struct no *topo) {
    struct no *atual = topo;
    printf("Pilha: ");
    while (atual != NULL) {
        printf("%d ", atual->numero);
        atual = atual->proximo;
    }
    printf("\n");
}

/**
 * Libera toda a memória alocada pela pilha
 * @param topo Ponteiro para o topo da pilha
 */
void liberarPilha(struct no *topo) {
    while (topo != NULL) {
        struct no *remover = topo;
        topo = topo->proximo;
        free(remover);
    }
}

int main() {
    struct no *pilha = NULL;
    int i;
    
    // Exemplo de uso com valores menores para teste
    for (i = 0; i < 10; i++) {
        pilha = push(pilha, i);
    }
    
    printf("Estado inicial da pilha:\n");
    imprimir(pilha);
    
    printf("\nRemovendo elementos:\n");
    for (i = 0; i < 5; i++) {
        pilha = pop(pilha);
    }
    
    printf("\nEstado final da pilha:\n");
    imprimir(pilha);
    
    // Libera a memória antes de encerrar
    liberarPilha(pilha);
    
    return 0;
}