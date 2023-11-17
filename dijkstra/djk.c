//https://www.beecrowd.com.br/repository/UOJ_1506.html

#include <stdio.h>
#include <stdlib.h>

int count = 1;
int qtd_global[10001];
int count_min_heap = 0;

typedef struct vertice {
    int visitado;
    int distancia;
    struct lista *lista_adj;
    int in;
    int lower;
} vertice;

typedef struct lista {
    int qtd;
    struct registro *inicio;
} lista;

typedef struct registro {
    int valor;
    int peso;
    struct registro *prox;
} registro;

typedef struct elemento {
    int vertice;
    int distancia;
} elemento;

elemento heap[1000];

registro *aloca_registro();
lista *aloca_lista();
elemento pop();
void inicializar_distancias(vertice * vertices);
int push_fila(elemento x);
int min(int x, int y);
int incluir_ordenado_lista(lista *l, int x, int peso);
void push(vertice *v, int x, int peso);
void dfs(vertice * vertices , int x, int pai);
void desce_minimo(int indice);
void subir_minimo(int indice);
int define_pai(int indice);
int define_filho_direita(int indice);
int define_filho_esquerda(int indice);
int empty();
void djikstra(vertice * vertices, int raiz);

/* int rabito_pode_ganhar() {
    // Retorne 1 se Rabito pode ganhar, 0 caso contrário
} */

int main() {
    int T;
    int N, M, K, P;
    int u, v, w;
    vertice *grafo;
    int posicoes_ossos[K];

    printf("Programa inicializado\n");
    scanf("%d", &T);

    grafo = (vertice*)calloc(10000, sizeof(vertice));

    while (T--) {
        scanf("%d %d", N, M);

        for (int i = 0; i < M; i++) {
            scanf("%d %d %d", &u, &v, &w);
            /* arestas[i].u = u;
            arestas[i].v = v;
            arestas[i].w = w; */
            push(&grafo[u], v, w);
            push(&grafo[v], u, w);
        }

        scanf("%d %d", K, P);
        for (int i = 0; i < K; i++) {
            scanf("%d", &posicoes_ossos[i]);
        }

        // chama djikstra = pega distancia com menor custo; flag1
        // verifica qual o caminho com maior qtd de arestas; flag2
        // se flag1 = flag 2, OK existe estratégia ideal
        
    }

    return 0;
}