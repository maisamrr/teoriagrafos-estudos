// https://www.spoj.com/problems/PT07Y/

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

registro *iniciarRegistro() {
    registro *novo = (registro*)calloc(1, sizeof(registro));

    return novo;
}

lista *inicializarLista() {
    lista *nova_lista = (lista*)calloc(1, sizeof(lista));

    return nova_lista;
}

void addNaLista(lista *lista, int conteudo) {
    registro *novo = iniciarRegistro();
    novo->valor = conteudo;

    if(lista->inicio == NULL) {
        lista->inicio = novo;
        lista->qtd_elementos++;

        return;
    }

    registro *aux = aux = lista->inicio;
    while(aux->proximo != NULL) {
        aux = aux->proximo;
    }
    aux->proximo = novo;
    lista->qtd_elementos++;
}

void push(vertice *vertice, int valor) {
    if(vertice->lista_adjacencia == NULL) {
        vertice->lista_adjacencia = inicializarLista();

    }
    addNaLista(vertice->lista_adjacencia, valor);
}

int dfs(vertice *vertice, int raiz, int pai) {
    vertice[raiz].visitado = 1; //visita a raiz
    registro *aux = vertice[raiz].lista_adjacencia->inicio; //inicializa a lista de adjacências

    if (vertice[raiz].lista_adjacencia == NULL) {
        return 0; //se a lista está vazia, não tem ciclo
    }

    //ciclo de um grafo: encontrar no processo de busca do dfs um vértice que já tenha sido visitado e não é o vértice pai do vértice em questão
    while (aux != NULL) { //percorrer o grafo para detectar se há ciclos
        if (vertice[aux->valor].visitado == 0) {
            dfs(vertice, aux->valor, raiz);
        } else if (aux->valor != pai) { 
            return 1;
        }

        aux = aux->proximo;
    }

    return 0;
}

int main() {

    int n; //qtd_vertices
    int m; //qtd_arestas
    int arestas;
    int u, v; //par de vertices da aresta
    vertice *grafo;

    scanf("%d %d", &n, &m); //qtd_vertices e qtd_arestas
    if(m != n-1) { //para ser árvore, quantidade de arestas é a quantidade de vértices menos 1
        printf("NO\n");
        return 0;
    }

    grafo = (vertice*)calloc(n+1, sizeof(vertice));

    for (int i = 1; i <= n; i++) { //inicializa todos os vértices como não visitados
        grafo[i].visitado = 0;
    }
    
    for(int i = 0; i < m; i++) { //ler arestas
        scanf("%d %d", &u, &v);
        push(&grafo[u], v);
        push(&grafo[v], u);
    }

    for (int i = 1; i <= n; i++) { //verifica se tem vértices desconectados no grafo 
        if (grafo[i].visitado == 0) {
            printf("NO\n"); //se tem, não pode ser árvore
            return 0;
        }
    }

    int ciclo = dfs(grafo, 1, -1); //dfs verificando se há ciclos

    if (ciclo == 1) {
        printf("NO\n"); //se tem ciclo não é árvore
    } else {
        printf("YES\n");
    }

    return 0;
}