#include "grafo.h"

/*
gcc grafo.c main.c -o grafo.exe
./grafo.exe
*/

int main () {

    clear_screen();
    Grafo *grafo = NULL; // vetor de grafos

    int orig, dest, ed; // características da aresta
    int *vis; // vetor de visitados (cálculo de profundidade)
    int *ordem; // vetor de ordem (cálculo de menor caminho) 
    float *dist; // vetor de distâncias (cálculo do menor caminho)
    float peso; // peso de uma aresta 
    int op, opc; // operadores
    
    do {
        opc = 1;
        menu();
        scanf("%d", &op);
        switch (op) {
        case 1:
            if (!grafo) {
                printf("\n\tCRIANDO O GRAFO\n\n");
                grafo = criarGrafo();
                vis = alocarVetor_I(grafo->n_vertices);
                ordem = alocarVetor_I(grafo->n_vertices);
                dist = alocarVetor_F(grafo->n_vertices);
            } else printf("\tJa existe um grafo criado!\n");
            break;
        case 2:
            if (grafo) {
                printf("\n\tINSERINDO ARESTAS\n\n");
                while (opc == 1) {
                    printf("\tPosicao dos dois grafos a serem conectados (origem,destino): ");
                    scanf("%d %d", &orig, &dest);
                    printf("\t1 - Se for digrafo (Ida)\n\t0 - Se nao for (Ida e Volta)\n\t");
                    scanf("%d", &ed);
                    if (grafo->eh_ponderado == 1) {
                        printf("\n\tPeso da aresta: ");
                        scanf("%f", &peso);
                    }
                    inserirAresta(grafo, orig, dest, ed, peso);
                    opc = FALSE;
                    while (opc < 1 || opc > 2) {
                        printf("\t1 - Inserir\n\t2 - Parar\n\t");
                        scanf("%d", &opc);
                        if (opc < 1 || opc > 2) printf("Operacao invalida!\n");
                    }
                }
            } else printf("Nao foi criado nenhum grafo!\n");
            break;
        case 3:
            if (grafo) {
                printf("\n\tREMOVENDO ARESTAS\n\n");
                while (opc == 1) {
                    printf("\tPosicao dos dois grafos a serem desconectados (origem,destino): ");
                    scanf("%d %d", &orig, &dest);
                    printf("\t1 - Se for digrafo (Ida)\n\t0 - Se nao for (Ida e Volta)\n\t");
                    scanf("%d", &ed);
                    if (ed == 2) ed = 0;
                    if (grafo->eh_ponderado == 1) {
                        printf("\tPeso da aresta: ");
                        scanf("%f", &peso);
                    }
                    removerAresta(grafo, orig, dest, ed);
                    opc = FALSE;
                    while (opc < 1 || opc > 2) {
                        printf("\t1 - Remover\n\t2 - Parar\n\t");
                        scanf("%d", &opc);
                        if (opc < 1 || opc > 2) printf("Operacao invalida!\n");
                    }
                }
            } else printf("Nao foi criado nenhum grafo!\n");
            break;
        case 4:
            if (grafo) {
                printf("\n\tIMPRIMINDO GRAFO\n\n");
                imprimirGrafo(grafo);   
            } else printf("Nao ha grafo criado!\n");
            break;
        case 5:
            if (grafo) {
                printf("\n\tBUSCA\n\n");
                auxBuscas(vis,grafo->n_vertices);
                opc = FALSE;
                while (opc < 1 || opc > 3) {
                    printf("\t1 - PROFUNDIDADE\n\t2 - LARGURA\n\t3 - MENOR CAMINHO\n\t");
                    scanf("%d", &opc);
                    if (opc < 1 || opc > 3) printf("\tOperacao invalida!\n\n");
                } 
                if (opc == 1) {
                    printf("\n\tPROFUNDIDADE\n\n");
                    printf("\tPosicao de inicio: ");
                    scanf("%d", &orig);
                    
                    buscaProfundidade(grafo, orig, vis,1);
                    
                    imprimirVisitados(vis,grafo->n_vertices);
                    printf("\n");
                }
                else if (opc == 2) {
                    printf("\n\tLARGURA\n\n");
                    printf("\tPosicao de inicio: ");
                    scanf("%d", &orig);
                    
                    buscaLargura(grafo, orig, vis);
                    
                    imprimirVisitados(vis,grafo->n_vertices);
                    printf("\n");
                }
                else if (opc == 3) {
                    printf("\n\tMENOR CAMINHO (DIJKSTRA)\n\n");
                    printf("\tPosicao de inicio: ");
                    scanf("%d", &orig);
                    
                    menorCaminho(grafo, orig, ordem, dist);
                    
                    printf("\n\tOrdem de visitacao para chegar em outros vertices partindo de '%d'\n", orig);
                    imprimirVisitados(ordem,grafo->n_vertices);
                    
                    printf("\n\tPeso dos caminhos para chegar em outros vertices partindo de '%d'\n", orig);
                    imprimirDist(dist,grafo->n_vertices);
                    printf("\n");
                }
            } else printf("Nao foi criado nenhum grafo!\n");
            break;
        case 6:
            printf("\n\tALGORITMO DE BORUVKA");
            algoritmoBoruvka(grafo,ordem);
            imprimirOrdem(ordem,grafo->n_vertices);
            calcularDist(grafo,ordem,dist);
            printf("\n");
            break;
        case 99:
            clear_screen();
            break;
        default:
            if (op != 0) printf("\nOperacao inválida!\n");
            break;
        }
    } while (op != 0);

    void clear_screen();
    
    if (grafo) liberarGrafo(grafo);

    return 0;
}
