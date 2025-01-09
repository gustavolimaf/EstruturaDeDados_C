/**
 * Implementação de Matriz Esparsa usando Listas Encadeadas em C
 * 
 * Esta estrutura organiza números em "linhas" baseadas no resto da divisão
 * por um módulo definido. Cada linha é gerenciada por um nó diretor que
 * mantém uma lista encadeada de números.
 * 
 * Características:
 * - Agrupa números pelo resto da divisão (módulo)
 * - Estrutura dinâmica que cresce conforme necessário
 * - Otimiza busca por padrões de números
 */

#include <stdio.h>
#include <stdlib.h>

#define MODULO 5  // Define o número de grupos possíveis

// Estrutura para os números armazenados
struct no {
    int numero;
    struct no *proximoNo;
};

// Estrutura para os diretores (cabeças das listas)
struct diretor {
    int resto;                    // Resto da divisão pelo módulo
    struct no *proximoNo;         // Início da lista de números
    struct diretor *proximoDiretor; // Próximo diretor
};

/**
 * Cria um novo diretor para um determinado resto
 * @param cabeca Ponteiro para o início da lista de diretores
 * @param resto Valor do resto para o novo diretor
 * @return Ponteiro para o novo diretor
 */
struct diretor *criarDiretor(struct diretor *cabeca, int resto) {
    struct diretor *novoDiretor = (struct diretor *) malloc(sizeof(struct diretor));
    if (novoDiretor == NULL) {
        fprintf(stderr, "Erro na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    
    novoDiretor->resto = resto;
    novoDiretor->proximoNo = NULL;
    novoDiretor->proximoDiretor = cabeca;
    return novoDiretor;
}

/**
 * Busca o diretor responsável por um determinado resto
 * @param cabeca Ponteiro para o início da lista de diretores
 * @param resto Valor do resto procurado
 * @return Ponteiro para o diretor encontrado ou NULL
 */
struct diretor *buscarDiretor(struct diretor *cabeca, int resto) {
    struct diretor *atual = cabeca;
    while (atual != NULL && atual->resto != resto) {
        atual = atual->proximoDiretor;
    }
    return atual;
}

/**
 * Insere um novo número na matriz esparsa
 * @param cabeca Ponteiro para o início da lista de diretores
 * @param numero Valor a ser inserido
 * @return Ponteiro para o início da lista de diretores
 */
struct diretor *inserir(struct diretor *cabeca, int numero) {
    int resto = numero % MODULO;
    
    // Procura ou cria o diretor apropriado
    struct diretor *diretor = buscarDiretor(cabeca, resto);
    if (diretor == NULL) {
        cabeca = criarDiretor(cabeca, resto);
        diretor = cabeca;
    }

    // Cria e insere o novo nó no início da lista
    struct no *novoNo = (struct no *) malloc(sizeof(struct no));
    if (novoNo == NULL) {
        fprintf(stderr, "Erro na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    
    novoNo->numero = numero;
    novoNo->proximoNo = diretor->proximoNo;
    diretor->proximoNo = novoNo;
    
    return cabeca;
}

/**
 * Remove um número da matriz esparsa
 * @param cabeca Ponteiro para o início da lista de diretores
 * @param numero Valor a ser removido
 */
void remover(struct diretor *cabeca, int numero) {
    if (cabeca == NULL) return;
    
    // Procura o diretor correto
    struct diretor *diretor = buscarDiretor(cabeca, numero % MODULO);
    if (diretor == NULL || diretor->proximoNo == NULL) return;
    
    // Remove o primeiro nó se for o número procurado
    if (diretor->proximoNo->numero == numero) {
        struct no *excluir = diretor->proximoNo;
        diretor->proximoNo = excluir->proximoNo;
        free(excluir);
        return;
    }
    
    // Procura o número na lista do diretor
    struct no *anterior = diretor->proximoNo;
    while (anterior->proximoNo != NULL && anterior->proximoNo->numero != numero) {
        anterior = anterior->proximoNo;
    }
    
    // Remove o nó se encontrado
    if (anterior->proximoNo != NULL) {
        struct no *excluir = anterior->proximoNo;
        anterior->proximoNo = excluir->proximoNo;
        free(excluir);
    }
}

/**
 * Imprime a matriz esparsa organizada por restos
 * @param cabeca Ponteiro para o início da lista de diretores
 */
void imprimir(struct diretor *cabeca) {
    printf("Matriz Esparsa (organizada por resto da divisão por %d):\n", MODULO);
    printf("------------------------------------------------\n");
    
    struct diretor *diretor = cabeca;
    while (diretor != NULL) {
        printf("Resto %d:\t", diretor->resto);
        
        struct no *no = diretor->proximoNo;
        while (no != NULL) {
            printf("%d ", no->numero);
            no = no->proximoNo;
        }
        printf("\n");
        
        diretor = diretor->proximoDiretor;
    }
    printf("------------------------------------------------\n");
}

/**
 * Libera toda a memória alocada pela matriz esparsa
 * @param cabeca Ponteiro para o início da lista de diretores
 */
void liberarMemoria(struct diretor *cabeca) {
    while (cabeca != NULL) {
        // Libera todos os nós da lista do diretor atual
        struct no *no = cabeca->proximoNo;
        while (no != NULL) {
            struct no *excluir = no;
            no = no->proximoNo;
            free(excluir);
        }
        
        // Libera o diretor atual
        struct diretor *excluir = cabeca;
        cabeca = cabeca->proximoDiretor;
        free(excluir);
    }
}

int main() {
    struct diretor *matriz = NULL;
    
    // Inserindo números de teste
    printf("Inserindo números de 0 a 99...\n\n");
    for (int i = 0; i < 100; i++) {
        matriz = inserir(matriz, i);
    }
    
    // Mostra estado inicial
    imprimir(matriz);
    
    // Remove alguns números
    printf("\nRemovendo números de 0 a 49...\n\n");
    for (int i = 0; i < 50; i++) {
        remover(matriz, i);
    }
    
    // Mostra estado final
    imprimir(matriz);
    
    // Libera memória
    liberarMemoria(matriz);
    
    return 0;
}