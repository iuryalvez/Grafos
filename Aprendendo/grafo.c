#include "grafo.h"

void menu() {
    printf("1 - Criar grafo\n");
    printf("2 - Inserir aresta\n");
    printf("3 - Remover aresta\n");
    printf("4 - Imprimir informacoes do grafo\n");
    printf("5 - Calcular profundidade dos elementos\n");
    // printf("99 - Destruir grafo\n");
    printf("0 - Sair\n");
}

Grafo *criarGrafo() {

    Grafo *grafo = malloc(sizeof(Grafo)); // alocando memória para o grafo    
    
    printf("\tNumero de vertices: ");
    scanf("%d", &grafo->n_vertices); // n_vertices = número de vértices/nós
    while (grafo->n_vertices < 0) {
        printf("\tO numero de vertices deve ser maior do que 0.\n");
        printf("\tNumero de vertices: ");
        scanf("%d", &grafo->n_vertices); // n_vertices = número de vértices/nós
    }

    printf("\tGrau maximo: ");
    scanf("%d", &grafo->grau_max); // grau_max = máximo de arestas/ligações que um grafo pode ter
    while (grafo->grau_max < 0 || grafo->grau_max > grafo->n_vertices) {
        printf("\tO valor do grau maximo deve ser maior do que 0 e menor que o numero de vertices.\n");
        printf("\tGrau maximo: ");
        scanf("%d", &grafo->grau_max); // n_vertices = número de vértices/nós
    }
    
    printf("\tEh ponderado?\n\t0 - Nao\t1 - Sim\n\t");
    scanf("%d", &grafo->eh_ponderado); // se for ponderado 1, se não 0
    while (grafo->eh_ponderado < 0 || grafo->eh_ponderado > 1) {
        printf("\tDigito invalido!\n");
        printf("\tEh ponderado?\n\t1 - Sim\t0 - Nao\n\t");
        scanf("%d", &grafo->eh_ponderado); // se for ponderado 1, se não 0
    }
    
    if (grafo) { // se retornar verdadeiro, está alocado corretamente 
        grafo->grau = aloca_vetor_int(grafo->n_vertices); // alocando memória para o máximo de arestas que um vértice pode ter (ligar com todos)
        grafo->arestas = aloca_matriz_int(grafo->n_vertices,grafo->n_vertices); // alocando memória para o armazenar o máximo de arestas (ligar com todos)
        if (grafo->eh_ponderado) grafo->pesos = aloca_matriz_float(grafo->n_vertices,grafo->n_vertices); // se for ponderado, precisa armazenar memória para os pesos
        printf("\tGrafo criado com sucesso!\n\n");
        return grafo;
    }
    else {
        printf("Erro de memoria [criarGrafo]!\n");
        return NULL;
    }
}

void liberarGrafo(Grafo *grafo) { // liberando memória para todos as estruturas alocadas dinamicamente
    if (grafo) {
        libera_matriz_int(grafo->arestas, grafo->n_vertices); // liberando a lista de adjacências
        if (grafo->eh_ponderado) libera_matriz_float(grafo->pesos, grafo->n_vertices); // liberando os pesos
        libera_vetor_int(grafo->grau); // liberando as ligações
        free(grafo); // liberando o grafo
        grafo = NULL;
        // printf("\tGrafo liberado com sucesso!\n\n");
    }
    else printf("Erro de memoria [liberarGrafo]!\n"); 
}


int inserirAresta(Grafo *grafo, int orig, int dest, int eh_digrafo, float peso) {
    if (grafo != NULL) {
        if (orig < 0 || orig >= grafo->n_vertices) {
            printf("Erro (src)! [inserirAresta]\n");
            return FALSE; // minha origem deve ser um valor valido (uma posição válida na lista de adjacências)
        }
        if (dest < 0 || dest >= grafo->n_vertices) { 
            printf("Erro (dest)! [inserirAresta]\n");
            return FALSE; // meu destino deve ser um valor valido (uma posição válida na lista de adjacências) 
        }
        grafo->arestas[orig][grafo->grau[orig]] = dest; // na lista de adjacências, armazenamos a ligação 'i' de orig que é com o dest 
        if (grafo->eh_ponderado) grafo->pesos[orig][grafo->grau[orig]] = peso; // se for ponderado, armazenamos na lista de pesos, o peso dessa ligação
        grafo->grau[orig]++; // atualizando para a próxima ligação
        if (eh_digrafo == 0) inserirAresta(grafo,dest,orig,1,peso); // se NÃO for digrafo, dest também tem que se ligar ao orig, então passamos trocados o orig e o dest
        printf("\tAresta inserida com sucesso entre os vertices '%d' e '%d'!\n\n", orig, dest);
        return TRUE;
    }
    else {
        printf("Erro de memoria [inserirAresta]!\n");
        return FALSE;
    }
}

