/**
 * Implementação de Árvore AVL em C
 * 
 * Este código implementa uma Árvore AVL com as seguintes funcionalidades:
 * - Inserir nós mantendo o balanceamento
 * - Rotações simples e duplas para balancear a árvore
 * 
 * Conceito:
 * A Árvore AVL é uma árvore binária de busca que mantém o equilíbrio ao garantir
 * que a diferença de altura entre as subárvores esquerda e direita de qualquer nó
 * não seja maior que 1.
 */

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore AVL
struct NoAVL {
    int numero;
    int altura;
    struct NoAVL *esquerda;
    struct NoAVL *direita;
};

/**
 * Calcula a altura de um nó
 * @param n Ponteiro para o nó
 * @return Altura do nó
 */
int altura(struct NoAVL* n) {
    return n ? n->altura : 0;
}

/**
 * Calcula o fator de balanceamento de um nó
 * @param n Ponteiro para o nó
 * @return Fator de balanceamento
 */
int fatorBalanceamento(struct NoAVL* n) {
    return n ? altura(n->esquerda) - altura(n->direita) : 0;
}

/**
 * Realiza uma rotação à direita
 * @param y Nó desbalanceado
 * @return Novo nó raiz após a rotação
 */
struct NoAVL* rotacaoDireita(struct NoAVL* y) {
    struct NoAVL* x = y->esquerda;
    struct NoAVL* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));
    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));

    return x;
}

/**
 * Realiza uma rotação à esquerda
 * @param x Nó desbalanceado
 * @return Novo nó raiz após a rotação
 */
struct NoAVL* rotacaoEsquerda(struct NoAVL* x) {
    struct NoAVL* y = x->direita;
    struct NoAVL* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));
    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));

    return y;
}

/**
 * Insere um novo nó na Árvore AVL
 * @param no Ponteiro para o nó raiz
 * @param numero Valor a ser inserido
 * @return Novo nó raiz após a inserção e balanceamento
 */
struct NoAVL* inserirAVL(struct NoAVL* no, int numero) {
    if (!no) {
        struct NoAVL* novoNo = (struct NoAVL*)malloc(sizeof(struct NoAVL));
        novoNo->numero = numero;
        novoNo->esquerda = novoNo->direita = NULL;
        novoNo->altura = 1;
        return novoNo;
    }

    if (numero < no->numero)
        no->esquerda = inserirAVL(no->esquerda, numero);
    else if (numero > no->numero)
        no->direita = inserirAVL(no->direita, numero);
    else
        return no;

    no->altura = 1 + (altura(no->esquerda) > altura(no->direita) ? altura(no->esquerda) : altura(no->direita));

    int balance = fatorBalanceamento(no);

    if (balance > 1 && numero < no->esquerda->numero)
        return rotacaoDireita(no);

    if (balance < -1 && numero > no->direita->numero)
        return rotacaoEsquerda(no);

    if (balance > 1 && numero > no->esquerda->numero) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    if (balance < -1 && numero < no->direita->numero) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

/**
 * Função principal para testar a Árvore AVL
 */
int main() {
    struct NoAVL* raiz = NULL;

    raiz = inserirAVL(raiz, 10);
    raiz = inserirAVL(raiz, 20);
    raiz = inserirAVL(raiz, 30);
    raiz = inserirAVL(raiz, 40);
    raiz = inserirAVL(raiz, 50);
    raiz = inserirAVL(raiz, 25);

    printf("Árvore AVL criada com sucesso.\n");

    return 0;
}