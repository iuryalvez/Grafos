#include "grafo.h"

void menu() {
    printf("1 - Criar grafo\n");
    printf("2 - Inserir aresta\n");
    printf("3 - Remover aresta\n");
    printf("4 - Imprimir informacoes do grafo\n");
    printf("5 - Busca\n");
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
        grafo->vertices = criarVertices(grafo);
        printf("\tGrafo criado com sucesso!\n\n");
        return grafo;
    }
    else {
        printf("Erro de memoria [criarGrafo]!\n");
        return NULL;
    }
}

Vertice *criarVertices (Grafo *grafo) {
    int i;
    if (grafo) {
        Vertice *verts = malloc(sizeof(Vertice)*grafo->n_vertices); // alocando memória para meu visitados de vértices
        verts->grau = 0;
        for (i = 0; i < grafo->n_vertices; i++) {
            verts[i].arestas = (int *) malloc(sizeof(int)*grafo->n_vertices); // alocando memória para o armazenar o máximo de arestas (ligar com todos)
        }
        if (grafo->eh_ponderado) {
            for (i = 0; i < grafo->n_vertices; i++) {
                verts[i].pesos = (float *) malloc(sizeof(float)*grafo->n_vertices); // se for ponderado, precisa armazenar memória para os pesos
            }
        }
        return verts;
    }
    else {
        printf("Erro! [criarVertices]\n");
        return NULL;
    }
}

void liberarVertices (Grafo *grafo) {
    int i;
    for (i = 0; i < grafo->n_vertices; i++) free(grafo->vertices[i].arestas); // liberando as arestas de cada vértice
    if (grafo->eh_ponderado) {
        for (i = 0; i < grafo->n_vertices; i++) free(grafo->vertices[i].pesos); // liberando os pesos de cada vértice
    }
    free(grafo->vertices); // liberando os vértices
}

void liberarGrafo(Grafo *grafo) { // liberando memória para todos as estruturas alocadas dinamicamente
    if (grafo) {
        liberarVertices(grafo);
        free(grafo); // liberando o grafo
        grafo = NULL;
        // printf("\tGrafo liberado com sucesso!\n\n");
    }
    else printf("Erro de memoria [liberarGrafo]!\n"); 
}


int inserirAresta(Grafo *grafo, int orig, int dest, int eh_digrafo, float peso) {
    if (grafo != NULL) {
        if (orig < 0 || orig >= grafo->n_vertices) {
            printf("Erro! A posicao de origem (%d) informada eh menor que 0 ou maior que o numero possivel de vertices (%d)\n", orig, grafo->n_vertices);
            return FALSE; // minha origem deve ser um valor valido (uma posição válida na lista de adjacências)
        }
        if (dest < 0 || dest >= grafo->n_vertices) { 
            printf("Erro! A posicao de destino (%d) informada eh menor que 0 ou maior que o numero possivel de vertices (%d)\n", dest, grafo->n_vertices);
            return FALSE; // meu destino deve ser um valor valido (uma posição válida na lista de adjacências) 
        }
        grafo->vertices[orig].arestas[grafo->vertices[orig].grau] = dest; // na lista de adjacências, armazenamos a ligação 'i' de orig que é com o dest 
        if (grafo->eh_ponderado) grafo->vertices[orig].pesos[grafo->vertices[orig].grau] = peso; // se for ponderado, armazenamos na lista de pesos, o peso dessa ligação
        grafo->vertices[orig].grau++; // atualizando para a próxima ligação
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
        // executa o while enquanto i não chegar no FINAL (o tamanho do grau do vertice[orig]) e também enquanto não encontrar a aresta do vertice[orig]
        // se chegar no final, para o looping || se encontrar, para o looping
        while (i < grafo->vertices[orig].grau && grafo->vertices[orig].arestas[i] != dest) i++; // procurando a aresta
        
        if (i == grafo->vertices[orig].grau) return FALSE; // se não for encontrado
        
        grafo->vertices[orig].grau--; // menos uma aresta
        grafo->vertices[orig].arestas[i] = grafo->vertices[orig].arestas[grafo->vertices[orig].grau]; // colocando o ultimo valor na posição que foi removida, ajustando as arestas do vertice!!
        if (grafo->eh_ponderado) grafo->vertices[orig].pesos[i] = grafo->vertices[orig].pesos[grafo->vertices[orig].grau]; // colocando o ultimo valor na posição que foi removida, ajustando os pesos do vértice!!
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
        imprimirVertices(grafo);
    } else printf("Erro de memoria! [imprimirGrafo]\n\n");   
}

