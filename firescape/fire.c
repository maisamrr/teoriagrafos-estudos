//https://www.codechef.com/problems/FIRESC
#include <stdio.h>
#include <stdlib.h>

typedef struct vertice {
    int visitado;
    struct lista *lista_adjacencia;
    int grupo_amigos;
} vertice;

typedef struct lista {
    int qtd_elementos;
    struct registro *inicio;
} lista;

typedef struct registro {
    int valor;
    struct registro *proximo;
} registro;

registro* inicializarRegistro() {
    registro *novo_registro = (registro*)calloc(1, sizeof(registro));

    return novo_registro;
}

lista* inicializarLista() {
    lista *nova_lista = (lista*)calloc(1, sizeof(lista));

    return nova_lista;
}

void addNaLista(lista *lista, int valor) {
    registro *novo_registro = inicializarRegistro();
    novo_registro->valor = valor;

    if(lista->inicio == NULL) {
        lista->inicio = novo_registro;
        lista->qtd_elementos++;

        return;
    }

    registro *aux = lista->inicio;
    while(aux->proximo != NULL) {
        aux = aux->proximo;
    }
    aux->proximo = novo_registro;
    lista->qtd_elementos++;
}

void push(vertice *vertice, int conteudo) {
    if(vertice->lista_adjacencia == NULL) {
        vertice->lista_adjacencia = inicializarLista();
    }

    addNaLista(vertice->lista_adjacencia, conteudo);
}

void dfs(vertice *grafo, int raiz, int grupo) {
    grafo[raiz].visitado = 1;
    grafo[raiz].grupo_amigos = grupo; // atribui o grupo de amizades

    registro *atual = grafo[raiz].lista_adjacencia->inicio;

    while (atual != NULL) {
        int vizinho = atual->valor;
        if (!grafo[vizinho].visitado) {
            dfs(grafo, vizinho, grupo);
        }
        atual = atual->proximo;
    }
}

int main() {
    int qtd_cenarios;
    int n; // n = qtd funcionarios = qtd vertices
    int m; // m = qtd de relacoes = qtd de arestas

    int i, j; // vertices das arestas

    vertice *grafo = (vertice*)calloc(10000, sizeof(vertice));

    printf("Input:\n");
    scanf("%d", &qtd_cenarios);

    for (int w = 0; w < qtd_cenarios; w++) {
        scanf("%d %d", &n, &m);

        for (int z = 1; z <= n; z++) { // inicializar o grafo para cada caso 
            grafo[z].visitado = 0; // define todos os vértices como não visitados
            grafo[z].lista_adjacencia = inicializarLista(); // cria uma lista de adjacência vazia para cada vértice
        }

        for (int k = 0; k < m; k++) {
            scanf("%d %d", &i, &j); // lê as relações de amizade e adiciona no grafo bidirecional
            push(&grafo[i], j);
            push(&grafo[j], i);
        }
        
        // cálculo do número máximo de rotas de saída de incêndio
        //usa o dfs para encontrar grupos de funcionários amigos,
        // iterando por todos os funcionários e, se um funcionário não foi visitado (ou seja, não faz parte de nenhum grupo de amizades encontrado até agora), inicia um novo dfs para encontrar todos os funcionários no mesmo grupo
        // contador num_grupos mantém o controle do número de grupos encontrados
        int num_grupos = 0;
        for (int z = 1; z <= n; z++) { 
            if (!grafo[z].visitado) {
                num_grupos++;
                dfs(grafo, z, num_grupos);
            }
        }
        printf("\nNúmero máximo de rotas de saída de incêndio: %d", num_grupos);

        // cálculo do número de maneiras de selecionar capitães
        long long num_maneiras = 1;
        for (int grupo = 1; grupo <= num_grupos; grupo++) { // percorrer todos os grupos de amizades que foram encontrados no grafo
            int num_membros_grupo = 0; // conta o número de funcionários em um grupo específico
            for (int z = 1; z <= n; z++) {  //  percorre todos os funcionários no grafo (todos os vértices)
                if (grafo[z].grupo_amigos == grupo) { // verifica se o funcionário pertence ao grupo de amizades atual
                    num_membros_grupo++; // se pertence, incrementa para contar mais um membro do grupo
                }
            }
            num_maneiras = num_maneiras * num_membros_grupo;
        }
        printf("\nNúmero de maneiras de selecionar os capitães: %lld", num_maneiras);
        printf("\n\n");
    }

    return 0;
}