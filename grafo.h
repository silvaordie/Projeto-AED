#ifndef grafo_header
#define	grafo_header

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lista.h"
#include "const_estru.h"

typedef struct _vert VERT;

typedef struct _grafo_fila GRAFO_FILA;

typedef struct _grafo GRAFO;

LISTA * new_grafo_fila(int size, int mut, LISTA *head);

void free_grafo(GRAFO * grafo);

GRAFO * constroi_grafo( int mut, char **words, int size);

GRAFO * init_grafo(int v);

void insrt_grafo(GRAFO * G, int v1, int v2, int peso);

int *path_search(GRAFO *G, int s, int dest , int mut, int * st, int *path);

int get_grafofila_size(GRAFO_FILA * grafo);

int get_grafofila_mut(GRAFO_FILA * grafo);

#endif