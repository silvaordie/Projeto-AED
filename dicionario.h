#ifndef dicionario_header
#define	dicionario_header

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lista.h"
#include "const_estru.h"
#include "grafo.h"

typedef struct _dicionario DICIONARIO;

/**string_cmp :Compara duas palavras e retorna 1 se p1<p2, caso contrario retorna 0
			:p1 	-> Palavra 1
			:p2 	-> Palavra 2
**/
int string_cmp(const void *p1, const void* p2);
/**	det_peso: Retorna o número de caracteres que duas palavras diferem, caso a diferença seja maior que permitida, retorna -1
			:pal1	-> Primeira palavra a comparar
			:pal2	-> Segunda palavra a comparar
			:mutmax	-> Número máximo de diferenças permitidas
**/
int det_peso(char * pal1, char * pal2, int mutmax);
/**	get_position : Retorna a posição de uma dada palavra num vetor de palavras ordenadas alfabeticamente
			:dicionario 	-> Vetor com todos os conjuntos de palavras com o mesmo tamanho e o numero destes conjuntos
			:pal1 			->Palavra a procurar
**/
char ** get_words(DICIONARIO *dicionario ,int idx);

GRAFO * get_grafo(DICIONARIO *dicionario, int idx);


int get_position(DICIONARIO * dicionario, char * pal, int n_min);
/** get_size : Retorna o número de palavras com o mesmo tamanho que as duas fornecidas
			:dicionario 	-> Vetor com todos os conjuntos de palavras com o mesmo tamanho e o numero destes conjuntos
			:pal1 			->Palavra 1
			:pal2 			->Palavra 2
**/
int get_size(DICIONARIO * dicionario, int size);
/** get_dicionario: Lê dum ficheiro .dic um dicionário e guarda-o num vetor de DICIONARIO
			:nome_dic	->Nome do ficheiro que contem o dicionario (.dic)
			:n_max		->Tamanho da maior palavra lida (Número de posições do vetor de DICIONARIO - 1)
**/
DICIONARIO * get_dicionario(char* nome_dic, int n_max, int n_min, LISTA * grafo_fila);
/** free_dic: Liberta toda a memória alocada para guardar as palavras lidas no vetor de DICIONARIO
			:dicionario 	-> Vetor de DICIONARIO
			:n_max			->Tamanho da maior palavra lida (Número de posições do vetor de DICIONARIO - 1)
**/
void free_dic( DICIONARIO * dicionario, int n_max, int n_min);
#endif 