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
        return 0;
    }

    registro *novo;
    novo = criarRegistro();
    novo->conteudo = valor;

    if(lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        registro *aux = lista->inicio;
        while(aux->proximo != NULL) { 
            aux = aux->proximo; 
        }
        aux->proximo = novo;         
    }

    return 1;
}

void imprimirLista(lista *lista) {
    registro *aux = lista->inicio;

    if(aux == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    printf("LISTA DE ADJACÊNCIA:\n");
    while(aux != NULL) {
        printf("%d -> ", aux->conteudo);
        aux = aux->proximo;
    }
    printf("\n\n");
}
    
int main() {

    lista* lista = criarLista();
    int qtd_vertices = 0;

    printf("Quantos vértices tem seu grafo?\n");
    scanf("%d", &qtd_vertices);

    int opcao;
    int a,b;
    do {
        printf("Escolha uma opção:\nDigite:\n1 - Adicionar aresta (A B)\n2 - Exibir grafo\n0 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Opção para adicionar aresta (A B)
                scanf("%d %d", &a, &b);
                addNaLista(lista, a);
                addNaLista(lista, b);
                imprimirLista(lista);
                break;
            case 2:
                // Opção para exibir o grafo
                printf("Dois - Exibir grafo\n");
                break;
            case 0:
                // Opção para sair
                printf("Sair\n");
                break;
            default:
                // Opção inválida
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
    
    return 0;
}