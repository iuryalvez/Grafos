#include "vet-mat.h"

struct grafo {
    int eh_ponderado; // informa se é ponderado ou não (as ligações possuirem peso)
    int n_vertices; // número de elementos (deve ser informado e fixo)
    int grau_max; // grau máximo: quantas arestas/ligações cada vértice/nó pode ter
    int **arestas; // guarda as conexões, as linhas representa os vértices e as colunas as ligações (lista de adjacências)
    float **pesos; // se for grafo ponderado (as ligações possuem peso)
    int *grau; // quantas ligações já existe em cada vértice
};

typedef struct grafo Grafo;

void menu();

Grafo *criarGrafo();

void liberarGrafo(Grafo *grafo);

int inserirAresta(Grafo *grafo, int orig, int dest, int eh_digrafo, float peso);

int removerAresta(Grafo *grafo, int orig, int dest, int eh_digrafo);

void imprimirGrafo(Grafo *grafo);

/**
 * @brief função recursiva que calcula a profundidade dos elementos de um grafo de acordo com uma posição (beg) de início
 * 
 * @param grafo grafo referência
 * @param beg posição de início
 * @param vis vetor de visitados
 * @param cont contador de profundidade
 */
void buscaProfundidade(Grafo *grafo, int beg, int *vis, int cont);

/**
 * @brief função auxiliar da buscaProfundidade que zera o vetor de visitados (cálculo da profundidade)
 * 
 * @param grafo grafo referência
 * @param beg início
 * @param vis vetor de visitados
 */
void auxBP(Grafo *grafo, int beg, int *vis);