void imprimirVertices(Grafo *grafo) {
    int i, j;

    printf("\t        |");
    for (i = 0; i < grafo->grau_max; i++) {
        printf(" Grau%d |", i);
    }
    printf("\n");
    for (i = 0; i < grafo->n_vertices; i++) {
        printf("\t| No%3d |", i);
        for (j = 0; j < grafo->grau_max; j++) {
            if (j < grafo->vertices[i].grau) printf(" %5d |", grafo->vertices[i].arestas[j]);
        }
        printf("\n");
    } 
    if (grafo->eh_ponderado == 1) {
        printf("\tLista de pesos das adjacencias\n\n");
        printf("\t        |");
        for (i = 0; i < grafo->grau_max; i++) {
            printf(" Grau%d |", i);
        }
        printf("\n");
        for (i = 0; i < grafo->n_vertices; i++) {
            printf("\t| No %3d |", i);
            for (j = 0; j < grafo->grau_max; j++) {
                if (j < grafo->vertices[i].grau) printf(" %5f |", grafo->vertices[i].pesos[j]);
            }
            printf("\n");
        }
    } else printf("\n\tO grafo nao eh ponderado\n\n");
    
    printf("\n\tLigacoes de cada vertice:\n\n");
    for (i = 0; i < grafo->n_vertices; i++) {
        if (i == 0) printf("\n\t     Nos -> %2d", i); 
        else printf(" %2d", i);
    }
    printf("\n\t");
    i = 0;
    printf("Ligacoes -> %2d", grafo->vertices[i].grau);
    i++;
    for (; i < grafo->n_vertices; i++) {
        printf(" %2d", grafo->vertices[i].grau);
    }
    printf("\n\n");
}

int *alocarVisitados(int tam) {
    int *visitados = calloc(tam,sizeof(int));
    if (!visitados) printf("Erro de alocacao de memoria!\n");
    return visitados;
}

void imprimirVisitados(int *visitados, int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        if (i == 0) printf("\n\t   Nos -> %2d", i); 
        else printf(" %2d", i);
    }
    printf("\n\t");
    i = 0;
    printf("Niveis -> %2d", visitados[i]);
    i++;
    for (; i < tam; i++) {
        printf(" %2d", visitados[i]);
    }
    printf("\n");
}

void buscaProfundidade(Grafo *grafo, int src, int *vis, int cont) {
    // a função utiliza as informações do grafo para calcular a profundidade de cada elemento
    // verifica-se por linha da matriz de adjacências as conexões de cada elemento e quão profundas elas são (de acordo com o cont)
    int i; // calcula a profundidade de acordo com o vértice de origem 'src'
    vis[src] = cont; // marca o vértice visitado com cont (se for 0 é pq n foi visitado), visita os vizinhos ainda não visitados
    printf("\n\tProfundidade: %d | Ligacao: %d", cont, src);
    for (i = 0; i < grafo->vertices[src].grau; i++) { // visitando os vizinhos (o grafo->grau indica quantos vizinhos tem na lista de adjacências)
        if (!vis[grafo->vertices[src].arestas[i]]) {
            printf(" -> %d", grafo->vertices[src].arestas[i]);
            buscaProfundidade(grafo,grafo->vertices[src].arestas[i],vis,cont+1); // passa o cont+1 pq significa que esta mais profundo em relação ao src
        }
    } // se não foi visitado para o vizinho da posição 'i', visita e guarda as informações dele
}

void auxBP(Grafo *grafo, int src, int *vis) {
    // zera as posições para o cálculo da profundidade de inícios diferentes
    int i, cont = 1;
    for (i = 0; i < grafo->n_vertices; i++) {
        vis[i] = 0; // preenche o visitados de visitados com o valor 0, marca os vertices nao visitados
    }
    buscaProfundidade(grafo,src,vis,cont);
}

void buscaLargura(Grafo *grafo, int src, int *vis) {
    int i; // auxiliar
    int vert; // vértice atual
    int cont = 1; // largura inicial 
    int *fila; // guarda a ordem que visitou os vértices
    int IF = 0; // início da fila 
    int FF = 0; // final da fila

    for (i = 0; i < grafo->n_vertices; i++) vis[i] = 0; // zera as posições para o cálculo da largura de inícios diferentes
    
    fila = (int *) malloc(grafo->n_vertices * sizeof(int)); // cria fila
    FF++; 
    fila[FF] = src; // insere src na fila
    vis[src] = cont; // o visitados de visitados armazena o valor de cont na posição do src
    
    printf("\t%d", src);
    while (IF != FF) { // a fila está crescendo assim: 1 -> 1 2 -> 1 2 3 -> 1 2 3 4 -> ... 
        IF = (IF + 1) % grafo->n_vertices; // atualiza o próximo início da fila
        vert = fila[IF]; // pega o primeiro da fila
        cont++; // atualiza o cont para o próximo
        for (i = 0; i < grafo->vertices[vert].grau; i++) { // visitando os vizinhos (o grafo->grau indica quantos vizinhos tem na lista de adjacências)
            if (!vis[grafo->vertices[vert].arestas[i]]) { // se não foi visitado para o vizinho da posição 'i', visita e guarda as informações dele
                FF = (FF + 1) % grafo->n_vertices; // atualiza o final da fila para visitar o próximo
                fila[FF] = grafo->vertices[vert].arestas[i]; // novo final da fila
                vis[grafo->vertices[vert].arestas[i]] = cont; // visitamos ele, agora irá verificar o próximo vizinho;
                printf(" -> %d", grafo->vertices[vert].arestas[i]);
            }
        }
    }
    free(fila); // libera a fila
}
