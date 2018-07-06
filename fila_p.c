#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fila_p.h"
#include "const_estru.h"




#define exchall(A,B) {  fila->pos[fila->fila[A]]=B; fila->pos[fila->fila[B]]=A;exch( fila->fila[A], fila->fila[B] ); }
#define insert(A) { 		fila->fila[fila->livre]=A;		fila->pos[A]=fila->livre; }

/*STRUCT FILA_p
	- Utilizada para guardar vertices numa fila prioritaria, sobre a forma de heap
		:livre 	-> Primeira posição livre da heap (Número de elementos)
		:size 	-> Número máximo de elementos da heap
		:fila 	-> Vetor que representa a fila prioritaria
		:pos 	-> Vetor que contem a posição de cada vertice pertencente à heap 
*/
typedef struct _fila_p{
	int livre;
	int size;
	int *fila;
	int * pos;
}FILA_P;

/** get_pos : Retorna a posição de um certo vertice na fila prioritaria
			:fila 	-> Fila prioritaria sobre a forma de uma heap
			:w 		-> Vertice a saber a posicao
**/
int get_pos(FILA_P * fila, int w)
{
	return fila->pos[w];
}
/** PQinit : Aloca memória e inicializa uma fila prioritaria
			:size 	-> Tamanho máximo da fila prioritaria 
**/
FILA_P * PQinit( int size )
{
	/*Aloca memoria para guardar a fila prioritaria*/
	FILA_P* fila= (FILA_P *)malloc(sizeof(FILA_P));
		nullexit(fila);
	/*Inicializa a fila prioritaria*/
	fila->livre=0;
	fila->size=size;
	fila->fila=(int *)malloc(size*sizeof(int));
		nullexit(fila->fila);
	fila->pos=(int *)malloc(size*sizeof(int));
		nullexit(fila->pos);

	return fila;
}
/** free_fila : Liberta a memória alocada para guardar uma fila prioritaria
			: fila 	-> Fila prioritaria a ser libertada
**/
void free_fila(FILA_P * fila)
{
	free(fila->fila);
	free(fila->pos);
	free(fila);
}
/** FixUp : Altera a posição dum vertice na fila prioritaria quando a prioridade do vertice acima de si for menor
			: fila 	-> Fila prioritaria(Heap)
			: Idx 	-> Posição na fila prioritaria do vértice a deslocar
			: wt	-> Vetor com os custos de todos os caminhos(prioridade inversa ao valor de wt)

**/
FILA_P * FixUp(FILA_P * fila, int Idx, int *wt)
{
	/*Enquanto a prioridade do vértice "pai" for menor que a do vertice Idx*/
	while(Idx>0 && less(wt[fila->fila[Idx]] , wt[fila->fila[(Idx-1)/2]] ) )
	{
		/*Troca os vertices e volta a comparar com o proximo*/
		exchall(Idx, (Idx-1)/2 );
		Idx=(Idx-1)/2;
	}

	return fila;
}
/** FixDown : Altera a posição dum vertice na fila prioritaria quando a prioridade do vertice abaixo de si for maior
			:fila 	-> Fila prioritaria (heap)
			: Idx 	-> Posição na fila prioritaria do vertice a deslocar
			: wt	-> Vetor com os custos de todos os caminhos(prioridade inversa ao valor de wt)
**/
FILA_P * FixDown(FILA_P * fila, int Idx, int * wt)
{
	int Child;
	/*Enquanto houver vertices "filho" do vertice Idx*/
	while(  less((Idx*2)+1 , fila->livre) )
	{

		Child= (Idx*2)+1;
		/*Determina qual o vertice "filho" com maior prioridade*/
		if( less( (Child+1) , fila->livre) && less( wt[fila->fila[Child + 1]] , wt[fila->fila[Child]] ) )
			Child++;
		/*Caso a condição de acervo se verifique, termina o ciclo*/
		if(  less( wt[fila->fila[Idx]] , wt[fila->fila[Child]] ) )
			break;
		/*Troca o vertice com o "filho" correspondente*/
		exchall( Idx, Child );

		Idx=Child;
	}

	return fila;
}
/** Modify: Modifica a posição dum vertice na fila prioritaria quando a sua prioridade muda
			:fila -> Fila prioritaria (Heap)
			: wt	-> Vetor com os custos de todos os caminhos(prioridade inversa ao valor de wt)
**/
FILA_P * Modify(FILA_P * fila, int Idx, int *wt)
{
	fila=FixUp( fila, Idx, wt);

	return fila;
}
/** PQdelmin: Retira da fila prioritaria o elemento com maior prioridade (wt[] mais baixo)
			:fila -> Fila prioritaria (Heap)
			: wt	-> Vetor com os custos de todos os caminhos(prioridade inversa ao valor de wt)s
**/
int  PQdelmin(FILA_P * fila, int*wt)
{
	int r=fila->fila[0];
	/*Troca o vertice mais prioritario com o menos prioritario*/
	exchall(0, fila->livre-1);
	/*Reorganiza o elemento da posição 0*/
	fila->livre-=1;
	fila=FixDown(fila, 0,wt);

	return r;
}
/** PQempty: Verifica se a fila prioritaria se enconta vazia
			:fila 	-> Fila prioritaria (Heap)
**/
int PQempty(FILA_P * fila)
{
	return (equal(fila->livre, 0) ? 1:0) ;
}
/** PQinsert : Insere um vertice ordenadamente na fila prioritaria de acordo com a sua prioridade
			:fila 	-> Fila prioritaria (Heap)
			: v 	-> Vertice a inserir na fila prioritaria
			: wt	-> Vetor com os custos de todos os caminhos(prioridade inversa ao valor de wt)s
**/
FILA_P * PQinsert( FILA_P * fila, int v, int * wt)
{
	if( less(fila->livre , (fila->size+1) ) )
	{
		/*Insere o vertice na primeira posição disponivel*/
		insert(v);
		/*Coloca o vertice na posição certa consoante o seu peso*/
		fila=FixUp(fila, fila->livre, wt);
		/*Incrementa o numero de vertices na fila prioritaria*/
		fila->livre++;
	}

	return fila;
}