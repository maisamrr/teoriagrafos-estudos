//https://www.hackerearth.com/practice/algorithms/graphs/breadth-first-search/practice-problems/algorithm/monk-and-the-islands/
#include <stdio.h>
#include <stdlib.h>

typedef struct vertice {
    int visitado;
    int distancia_raiz;
    struct lista *lista_adjacencia;
} vertice;

typedef struct lista {
    int quantidade_elementos;
    struct registro *inicio;
} lista;

typedef struct registro {
    int valor;
    struct registro *proximo;
} registro;

typedef struct fila {
    int tamanho;
    struct registro *primeiro;
    struct registro *ultimo;
} fila;

registro *iniciarRegistro() {
    registro *novo_registro;
    novo_registro = (registro*)calloc(1, sizeof(registro));
    
    return novo_registro;
}

lista *iniciarLista() {
    lista *nova_lista;
    nova_lista = (lista*)calloc(1, sizeof(lista));

    return nova_lista;
}

fila *iniciarFila() {
    fila *nova_fila;
    nova_fila = (fila*)calloc(1, sizeof(fila));

    return nova_fila;
}

void addNaLista(lista *lista, int a) {
    registro *novo_registro = iniciarRegistro();
    novo_registro->valor = a;
    registro *aux;

    if(lista->inicio == NULL) {
        lista->inicio = novo_registro;
        lista->quantidade_elementos++;
        return;
    }

    aux = lista->inicio;
    while(aux->proximo != NULL) {
        aux = aux->proximo;
    }
    aux->proximo = novo_registro;
    lista->quantidade_elementos++;
}

void push(vertice *vertice, int a) {
    if(vertice->lista_adjacencia == NULL) {
        vertice->lista_adjacencia = iniciarLista();
    }
    addNaLista(vertice->lista_adjacencia, a);
}

void addNaFila(fila *fila, int a) {
    registro *novo_registro = iniciarRegistro();
    novo_registro->valor = a;

    if(fila->primeiro == NULL) {
        fila->primeiro = novo_registro;
        fila->ultimo = novo_registro;
        fila->tamanho++;
        return;
    }

    fila->ultimo->proximo = novo_registro;
    fila->ultimo = novo_registro;
}

int removerDaFila(fila *fila) {
    if(fila->primeiro == NULL) {
        return -1;
    }
    registro *aux;
    int removido = fila->primeiro->valor;
    aux = fila->primeiro->proximo;
    fila->primeiro = aux;
    fila->tamanho--;

    return removido;
}

int bfs (vertice *vertices, int raiz) {
    fila *minha_fila = iniciarFila();
    int atual;
    
    addNaFila(minha_fila, raiz);
    while(minha_fila =! 0) {
        atual = removerDaFila(minha_fila);
        vertices[atual].visitado = 1;

        //colocar todos os elementos da lista de adjacência do atual na fila       
        registro *aux;
        aux = vertices[atual].lista_adjacencia->inicio;
        while(aux->proximo != NULL) {
            addNaFila(minha_fila, aux->valor);
            aux = aux->proximo;
        }
    }

}

int main() {

    return 0;
}