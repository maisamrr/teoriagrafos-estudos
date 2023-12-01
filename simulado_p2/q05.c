#include <stdio.h>
#include <limits.h>

#define V 1000

int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int graph[V][V], int src, int dest) {
    int dist[V];
    int sptSet[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;
    dist[src] = 0;
    for (int count = 0; count < V-1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    if(dist[dest] != INT_MAX) {
        printf("Distância: %d\n", dist[dest]);
    } else {
        printf("NO\n");
    }
}

int main() {
    int t;
    printf("Programa inicializado\n");
    scanf("%d", &t);
    while(t--) {
        int v, k;
        scanf("%d %d", &v, &k);
        int graph[V][V] = {0};
        for(int i = 0; i < k; i++) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            graph[a][b] = c;
        }
        int A, B;
        scanf("%d %d", &A, &B);
        dijkstra(graph, A, B);
    }
    return 0;
}
