/** FICHEIRO dicionario.c
**	
**	Contém todas as funções que efetuam operações sobre a estrutura de dados DICIONARIO
**
**	Disponiveis fora do ficheiro:
**
**	-int get_position(DICIONARIO * dicionario, char * pal);
**
**	-int get_size(DICIONARIO * dicionario, char* pal1, char* pal2);
**
**	-DICIONARIO * get_dicionario(char* nome_dic, int *n_max);
**
**	-void free_dic( DICIONARIO * dicionario, int n_max);
**
**/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lista.h"
#include "const_estru.h"
#include "grafo.h"

#define detpesomacro(A,B) {		if(pal1[A]!=pal2[A]) B++;	}
/*STRUCT PALAVRA
	-	Utilizada para guardar uma palavra e o seu tamanho
		:size -> Tamanho da palavra
		:word -> Palavra
*/
typedef struct _palavra{
	int size;
	char *word;
}PALAVRA;
/*STRUCT DICIONARIO
	- Utilziada para guardar palavras do mesmo tamanho lidas do ficheiro .dic, juntamente com o seu grafo
		:size 	-> Número de palavras do mesmo tamanho
		:words 	-> Vetor com as palavras do mesmo tamanho
		:graph 	-> Ponteiro para o grafo das palavras do vetor words
*/
typedef struct _dicionario{
	int size;
	char ** words;
	GRAFO * graph;
} DICIONARIO;

/** get_words: Retorna o vetor de palavras do mesmo tamanho da posição idx do dicionario
			:dicionario 	-> Vetor de DICIONARIO'S
			:idx 			-> Posição no dicionario do vetor de palavras a retornar
	Complexidade: O(1)
**/
char ** get_words(DICIONARIO *dicionario ,int idx)
{
	return dicionario[idx].words;
}
/** get_grafo : Retorna o grafo da posição Idx do dicionario
		:dicionario 	-> Vetor de DICIONARIO's
		:idx 			-> Posição no vetor de DICIONARIO'S a retorna o grafo
	Complexidade: O(1)

**/
GRAFO * get_grafo(DICIONARIO *dicionario, int idx)
{
	return dicionario[idx].graph;
}

/**	swap_str: Troca duas palavras de posição num vetor de palavras
			:arg1	->Ponteiro para a posição da primeira palavra
			:arg2	->Ponteiro para a posição da segunda palavra
	Complexidade: O(1)

**/
void swap_str(char  **arg1, char  **arg2)
{
	/*Troca os ponteiros das duas palavras*/
     char *tmp = *arg1;
    *arg1 = *arg2;
    *arg2 = tmp;
}
/**string_cmp :Compara duas palavras e retorna 1 se p1<p2, caso contrario retorna 0
			:p1 	-> Palavra 1
			:p2 	-> Palavra 2
	Complexidade: O(1)

**/
int string_cmp(const void *p1, const void* p2)
{
	if (strcmp( *(char * const *)p1, *(char * const *)p2) >0)
		return 1;

	return 0;
}
void FixDown_char(char** words, int Idx, int size)
{
	int Child;

	while(  less((Idx*2)+1 , size) )
	{
		Child= (Idx*2)+1;
		if( less( (Child+1) , size) && string_cmp(words[Child +1] , words[Child]) )
			Child++;


		if(  string_cmp( words[Idx] , words[Child] ) )
			break;

		swap_str( &words[Idx], &words[Child] );

		Idx=Child;
	}
}

