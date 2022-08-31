#include <stdio.h>
#include <stdlib.h>

#define TRUE 1;
#define FALSE 0;

void print_vetor_int(int *vetor, int tam);

void print_matriz_int(int **matriz, int l, int c);

void print_matriz_float(float **matriz, int l, int c);

int **aloca_matriz_int(int l, int c);

void libera_matriz_int(int **matriz, int l);

float **aloca_matriz_float(int l, int c);

void libera_matriz_float(float **matriz, int l);

int *aloca_vetor_int(int tam);

void libera_vetor_int(int *vetor);
