#include "grafo.h"

void menu() {
    printf("GRAFOS - ALGORITMO DE BORUVKA\n\n");
    printf("1  ->  CRIAR GRAFO\n");
    printf("2  ->  INSERIR ARESTA\n");
    printf("3  ->  REMOVER ARESTA\n");
    printf("4  ->  IMPRIMIR INFORMACOES DO GRAFO\n");
    printf("5  ->  BUSCA\n");
    printf("6  ->  ALGORITMO DE BORUVKA\n");
    printf("99 ->  LIMPAR A TELA\n");
    printf("0  ->  SAIR\n");
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
        Vertice *verts;
        verts = (Vertice *) malloc(sizeof(Vertice)*grafo->n_vertices); // alocando memória para meu visitados de vértices
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
        printf(" Adjc%d |", i+1);
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
        printf("\n\tLista de pesos das adjacencias\n\n");
        printf("\t         |");
        for (i = 0; i < grafo->grau_max; i++) {
            printf(" Grau%d |", i);
        }
        printf("\n");
        for (i = 0; i < grafo->n_vertices; i++) {
            printf("\t| No %3d |", i);
            for (j = 0; j < grafo->grau_max; j++) {
                if (j < grafo->vertices[i].grau) printf(" %.3f |", grafo->vertices[i].pesos[j]);
            }
            printf("\n");
        }
    } else printf("\n\tO grafo nao eh ponderado\n\n");
    
    printf("\n\tLigacoes de cada vertice:\n");
    for (i = 0; i < grafo->n_vertices; i++) {
        if (i == 0) printf("\n\tVertices -> %2d", i); 
        else printf(" %2d", i);
    }
    i = 0;
    printf("\n\tLigacoes -> %2d", grafo->vertices[i].grau);
    i++;
    for (; i < grafo->n_vertices; i++) {
        printf(" %2d", grafo->vertices[i].grau);
    }
    printf("\n\n");
}

void imprimirVisitados(int *visitados, int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        if (i == 0) printf("\n\tVertice -> %2d", i); 
        else printf(" %2d", i);
    }
    printf("\n\t");
    i = 0;
    printf(" Niveis -> %2d", visitados[i]);
    i++;
    for (; i < tam; i++) {
        printf(" %2d", visitados[i]);
    }
    printf("\n");
}

void auxBuscas(int *visitados, int tam) {
    int i;
    for (i = 0; i < tam; i++) visitados[i] = 0;
}

void buscaProfundidade(Grafo *grafo, int src, int *vis, int cont) {
    // a função utiliza as informações do grafo para calcular a profundidade de cada elemento
    // verifica-se as conexões de cada elemento da lista e quão profundas elas são (de acordo com o cont)
    int i; // calcula a profundidade de acordo com o vértice de origem 'src'
    vis[src] = cont; // marca o vértice visitado com cont (se for 0 é pq n foi visitado), visita os vizinhos ainda não visitados
    
    // printf("\n\tVisitando os vizinhos de %d:\n\n", src); // Debugando
    
    for (i = 0; i < grafo->vertices[src].grau; i++) { // visitando os vizinhos (o grafo->grau indica quantos vizinhos tem na lista de adjacências)

        // printf("\tVizinhos de '%d':\n", src);
        // printf("\t(P:%d) Vizinho%d: %d\n\n", cont, i+1, grafo->vertices[src].arestas[i]); // Debugando

        if (!vis[grafo->vertices[src].arestas[i]]) { // se não foi visitado para o vizinho da posição 'i', visita e guarda as informações dele
            buscaProfundidade(grafo,grafo->vertices[src].arestas[i],vis,cont+1); // passa o cont+1 pq significa que esta mais profundo em relação ao src
            // printf("\tValor de vis[%d]: %d\n\n", grafo->vertices[src].arestas[i], vis[grafo->vertices[src].arestas[i]]); // Debugando
        }
        if (cont+1 < vis[grafo->vertices[src].arestas[i]]) { // se foi encontrado em outro sub-grafo mas não é tão profundo quanto lá
            vis[grafo->vertices[src].arestas[i]] = cont+1; 
            buscaProfundidade(grafo,grafo->vertices[src].arestas[i],vis,cont+1); // precisamos recalcular a profundiade dos outros elementos saindo dos vizinhos desse
            // pq se está errado pra esse vizinho, também vai estar errado para os vizinhos dele
        }
    } 
}

