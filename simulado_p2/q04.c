#include <stdio.h>
#include <stdlib.h>

typedef struct vertice {
    int visitado;
    int lista_adj[1000];
    int tam_lista_adj;
    int in;
    int lower;
} vertice;

int count;
int bridge_count;

void mostrar_tudo (vertice * vertices, int qtd_vertices);

int menor(int a, int b) ;
void dfs2(vertice * vertices, int qtd_vertices, int raiz, int pai);

int main() {
    int NC; //qtd casos
    int N; //qtd_vertices
    int M; //qtd_arestas;
    int i, a, b = 0;
    vertice * vertices;
    printf("Programa inicializado\n");
    scanf("%d",&NC);

    for (int j = 0; j < NC; j++) {
        bridge_count = 0;
        scanf("%d %d",&N, &M);

        vertices = (vertice*)calloc(N + 1, sizeof(vertice));

        for(i = 0; i < M; i++) {
            scanf("%d %d",&a,&b);
            vertices[a].lista_adj[vertices[a].tam_lista_adj] = b;
            vertices[a].tam_lista_adj++;
            vertices[b].lista_adj[vertices[b].tam_lista_adj] = a;
            vertices[b].tam_lista_adj++;
        }
        printf("\nCaso #%d", j+1);
        dfs2(vertices, N, 1, 1);
        if (bridge_count == 0) {
            printf("\nSem pontes");
        } else {
            printf("\nTotal de pontes: %d\n", bridge_count);
        }
    }
    return 0;
}

void mostrar_tudo (vertice * vertices, int qtd_vertices) {
    int i, j;

    for(i = 1; i <= qtd_vertices; i++) {
        for(j = 0; j < vertices[i].tam_lista_adj; j++) {
            printf("%d ", vertices[i].lista_adj[j]);
        }
    }
}

void dfs2(vertice * vertices, int qtd_vertices, int raiz, int pai) {
    int i,filho;

    vertices[raiz].visitado = 1;
    vertices[raiz].in = count;
    vertices[raiz].lower = count;
    count++;

    for(i = 0; i < vertices[raiz].tam_lista_adj; i++) {
        filho = vertices[raiz].lista_adj[i];
        if (filho == pai) {
            continue;
        } else {
            if (vertices[filho].visitado == 1) {
                //back edge
                vertices[raiz].lower = menor(vertices[raiz].lower,vertices[filho].in);
            } else {
                //forward edge
                dfs2(vertices,qtd_vertices,filho,raiz);

                if (vertices[filho].lower > vertices[raiz].in) {
                    bridge_count++;
                    printf("\nPonte #%d: %d %d ", bridge_count, raiz, filho); //ponte entre
                } 
                vertices[raiz].lower = menor(vertices[raiz].lower, vertices[filho].lower);
            }
        }
    }
}

int menor(int a, int b) { 
    return a < b ? a : b;
}