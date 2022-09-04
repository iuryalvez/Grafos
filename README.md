# Grafos

Repositório para implementação de códigos a respeito de grafos

### Lista de Adjacências 1

Lista de adjacências utilizando esta estrutura:

    struct grafo {
        int eh_ponderado; // informa se é ponderado ou não (as ligações possuirem peso)
        int n_vertices; // número de elementos (deve ser informado e fixo)
        int grau_max; // grau máximo: quantas arestas/ligações cada vértice/nó pode ter
        int **arestas; // guarda as conexões, as linhas representa os vértices e as colunas as ligações (lista de adjacências)
        float **pesos; // se for grafo ponderado (as ligações possuem peso)
        int *grau; // quantas ligações já existe em cada vértice
    };

    typedef struct grafo Grafo;

### Lista de Adjacências 2

Lista de adjacências utilizando esta estrutura:  

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

### Funções
