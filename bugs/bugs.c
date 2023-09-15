#include <stdio.h>
#include <stdlib.h>

typedef struct vertice {
    int visitado;
    int cor;
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

void push(vertice *vertice, int a) {
    if(vertice->lista_adjacencia == NULL) {
        vertice->lista_adjacencia = inicializarLista();
    }
    addNaLista(vertice->lista_adjacencia, a);
}

int dfs(vertice *v, int no_raiz, int cor) {
    registro *aux;
    v[no_raiz].visitado = 1;
    v[no_raiz].cor = cor;

    if(v[no_raiz].lista_adjacencia == NULL) { //se não tiver arestas
        return 0; //acabou
    }

    aux = v[no_raiz].lista_adjacencia->inicio; //inicializa aux para apontar para o início da lista de adjacência da raiz

    while(aux != NULL) { //loop para percorrer a lista de adjacência da raiz
        if(v[aux->valor].visitado == 0) { //se não foi visitado
            if (!dfs(v, aux->valor, v[no_raiz].cor*-1)) {  
                return 0;
            };
        } else {
            if (v[aux->valor].cor == v[no_raiz].cor) {
                return 0;
            }
        }
        aux = aux->proximo; //vai pro próximo vértice adjacente
    }

    return 1;
}

int main() {

    int qtd_cenarios; //grafos
    int qtd_bugs; //vertices
    int qtd_interacoes; //arestas
    
    printf("Input:\n");
    scanf("%d", &qtd_cenarios);

    int *resultados = (int*)calloc(qtd_cenarios + 1, sizeof(int));
    
    for(int cenario = 1; cenario <= qtd_cenarios; cenario++) {
        scanf("%d %d", &qtd_bugs, &qtd_interacoes);
        vertice *vertices = (vertice*)calloc(qtd_bugs + 1, sizeof(vertice));

        int a, b;
        //pegar arestas e colocar os vertices delas no grafo 
        for (int j = 0; j < qtd_interacoes; j++) {
            scanf("%d %d", &a, &b);
            push(&vertices[a], b);
            push(&vertices[b], a);
        }

        int achou = 0;
        for(int k = 1; k <= qtd_bugs; k++) {
            if(vertices[k].visitado == 0) {
                if(!dfs(vertices, k, 1)) {
                    achou = 1;
                }
            }
        }
        resultados[cenario] = achou;

        free(vertices);
    }

    for (int cenario = 1; cenario <= qtd_cenarios; cenario++) {
        printf("Scenario #%d:\n", cenario);
        if (resultados[cenario] == 1) {
            printf("Suspicious bugs found!\n");
        } else {
            printf("No suspicious bugs found!\n");
        }
    }
    
    free(resultados);
    
    return 0;
}