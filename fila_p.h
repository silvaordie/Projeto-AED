#ifndef fila_p_header
#define fila_p_header

#include <stdlib.h>

typedef struct _fila_p FILA_P;
/** get_pos : Retorna a posição de um certo vertice na fila prioritaria
			:fila 	-> Fila prioritaria sobre a forma de uma heap
			:w 		-> Vertice a saber a posicao
**/
int get_pos(FILA_P * fila, int w);
/** Modify: Modifica a posição dum vertice na fila prioritaria quando a sua prioridade muda
			:fila -> Fila prioritaria (Heap)
			: wt	-> Vetor com os custos de todos os caminhos(prioridade inversa ao valor de wt)
**/
FILA_P * Modify(FILA_P * fila, int v, int * wt);
/** PQinit : Aloca memória e inicializa uma fila prioritaria
			:size 	-> Tamanho máximo da fila prioritaria 
**/
FILA_P * PQinit( int size );
/** free_fila : Liberta a memória alocada para guardar uma fila prioritaria
			: fila 	-> Fila prioritaria a ser libertada
**/
void free_fila(FILA_P * fila);
/** PQinsert : Insere um vertice ordenadamente na fila prioritaria de acordo com a sua prioridade
			:fila 	-> Fila prioritaria (Heap)
			: v 	-> Vertice a inserir na fila prioritaria
			: wt	-> Vetor com os custos de todos os caminhos(prioridade inversa ao valor de wt)s
**/
FILA_P * PQinsert( FILA_P * fila, int v, int * wt);
/** PQdelmin: Retira da fila prioritaria o elemento com maior prioridade (wt[] mais baixo)
			:fila -> Fila prioritaria (Heap)
			: wt	-> Vetor com os custos de todos os caminhos(prioridade inversa ao valor de wt)s
**/
int  PQdelmin(FILA_P * fila, int * wt);
/** PQempty: Verifica se a fila prioritaria se enconta vazia
			:fila 	-> Fila prioritaria (Heap)
**/
int PQempty(FILA_P * fila);

#endif




