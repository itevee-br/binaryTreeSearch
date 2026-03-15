#include <stdlib.h>
#include <stdio.h>

typedef struct No {
    int valor; // Valor armazenado no nó
    struct No* esq; // Ponteiro para o menor (esq <)
    struct No* dir; // Ponteiro para o maior (dir >)
} No;

No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    
    if (novo != NULL) {
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    
    return novo;
}

No* botar(No* raiz, int valor){
    if (raiz == NULL){ // Se não existir um no raiz, ele sera o RAIZ
        return criarNo(valor); // Muito cinema
    }

    if (valor < raiz -> valor){
        //printf("menor\n");
        raiz->esq = botar(raiz->esq,valor);
        //chama para botar na esquerda
        // o nó da esquerda sera a raiz, se for vazio é adicionado ai
        // mas se tiver algo continua verificandooo
    } else if (valor > raiz -> valor){
        //printf("maior\n");
        raiz->dir = botar(raiz->dir,valor);
        // mesma logica aqui
    }
    return raiz;
}

No* buscar(No* raiz, int valor){
    if (raiz == NULL || valor == raiz -> valor){
        if (raiz == NULL){
            printf("procurando(%i)..\n> não encontrei ;-;\n",valor);
        } else {
            printf("procurando(%i)..\n> encontrei :)\n",valor);
        }
        return raiz;
        // se for NULL seguinifica que não encontrou nada
        // se ENCONTRAR retorna o PONTEIRO da posição
        // do elemento que estamos procurando.
    } else if (valor < raiz -> valor){
        return buscar(raiz->esq, valor);
        // valor menor < esq
    } else {
        return buscar(raiz->dir, valor);
        // valor maior > dir
    }
}

void imprimirReal(No* raiz) {
    if (raiz != NULL) {
        imprimirReal(raiz->esq);   // Primeiro os menores
        printf("%d ", raiz->valor);   // Depois a raiz
        imprimirReal(raiz->dir);   // Por fim os maiores
    }
    // para fazer o reverso basta inverter a ordem da.. ordem.
}

No* menor(No*raiz){
    if (raiz->esq==NULL){
        return raiz; // esse é o menor no
    } else {
        return menor(raiz->esq); // continua procurando o menor
    }
}

No* removerReal(No* raiz, int valor){
    if (raiz == NULL){
        printf("> não encontrei esse valor\n");
        return NULL;
    }

    if (valor < raiz->valor){
        raiz->esq = removerReal(raiz->esq,valor);
    } else if (valor > raiz->valor){
        raiz->dir = removerReal(raiz->dir,valor);
    } else {
        // ENCONTROU E ESTA REMOVENDO
        if (raiz->esq == NULL && raiz->dir == NULL){
            printf("> não encontrei filhos\n");
            free(raiz);
            return NULL;
        } else if (raiz->esq==NULL || raiz->dir==NULL){
            printf("> encontrei um filho\n");
            if (raiz->dir != NULL){ // se o filho é direito
                No * temp = raiz->dir;
                free(raiz);
                return temp;
            } else { // se o filho é esquerdo
                No * temp = raiz->esq;
                free(raiz);
                return temp;
            }
        } else {
            printf("> encontrei dois filhos\n");
            // MENOR DA DIREITA
            No* sucessor = menor(raiz->dir); // encontrar o substituto
            raiz->valor = sucessor->valor; // substituir
            raiz->dir = removerReal(raiz->dir,sucessor->valor);
            return raiz;
        }
    }
    return raiz;
}

// funções feitas APENAS para fazer print
// pois como as funções são recursivas o print sai estranho
void imprimir(No* raiz){
    printf("Arvore em ordem:\n> ");
    imprimirReal(raiz);
    printf("\n");
}
No* remover(No* raiz, int valor){
    printf("Removendo(%i)..\n",valor);
    return removerReal(raiz, valor);
}
No* adicionar(No* raiz, int valor){
    printf("(%i) adicionado!\n",valor);
    return botar(raiz, valor);
}
void help(){
    printf("Funções disponiveis e como chama-las");
    printf("> adicionar()");
    printf("> remover()");
    printf("> buscar()");
    printf("> imprimir()");
}

int main() {
    No* raiz = NULL; //inicia a variavel de raiz
    No* buscador = NULL; //inicia a variavel de busca

    raiz = adicionar(raiz,67);
    raiz = adicionar(raiz,6);
    raiz = adicionar(raiz,7);
    raiz = adicionar(raiz,82);
    raiz = adicionar(raiz,85);
    
    buscador = buscar(raiz, 7);
    buscador = buscar(raiz, 76);

    imprimir(raiz);

    raiz = remover(raiz,67);

    imprimir(raiz);

    raiz = remover(raiz,82);

    imprimir(raiz);

    printf("\nOlá, mundo!\n");
    return 0;
}