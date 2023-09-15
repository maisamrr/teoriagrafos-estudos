#include <stdio.h>
#include <stdlib.h>

typedef struct vertice {
    int visitado;
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

lista *inicializarLista() {
    lista *nova_lista;
    nova_lista = (lista*)calloc(1, sizeof(lista));
    return nova_lista;
}

registro *inicializarRegistro() {
    registro *novo_registro;
    novo_registro = (registro*)calloc(1, sizeof(registro));
    return novo_registro;
}

void addNaLista(lista *lista, int valor_vertice) {
    registro *novo_registro = inicializarRegistro();
    novo_registro->valor = valor_vertice;
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

void imprimirLista(lista *lista) {
     if(lista->inicio == NULL) {
        printf("A lista está vazia\n");
    }

    registro *aux;
    aux = lista->inicio;
    for(int i = lista->quantidade_elementos; i > 0; i--) {
        printf("%d -> ", aux->valor);
        aux = aux->proximo;
    }
    printf("\n\n");
}

void push(vertice *vertice, int a) {
    if(vertice->lista_adjacencia == NULL) {
        vertice->lista_adjacencia = inicializarLista();
    }
    addNaLista(vertice->lista_adjacencia, a);
}

void imprimirGrafo(int qtd_vertices_grafo, vertice *v) {

    for(int i = 1; i < qtd_vertices_grafo+1; i++) {
        printf("Lista de adjacências do vértice %d : ", i);
        imprimirLista(v[i].lista_adjacencia);
        printf("\n");
    }
}

//aqui, devemos passar o vetor de vértices e o nó raiz por onde queremos iniciar a busca
void dfs(vertice *v, int no_raiz) {
    registro *aux;
    v[no_raiz].visitado = 1; //dizendo a raiz foi visitada
    printf(" %d", no_raiz); // vamos dar um confere na hora de chamar essa função

    if(v[no_raiz].lista_adjacencia == NULL) { //se não houver nada na lista de adjacência da raiz, acaba por aí
        return;
    }

    aux = v[no_raiz].lista_adjacencia->inicio; // indicando que a lista de adjacência começa no no raiz, ou seja, ele é o início dessa lista

    while(aux != NULL) { //a partir desse nó aux, que aponta para o início,
        if(v[aux->valor].visitado == 0) { //se ele ainda não foi visitado,
            dfs(v, aux->valor); //chama o dfs recursivamente para visitar o nó
        }
        aux = aux->proximo; // e aponta para o próximo nó
    }
}

int main() {
    int qtd_vertices_grafo;
    int qtd_arestas_grafo;
    int a, b;

    printf("Digite a quantidade de vértices do grafo\n");
    scanf("%d", &qtd_vertices_grafo);
    vertice *vertices = (vertice*)calloc(10000, sizeof(vertice));

    printf("Digite a quantidade de arestas do grafo\n");
    scanf("%d", &qtd_arestas_grafo);

    printf("Digite as arestas do grafo:\n");
    for(int i = 0; i < qtd_arestas_grafo; i++) {
        scanf("%d %d", &a, &b);
        push(&vertices[a], b);
        push(&vertices[b], a);
    }

    // printf("Hora da verdade:\n");
    // imprimirGrafo(qtd_vertices_grafo, vertices);

    printf("DFS em ação:\n");
    dfs(vertices, 1);

    return 0;
}