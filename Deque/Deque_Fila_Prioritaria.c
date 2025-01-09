/**
 * Implementação de Deque com Fila Prioritária em C
 * 
 * Este código implementa um deque com duas filas:
 * - Fila Preferencial: atendimento prioritário
 * - Fila Normal: atendimento regular
 * 
 * Regra de atendimento:
 * - A cada 5 atendimentos preferenciais, 1 pessoa da fila normal é atendida
 * - Se uma das filas estiver vazia, atende-se a outra fila
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura de um nó da fila
struct no {
    int numero;
    struct no *proximo;
};

// Estrutura do deque com duas filas
struct deque {
    struct no *filaNormal;
    struct no *filaPreferencial;
};

/**
 * Remove e retorna o último elemento de uma fila
 * @param fila Ponteiro para o início da fila
 * @return Novo ponteiro para o início da fila
 */
struct no *sair(struct no *fila) {
    // Fila vazia
    if (fila == NULL) {
        return NULL;
    }
    
    // Fila com um elemento
    if (fila->proximo == NULL) {
        printf("Atendido: %d\n", fila->numero);
        free(fila);
        return NULL;
    }
    
    // Fila com múltiplos elementos
    struct no *penultimo = fila;
    while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
    }
    
    printf("Atendido: %d\n", penultimo->proximo->numero);
    free(penultimo->proximo);
    penultimo->proximo = NULL;
    return fila;
}

/**
 * Insere um novo número em uma das filas do deque
 * @param cabeca Ponteiro para o deque
 * @param tipo true para fila normal, false para preferencial
 * @param numero Valor a ser inserido
 * @return Ponteiro para o deque
 */
struct deque *entrar(struct deque *cabeca, bool tipo, int numero) {
    struct no *novoNo = (struct no *) malloc(sizeof(struct no));
    
    if (novoNo == NULL) {
        fprintf(stderr, "Erro na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    
    novoNo->numero = numero;
    novoNo->proximo = NULL;
    
    if (tipo) {  // Fila Normal
        novoNo->proximo = cabeca->filaNormal;
        cabeca->filaNormal = novoNo;
    } else {     // Fila Preferencial
        novoNo->proximo = cabeca->filaPreferencial;
        cabeca->filaPreferencial = novoNo;
    }
    
    return cabeca;
}

/**
 * Realiza o atendimento seguindo as regras de prioridade
 * @param cabeca Ponteiro para o deque
 * @param contador Contador de atendimentos preferenciais
 */
void atender(struct deque *cabeca, int *contador) {
    // Deque vazio
    if (!cabeca->filaNormal && !cabeca->filaPreferencial) {
        printf("Nenhuma fila para atender!\n");
        return;
    }
    
    // Apenas fila normal tem pessoas
    if (!cabeca->filaPreferencial) {
        cabeca->filaNormal = sair(cabeca->filaNormal);
        return;
    }
    
    // Apenas fila preferencial tem pessoas
    if (!cabeca->filaNormal) {
        cabeca->filaPreferencial = sair(cabeca->filaPreferencial);
        *contador += 1;
        return;
    }
    
    // Ambas as filas têm pessoas
    if (*contador > 4) {  // Após 5 preferenciais, atende 1 normal
        cabeca->filaNormal = sair(cabeca->filaNormal);
        *contador = 0;
    } else {
        cabeca->filaPreferencial = sair(cabeca->filaPreferencial);
        *contador += 1;
    }
}

/**
 * Imprime o estado atual das filas
 * @param cabeca Ponteiro para o deque
 */
void imprimir(struct deque *cabeca) {
    printf("\nFila Preferencial: ");
    struct no *atual = cabeca->filaPreferencial;
    while (atual != NULL) {
        printf("%d ", atual->numero);
        atual = atual->proximo;
    }
    
    printf("\nFila Normal: ");
    atual = cabeca->filaNormal;
    while (atual != NULL) {
        printf("%d ", atual->numero);
        atual = atual->proximo;
    }
    printf("\n");
}

int main() {
    // Inicialização do deque
    struct deque *cabeca = (struct deque *) malloc(sizeof(struct deque));
    if (cabeca == NULL) {
        fprintf(stderr, "Erro na alocação de memória.\n");
        return EXIT_FAILURE;
    }
    
    cabeca->filaNormal = NULL;
    cabeca->filaPreferencial = NULL;
    int contador = 0;
    
    // Exemplo de uso
    printf("Inserindo pessoas na fila preferencial (números 100-109):\n");
    for (int i = 100; i < 110; i++) {
        cabeca = entrar(cabeca, false, i);
    }
    
    printf("Inserindo pessoas na fila normal (números 0-4):\n");
    for (int i = 0; i < 5; i++) {
        cabeca = entrar(cabeca, true, i);
    }
    
    printf("\nEstado inicial das filas:\n");
    imprimir(cabeca);
    
    printf("\nRealizando atendimentos:\n");
    for (int i = 0; i < 15; i++) {
        atender(cabeca, &contador); 
    }
    
    printf("\nEstado final das filas:\n");
    imprimir(cabeca);
    
    // Libera memória
    while (cabeca->filaNormal != NULL) {
        struct no *temp = cabeca->filaNormal;
        cabeca->filaNormal = cabeca->filaNormal->proximo;
        free(temp);
    }
    while (cabeca->filaPreferencial != NULL) {
        struct no *temp = cabeca->filaPreferencial;
        cabeca->filaPreferencial = cabeca->filaPreferencial->proximo;
        free(temp);
    }
    free(cabeca);
    
    return 0;
}