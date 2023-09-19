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

int bfs (vertice *vertices, int raiz, int qtd_vertices) {
    fila *minha_fila = iniciarFila();
    int atual;
    
    for(int i = 0; i < qtd_vertices; i++ ) {
        vertices[i].visitado = 0; //nenhum vertice visitado ainda
        vertices[i].distancia_raiz = -1; 
    }

    vertices[raiz].distancia_raiz = 0; //distancia da raiz para ela mesma

    addNaFila(minha_fila, raiz);
    while(minha_fila->tamanho != 0) {
        atual = removerDaFila(minha_fila); //tira o primeiro da fila
        vertices[atual].visitado = 1; //setar o atual como visitada

        //colocar todos os elementos da lista de adjacência do atual na fila       
        registro *aux;
        aux = vertices[atual].lista_adjacencia->inicio; //pegar o primeiro valor da lista de adjacência do atual
        while(aux->proximo != NULL) { //andar na lita de adjacências do atual
            if (vertices[aux->valor].visitado == 0) {
                addNaFila(minha_fila, aux->valor); //bota na fila
                vertices[aux->proximo->valor].distancia_raiz = vertices[atual].distancia_raiz + 1; //seta a distância
                aux = aux->proximo; //anda pro próximo
            }
            
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
        //pegar arestas e colocar os vertices delas no grafo 
        for (int j = 0; j < qtd_arestas; j++) {
            scanf("%d %d", &a, &b);
            push(&vertices[a], b);
            push(&vertices[b], a);
        }

        printf("\nOutput: %d", bfs(vertices, 1, qtd_vertices));
        
        free(vertices);
    }
    
    return 0;
}