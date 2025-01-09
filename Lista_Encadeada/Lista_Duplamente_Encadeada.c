/**
 * Implementação de Lista Duplamente Encadeada em C
 * 
 * Este código implementa uma lista duplamente encadeada, onde cada nó contém:
 * - Um número inteiro como dado
 * - Um ponteiro para o nó anterior
 * - Um ponteiro para o próximo nó
 * 
 * Características principais:
 * - Permite inserção no final da lista
 * - Permite remoção de qualquer elemento
 * - Mantém referências bidirecionais entre os nós
 */

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da lista
struct no {
    int numero;
    struct no *anterior;
    struct no *proximo;
};

/**
 * Insere um novo número no final da lista
 * @param cabeca Ponteiro para o início da lista
 * @param numero Valor a ser inserido
 * @return Ponteiro para o início da lista (pode mudar se lista estava vazia)
 */
struct no *inserir(struct no *cabeca, int numero) {
    // Aloca e inicializa novo nó
    struct no *novoNo = (struct no *) malloc(sizeof(struct no));
    novoNo->numero = numero;
    novoNo->anterior = NULL;
    novoNo->proximo = NULL;

    // Lista vazia: novo nó se torna a cabeça
    if (cabeca == NULL) {
        return novoNo;
    }

    // Inserção no final: percorre até o último nó
    struct no *ultimo = cabeca;
    while (ultimo->proximo != NULL) {
        ultimo = ultimo->proximo;
    }
    
    // Faz as ligações bidirecionais
    ultimo->proximo = novoNo;
    novoNo->anterior = ultimo;
    
    return cabeca;
}

/**
 * Remove um número específico da lista
 * @param cabeca Ponteiro para o início da lista
 * @param numero Valor a ser removido
 * @return Ponteiro para o início da lista (pode mudar se removeu primeiro elemento)
 */
struct no *remover(struct no *cabeca, int numero) {
    // Lista vazia: nada a fazer
    if (cabeca == NULL) {
        return NULL;
    }

    // Remoção do primeiro elemento
    if (cabeca->numero == numero) {
        struct no *novoInicio = cabeca->proximo;
        free(cabeca);
        
        if (novoInicio != NULL) {
            novoInicio->anterior = NULL;
        }
        return novoInicio;
    }

    // Busca o elemento a ser removido
    struct no *atual = cabeca;
    while (atual != NULL && atual->numero != numero) {
        atual = atual->proximo;
    }

    // Elemento não encontrado
    if (atual == NULL) {
        return cabeca;
    }

    // Ajusta os ponteiros para "pular" o nó removido
    atual->anterior->proximo = atual->proximo;
    if (atual->proximo != NULL) {
        atual->proximo->anterior = atual->anterior;
    }

    free(atual);
    return cabeca;
}

/**
 * Imprime todos os elementos da lista
 * @param cabeca Ponteiro para o início da lista
 */
void imprimir(struct no *cabeca) {
    struct no *atual = cabeca;
    while (atual != NULL) {
        printf("%d, ", atual->numero);
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
    printf("+----------------+\n");
    printf("| Menu de Opcoes |\n");
    printf("+----------------+\n");
    printf("| 1 - Inserir    |\n");
    printf("| 2 - Remover    |\n");
    printf("| 3 - Imprimir   |\n");
    printf("| 4 - Sair       |\n");
    printf("+----------------+\n");
    printf("Digite a opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

int main() {
    struct no *cabeca = NULL;
    int opcao = 0;
    int numero;

    while (opcao != 4) {
        opcao = menu();
        switch(opcao) {
            case 1:
                printf("Digite o numero: ");
                scanf("%d", &numero);
                cabeca = inserir(cabeca, numero);
                break;
            case 2:
                printf("Digite o numero: ");
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