void Heapify_char(char ** words, int size)
{

  int i=0;

  for(i=(size-1)/2; i>=0; i--)
  {
    FixDown_char(words, i, size);
  }
  
  return;
}
void HeapSort(char ** words, int size)
{
  int top=size-1;

  Heapify_char(words, size);

  while(top>0)
  {
  	swap_str(&words[top], &words[0]);
  	top--;
    FixDown_char(words, 0, top);
  }

  return;
}
/** procura_bin : Retorna a posição de uma dada palavra num vetor de palavras ordenado, ou -1 caso não a encontre (Procura binária)
			:a 	->Vetor que contém as palavras
			:ini -> Indice do inicio do vetor que se pretende pesquisar
			:fim -> Indice do final do vetor que se pretende pesquisar
			:pal ->Palavra a procurar no vetor
	Complexidade: O( log(fim-ini) )

**/
int procura_bin(char** a, int ini, int fim, char * pal)
{
	if(fim >= ini)
	{
		int meio=ini+(fim-ini)/2;
		/*Caso a palavra esteja no meio retorna o indice 'meio'*/
		if(strcmp(a[meio],pal)==0)
			return meio;
		if(strcmp(a[meio], pal)>0) /*Se a palavra do meio for menor que a pretendida realiza a procura novamente na primeira metade da tabela*/
			return procura_bin(a,ini, meio-1, pal);
		/*Caso contrario realiza a procura na segunda metade da tabela*/
		return procura_bin(a, meio+1, fim, pal);	
	}
	/*Caso não encontre a palavra retorna -1*/
		return -1;
}
/** get_size : Retorna o número de palavras com o mesmo tamanho que as duas fornecidas
			:dicionario 	-> Vetor com todos os conjuntos de palavras com o mesmo tamanho e o numero destes conjuntos
	Complexidade: O(1)

**/
int get_size(DICIONARIO * dicionario, int size)
{
	return dicionario[size].size;
}
/**	get_position : Retorna a posição de uma dada palavra num vetor de palavras ordenadas alfabeticamente
			:dicionario 	-> Vetor com todos os conjuntos de palavras com o mesmo tamanho e o numero destes conjuntos
			:pal1 			->Palavra a procurar
			:n_min			->Tamanho da menor palavra guardada no dicionário
	Complexidade: O(dicionario.size)

**/
int get_position(DICIONARIO * dicionario, char * pal, int n_min)
{
	int size=strlen(pal);
	/*retorna o valor encontrado através da procura binaria*/
	return procura_bin(dicionario[realpos(size)].words, 0, dicionario[realpos(size)].size ,pal );
}

/** inserir_pal: Cria um nó da estrutura PALAVRA e insereo na lista de palavras lidas
			:pal 	-> Palavra lida do ficheiro
			:head	-> Ponteiro para a cabeça de palavras lidas
		Complexidade: O(1)
**/
LISTA * inserir_pal(char * pal, LISTA * head)
{
	/*Aloca memoria para o novo no*/
	Item node=(PALAVRA *)malloc(sizeof(PALAVRA));
		/*Verifica a alocação*/
		nullexit(node);
	/*Inicializa o no*/
	((PALAVRA *)node)->size=strlen(pal);
	((PALAVRA *)node)->word=(char *)malloc( ( ((PALAVRA *)node)->size+1)*sizeof(char));
		nullexit( ((PALAVRA *)node)->word );


	strcpy(((PALAVRA *)node)->word, pal);
	/*Insere-o na lista*/
	head=isrt_lista(head, node);

	return head;
}
/** ler_dic: Le um dicionario dum ficheiro .dic e guarda-o numa lista simplesmente ligada e guarda o tamanho da maior palavra
			:nome_dic	->Nome do ficheiro que contém o dicionario (.dic)
			:head		-> Ponteiro para a cabeça da lista de palavras lida
			:n_max		-> Tamanho da maior palavra
		Complexidade: O(Nº de palavras do dicionario)

**/
LISTA * ler_dic(char * nome_dic, LISTA *head, int n_max, int n_min, int **ocorrencias)
{
	FILE* dic=NULL;
	char novaPal[PALMAX];
	int novasize;
	/*Abre o ficheiro*/
	dic=fopen(nome_dic, "r");
	/*Verifica se o ficheiro foi aberto*/
	nullexit(dic);

	*ocorrencias=(int *)calloc(PALMAX,sizeof(int));
	nullexit(*ocorrencias);

	/*Enquanto houver palavras a ler*/
	while(fscanf(dic, "%s", novaPal) == 1)
	{
		novasize=strlen(novaPal);
		if( !less(n_max , novasize)  && !less(novasize ,n_min) ) 
		{
			/*Insere a nova palavra na lista*/
			head=inserir_pal(novaPal, head);
			(*ocorrencias)[ novasize ]++;		
		}
  	}
  	/*Fecha o ficheiro*/
  	fclose(dic);

  	return head;
}

