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

Grafo *criarGrafo(int n_vertices, int grau_max, int eh_ponderado);

void liberarGrafo(Grafo *grafo);

int inserirAresta(Grafo *grafo, int orig, int dest, int eh_digrafo, float peso);

int removerAresta(Grafo *grafo, int orig, int dest, int eh_digrafo);

void imprimirGrafo(Grafo *grafo);
