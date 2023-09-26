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

fila *iniciarFila() {
    fila *nova_fila;
    nova_fila = (fila*)calloc(1, sizeof(fila));

    return nova_fila;
}

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

int addNaLista(lista *l, int x) {
    registro *novoRegistro;
    novoRegistro = iniciarRegistro();
    novoRegistro->valor = x;

    if (l->inicio == NULL)
    {
        l->inicio = novoRegistro;
        l->quantidade_elementos++;
        return 0;
    }

    registro *aux = l->inicio;

    while (aux->proximo != NULL)
    {
        aux = aux->proximo;
    }

    aux->proximo = novoRegistro;
    l->quantidade_elementos++;
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

void push(vertice *vertice, int a) {
    if(vertice->lista_adjacencia == NULL) {
        vertice->lista_adjacencia = iniciarLista();
    }
    addNaLista(vertice->lista_adjacencia, a);
}

int bfs (vertice *vertices, int raiz, int qtd_vertices) {
    fila *minha_fila = iniciarFila();
    int atual;
    registro *aux;

    for(int i = 0; i < qtd_vertices; i++) {
        vertices[i].visitado = 0; //nenhum vertice visitado ainda
        vertices[i].distancia_raiz = -1; //podemos inicializar com qualquer valor
    }

    addNaFila(minha_fila, raiz);
    vertices[raiz].visitado = 1;
    vertices[raiz].distancia_raiz = 0; //distancia da raiz para ela mesma

    while(minha_fila->tamanho > 0) {
        atual = removerDaFila(minha_fila); //tira o primeiro da fila
        aux = vertices[atual].lista_adjacencia->inicio; //pegar o primeiro valor da lista de adjacência do atual

        //colocar todos os elementos da lista de adjacência do atual na fila    
        while(aux != NULL) { //andar na lista de adjacências do atual
            if(vertices[aux->valor].visitado == 0) {
                vertices[aux->valor].visitado = 1; //setar o atual como visitada
                addNaFila(minha_fila, aux->valor);
                vertices[aux->valor].distancia_raiz = vertices[atual].distancia_raiz + 1;
            }
            aux = aux->proximo;
        }
    }

    return vertices[qtd_vertices].distancia_raiz;
}

int main() {

    int qtd_cenarios;
    int qtd_vertices;
    int qtd_arestas;
    
    scanf("%d", &qtd_cenarios);
    
    for(int cenario = 1; cenario <= qtd_cenarios; cenario++) {
        scanf("%d %d", &qtd_vertices, &qtd_arestas);
        vertice *vertices = (vertice*)calloc(qtd_vertices + 1, sizeof(vertice));

        int a, b;
        for (int j = 0; j < qtd_arestas; j++) {
            scanf("%d %d", &a, &b);
            push(&vertices[a], b);
            push(&vertices[b], a);
        }
        printf("\n");
        printf("%d\n", bfs(vertices, 1, qtd_vertices));
        
        free(vertices);
    }
    
    return 0;
}