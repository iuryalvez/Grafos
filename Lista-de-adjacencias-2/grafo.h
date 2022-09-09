#include <stdio.h>
#include <stdlib.h>

#define TRUE 1 // booleano
#define FALSE 0 // booleano

// estrutura de um vértice
struct vertice {
    int *arestas; // guarda as conexões, é a lista de adjacências, cada elemento do vetor é uma aresta do vértice com outro
    float *pesos; // se for grafo ponderado (as ligações possuem peso), cada elemento representa o peso de uma das arestas do vetor de arestas 
    int grau; // quantas ligações existe no vértice
};

typedef struct vertice Vertice;

// estrutura de um grafo
struct grafo {
    int eh_ponderado; // informa se é ponderado ou não (as ligações possuirem peso)
    int n_vertices; // número de elementos (deve ser informado e fixo)
    int grau_max; // grau máximo: quantas arestas/ligações cada vértice/nó pode ter
    Vertice *vertices; // vetor de vertices, cada posição é um vértice (lista de adjacências)
};

typedef struct grafo Grafo;

// menu de opções da função main
void menu();

/**
 * @brief função que aloca memória para armazenar um grafo
 * 
 * @return Grafo* grafo alocado dinamicamente 
 */
Grafo *criarGrafo();

/**
 * @brief função que libera o grafo alocado dinamicamente
 * 
 * @param grafo grafo referente
 */
void liberarGrafo(Grafo *grafo);

/**
 * @brief função que aloca dinamicamente o vetor de vértices de um grafo (a lista de adjacências)
 * 
 * @param grafo grafo referente
 * @return Vertice* vetor de vértices (lista de adjacências)
 */
Vertice *criarVertices (Grafo *grafo);

/**
 * @brief função que libera os vértices alocados dinamicamente
 * 
 * @param grafo grafo referente
 */
void liberarVertices (Grafo *grafo);

/**
 * @brief 
 * 
 * @param grafo grafo referente
 * @param orig vértce origem
 * @param dest vértice destino
 * @param eh_digrafo informa se a aresta é direcionada
 * @param peso informa o peso da aresta (se houver)
 * @return int booleano
 */
int inserirAresta(Grafo *grafo, int orig, int dest, int eh_digrafo, float peso);

/**
 * @brief função que remove uma aresta entre dois vértices
 * 
 * @param grafo grafo referente
 * @param orig vértice origem
 * @param dest vértice destino
 * @param eh_digrafo informa se a aresta é direcionada
 * @return int booleano
 */
int removerAresta(Grafo *grafo, int orig, int dest, int eh_digrafo);

/**
 * @brief função que imprime o grafo e suas informações complementares
 * 
 * @param grafo grafo referente
 */
void imprimirGrafo(Grafo *grafo);

/**
 * @brief função que imprime os vértices do grafo em formato de lista de adjacências
 * 
 * @param grafo grafo referente
 */
void imprimirVertices(Grafo *grafo);

/**
 * @brief função recursiva que calcula a profundidade dos elementos de um grafo de acordo com uma posição (src) de início
 * 
 * @param grafo grafo referência
 * @param src posição de início
 * @param vis vetor de visitados
 * @param cont contador de profundidade
 */
void buscaProfundidade(Grafo *grafo, int src, int *vis, int cont);

/**
 * @brief função iterativa que calcula a largura dos vértices vizinhos do vértice src
 * 
 * @param grafo grafo referente
 * @param src vértice inicial, calcula a largura a partir dele
 * @param vis vetor de visitados, retorna a largura de cada vértice (cada vértice é uma posição 'i' do vetor)
 */
void buscaLargura(Grafo *grafo, int src, int *vis);

/**
 * @brief função que aloca um vetor de inteiros via malloc
 * 
 * @param tam tamanho do vetor
 * @return int* um endereço de memória de um vetor alocado
 */
int *alocarVetor_I(int tam);

/**
 * @brief função que aloca memória dinamicamente para o vetor de distâncias
 * 
 * @param tam tamanho do vetor
 * @return float* vetor alocado dinamicamente
 */
float *alocarVetor_F(int tam);

/**
 * @brief função que imprime o vetor de visitados em formatação compreensível
 * 
 * @param visitados vetor de visitados
 * @param tam tamanho do vetor
 */
void imprimirVisitados(int *visitados, int tam);

/**
 * @brief função que imprime as distâncias entre os vértices
 * 
 * @param dist vetor de distâncias
 * @param tam tamanho do vetor
 */
