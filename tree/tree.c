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

void dfs(vertice *vertice, int raiz, int anterior, int *tem_ciclo) {
    
    registro *aux = vertice[raiz].lista_adjacencia->inicio;;
    vertice[raiz].visitado = 1;

    if (vertice[raiz].lista_adjacencia == NULL)
    {
        return;
    }

    while (aux != NULL)
    {
        if (vertice[aux->valor].visitado == 0)
        {
            dfs(vertice, aux->valor, raiz, tem_ciclo);
        }
        else if (aux->valor != anterior)
        {
            *tem_ciclo = 1;
        }

        aux = aux->proximo;
    }
}

int main() {

    int n; //qtd_vertices
    int m; //qtd_arestas
    int arestas;
    int u, v; //par de vertices da aresta
    vertice *grafo;
    int tem_ciclo = 0;

    scanf("%d %d", &n, &m); //qtd_vertices e qtd_arestas

    if (m != n - 1) {
        printf("NO");
        return 0;
    }

    grafo = (vertice*)calloc(n+1, sizeof(vertice));
    
     for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);
        grafo[u].visitado = 0;
        grafo[v].visitado = 0;
        push(&grafo[u], v);
        push(&grafo[v], u);
    };

    dfs(grafo, u, -1, &tem_ciclo);

    for (int i = 1; i <= n; i++) {
        if (grafo[i].visitado == 0) {
            printf("NO\n");
            return 0;
        }
    }

    if (tem_ciclo) {
        printf("NO");
    } else {
        printf("YES");
    }

    return 0;
}