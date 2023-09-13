Esse repositório guarda meu material de estudo para a disciplina de Teoria dos grafos - Curso de Ciência da Computação - IESB/Sul - 2023.2.

# Grafos
Grafo é um par de conjuntos onde um primeiro conjunto são de vértices e o segundo conjunto são pares de vértices (arestas) que pertencem ao primeiro conjunto.

## Formas de representação
Existem duas formas: matriz de adjacência (listar no formato de linha coluna todos os vértices) e lista de adjacências. É preciso "mapear" o grafo para saber seus vértices e arestas.

**OBS**: Não é pq um vértice não está conectado a outro vértice que ele não pertence ao grafo. Se faz parte do conjunto, faz parte do grafo.
## Lista de adjacências
A lista de adjacência é implementada usando uma lista encadeada, onde cada nó da lista (registro) representa um vértice adjacente. Isso permite uma representação eficiente de grafos, especialmente quando se trata de grafos esparsos, onde nem todos os vértices estão conectados entre si.

## Classificação
Existe uma classificação de grafos que separa grafos direcionais e grafos não-direcionais:
- Grafos não-direcionais: as arestas indicam a direção pros dois lados (indo e voltando)
- Grafos direcionais: as arestas possuem direção

## Estruturas do código
Utiliza-se aqui três estruturas para compor o grafo, conforme o código abaixo.

```c
typedef struct vertice {
    int visitado;
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
```

A imagem abaixo organiza as estruturas das quais precisaremos. Cada uma delas tem uma cor e a seguir será explicado como funcionam.
![Imagem da estrutura de código com cores para cada uma delas. Vértices são laranjas, listas são verdes e registros são rosas.](./imagens/img_01.png)

Para entender melhor como funciona, vamos seguir os seguintes passos:
1. Criamos os vértices A, B e C

![Imagem de três vértices A, B e C sem nenhum conteúdo ainda neles.](./imagens/img_02.png)

2. Inicializamos o campo visitado dos vértices
![Imagem de cada um dos vértices com "A.visitado = 0", para cada um deles. Destaque para lembrar que a estrutura do vértice inclui um inteiro e uma struct de lista. Tudo está com a cor laranja.](./imagens/img_03.png)


3. Vamos criar as listas de adjacências para os vértices
![Lista A, Lista B e Lista C são inicializadas na cor verde. Conta com o desenho de um retângulo escrito "registro" dentro e "lista_A.quantidade = 0" ao lado, para cada uma das listas. Destaque para lembrar que a estrutura da lista inclui um inteiro que se refere à quantidade de elementos dela e uma struct de registro que aponta para o início da lista.](./imagens/img_04.png)

4. Criaremos os registros com seus valores
![Imagem na cor rosa com três retângulos divididos ao meio, com um número dentro de cada um no lado esquerdo e no lado direito um círculo. Os números são 1, 2 e 3. Destaque para lembrar que os números se referem ao valor do registro e uma struct do tipo registro, que aponta para um próximo registro](./imagens/img_05.png)

5. Vamos ligar um dos registros na lista de adjacência de A
![Está escrito "lista_A", tem um retângulo desenhado e escrito "lista.Aqtd = 1", tudo na cor verde. Dentro do retângulo verde, tem um outro retângulo rosa, que se refere a um registro. Esse registro é do número 1 e ele está com uma seta horizontal para a direita saindo do círculo, mas ainda sem apontar para nenhum outro registro.](./imagens/img_06.png)

6. Vamos dizer que o registro 1 está ligado (aponta) para o registro 2
![Aqui há um retângulo dividido ao meio, com o número 1 dentro dele no lado esquerdo e no lado direito um círculo, que tem uma seta horizontal apontando para a direita. Agora essa seta aponta para um retângulo dividido ao meio, com o número 2 dentro dele no lado esquerdo e no lado direito um círculo, que tem uma seta horizontal apontando para a direita, mas nenhum registro depois dela.](./imagens/img_07.png)

7. Assim, imediatamente a lista A vai mudar, já que o registro que ela contém (1)
agora inclui seu vizinho (2), ou seja, aponta para alguém (2)
![A imagem anterior se repete, porém agora ela é totalmente englobada por um retângulo maior, da cor verde, com o nome "lista_A" ao lado dele.](./imagens/img_08.png)

8. Não podemos esquecer de atualizar a quantidade de elementos na lista de adjacência de A
![Mesma imagem anterior, porém agora há um texto "lista_A.qtd = 2" na cor verde.](./imagens/img_09.png)

9. Também temos que atualizar o vértice A para ele apontar para a lista correta
![Mesma imagem anterior, porém tudo é englobado por um retângulo laranja, com o texto "A" ao lado.](./imagens/img_10.png)

É assim que a estrutura de um vértice funciona nesse algoritmo. Dá pra entender que todas essas coisas estão conectadas. A lista não precisa guardar todos os vértices dentro dela porque o próprio vértice já tem em si a informação de pra quem ele vai apontar. Logo, sabendo o início da lista (de qual elemento se trata) e a quantidade de vértices vizinhos, conseguimos ter o controle de, posteriormente, percorrer essa lista de adjacências de um vértice.

## Algumas funções iniciais para desenvolver o grafo

Arquivo de referência para ver tudo funcionando: 01_introducao.c

Aqui vamos desenvolver:
- `inicializarLista();`
- `inicializarRegistro();`
Essas funções o nome já diz tudo. Elas alocam memória para que essas estruturas sejam inicializadas, para isso usamos o [calloc()](https://pt.stackoverflow.com/questions/179205/qual-%C3%A9-a-diferen%C3%A7a-entre-calloc-e-malloc).

- `addNaLista();`
- `imprimirLista();`
Essas funções servem para adicionar um novo registro numa lista e imprimir uma lista específica.

- `push();`
**Aqui a gente tá falando da elite**: serve para adicionar um registro na lista de adjacência de um vértice específico

- `imprimirGrafo();`
Imprime cada um dos vértices e suas listas de adjacências.

No arquivo de referência é muito importante notar a linha 88. Segue a `main` pra mostrar aqui:

```c
int main() {
    int qtd_vertices_grafo;
    int qtd_arestas_grafo;
    int a, b;

    printf("Digite a quantidade de vértices do grafo\n");
    scanf("%d", &qtd_vertices_grafo);
    vertice *vertices = (vertice*)calloc(10000, sizeof(vertice));

    printf("Digite a quantidade de arestas do grafo\n");
    scanf("%d", &qtd_arestas_grafo);

    printf("Digite as arestas do grafo:\n");
    for(int i = 0; i < qtd_arestas_grafo; i++) {
        scanf("%d %d", &a, &b);
        push(&vertices[a], b);
        push(&vertices[b], a);
    }

    printf("Hora da verdade:\n");
    imprimirGrafo(qtd_vertices_grafo, vertices);

    return 0;
}
```
Isso daqui `vertice *vertices = (vertice*)calloc(10000, sizeof(vertice));` é muito importante, porque vai garantir que a gente possa alocar um vetor de vértices e depois possa acessá-los, o que é basicamente a estrutura do grafo. 

A nossa função `push()` vai fazer todo o trabalho de basicamente adicionar uma nova aresta no grafo.

## Referências
[SOpt](https://github.com/maniero/SOpt/tree/master/C)