/** aloca_dic: Aloca espaço destinado a guardar um vetor de estruturas DICIONARIO
			:n_max			->Tamanho da maior palavra (Numero de posições do vetor)
			:ocorrencias	->Número de ocorrências de todos os tamanhos de palavras lidos
		Complexidade: O(n_max-n_min)*Nºde ocorrencias de cada tamanho de palavra

**/
DICIONARIO * aloca_dic(int n_max, int n_min, int *ocorrencias)
{
	int i=0, j=0;
	/*Aloca um vetor de DICIONARIO, de forma a que possa ser acedido por n_max*/
	DICIONARIO * dicionario= (DICIONARIO*)calloc((n_max+1)-n_min ,sizeof(DICIONARIO) );
		/*Verifica a alocação*/
		nullexit(dicionario);

	/*Para cada uma das posições do vetor de DICIONARIO*/
	for (i=0; !less( realpos(n_max) , i) ; i++)
	{
		/*Caso tenham sido lidas palavaras de tamanho i*/
		if(less(0,ocorrencias[i+n_min]))
		{
			/*Aloca um vetor de strings com o numero de ocorrencias da palavra de tamanho i*/
			dicionario[i].words=(char **)malloc(ocorrencias[i+n_min]*sizeof(char*));
				nullexit(dicionario[i].words);
			/*Para todas as posições do vetor de strings*/
			for(j=0; less(j , ocorrencias[i+n_min]); j++)
			{
				/*Alloca memoria para guardar uma palavra de tamanho i(i+1 para incluior o \0)*/
				dicionario[i].words[j]=(char *)malloc((i+n_min+1)*sizeof(char));
				/*Verifica a alocação*/
					nullexit(dicionario[i].words[j]);
			}			
		}
	}

	return dicionario;
}
/** free_palavra: Liberta a memória usada para guardar um elemento da estrutura PALAVRA
			this	->Item que se quer libertar memoria
**/
void free_palavra(Item  this)
{
	free( ((PALAVRA*)this)->word );
	free( (PALAVRA *)this );
}
/** guarda_dic: Transforma a lista de palavras lidas do ficheiro num vetor de DICIONARIO
			:head			->Ponteiro para a cabeça das palavras lidas do ficheiro .dic
			:ocorrencias	->Vetor d inteiros com as ocorrências de todos os tamanhos de palavras
			:n_max			->Tamanho da maior palavra
		Complexidade: O(n_max-n_min)+O(Nº de palavras lidas)

**/
DICIONARIO * guarda_dic( LISTA *head, int *ocorrencias, int n_max, int n_min)
{
	int i=0;
	DICIONARIO* dicionario= NULL;

	LISTA *temp=head;
	PALAVRA* aux;
	/*Aloca memoria para guardar o vetor de DICIONARIO*/
	dicionario=aloca_dic(n_max, n_min, ocorrencias);
	/*Guarda para todos os tamanhos de palavra o número de ocorrências deste*/
	for(i=0; !less( realpos(n_max) ,i); i++)
	{
		dicionario[i].size = ocorrencias[i+n_min];
	}
	/*Percorre a lista de PALAVRA*/
	while(!equal(temp,NULL) )
	{
		/*Recebe a PALAVRA do no atual*/
		aux=(PALAVRA *)getItem_lista(temp);
		/*Decrementa as ocorrencias para indicar que existe menos uma palavra de tamanho x na lista*/
		ocorrencias[ (aux )->size  ]--;

		/*	Copia a palavra da lista de PALAVRA para o vetor de DICIONARIO para a ultima posição disponivel no vetor de strings da posição*/
		/*correspondente do vetor de DICIONARIO*/
		strcpy( dicionario[ realpos(aux->size) ].words[ ocorrencias[ aux->size ] ], aux->word);
		/*Passa para o proximo no da lista*/
		temp=getNext_lista(temp);
	}
	/*Liberta a memoria usada para guardar a lista de PALAVRA*/
	free_lista( head, free_palavra);
	return dicionario;
}

