#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int cor;
    struct lista *lista_adjacencia;
} vertice;

typedef struct lista
{
    int quantidade_elementos;
    struct registro *inicio;
} lista;

typedef struct registro
{
    int valor;
    struct registro *proximo;
} registro;

lista *inicializarLista()
{
    lista *nova_lista;
    nova_lista = (lista *)calloc(1, sizeof(lista));
    return nova_lista;
}

registro *inicializarRegistro()
{
    registro *novo_registro;
    novo_registro = (registro *)calloc(1, sizeof(registro));
    return novo_registro;
}

void addNaLista(lista *lista, int valor_vertice)
{
    registro *novo_registro = inicializarRegistro();
    novo_registro->valor = valor_vertice;
    registro *aux;

    if (lista->inicio == NULL)
    {
        lista->inicio = novo_registro;
        lista->quantidade_elementos++;
        return;
    }

    aux = lista->inicio;
    while (aux->proximo != NULL)
    {
        aux = aux->proximo;
    }
    aux->proximo = novo_registro;
    lista->quantidade_elementos++;
}

void imprimirLista(lista *lista)
{
    if (lista->inicio == NULL)
    {
        printf("A lista está vazia\n");
    }

    registro *aux;
    aux = lista->inicio;
    for (int i = lista->quantidade_elementos; i > 0; i--)
    {
        printf("%d -> ", aux->valor);
        aux = aux->proximo;
    }
    printf("NULL \n\n");
}

// esse push serve para adicionar um registro na lista de adjacência de um vértice específico
void push(vertice *vertice, int a)
{
    if (vertice->lista_adjacencia == NULL)
    {
        vertice->lista_adjacencia = inicializarLista();
    }
    addNaLista(vertice->lista_adjacencia, a);
    vertice->lista_adjacencia->quantidade_elementos++;
}

void imprimirGrafo(int qtd_vertices_grafo, vertice *v)
{

    for (int i = 1; i < qtd_vertices_grafo + 1; i++)
    {
        printf("Lista de adjacencias do vertice %d : ", i);
        imprimirLista(v[i].lista_adjacencia);
        printf("\n");
    }
}

int dfs(vertice *vertices, int raiz, int cor)
{
    registro *aux;
    vertices[raiz].visitado = 1;
    vertices[raiz].cor = cor;

    if (vertices[raiz].lista_adjacencia == NULL)
    {
        return -1;
    }

    aux = vertices[raiz].lista_adjacencia->inicio;

    while (aux != NULL)
    {

        if (vertices[aux->valor].visitado == 0)
        {
            if (!dfs(vertices, aux->valor, vertices[raiz].cor * -1))
            {
                return 0;
            };
        }
        else
        {
            if (vertices[aux->valor].cor == vertices[raiz].cor)
            {
                return 0;
            }
        }

        aux = aux->proximo;
    }

    return 1;
}

int main()
{

    int qtd_vertices_grafo;
    int qtd_arestas_grafo;
    int qtd_casos;

    scanf("%d", &qtd_casos);

    while (qtd_casos--)
    {
        int a, b;

        scanf("%d %d", &qtd_vertices_grafo, &qtd_arestas_grafo);

        vertice *vertices = (vertice *)calloc(10000, sizeof(vertice));

        for (int i = 0; i < qtd_arestas_grafo; i++)
        {
            scanf("%d %d", &a, &b);
            push(&vertices[a], b);
            push(&vertices[b], a);
        }
        
        int flag = 0;
        printf("Scenario #%d:\n", qtd_casos);

        for (int i = 1; i < qtd_vertices_grafo; i++) {
            if (vertices[i].visitado == 0) {
                if (!dfs(vertices, i, 1)) {
                    flag = 1;
                }
            }
        }

        if (flag)
            printf("Suspicious bugs found!\n");
        else
            printf("No suspicious bugs found!\n");

        free(vertices);
    }

    return 0;
}