void imprimirDist(float *dist, int tam);

/**
 * @brief função auxiliar das buscas que zera o vetor de visitados para novas eventuais buscas
 * 
 * @param visitados vetor de visitados
 * @param tam tamanho do vetor
 */
void auxBuscas(int *visitados, int tam);

/**
 * @brief função que busca pelo menor caminho entre dois vértices
 * 
 * @param grafo grafo referente
 * @param ini vértice inicial
 * @param ordem ordem de visitação para chegar no vértice final pelo menor caminho
 * @param dist distância do vértice inicial até o vértice final
 */
void menorCaminho(Grafo *grafo, int ini, int *ordem, float *dist);

/**
 * @brief função auxiliar da menorCaminho() que procura vértice com menor distância até o momento e que não tenha sido visitado
 * 
 * @param dist distância vértice inicial até o final
 * @param visitados vetor de visitados
 * @param NV número de vértices
 * @return int 
 */
int procuraMenorDistancia(float *dist, int *visitados, int NV);

/**
 * @brief função que executa o algoritmo de Boruvka em um grafo
 * 
 * @param grafo grafo referente
 * @param ordem ordem dos elementos
 * @param dist distâncias entre cada vértice 
 */
void algoritmoBoruvka(Grafo *grafo, int *ordem);


/**
 * @brief função que encontra o vizinho mais próximo de um grupo de vizinhos
 * 
 * @param V vetor de vértices
 * @param grupo grupo de vizinhos
 * @param ord retorna o vértice que eu preciso acessar para chegar em VMP
 * @return int vizinho mais pŕoximo do grupo (VMP)
 */
int VMPdoGrupo(Vertice *V, int *grupo, int *ord);

/**
 * @brief função que encontra o vizinho mais próximo do vértice da posição pos
 * 
 * @param V vértice referente
 * @param pos vértice que precisamos encontrar o vizinho mais próximo
 * @return int vizinho mais próximo 
 */
int VMPdoVertice(Vertice V, int *grupo);

/**
 * @brief função que une o vetor G1 com o vetor G2
 * 
 * @param G1 vetor G1
 * @param G2 vetor G2
 */
void unirGrupos(int *G1, int *G2);

/**
 * @brief função que retorna o tamanho do grupo
 * 
 * @param grupo grupo marcado com -1 no final para saber o tamanho
 * @return int tamanho do grupo
 */
int tamanhoGrupo(int *grupo);

/**
 * @brief função que busca um vértice no grupo
 * 
 * @param grupo grupo referente
 * @param elem elemento que será buscado
 * @return int TRUE (1) se está, FALSE (0) se não
 */
int buscaVerticeNoGrupo(int *grupo, int elem);

/**
 * @brief função que inicializa os valores do grupo (-1) e i para grupo[i][0]
 * 
 * @param grupos matriz de grupos
 * @param tam tamanho do número de vértices
 */
void inicializaGrupos(int **grupos, int tam);

/**
 * @brief função que inicializa o vetor de valores válidos (todos são válidos no começo)
 * 
 * @param validos vetor de válidos
 * @param tam tamanho do vetor
 */
void inicializaValidos(int *validos, int tam);

/**
 * @brief inicializa a ordem a ser percorrida para encontrar os elementos
 * 
 * @param ordem vetor ordem
 * @param tam tamanho do vetor
 */
void inicializaOrdem(int *ordem, int tam);

/**
 * @brief função que imprime um grupo
 * 
 * @param grupo grupo referente
 */
void imprimirGrupo(int *grupo);

/**
 * @brief função que imprime a ordem formatada
 * 
 * @param ordem ordem referente
 * @param tam tamanho do vetor
 */
void imprimirOrdem(int *ordem, int tam);

/**
 * @brief função que calcula o vetor de distâncias
 * 
 * @param grafo grafo referente
 * @param ordem vetor da ordem
 * @param dist vetor de distâncias
 */
void calcularDist(Grafo *grafo, int *ordem, float *dist);

/**
 * @brief função que aloca a matriz de grupos
 * 
 * @param tam tamanho do grafo (núm. de vért.)
 * @return int** matriz alocada
 */
int **alocarGrupos(int tam);

/**
 * @brief função que libera a memória da matriz de grupos
 * 
 * @param grupos matriz de grupos
 * @param tam tamanho (núm. de vért.)
 */
void liberarGrupos(int **grupos, int tam);

// Limpa o terminal
void clear_screen();
