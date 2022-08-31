#include "grafo.h"

Grafo *criarGrafo(int n_vertices, int grau_max, int eh_ponderado) {
    Grafo *grafo = malloc(sizeof(Grafo)); // alocando memória para o grafo    
    if (grafo) { // se retornar verdadeiro, está alocado corretamente 
        grafo->n_vertices = n_vertices; // número de vértices/nós
        grafo->grau_max = grau_max; // máximo de arestas/ligações que um grafo pode ter
        grafo->eh_ponderado = (eh_ponderado != 0) ? 1 : 0; // se for ponderado 1, se não 0
        grafo->grau = aloca_vetor_int(n_vertices); // alocando memória para o máximo de arestas que um vértice pode ter (ligar com todos)
        grafo->arestas = aloca_matriz_int(n_vertices,n_vertices); // alocando memória para o armazenar o máximo de arestas (ligar com todos)
        if (grafo->eh_ponderado) grafo->pesos = aloca_matriz_float(n_vertices,n_vertices); // se for ponderado, precisa armazenar memória para os pesos
        return grafo;
    }
    else printf("Erro de memoria!\n");
}

void liberarGrafo(Grafo *grafo) { // liberando memória para todos as estruturas alocadas dinamicamente
    if (grafo) {
        libera_matriz_int(grafo->arestas, grafo->n_vertices); // liberando a lista de adjacências
        if (grafo->eh_ponderado) libera_matriz_float(grafo->pesos, grafo->n_vertices); // liberando os pesos
        libera_vetor_int(grafo->grau); // liberando as ligações
        free(grafo); // liberando o grafo
    }
    else printf("Erro de memoria!\n"); 
}


int inserirAresta(Grafo *grafo, int orig, int dest, int eh_digrafo, float peso) {
    if (grafo != NULL) {
        if (orig < 0 || orig >= grafo->n_vertices) {
            printf("Erro! [inserirAresta]\n");
            return FALSE; // minha origem deve ser um valor valido (uma posição válida na lista de adjacências)
        }
        if (dest < 0 || dest >= grafo->n_vertices) { 
            printf("Erro! [inserirAresta]\n");
            return FALSE; // meu destino deve ser um valor valido (uma posição válida na lista de adjacências) 
        }
        grafo->arestas[orig][grafo->grau[orig]] = dest; // na lista de adjacências, armazenamos a ligação 'i' de orig que é com o dest 
        if (grafo->eh_ponderado) grafo->pesos[orig][grafo->grau[orig]] = peso; // se for ponderado, armazenamos na lista de pesos, o peso dessa ligação
        grafo->grau[orig]++; // atualizando para a próxima ligação
        if (eh_digrafo == 0) inserirAresta(grafo,dest,orig,1,peso); // se NÃO for digrafo, dest também tem que se ligar ao orig, então passamos trocados o orig e o dest
        return TRUE;
    }
    else {
        printf("Erro de memoria!\n");
        return FALSE;
    }
}

int removerAresta(Grafo *grafo, int orig, int dest, int eh_digrafo) {
    if (grafo != NULL) {
        if (orig < 0 || orig >= grafo->n_vertices) {
            printf("Erro! [removerAresta]\n");
            return FALSE; // minha origem deve ser um valor valido (uma posição válida na lista de adjacências)
        }
        if (dest < 0 || dest >= grafo->n_vertices) {
            printf("Erro! [removerAresta]\n");
            return FALSE; // minha origem deve ser um valor valido (uma posição válida na lista de adjacências)
        }
            
        int i = 0;
        while (i < grafo->grau[orig] && grafo->arestas[orig][i] != dest) i++; // procurando a aresta
        
        if (i == grafo->grau[orig]) return FALSE; // se não for encontrado
        
        grafo->grau[orig]--; // menos uma aresta
        grafo->arestas[orig][i] = grafo->arestas[orig][grafo->grau[orig]]; // colocando o ultimo valor na posição que foi removida
        if (grafo->eh_ponderado) grafo->pesos[orig][i] = grafo->pesos[orig][grafo->grau[orig]]; // colocando o ultimo valor na posição que foi removida
        if (eh_digrafo == 0) removerAresta(grafo, dest, orig, 1); // removendo a aresta que liga dest a orig se NÃO for digrafo
        return TRUE;
    }
    else {
        printf("Erro de memoria!\n");
        return FALSE;
    }
}

void imprimirGrafo(Grafo *grafo) {
    int i;
    printf("\tO grafo possui %d vertices\n", grafo->n_vertices);
    printf("\tO grau maximo de cada vertice eh %d\n", grafo->grau_max);
    printf("\n\tLista de adjacencias\n\n");
    print_matriz_int(grafo->arestas,grafo->n_vertices,grafo->n_vertices);
    if (grafo->eh_ponderado == 1) {
        printf("\tLista de pesos das adjacencias\n\n");
        print_matriz_float(grafo->pesos,grafo->n_vertices,grafo->n_vertices);
    } else printf("\n\tO grafo nao eh ponderado\n");
    printf("\n\tLigacoes de cada vertice:\n\n");
    print_vetor_int(grafo->grau, grafo->n_vertices);
    printf("\n");
}