int removerAresta(Grafo *grafo, int orig, int dest, int eh_digrafo) {
    if (grafo != NULL) {
        if (orig < 0 || orig >= grafo->n_vertices) {
            printf("Erro (src)! [removerAresta]\n\n");
            return FALSE; // minha origem deve ser um valor valido (uma posição válida na lista de adjacências)
        }
        if (dest < 0 || dest >= grafo->n_vertices) {
            printf("Erro (dest)! [removerAresta]\n\n");
            return FALSE; // minha origem deve ser um valor valido (uma posição válida na lista de adjacências)
        }
            
        int i = 0;
        while (i < grafo->grau[orig] && grafo->arestas[orig][i] != dest) i++; // procurando a aresta
        
        if (i == grafo->grau[orig]) return FALSE; // se não for encontrado
        
        grafo->grau[orig]--; // menos uma aresta
        grafo->arestas[orig][i] = grafo->arestas[orig][grafo->grau[orig]]; // colocando o ultimo valor na posição que foi removida
        if (grafo->eh_ponderado) grafo->pesos[orig][i] = grafo->pesos[orig][grafo->grau[orig]]; // colocando o ultimo valor na posição que foi removida
        if (eh_digrafo == 0) removerAresta(grafo, dest, orig, 1); // removendo a aresta que liga dest a orig se NÃO for digrafo
        printf("\tAresta removida com sucesso entre os vertices '%d' e '%d'!\n\n", orig, dest);
        return TRUE;
    }
    else {
        printf("Erro de memoria! [removerAresta]\n\n");
        return FALSE;
    }
}

void imprimirGrafo(Grafo *grafo) {
    int i;
    if (grafo) {
        printf("\tO grafo possui %d vertices\n", grafo->n_vertices);
        printf("\tO grau maximo de cada vertice eh %d\n", grafo->grau_max);
        printf("\n\tLista de adjacencias\n\n");
        print_matriz_int(grafo->arestas,grafo->n_vertices,grafo->n_vertices);
        
        if (grafo->eh_ponderado == 1) {
            printf("\tLista de pesos das adjacencias\n\n");
            print_matriz_float(grafo->pesos,grafo->n_vertices,grafo->n_vertices);
        } else printf("\n\tO grafo nao eh ponderado\n\n");
        
        printf("\n\tLigacoes de cada vertice:\n\n");
        print_vetor_int(grafo->grau, grafo->n_vertices);
        printf("\n");
    
    } else printf("Erro de memoria! [imprimirGrafo]\n\n");   
}

void buscaProfundidade(Grafo *grafo, int beg, int *vis, int cont) {
    // a função utiliza as informações do grafo para calcular a profundidade de cada elemento
    // verifica-se por linha da matriz de adjacências as conexões de cada elemento e quão profundas elas são (de acordo com o cont)
    int i; // calcula a profundidade de acordo com o vértice de origem 'beg'
    vis[beg] = cont; // marca o vértice visitado com cont (se for 0 é pq n foi visitado), visita os vizinhos ainda não visitados
    for (i = 0; i < grafo->grau[beg]; i++) {
        if (!vis[grafo->arestas[beg][i]]) buscaProfundidade(grafo,grafo->arestas[beg][i],vis,cont+1); // passa o cont+1 pq significa que esta mais profundo em relação ao beg
    }
}

void auxBP(Grafo *grafo, int beg, int *vis) {
    // zera as posições para o cálculo da profundidade de inícios diferentes
    int i, cont = 1;
    for (i = 0; i < grafo->n_vertices; i++) {
        vis[i] = 0; // preenche o vetor de visitados com o valor 0, marca os vertices nao visitados
    }
    buscaProfundidade(grafo,beg,vis,cont);
}
