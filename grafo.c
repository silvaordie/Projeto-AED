#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fila_p.h"
#include "lista.h"
#include "const_estru.h"
#include "dicionario.h"


#define MAXWT 1000.00
#define P (wt[ temp ] + t->peso)
#define atribui(A,B,C) { wt[A]=B; st[A]=C ;}
#define new_vertmacro() {	edge->w= w; edge->peso = peso; edge->next= head;}

/*STRUCT VERT
	-Representa um vértice do grafo
		:w 		-> Vertice do grafo
		:peso 	-> Peso da ligação com o vértice adjacente
		:next 	-> Ponteiro para o próximo vértice adjacente ao mesmo que w
*/
typedef struct _vert{
	int w;
	int peso;
	struct _vert *next;
} VERT;
/*STRUCT GRAFO_FILA
	-Representa um nó de uma lista com as propriedades dos grafos a serem construidos
		:size 	-> Tamanho das palavras que irao pertencer ao grafo
		:mut 	-> Numero maximo de mutaçoes permitidas entre palavras do grafo
*/
typedef struct _grafo_fila{
	int size;
	int mut;
}GRAFO_FILA;
/*STRUCT GRAFO
	-Representa um grafo, adirecionado representado por lista de adjacencias
		:v 		-> Número de vértices do grafo
		:mut 	-> Ńumero de mutacoes maximas entre palavras do grafo
		:adj 	-> Vetor com todas as listas de adjacencias entre palavras do grafo
*/
typedef struct _grafo{
	int v;
	int mut;
	VERT ** adj;
} GRAFO;
/** get_grafofila_size : Retorna o tamanho das palavras do grafo a ser construido
			:grafo 	-> Nó da lista de grafos a serem construidos
**/
int get_grafofila_size(GRAFO_FILA * grafo)
{
	return grafo->size;
}
/** get_grafofila_mut : Retorna o valor das mutações máximas permitidas entre palavras do grafo
			:grafo 	-> Nó da lista de grafos a serem construidos
**/
int get_grafofila_mut(GRAFO_FILA * grafo)
{
	return grafo->mut;
}
/** free_vert: Liberta a memória alocada para guardar um vértice dum grafo
			:this	->Vertice do grafo a libertar
**/
void free_vert(Item  this)
{
	free( (VERT *)this );
}
/**	free_adj: Liberta a memória alocada para guardar as adjacencias dum vertice dum grafo
			:head 	->Ponteiro para a lista de adjacencias dum grafo
**/
void free_adj(VERT * head)
{
	VERT * aux=head;
	/*Enquanto houver elementos na lista*/
	while( !equal(head,NULL) )
	{/*Remove o ultimo elemento da lista*/
		aux=head;
		head=head->next;

		free(aux);
	}
}
/**	free_grafo: Liberta a memória alocada para guardar um grafo
			:dicionario ->Posição do vetor de DICIONARIO's que contem o grafo a libertar
**/
void free_grafo(GRAFO * grafo)
{
	int j;

	for(j=0; less(j,grafo->v) ; j++)
	{
		free_adj(grafo->adj[j]);	
	}
	free(grafo->adj);
	free(grafo);
}
/** constroi_grafo: Constroi um grafo com lista de adjacencias em que o número de diferenças entre palavras adjacentes é menor ou igual que as mutações máximas
			:mut 			-> Número de mutações máximas entre palavras adjacentes no grafo
			:dicionario 	-> DICIONARIO onde irá ser construido o grafo
**/
GRAFO * constroi_grafo( int mut, char **words, int size)
{
	/**Inicializa o grafo**/
	GRAFO * grafo= init_grafo( size );
	int i=0, j=1;
	int peso;

	/*Testa cada palavra com todas as outras*/
	for(i=0; less(i,size) ;i++ )
	{
		for(j=i+1; less(j,size); j++)
		{
			/*Determina as diferenças entre as duas palavras*/
			peso=det_peso(words[i], words[j], mut);
			/*Caso a diferença seja menor que a permitida máxima, insere a ligação no grafo*/
			if( less(0,peso) )
				insrt_grafo(grafo, i, j, peso*peso );
		}
	}
	return grafo;
}
/** init_grafo : Inicializa um grafo com lista de adjacências
			:v 	-> Número de vértices do grafo
**/
GRAFO * init_grafo(int v)
{
	/*Alloca memória para guardar o grafo*/
	GRAFO * G= (GRAFO *)malloc(sizeof(GRAFO));
		nullexit(G);
	/*Inicializa o número de vertices do grafo*/
	G->v= v;
	/*Aloca memória para guardar a lista de adjacencias de cada vertice do grafo*/
	G->adj= (VERT **)calloc(v , sizeof(VERT*));
		nullexit(G->adj);

	return G;
}

