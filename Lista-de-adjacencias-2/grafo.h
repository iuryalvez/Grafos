#include <stdio.h>
#include <stdlib.h>

#define TRUE 1;
#define FALSE 0;

struct vertice {
    int *arestas; // guarda as conexões, é a lista de adjacências, cada elemento do vetor é uma aresta do vértice com outro
    float *pesos; // se for grafo ponderado (as ligações possuem peso), cada elemento representa o peso de uma das arestas do vetor de arestas 
    int grau; // quantas ligações existe no vértice
};

typedef struct vertice Vertice;

struct grafo {
    int eh_ponderado; // informa se é ponderado ou não (as ligações possuirem peso)
    int n_vertices; // número de elementos (deve ser informado e fixo)
    int grau_max; // grau máximo: quantas arestas/ligações cada vértice/nó pode ter
    Vertice *vertices; // vetor de vertices, cada posição é um vértice
};

typedef struct grafo Grafo;

void menu();

Grafo *criarGrafo();

void liberarGrafo(Grafo *grafo);

Vertice *criarVertices (Grafo *grafo);

void liberarVertices (Grafo *grafo);

int inserirAresta(Grafo *grafo, int orig, int dest, int eh_digrafo, float peso);

int removerAresta(Grafo *grafo, int orig, int dest, int eh_digrafo);

void imprimirGrafo(Grafo *grafo);

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
 * @brief função auxiliar da buscaProfundidade que zera o vetor de visitados (cálculo da profundidade)
 * 
 * @param grafo grafo referência
 * @param src início
 * @param vis vetor de visitados
 */
void auxBP(Grafo *grafo, int src, int *vis);

void buscaLargura(Grafo *grafo, int src, int *vis);

int *alocarVisitados(int tam);

void imprimirVisitados(int *visitados, int tam);
