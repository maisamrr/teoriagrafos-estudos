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

typedef struct registro
{
    int conteudo;
    struct registro *proximo;
} registro;

int main() {
    vertice vertice1;
    vertice1.visitado = 0;

    lista lista1;
    lista1.qtd_elementos = 0;

    registro registro1;
    registro1.conteudo = 1;
    lista1.inicio = &registro1;

    vertice1.lista_adjacencia = &lista1;

    registro registro2;
    registro2.conteudo = 2;
    
    registro1.proximo = &registro2;
    lista1.qtd_elementos = 2;

    registro registro3;
    registro3.conteudo = 3;
    
    registro2.proximo = &registro3;

    //imprimir a lista 1
    registro *aux = lista1.inicio;
    for(int i = 0; i < lista1.qtd_elementos; i++) {
        printf("%d -> ", aux->conteudo);
        aux = aux->proximo;
    }

    return 0;
}