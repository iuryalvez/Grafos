#include "grafo.h"

/*
gcc grafo.c vet-mat.c main.c -o grafo.exe
./grafo.exe
*/

int main () {

    Grafo *grafo = NULL; // vetor de grafos

    int orig, dest, ed; // caracteristicas da aresta
    int *vis; // vetor de visitados (cálculo de profundidade)
    float peso;
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
                vis = aloca_vetor_int(grafo->n_vertices);
            } else printf("\tJa existe um grafo criado!\n");
            break;
        case 2:
            if (grafo) {
                printf("\n\tINSERINDO ARESTAS\n\n");
                while (opc == 1) {
                    printf("\tPosicao dos dois grafos a serem conectados: ");
                    scanf("%d %d", &orig, &dest);
                    printf("\t1 - Se for digrafo (Ida)\n\t0 - Se nao for (Ida e Volta)\n\t");
                    scanf("%d", &ed);
                    if (grafo->eh_ponderado == 1) {
                        printf("Peso da aresta: ");
                        scanf("%f", &peso);
                    }
                    inserirAresta(grafo, orig, dest, ed, peso);
                    opc = 0;
                    while (opc < 1 || opc > 2) {
                        printf("\t1 - Inserir\n\t2 - Parar\n");
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
                    printf("\tPosicao dos dois grafos a serem desconectados: ");
                    scanf("%d %d", &orig, &dest);
                    printf("\t1 - Se for digrafo (Ida)\n\t0 - Se nao for (Ida e Volta)\n\t");
                    scanf("%d", &ed);
                    if (ed == 2) ed = 0;
                    if (grafo->eh_ponderado == 1) {
                        printf("\tPeso da aresta: ");
                        scanf("%f", &peso);
                    }
                    removerAresta(grafo, orig, dest, ed);
                    opc = 0;
                    while (opc < 1 || opc > 2) {
                        printf("\t1 - Remover\n\t2 - Parar\n");
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
                opc = 0;
                while (opc < 1 || opc > 2) {
                    printf("\t1 - Profundidade\n\t2 - Largura\n\t");
                    scanf("%d", &opc);
                    if (opc < 1 || opc > 2) printf("Operacao invalida!\n\n");
                } 
                if (opc == 1) {
                    printf("\n\tPROFUNDIDADE\n\n");
                    printf("\tPosicao de inicio: ");
                    scanf("%d", &orig);
                    auxBP(grafo, orig, vis);
                    printf("\n");
                    print_vetor_int(vis,grafo->n_vertices);
                    printf("\n");
                }
                else {
                    printf("\n\tLARGURA\n\n");
                    printf("\tPosicao de inicio: ");
                    scanf("%d", &orig);
                    buscaLargura(grafo, orig, vis);
                    printf("\n");
                    print_vetor_int(vis,grafo->n_vertices);
                    printf("\n");
                }
            } else printf("Nao foi criado nenhum grafo!\n");
            break;  
        // case 99:
        //     printf("\n\tLIBERANDO GRAFO\n\n");
        //     if (grafo) liberarGrafo(grafo); 
        //     else printf("Nao foi criado nenhum grafo para ser liberado!\n");
        //     break;
        default:
            if (op != 0) printf("Operacao inválida!\n");
            break;
        }
    } while (op != 0);
    
    if (grafo) liberarGrafo(grafo);

    return 0;
}
