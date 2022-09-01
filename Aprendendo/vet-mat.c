#include "vet-mat.h"

void print_vetor_int(int *vetor, int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        if (i == 0) printf("\n\t   Nos -> %2d", i); 
        else printf(" %2d", i);
    }
    printf("\n\t");
    i = 0;
    printf("Niveis -> %2d", vetor[i]);
    i++;
    for (; i < tam; i++) {
        printf(" %2d", vetor[i]);
    }
    printf("\n");
}

void print_matriz_int(int **matriz, int l, int c) {
    int i, j;
    printf("\t| No |");
    for (i = 0; i < c; i++) {
        printf(" Grau%d |", i);
    }
    printf("\n");
    for (i = 0; i < l; i++) {
        printf("\t| %2d |", i);
        for (j = 0; j < c; j++) {
            printf(" %5d |", matriz[i][j]);
        }
        printf("\n");
    } 
}

void print_matriz_float(float **matriz, int l, int c) {
    int i, j;
    for (i = 0; i < l; i++) {
        printf("\t|");
        for (j = 0; j < c; j++) {
            printf("%6f | ", matriz[i][j]);
        }
        printf("\n");
    }
}

int **aloca_matriz_int(int l, int c) {
    int i, j;
    int **matriz = NULL;
    matriz = (int **) malloc(sizeof(int *)*l);
    if (!matriz) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }
    for (i = 0; i < c; i++) {
        matriz[i] = (int *) malloc(sizeof(int)*c);
        if (!matriz[i]) {
            printf("Erro de alocação de memória!\n");
            return NULL;
        }
    }
    // caso seja necessário inicializar com -1 ↓
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            matriz[i][j] = -1;
        }
    }
    return matriz;
}

void libera_matriz_int(int **matriz, int l) {
    int i, j;
    for (i = 0; i < l; i++) {
        matriz[i] = NULL;
        free(matriz[i]);
    }
    matriz = NULL;
    free(matriz);
}

float **aloca_matriz_float(int l, int c) {
    int i, j;
    float **matriz = NULL;
    matriz = (float **) calloc(sizeof(float *),l);
    if (!matriz) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }
    for (i = 0; i < c; i++) {
        matriz[i] = (float *) calloc(sizeof(float),c);
        if (!matriz[i]) {
            printf("Erro de alocação de memória!\n");
            return NULL;
        }
    }
    return matriz;
}

void libera_matriz_float(float **matriz, int l) {
    int i, j;
    for (i = 0; i < l; i++) {
        matriz[i] = NULL;
        free(matriz[i]);
    }
    matriz = NULL;
    free(matriz);
}

int *aloca_vetor_int(int tam) {
    int *vetor = calloc(tam,sizeof(int));
    if (!vetor) printf("Erro de alocacao de memoria!\n");
    return vetor;
}

void libera_vetor_int(int *vetor) {
    vetor = NULL;
    free(vetor);
}
