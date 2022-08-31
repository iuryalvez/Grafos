#include "grafo.h"

/*
gcc grafo.c vet-mat.c main.c -o grafo.exe
./grafo.exe
*/

int main () {

    Grafo *grafo = NULL; // vetor de grafos

    int orig, dest, ed; // caracteristicas da aresta
    float peso;
    int op, opc; // operadores
    
    do {
        opc = 1;
        menu();
        scanf("%d", &op);
        switch (op) {
        case 1:
            printf("\nCRIANDO O GRAFO\n\n");
            grafo = criarGrafo();
            break;
        case 2:
            printf("\nINSERINDO ARESTAS\n\n");
            while (opc == 1) {
                printf("Posicao dos dois grafos a serem conectados: ");
                scanf("%d %d", &orig, &dest);
                printf("1 - Se for digrafo\n0 - Se nao for\n");
                scanf("%d", &ed);
                if (ed == 2) ed = 0;
                if (grafo->eh_ponderado == 1) {
                    printf("Peso da aresta: ");
                    scanf("%f", &peso);
                }
                inserirAresta(grafo, orig, dest, ed, peso);
                printf("\n\n1 - Inserir\n2 - Parar\n");
                scanf("%d", &opc);
            }
            break;
        case 3:
            printf("\nREMOVENDO ARESTAS\n\n");
            while (opc == 1) {
                printf("Posicao dos dois grafos a serem desconectados: ");
                scanf("%d %d", &orig, &dest);
                printf("1 - Se for digrafo\n0 - Se nao for\n");
                scanf("%d", &ed);
                if (ed == 2) ed = 0;
                if (grafo->eh_ponderado == 1) {
                    printf("Peso da aresta: ");
                    scanf("%f", &peso);
                }
                removerAresta(grafo, orig, dest, ed);
                printf("\n\n1 - Remover\n2 - Parar\n");
                scanf("%d", &opc);
            }
            break;
        case 4:
            printf("\nIMPRIMINDO GRAFO\n\n");
            imprimirGrafo(grafo);   
            break;
        case 5:
            printf("\nLIBERANDO GRAFO\n\n");
            liberarGrafo(grafo); 
            break;
        default:
            if (op != 0) printf("Operacao inválida!\n");
            break;
        }
    } while (op != 0);
    
    if (grafo != NULL) liberarGrafo(grafo);

    return 0;
}