LISTA * new_grafo_fila(int size, int mut, LISTA *head)
{
	GRAFO_FILA * grafo=(GRAFO_FILA *)malloc(sizeof(GRAFO_FILA));
		nullexit(grafo);

	grafo->size=size;
	grafo->mut=mut;

	head=isrt_lista(head, grafo);

	return head;
}
/** new_vert : Inicializa e insere um novo vertice na lista de adjacencias correspondente
			:head	-> Ponteiro para a lista de adjacencias a inserir o novo vertice
			:w 		-> Indice do vertice a inserir na lista de adjacencias
			:peso	-> Peso da ligação com o vértice adjacente
**/
VERT * new_vert(VERT * head, int w,int peso )
{
	/*Aloca memória para guardar o novo vértice*/
	VERT * edge=(VERT *)malloc(sizeof(VERT));
		nullexit(edge);
	/*Inicializa e insere o novo vertice na lista de adjacencias*/
	new_vertmacro();
	/*Atualiza o ponteiro para a head da lista de adjacencias*/
	head=edge;

	return head;
}
/**	insrt_grafo : Insere a nova adjacencia no grafo
			:G 		-> Grafo a inserir a nova adjacencia
			:v1		-> Vertice 1 da adjacencia
			:v2		-> Vertice 2 da adjacencia
			:peso 	-> Peso da ligação dos dois vertices
**/
void insrt_grafo(GRAFO * G, int v1, int v2, int peso)
{
	/*Insere o vertice 2 na lista de adjacencias do vertice 1*/
	G->adj[v1]= new_vert(G->adj[v1],v2, peso);
	/*Insere o vertice 1 na lista de adjacencias do vertice 2*/
	G->adj[v2]= new_vert(G->adj[v2],v1, peso);
}
/**	path_search : Procura o caminho mais curto entre dois vertices num grafo, retorna o vetor com o caminho do vertice de origem aos restantes encontrados
				tal como o custo do caminho (1000 se não encontrar caminho)
			:G 	-> Grafo a realizar a procura
			:s 	-> Vertice origem da procura
			:dest 	-> Vertice destino na procura
			:st 	-> Vetor com o vertice anterior no caminho de cada vertice do grafo
			:path 	-> Custo do caminho entre os dois vertices
**/
int *path_search(GRAFO *G, int s, int dest , int mut, int * st, int *path)
{
	/*Caso não exista grafo a realizar a procura*/
	if( equal(G,NULL) )
	{
		/*Se os vertices de origem e destino forem iguas, o custo é 0*/
		if( equal(dest,s) )
			*path=0;
		/*Caso contrario o custo do caminho é 1*/
		else
			*path=1;
		/*Não retorna o vetor com o caminho*/
		return NULL;		
	}

	int v,w;
	int temp;
	VERT *t;
	FILA_P *fila;

	/*Aloca memoria para o vetor com o caminho*/
	st=(int *)malloc( G->v *sizeof(int) );
		nullexit(st);
	/*Aloca memoria para o vetor com o peso do caminho dum vertice encontrado ao vertice de origem*/
	int *wt=(int *)malloc( G->v *sizeof(int) );
		nullexit(wt);
	/*Inicializa uma fila prioritária de forma a guardar todos os vertices do grafo, na qual a prioridade dum vertice é dada pelo inverso do wt[] correspondente*/
	fila=PQinit(G->v);
	/*Inicializa todas as posições do vetor com o caminho a -1, e do vetor de pesos a 1000. Insere o vertice na fila prioritaria*/
	for(v=0; less(v, G->v); v++)
	{
		/*Inicia a posição v dos vetores*/
		atribui(v,MAXWT,-1);
		/*Insere o vertice na fila prioritaria*/
		fila=PQinsert(fila, v, wt);
	}
	/*Atribui peso 0 ao vertice de origem*/
	wt[ s ]=0;
	/*Atualiza a fila prioritaria devido à mudança de prioridade do vertice de origem*/
	fila=Modify(fila, s, wt);
	/*Enquanto houver vertices na fila prioritaria*/
	while( !PQempty(fila) )
	{
		/*Retira o vertice mais prioritario da fila(wt[] mais baixo)*/
		temp=PQdelmin(fila, wt);
		/*Caso tenha retirado o vertice de destino*/
		if( equal(temp,dest) )
		{
			/*Atualiza o valor do custo do caminho*/
			*path=wt[temp];
			/*Liberta a memoria usada para a fila prioritria*/
			free_fila(fila);
			/*Liberta a memoria utilizada para guardar o vetor de custo de caminhos*/
			free(wt);
			/*Retorna o vetor com o caminho*/
			return st;
		}
		/*Caso seja um vertice que ja esteja no caminho*/
		if( !equal( wt[ temp ] , MAXWT ) )
		{
			/*Percorre a lista de adjacencias do vertice retirado da ila prioritaria*/
			for(t=G->adj[temp]; !equal(t,NULL) ; t=t->next)
			{
				w=t->w;
				/*Caso o custo do caminho do vertice da lista de adjacencias seja menor que o encontrado previamente, atualiza o caminho*/
				if( less(P , wt[ w ]) && !less( mut*mut,t->peso ) )
				{
					/*Atualiza os vetores com o caminho e o custo do mesmo*/
					atribui(w,P,temp);
					/*Atualiza a fila prioritaria*/
					fila=Modify(fila, get_pos(fila, w), wt);
				}
			}
		}
	}
	
	return st;
}