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
    int i, j;
    if (grafo) {
        Vertice *verts = malloc(sizeof(Vertice)*grafo->n_vertices); // alocando memória para meu visitados de vértices
        verts->grau = FALSE;
        for (i = 0; i < grafo->n_vertices; i++) {
            verts[i].arestas = (int *) malloc(sizeof(int)*grafo->n_vertices); // alocando memória para o armazenar o máximo de arestas (ligar com todos)
            for (j = 0; j < grafo->n_vertices; j++) {
                verts[i].arestas[j] = -1;
            }
        }
        if (grafo->eh_ponderado) {
            for (i = 0; i < grafo->n_vertices; i++) {
                verts[i].pesos = (float *) malloc(sizeof(float)*grafo->n_vertices); // se for ponderado, precisa armazenar memória para os pesos
                for (j = 0; j < grafo->n_vertices; j++) {
                    verts[i].pesos[j] = -1;
                }
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
    // verifica-se as conexões de cada elemento da lista e quão profundas elas são (de acordo com o cont)
    int i; // calcula a profundidade de acordo com o vértice de origem 'src'
    vis[src] = cont; // marca o vértice visitado com cont (se for 0 é pq n foi visitado), visita os vizinhos ainda não visitados
    
    // printf("\n\tVisitando os vizinhos de %d:\n\n", src); // Debugando
    
    for (i = 0; i < grafo->vertices[src].grau; i++) { // visitando os vizinhos (o grafo->grau indica quantos vizinhos tem na lista de adjacências)

        // printf("\t(P:%d) Vizinho%d: %d\n\n", cont, i+1, grafo->vertices[src].arestas[i]); // Debugando
    
        if (vis[grafo->vertices[src].arestas[i]] == -1) { // se não foi visitado para o vizinho da posição 'i', visita e guarda as informações dele
            buscaProfundidade(grafo,grafo->vertices[src].arestas[i],vis,cont+1); // passa o cont+1 pq significa que esta mais profundo em relação ao src
            // printf("\tValor de vis[%d]: %d\n\n", grafo->vertices[src].arestas[i], vis[grafo->vertices[src].arestas[i]]); // Debugando
        }
        if (cont+1 < vis[grafo->vertices[src].arestas[i]]) vis[grafo->vertices[src].arestas[i]] = cont+1; // se foi encontrado em outro sub-grafo mas não é tão profundo quanto lá
    } 
}

void auxBP(Grafo *grafo, int src, int *vis) {
    // zera as posições para o cálculo da profundidade de inícios diferentes
    int i, cont = 1;
    for (i = 0; i < grafo->n_vertices; i++) {
        vis[i] = -1; // preenche o visitados de visitados com o valor -1, marca os vertices nao visitados
    }
    buscaProfundidade(grafo,src,vis,cont);
}

void buscaLargura(Grafo *grafo, int src, int *vis) {
    int i; // auxiliar
    int vert; // vértice atual
    int *ordem; // guarda a ordem que visitou os vértices
    int cont1 = 0; // início da ordem 
    int cont2 = 1; // final da ordem

    // inicializando o vetor de visitados com um valor inválido para identificarmos que não foi visitado
    for (i = 0; i < grafo->n_vertices; i++) vis[i] = -1; // -1 é o valor inváldo para sabermos que não foi visitado

    ordem = (int *) malloc(grafo->n_vertices * sizeof(int)); // cria ordem dinamicamente
    ordem[0] = src; // insere src na ordem, é o primeiro
    vis[src] = 1; // o vetor de visitaodos na posição src é o raio inicial 
    
    while (cont1 != cont2) { // iremos somar cont2 até um número limite e só pararemos quando cont1 chegar em cont2
        vert = ordem[cont1]; // pega o vert atualizado da ordem, VERIFICA OS VIZINHOS DELE
        
        // printf("\n\tVisitando os vizinhos de %d:\n", vert); // Debugando

        for (i = 0; i < grafo->vertices[vert].grau; i++) { // visitando os vizinhos (o grau do vertice indica quantos vizinhos tem na lista de adjacências)
            
            // printf("\n\tVizinho %d: %d\n\n", i+1, grafo->vertices[vert].arestas[i]);
            // printf("\tRaio: %d\n\n", raio);
            
            if (vis[grafo->vertices[vert].arestas[i]] == -1) { // se não foi visitado para o vizinho da posição 'i', visita e guarda as informações dele
                ordem[cont2] = grafo->vertices[vert].arestas[i]; // novo ultimo elemento da ordem
                vis[grafo->vertices[vert].arestas[i]] = vis[vert]+1; // o raio do vizinho i de VERT vale o raio do VERT+1;
                cont2++; // atualiza o final da ordem para o próximo vizinho se houver
            }

            // imprimirVisitados(vis,grafo->n_vertices); // Debugando 
        }
        cont1++; // atualiza o próximo início da ordem
    }
    free(ordem); // libera a ordem
}