/** free_dic: Liberta toda a memória alocada para guardar as palavras lidas no vetor de DICIONARIO e o grafo correspondente
			:dicionario 	-> Vetor de DICIONARIO
			:n_max			->Tamanho da maior palavra lida (Número de posições do vetor de DICIONARIO - 1)
**/
void free_dic( DICIONARIO * dicionario, int n_max, int n_min)
{
	int i=0, j=0;
	/*Para todas as posições do vetor de DICIONARIO*/
	for(i=0; i<= realpos(n_max); i++)
	{
		/*Para todas as poisções do vetor de strings*/
		for(j=0; less(j,dicionario[i].size); j++)
		{
			/*Liberta a memoria alocada para guardar uma palavra de tamanho i*/
			free(dicionario[i].words[j]);
		}
		/*Liberta a memoria alocada para o vetor de strigs*/
		free(dicionario[i].words);
		/*Liberta a memória alocada para guardar o grafo*/
		if( !equal(dicionario[i].graph, NULL))
			free_grafo(dicionario[i].graph);
	}
	/*Liberta a memoria alocada para o vetor de DICIONARIO*/
	free(dicionario);
}
/**	det_peso: Retorna o número de caracteres que duas palavras diferem, caso a diferença seja maior que permitida, retorna -1
			:pal1	-> Primeira palavra a comparar
			:pal2	-> Segunda palavra a comparar
			:mutmax	-> Número máximo de diferenças permitidas
**/
int det_peso(char * pal1, char * pal2, int mutmax)
{
	int i;
	int dif=0;
	/*Compara cada caracter da palavra, enquanto a diferença entre as palavras seja menor que a permitida maxima*/
	for(i=0; less(i,strlen(pal1)) && !less(mutmax,dif); i++)
	{	/*Caso difiram, incrementa as diferenças*/
		detpesomacro(i,dif);
	}
	/*Retorna o numero de diferenças, caso seja menor que a permitida maxima, caso contrario retorna -1*/
	return (less(mutmax ,dif)? -1 : dif );
}

/** free_grafo_fila : Liberta a memória alocada para guardar as propriedades de um grafo a ser construido
			:this -> GRAFO_FILA a ser libertado
**/
void free_grafo_fila(Item  this)
{
	free( (GRAFO_FILA *)this );
}
/**	constroi_grafos : Constroi todos os grafos necessários para a resolução do problema com base nas propriedades guardadas numa lista
			: dicionario -> Vetor de DICIONARIO's
			: grafo_fila -> Lista com as propriedades de todos os grafos a serem construidos
			: n_min -> Tamanho da palavra mais pequena do dicionario guardado
**/
DICIONARIO * constroi_grafos(DICIONARIO * dicionario, LISTA * grafo_fila, int n_min)
{
	LISTA *aux=grafo_fila;
	GRAFO_FILA * grafo;
	int grafo_size, grafo_mut;
	/*Percorre a lista*/
	while(aux!=NULL) 
	{

		/*Recebe as propriedades do proximo grafo a construir*/
		grafo=(GRAFO_FILA *)getItem_lista(aux);
		grafo_size=get_grafofila_size(grafo);
		grafo_mut=get_grafofila_mut(grafo);
		/*Ordena as palavras do mesmo tamanho alfabeticamente*/
		qsort(dicionario[ realpos(grafo_size) ].words, dicionario[ realpos(grafo_size) ].size , sizeof(char *), string_cmp);
		/*Constroi o grafo com as proriedades lidas da lista*/
		dicionario[ realpos(grafo_size) ].graph = constroi_grafo( grafo_mut , dicionario[realpos(grafo_size)].words ,dicionario[realpos(grafo_size)].size);
		/*Passa para o próximo no da lista*/
		aux=getNext_lista(aux);
	}
	/*Apaga a lista das propriedades dos grafos a construir*/
	free_lista(grafo_fila, free_grafo_fila);

	return dicionario;
}
/** get_dicionario: Lê dum ficheiro .dic um dicionário e guarda-o num vetor de DICIONARIO assim como os grafos necessários para a resolução dos problemas lidos
			:nome_dic	->Nome do ficheiro que contem o dicionario (.dic)
			:n_max		->Tamanho da maior palavra lida (Número de posições do vetor de DICIONARIO - 1)
**/
DICIONARIO * get_dicionario(char* nome_dic, int n_max, int n_min, LISTA * grafo_fila)
{
	LISTA *head=NULL;
	int *ocorrencias=NULL;
	DICIONARIO * dicionario=NULL;

	/*Le as palavras escritas no ficheiro e guarda-as numa lista de PALAVRAS, juntamente com o seu tamanho*/
	head=ler_dic(nome_dic, head, n_max, n_min, &ocorrencias);
	/*Guarda as palavras lidas num vetor de DICIONARIO*/
	dicionario= guarda_dic(head, ocorrencias, n_max, n_min);
	/*Liberta a memoria usada para o vetor de inteiros ocorrencias*/
	free(ocorrencias);
	/*Constroi os grafos necessários para a resolução dos problemas lidos*/
	dicionario= constroi_grafos(dicionario, grafo_fila, n_min);

	return dicionario;
}
