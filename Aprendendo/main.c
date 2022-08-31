#include "grafo.h"

int main () {

    Grafo *grafo = NULL; // vetor de grafos

    int nv, gm, ep; // caracteristicas do grafo
    int orig, dest, ed; // caracteristicas da aresta
    int op = 1; // operador
    float peso;

    printf("\nCRIANDO O GRAFO\n\n");
    printf("Numero de vertices: ");
    scanf("%d", &nv);
    printf("Grau maximo: ");
    scanf("%d", &gm);
    printf("Eh ponderado?\n1 - Sim\n2 - Nao\n");
    scanf("%d", &ep);
    if (ep == 2) ep = 0;

    grafo = criarGrafo(nv,gm,ep); // 1º passo

    printf("\nINSERINDO ARESTAS\n\n");
    while (op != 0) {
        printf("1 - Inserir\n0 - Parar\n");
        scanf("%d", &op);
        if (op == 1) {
            printf("Posicao dos dois grafos a serem conectados: ");
            scanf("%d %d", &orig, &dest);
            printf("Eh digrafo?\n1 - Sim\n2 - Nao\n");
            scanf("%d", &ed);
            if (ed == 2) ed = 0;
            if (ep == 1) {
                printf("Peso da aresta: ");
                scanf("%f", &peso);
            }
            inserirAresta(grafo, orig, dest, ed, peso);
            printf("\n");
        }
    }
    
    imprimirGrafo(grafo);

    liberarGrafo(grafo); // último passo

    return 0;
}
