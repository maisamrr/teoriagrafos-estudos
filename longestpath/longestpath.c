// https://www.spoj.com/problems/PT07Z/

#include <stdio.h>
#include <stdlib.h>

typedef struct vertice {
    int visitado;
    int distancia_raiz;
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

typedef struct fila {
    int tamanho;
    struct registro *primeiro;
    struct registro *ultimo;
} fila;

fila *iniciarFila() {
    fila *nova_fila;
    nova_fila = (fila*)calloc(1, sizeof(fila));

    return nova_fila;
}

lista *inicializarLista() {
    lista *nova_lista;
    nova_lista = (lista*)calloc(1, sizeof(lista));

    return nova_lista;
}

registro *iniciarRegistro() {
    registro *novo = (registro*)calloc(1, sizeof(registro));

    return novo;
}

int addNaLista(lista *l, int x) {
    registro *novoRegistro;
    novoRegistro = iniciarRegistro();
    novoRegistro->valor = x;

    if (l->inicio == NULL)
    {
        l->inicio = novoRegistro;
        l->qtd_elementos++;
        return 0;
    }

    registro *aux = l->inicio;

    while (aux->proximo != NULL)
    {
        aux = aux->proximo;
    }

    aux->proximo = novoRegistro;
    l->qtd_elementos++;
    return 1;
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
    fila->tamanho++;
}

int removerDaFila(fila *fila) {
    if(fila->primeiro == NULL) {
        return -1;
    }
    int removido;
    removido = fila->primeiro->valor;
    fila->primeiro = fila->primeiro->proximo;
    fila->tamanho--;

    return removido;
}

void push(vertice *vertice, int valor) {
    if(vertice->lista_adjacencia == NULL) {
        vertice->lista_adjacencia = inicializarLista();

    }
    addNaLista(vertice->lista_adjacencia, valor);
}

int bfs (vertice *vertices, int raiz, int qtd_vertices) {
    fila *minha_fila = iniciarFila();
    int atual;
    registro *aux;

    for(int i = 0; i < qtd_vertices; i++) {
        vertices[i].visitado = 0;
        vertices[i].distancia_raiz = -1;
    }

    addNaFila(minha_fila, raiz);
    vertices[raiz].visitado = 1;
    vertices[raiz].distancia_raiz = 0;

    while(minha_fila->tamanho > 0) {
        atual = removerDaFila(minha_fila);
        aux = vertices[atual].lista_adjacencia->inicio; 

        while(aux != NULL) {
            if(vertices[aux->valor].visitado == 0) {
                vertices[aux->valor].visitado = 1;
                addNaFila(minha_fila, aux->valor);
                vertices[aux->valor].distancia_raiz = vertices[atual].distancia_raiz + 1;
            }
            aux = aux->proximo;
        }
    }

    return atual;
}

int main() {

    int n;
    int u, v;
    vertice *grafo;
    int tem_ciclo = 0;

    scanf("%d", &n);

    grafo = (vertice*)calloc(n+1, sizeof(vertice));
    
    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &u, &v);
        grafo[u].visitado = 0;
        grafo[v].visitado = 0;
        push(&grafo[u], v);
        push(&grafo[v], u);
    };

    int test = bfs(grafo, bfs(grafo, 1, n), n);

    printf("%i", grafo[test].distancia_raiz);
    

    return 0;
}