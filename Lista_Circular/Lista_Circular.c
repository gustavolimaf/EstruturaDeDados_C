/**
 * Implementação de Lista Circular Simples em C
 * 
 * Este código implementa uma lista circular simples, onde:
 * - Cada nó contém um número e um ponteiro para o próximo nó
 * - O último nó aponta de volta para o primeiro (circular)
 * - Não há nó anterior (encadeamento simples)
 * 
 * Características principais:
 * - Inserção sempre no final da lista
 * - Remoção de qualquer elemento
 * - Mantém circularidade da lista
 */

#include <stdio.h>
#include <stdlib.h>

struct no {
    int numero;
    struct no *proximo;
};

/**
 * Insere um novo número no final da lista
 * @param cabeca Ponteiro para o início da lista
 * @param numero Valor a ser inserido
 * @return Ponteiro para o início da lista
 */
struct no *inserir(struct no *cabeca, int numero) {
    struct no *novoNo = (struct no *) malloc(sizeof(struct no));
    novoNo->numero = numero;
    novoNo->proximo = NULL;

    // Lista vazia: novo nó aponta para si mesmo
    if (cabeca == NULL) {
        novoNo->proximo = novoNo;
        return novoNo;
    }

    // Inserção no final: percorre até o último nó
    struct no *ultimo = cabeca;
    while (ultimo->proximo != cabeca) {
        ultimo = ultimo->proximo;
    }
    
    ultimo->proximo = novoNo;
    novoNo->proximo = cabeca;
    return cabeca;
}

/**
 * Remove um número específico da lista
 * @param cabeca Ponteiro para o início da lista
 * @param numero Valor a ser removido
 * @return Ponteiro para o início da lista
 */
struct no *remover(struct no *cabeca, int numero) {
    if (cabeca == NULL) {
        return NULL;
    }

    // Remoção do primeiro elemento
    if (cabeca->numero == numero) {
        // Caso especial: lista com um único elemento
        if (cabeca == cabeca->proximo) {
            free(cabeca);
            return NULL;
        }
        
        // Lista com mais elementos
        struct no *ultimo = cabeca;
        while (ultimo->proximo != cabeca) {
            ultimo = ultimo->proximo;
        }
        
        struct no *novoInicio = cabeca->proximo;
        ultimo->proximo = novoInicio;
        free(cabeca);
        return novoInicio;
    }

    // Busca o elemento anterior ao que será removido
    struct no *anterior = cabeca;
    while (anterior->proximo != cabeca && 
           anterior->proximo->numero != numero) {
        anterior = anterior->proximo;
    }

    // Elemento não encontrado
    if (anterior->proximo == cabeca) {
        return cabeca;
    }

    // Remove o nó encontrado
    struct no *remover = anterior->proximo;
    anterior->proximo = remover->proximo;
    free(remover);
    return cabeca;
}

/**
 * Imprime todos os elementos da lista
 * @param cabeca Ponteiro para o início da lista
 */
void imprimir(struct no *cabeca) {
    if (cabeca == NULL) {
        return;
    }

    struct no *atual = cabeca;
    do {
        printf("%d\n", atual->numero);
        atual = atual->proximo;
    } while (atual != cabeca);
}

/**
 * Exibe menu de opções e retorna a escolha do usuário
 * @return Opção escolhida
 */
int menu() {
    int opcao;
    printf("--------------------\n");
    printf("       Menu         \n");
    printf("--------------------\n");
    printf("| 1 - Inserir     |\n");
    printf("| 2 - Remover     |\n");
    printf("| 3 - Imprimir    |\n");
    printf("| 4 - Sair        |\n");
    printf("--------------------\n");
    printf("Digite sua opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

int main() {
    struct no *cabeca = NULL;
    int opcao = 0;
    int numero;

    while (opcao != 4) {
        opcao = menu();
        switch (opcao) {
            case 1:
                printf("Digite o numero a inserir: ");
                scanf("%d", &numero);
                cabeca = inserir(cabeca, numero);
                break;
            case 2:
                printf("Digite o numero a remover: ");
                scanf("%d", &numero);
                cabeca = remover(cabeca, numero);
                break;
            case 3:
                imprimir(cabeca);
                break;
        }
    }
    return 0;
}