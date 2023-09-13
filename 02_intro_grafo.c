#include <stdio.h>
#include <stdlib.h>

typedef struct vertice {
    int visitado;
    struct lista *lista_adjacencia;
} vertice;

typedef struct lista {
    int qtd_elementos;
    struct registro *inicio;
} lista;

typedef struct registro {
    int conteudo;
    struct registro *proximo;
} registro;

registro *criarRegistro() {
    registro *novo;
    novo = (registro*)calloc(1, sizeof(registro));
    return novo;
};

lista *criarLista() {
    lista *nova;
    nova = (lista*)calloc(1, sizeof(lista));
    return nova;
}

int addNaLista(lista *lista, int valor) {
    if(lista == NULL) {
        return;
    }

    //criar registro
    registro *novo;
    novo = criarRegistro();
    novo->conteudo = valor;

    //se a lista estiver vazia, o novo registro é o início dela
    if(lista->inicio == NULL) {
        lista->inicio = novo;
    } else { // se não estiver vazia, percorrer para add o novo após o último registro
        registro *aux = lista->inicio; //aux aponta para o inicio
        while(aux->proximo != NULL) { //enqt aux não apontar para NULL
            aux = aux->proximo; //ele vira o próximo nó
        }
        aux->proximo = novo; //qd sair da condição, ele vira o novo nó          
    }
}
    
int main() {
    
    return 0;
}