void buscaLargura(Grafo *grafo, int src, int *vis) {
    int i; // auxiliar
    int vert; // vértice atual
    int *ordem; // guarda a ordem que visitou os vértices
    int cont1 = 0; // início da ordem 
    int cont2 = 1; // final da ordem

    ordem = (int *) malloc(grafo->n_vertices * sizeof(int)); // cria ordem dinamicamente
    ordem[0] = src; // insere src na ordem, é o primeiro
    vis[src] = 1; // o vetor de visitaodos na posição src é o raio inicial 
    
    while (cont1 != cont2) { // iremos somar cont2 até um número limite e só pararemos quando cont1 chegar em cont2
        vert = ordem[cont1]; // pega o vert atualizado da ordem, VERIFICA OS VIZINHOS DELE
        
        // printf("\n\tVisitando os vizinhos de %d:\n", vert); // Debugando

        for (i = 0; i < grafo->vertices[vert].grau; i++) { // visitando os vizinhos (o grau do vertice indica quantos vizinhos tem na lista de adjacências)
            
            // printf("\n\tVizinho %d: %d\n\n", i+1, grafo->vertices[vert].arestas[i]);
            // printf("\tRaio: %d\n\n", raio);
            
            if (!vis[grafo->vertices[vert].arestas[i]]) { // se não foi visitado para o vizinho da posição 'i', visita e guarda as informações dele
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

float *alocarVetor_F(int tam) {
    int i;
    float *dist = malloc(sizeof(float) * tam);
    return dist;
}

void menorCaminho(Grafo *grafo, int ini, int *ordem, float *dist) {
    // Algoritmo de Dijkstra
    int i, cont, vizinho, *visitados, vert;
    
    cont = grafo->n_vertices;

    visitados = alocarVetor_I(grafo->n_vertices); // calloc

    for (i = 0; i < grafo->n_vertices; i++) { // inicializando com valores inválidos
        ordem[i] = -1; 
        dist[i] = -1; 
    }

    dist[ini] = 0; // distância do início pra ele mesmo é 0
    // vai ser o primeiro vértice a ser visitado pq vai ser o único com valor válido

    while (cont > 0) {
        vert = procuraMenorDistancia(dist,visitados,grafo->n_vertices);  // procura a menor distância entre os vizinhos de vert
        if (vert == -1) break; // se não houver caminho partindo de ini
        
        visitados[vert] = 1; // vert agora foi visitado
        
        for (i = 0; i < grafo->vertices[vert].grau; i++) { // para cada vértice vizinho do meu VERT, eu preciso calcular a distância dele até VERT
            vizinho = grafo->vertices[vert].arestas[i]; // calculando a dist do vizinho 'i' e atualizando a distância dos vizinhos que já existem
            if (!grafo->eh_ponderado) { //  se não é ponderado, considerar cada aresta com peso unitário
                
                // se a dist do vizinho for menor que 0, colocamos a distância atual lá (distância de vert+1)
                // mas se já houver uma dist no vizinho, verifica se a dist[vert]+1 não é menor que a que está lá...
                // porque se a distância do vert + 1 for MENOR que a distância ATUAL do vizinho, então temos que atualizar a distância do vizinho...
                // porque siginifica que encontramos uma distância MENOR pra chegar no vizinho 'i', que é o que queremos. 
                
                if (dist[vizinho] < 0 || dist[vizinho] > dist[vert]+1) { // verificando as distâncias de vert com seus vizinhos
                    dist[vizinho] = dist[vert]+1; // se ele é um vizinho de vert, a distância dele pro vert é dist[vert]+1
                    ordem[vizinho] = vert; // para chegar no viznho, tem que chegar a partir de vert 
                }
            }
            else {

                // se a dist do vizinho for menor que 0, colocamos a distância atual lá (distância de vert + os devidos pesos)
                // mas se já houver uma dist no vizinho, verifica se a dist[vert]+pesos não é menor que a que está lá...
                // porque se a distância do vert+PESOS for MENOR que a distância ATUAL do vizinho, então temos que atualizar a distância do vizinho...
                // porque siginifica que encontramos uma distância MENOR pra chegar no vizinho 'i', que é o que queremos. 
                
                if (dist[vizinho] < 0 || dist[vizinho] > dist[vert] + grafo->vertices[vert].pesos[i]) { // se o peso dessa ligação é menor que antes
                    dist[vizinho] = dist[vert] + grafo->vertices[vert].pesos[i]; // se é ponderado, verificar qual o peso da ligação e colocar quanto vale
                    ordem[vizinho] = vert; // para chegar no vizinho, tem que chegar a partir de vert
                }
            }
        }
        
        cont--;
    }

    free(visitados);

}

int procuraMenorDistancia(float *dist, int *visitados, int NV) {
    // Estamos procurando a menor distância entre os vizinhos que não foram visitados.
    int i; // auxiliar
    int menor;
    int primeiro = 1;
    for (i = 0; i < NV; i++) {
        if (dist[i] >= 0 && visitados[i] == 0) { // se a dist[i] for um valor válido e ainda não tiver sido visitado...
            if (primeiro) { // se for o primeiro, coloca um valor válido no menor
                menor = i;
                primeiro = 0;
            } else { // se não, verificar se existe uma dist que é menor que a do menor
                if (dist[menor] > dist[i]) menor = i;
            }
        }
    }
    return menor;
}

void algoritmoBoruvka (Grafo *grafo, int *ordem) {
    
    // Requisito: Grafo fortemente conexo com arestas ponderadas estabelecidas entre todos eles, não pode haver grafos que
    // ligam a si mesmos ou grafos com duas arestas não direcionadas ou grafos com muitas arestas de mesmo peso.

    int **grupos = alocarGrupos(grafo->n_vertices); // alocando os grupos dinamicamente
    int *validos = alocarVetor_I(grafo->n_vertices); // alocando o vetor de inteiros dinamicamente

    inicializaGrupos(grupos, grafo->n_vertices); // colocando o primeiro elemento em cada grupo e -1 no resto das posições dos grupos
    
    inicializaValidos(validos,grafo->n_vertices); // colocando 1 em todas as posições do vetor de valores válidos
    
    inicializaOrdem(ordem, grafo->n_vertices); // colocando -1 em todas as posições do vetor de valores da ordem

    int cont = 1; // contador de quantos grupos já foram somados
    int i, j; // auxiliar
    int vmp; // vizinho mais próximo
    int posVMP; // posição do vizinho mais próximo
    int *ord; // guarda a ordem qual elemento eu preciso acessar para chegar em outro elemento

    // Calcular a ordem por meio da ideia de grupos de Boruvka
    while (cont < grafo->n_vertices) {
        for (i = 0; i < grafo->n_vertices; i++) {
            if (validos[i]) printf("\n\n\t%dº Estudo de Grupo\n\n", cont);
            if (!validos[i]) continue; // se não é um grupo válido, vai pra próxima iteração
            
            printf("\tGrupo sendo estudado:\n");
            imprimirGrupo(grupos[i]);
            
            // calculando a posição do vizinho mais próximo de i (é definido que existe um mais próximo)
            posVMP = VMPdoGrupo(grafo->vertices, grupos[i], ord); 
            
            // calculando o vizinho mais próximo
            vmp = grafo->vertices[ord[0]].arestas[posVMP]; 

            // vmp encontrado no Vertice = ord[0];
            for (j = 0; j < grafo->n_vertices; j++) {
                if (!validos[j]) continue; // se não é um grupo válido, vai pra próxima iteração
                if (buscaVerticeNoGrupo(grupos[j],vmp) == 1) break; // se encontrar o elemento VMP no grupo[j]
            }
            printf("\tO VMP esta no grupo '%d', entao precisamos unir os dois grupos\n\n", j);
            
            // unindo os dois grupos a partir do grupo do vizinho mais pŕoximo
            // aumentar no grupo de menor índice
            if (i < j) {
                printf("\tUniao do grupo '%d' com o '%d':\n", i, j);
                unirGrupos(grupos[i],grupos[j]); 
                imprimirGrupo(grupos[i]); 

                printf("\tComo unimos G%d a outro grupo, G%d nao eh mais um grupo valido\n\n", j, j);
                validos[j] = 0; // não é mais um grupo válido
                ordem[vmp] = ord[0]; // deve ser acessado por ord[0], que é seu vizinho mais próximo
                if (ordem[ord[0]] == -1) { // se não houver um valor válido no vizinho mais próximo, então precisamos colocar um meio de chegar nele também
                    ordem[ord[0]] = vmp; // eve ser acessado por VMP, que é seu vizinho mais próximo
                }
            }
            else {
                printf("\tTemos sempre que unir em direcao ao grupo de menor indice, entao uniremos '%d' ao '%d':\n", j, i);
                unirGrupos(grupos[j], grupos[i]); 
                imprimirGrupo(grupos[j]);

                printf("\tComo unimos G%d a outro grupo, G%d nao eh mais um grupo valido\n\n", i, i);
                validos[i] = 0; // invalidar o maior grupo

                // Como a direção acesso é sempre do G menor para o G maior
                // Temos que colocar que a ordem do elemento encontrado veio do seu vizinho mais próximo
                ordem[ord[0]] = vmp; // assim como o VMP vem dele, ele também vem do VMP, mas nesse caso, privilegiamos o VMP
                if (ordem[vmp] == -1) { // se não houver um valor válido no vizinho mais próximo, então precisamos colocar um meio de chegar nele também
                    ordem[vmp] = ord[0]; // deve ser acessado por ord[0], que é seu vizinho mais próximo
                }
            }
            
            printf("\tOrdem de visitacao ate agora:\n\n");
            imprimirOrdem(ordem, grafo->n_vertices);

            cont++; // mais um grupo somado
        }
        // printf("cont: %d\n", cont);
    }
    imprimirGrupo(grupos[0]);
    liberarGrupos(grupos,grafo->n_vertices);
} 

int VMPdoGrupo (Vertice *V, int *grupo, int *ord) {

    int tam = tamanhoGrupo(grupo); // tamanho do grupo para verificarmos cada vértice do grupo
    int i;
    int posVP; // vizinho mais próximo do vertice
    int posVMP; // vizinho mais pŕoximo do grupo
    int check = 1;
    
    // Veja bem, cada elemento do meu grupo representa um VÉRTICE V[grupo[i]] do grafo
    // Cada posVP representa a posição do vizinho mais próximo
    // O i é o auxiliar que eu uso para chegar em um valor possível dentro dos meus valores do grupo
    for (i = 0; i < tam; i++) {
        printf("\tAvaliando o vertice '%d'\n\n", grupo[i]);
        posVP = VMPdoVertice(V[grupo[i]], grupo); // calculando o vizinho mais próximo de i (é definido que existe um mais próximo)
        
        if (posVP == -1) {
            continue; // significa que valor não há valores válidos para este vértice mais
        }

        // Tendo o vetor de vizinhos mais próximos, precisamos saber qual é o vizinho mais próximo definitivo, o menor peso
        if (check == 1) { // primeiro valor válido (pode não estar em i == 0)
            posVMP = posVP; // se for o primeiro, damos valor válido para entrar na próxima iteração
            // o valor que eu peguei foi encontrado graças ao Vert. = grupo[i], preciso guardar ele para saber a ordem
            ord[0] = grupo[i];
            check = 0; // não é mais o primeiro, devo verificar se é menor que o valor que está guardado
        }
        else {
            if (V[grupo[i]].pesos[posVP] < V[ord[0]].pesos[posVMP]) {
                posVMP = posVP;
                // o valor que eu peguei foi encontrado graças ao V[grupo[i]], preciso guardar ele para saber a ordem
                ord[0] = grupo[i]; 
            }
        }
    }
    printf("\tO vizinho mais proximo definitivo foi encontrado no vertice '%d' ele eh o vizinho de posicao '%d'\n", ord[0], posVMP); 
    printf("\tEssa posicao armazena o vertice '%d' de peso %.2f\n\n", V[ord[0]].arestas[posVMP], V[ord[0]].pesos[posVMP]);

    return posVMP; // retorno da posição do vizinho mais próximo entre os elementos do meu grupo
}

int VMPdoVertice (Vertice V, int *grupo) {
    
    // Posição do vizinho mais próximo, também preciso acessar o peso dessa posição
    // Por isso não guardo o valor da posição 
    int posVMP = -1; 
    
    int i; 
    for (i = 0; i < V.grau; i++) {
        printf("\t\tVendo se o vizinho[%d]: %d de peso: %.2f é o vizinho mais proximo desse vertice\n\n", i, V.arestas[i], V.pesos[i]);
        if (posVMP == -1) { // se for o primeiro valor
            if (buscaVerticeNoGrupo(grupo,V.arestas[i]) == FALSE) posVMP = i;
            else printf("\t\tO vizinho ja pertence ao grupo, nao deve ser considerado\n\n");
        }
        if (posVMP != -1) {
            if (buscaVerticeNoGrupo(grupo,V.arestas[i]) == FALSE && V.pesos[i] < V.pesos[posVMP]) {
                // printf("Vertice[%d]: %d, Peso: %f\n\n", posVMP, V.arestas[posVMP], V.pesos[posVMP]);
                posVMP = i; // se encontrar um vizinho mais próximo VÁLIDO
            }
        }
    }
    if (posVMP != -1) printf("\t\tO vizinho[%d]: %d, de peso: %.2f eh um candidato de ser o vizinho mais proximo do grupo\n\n", posVMP, V.arestas[posVMP], V.pesos[posVMP]);
    else printf("\t\tO vertice nao possui candidatos a serem considerados, todos seus vizinhos fazem parte do grupo\n\n");
    return posVMP; // retorno o valor do vizinho mais próximo desse vértice
}

void unirGrupos(int *G1, int *G2) {
    int i, j;
    i = tamanhoGrupo(G1);
    // adicionar elementos de G2 em G1 a partir do i encontrado
    for (j = 0; G2[j] != -1; j++, i++) G1[i] = G2[j];
}


int tamanhoGrupo(int *grupo) {
    int tam;
    // encontrar posição do último elemento de G1
    for (tam = 0; grupo[tam] != -1; tam++);
    // printf("\nTamanho do grupo: %d\n",tam); // Debug verificação
    return tam;
}

int buscaVerticeNoGrupo(int *grupo, int vertice) {
    int tam = tamanhoGrupo(grupo);
    int i;
    for (i = 0; i < tam; i++) {
        if (vertice == grupo[i]) {
            // se encontrar o vértice neste grupo, é porque o vértice está nesse grupo
            return TRUE; 
        }    
    }    
    return FALSE;
}

void inicializaGrupos(int **grupos, int tam) {
    int i, j;
    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam+1; j++) {
            if (j == 0) grupos[i][j] = i;
            else grupos[i][j] = -1;
        }
    }
}

void inicializaValidos(int *validos, int tam) {
    int i;
    for (i = 0; i < tam; i++) validos[i] = 1;
}

void inicializaOrdem(int *ordem, int tam) {
    int i;
    for (i = 0; i < tam; i++) ordem[i] = -1;
}

void imprimirGrupo(int *grupo) {
    int tam = tamanhoGrupo(grupo);
    int i;
    printf("\t{[%d]", grupo[0]);
    for (i = 1; i < tam; i++) {
        printf(",[%d]", grupo[i]);
    }
    printf("}\n\n");
}

void imprimirOrdem(int *ordem, int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        if (i == 0) printf("\n\tVertice -> %2d", i); 
        else printf(" %2d", i);
    }
    printf("\n\t");
    i = 0;
    printf(" Acesso -> %2d", ordem[i]);
    i++;
    for (; i < tam; i++) {
        printf(" %2d", ordem[i]);
    }
    printf("\n");
}

void calcularDist(Grafo *grafo, int *ordem, float *dist) {
    int i, j;
    float md; // menor distância
    
    md = 0;

    for (i = 1; i < grafo->n_vertices; i++) {
        for (j = 0; j < grafo->n_vertices; j++) {
            if (ordem[i] == grafo->vertices[i].arestas[j]) break; // encontrando a posição do vertice vizinho 'ordem[i]' em V[i]  
        }
        dist[i] = grafo->vertices[i].pesos[j];
    }
    
    imprimirDist(dist,grafo->n_vertices);
    printf("\n\tCalculando arvore geradora de custo minimo (minimum spanning tree)\n");
    printf("\tPartindo do vertice 0, a distancia total para percorrer todos os vertices, eh: ");
    for (i = 0; i < grafo->n_vertices; i++) md += dist[i];
    printf("%.2f\n\n", md);
}

void imprimirDist(float *dist, int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        if (i == 0) printf("\n\t Vertices -> %4d", i); 
        else printf(" %4d", i);
    }
    printf("\n\t");
    i = 0;
    printf("Distancia -> %.2f", dist[i]);
    i++;
    for (; i < tam; i++) {
        printf(" %.2f", dist[i]);
    }
    printf("\n");
}

int **alocarGrupos(int tam) {
    int i;
    int **grupos = malloc(tam*sizeof(int *));
    if (!grupos) {
        printf("Erro! Memoria insuficiente!\n");
        return NULL;
    }
    for (int i = 0; i < tam+1; i++) {
        grupos[i] = malloc(sizeof(int)*(tam+1));
        if (!grupos[i]) {
            printf("Erro! Memoria insuficiente!\n");
            return NULL;
        }
    }
    return grupos;
}

void liberarGrupos(int **grupos, int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        free(grupos[i]);
    }
    free(grupos);
}

int *alocarVetor_I(int tam) {
    int *v = malloc(tam*sizeof(int));
    if (!v) printf("Erro de alocacao de memoria!\n");
    return v;
}

void clear_screen() {
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else

    #endif
}
