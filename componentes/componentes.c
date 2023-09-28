//https://www.hackerearth.com/pt-br/problem/algorithm/connected-components-in-a-graph/
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
    int valor;
    struct registro *proximo;
} registro;

registro *inicializarRegistro() {
    registro *novo_registro;
    novo_registro = (registro *)calloc(1, sizeof(registro));
    return novo_registro;
}

lista *inicializarLista() {
    lista *nova_lista;
    nova_lista = (lista *)calloc(1, sizeof(lista));
    return nova_lista;
}

void addNaLista(lista *lista, int n) {
    registro *novo_registro = inicializarRegistro();
    novo_registro->valor = n;

    if (lista->inicio == NULL) {
        lista->inicio = novo_registro;
        lista->qtd_elementos++;
        return;
    }

    registro *aux = lista->inicio;
    while (aux->proximo != NULL) {
        aux = aux->proximo;
    }
    aux->proximo = novo_registro;
    lista->qtd_elementos++;
}

void push(vertice *vertice, int a) {
    if (vertice->lista_adjacencia == NULL) {
        vertice->lista_adjacencia = inicializarLista();
    }
    addNaLista(vertice->lista_adjacencia, a);
}

void dfs(vertice *grafo, int raiz) {
    grafo[raiz].visitado = 1;

    registro *atual = grafo[raiz].lista_adjacencia->inicio;

    while (atual != NULL) {
        int vizinho = atual->valor;
        if (!grafo[vizinho].visitado) {
            dfs(grafo, vizinho);
        }
        atual = atual->proximo;
    }
}

int main() {
    int n, e;
    int u, v;

    printf("Input:\n");
    scanf("%d %d", &n, &e);

    vertice *grafo = (vertice *)calloc(10000, sizeof(vertice));

    int num_grupos = 0;

    for (int z = 1; z <= n; z++) {                                                   
        grafo[z].visitado = 0;                          
        grafo[z].lista_adjacencia = inicializarLista(); 
    }

    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        push(&grafo[u], v);
        push(&grafo[v], u);
    }

    for (int i = 1; i <= n; i++) {
        if (!grafo[i].visitado) {
            dfs(grafo, i);
            num_grupos++;
        }
    }

    printf("Output:\n");
    printf("%d\n", num_grupos);

    return 0;
}
