#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lista.h"
#include "const_estru.h"
#include "dicionario.h"
#include "grafo.h"


/**	get_problemas: Lê dum ficheiro de problemas (*.pal) o tamanho da maior e da menor palavra
				  e determina que grafos é que devem ser construidos para a resolução dos problemas
			:nome_prob 	-> Nome do ficheiro que contem os problemas a serem resolvidos
			:n_max 		-> Tamanho das maiores palavras a serem guardadas
			:n_min 		-> Tamanho das menores palavras a serem guardadas
			:grafo_fila -> Lista que contém as propriedades dos grafos a serem construidos
	Complexidade: O( (Nº de problemas) + (n_max-n_min) )
**/
void get_problemas(char* nome_prob, int * n_max, int  * n_min, LISTA **grafo_fila)
{
	FILE *fp=NULL;

	char palA[PALMAX];	int sizeA;
	char palB[PALMAX];	int sizeB;
	int op;
	int grafos[47]={0};
	int i=0;
	int peso;

	*n_max=0;
	/*Abre o ficheiro*/
	fp=fopen(nome_prob, "r");
		/*Verifica se o ficheiro foi aberto*/
		nullexit(fp);
	/*Enquanto existem formatos de problemas a ler*/
	while(fscanf(fp, " %s %s %i ", palA, palB, &op) == 3)
	{
		/*Guarda os tamanhos das palavras lidas*/
		sizeA=strlen(palA);
		sizeB=strlen(palB);
		/*Caso ainda n tenha sido nenhuma palavra lida, inicializa n_min com a palavra lida*/
		if( equal(*n_min,0) )
			*n_min=sizeA;
		/*Caso uma das palavras lidas seja maior que n_max, atualiza o valor de n_max*/
		if(less(*n_max,sizeA) || less(*n_max,sizeB))
		{
			/*Caso A>n_max*/
			if(less(*n_max,sizeA))
				*n_max=sizeA;
			/*Caso B > n_max*/
			else
				*n_max=sizeB;				
		}
		/*Caso uma das palavras lidas seja menor que min, atualiza o valor de min*/
		if(less(sizeA,*n_min) || less(sizeB,*n_min))
		{
			/*Caso A < n_min*/
			if(less(sizeA,*n_min))
				*n_min=sizeA;
			/*Caso B< n_min*/
			else
				*n_min=sizeB;				
		}
		/*Se o número de mutações maximas permitidas do grafo lidas anteriormente for menor que a lida, atualiza o valor das mutações 
	máximas permitidas no grafo das palavras de tamanho sizeA/B, sse a diferença entre as duas palavras justifique a construção do grafo
	e se as duas palavras forem do mesmo tamanho*/
		peso=det_peso(palA, palB, op);
		if(  less(grafos[sizeA] , op) && ( less(peso,0) || less(1,peso) ) && equal(sizeA, sizeB) )
			grafos[sizeA]=op;
  	}
  	/*Para cada tamanho de palavras a serem guardadas*/
  	for(i=*n_min; !less(*n_max, i) ;i++)
  	{
  		/*Caso exista um grafo a ser construido, insere as proriedades deste numa lista*/
  		if( grafos[i] )
  	  		*grafo_fila=new_grafo_fila(i, grafos[i], *grafo_fila);	
  	}
  	/*Fecha o ficheiro*/
  	fclose(fp);
}
/** wp_recur : Escreve um caminho de tras para a frente, presente num vetor
			:words 	-> Vetor de palavras do mesmo tamanho
			:st 	-> Vetor que contem o caminho a escrever
			:s 		-> Vertice origem do caminho
			:u 		-> Vertice da palavra a ser escrita no ficheiro
			:fp 	-> Ficheiro a escrever o caminho
			:path 	-> Custo do caminho a ser escrito
	Complexidade: O(1)
**/
void wp_recur(char ** words, int*st, int s,int u, FILE * fp, int path)
{
	/*Caso exista caminho a ser percorrido, passa para o proximo vertice do mesmo  e imprime vertice*/
	if ( !equal(st[u],-1) )
	{
		wp_recur(words, st, s ,st[u], fp, path);
		fprintf(fp, "%s \n", words[u]);			
	}
	/*Caso tenha chegado ao fim do caminho, imprime o vertice de origem e o custo do caminho*/
	else			
		fprintf(fp, "%s %i\n", words[u], path);	
}
/** write_path : Retoma a escrita dos caminhos no ficheiro
			:words 	-> Vetor de palavras do mesmo tamanho
			:st 	-> Vetor que contem o caminho inverso ao desejado
			:s 		-> Vertice de origem do caminho
			:dest 	-> Vertice de destino do caminho
			:fp 	-> Ficheiro a escrever o caminho
			:path 	-> Custo do caminho encontrado
	Complexidade: O(Palavras existentes no caminho)
**/
FILE * write_path(char ** words, int * st, int s,int dest, FILE * fp, int path)
{
	int u=dest;

	switch( path )
	{
		/*Caso não tenha sido encontrado caminho entre os dois vertices*/
		case(1000):			fprintf(fp, "%s -1\n%s\n",words[s], words[u]);		break;
		/*Caso o caminho entre vertices tenha custo unitario*/
		case( 1  ):			fprintf(fp, "%s %i\n%s\n", words[s], path,words[u]);break;
		/*Caso o vertice de origem seja igual ao vertice de destino*/
		case( 0  ):			fprintf(fp, "%s %i\n%s\n", words[u], path,words[u]);break;
		/*Caso tenha sido encontrado um caminho, fora das condições acima descritas*/
		default:			wp_recur(words, st, s , u, fp, path);	break;
	}
	fprintf(fp, "\n");
	/*Caso tenha sido construido um vetor com o caminho, apaga-o*/
	if( !equal(st,NULL) )
		free(st);

	return fp;
}
/**	write_file: Escreve um ficheiro .path com o resultado de todos os problemas lidos
			:file_out	-> Nome do ficheiro de saida (*.path)
			:nome_prob 	-> Nome do ficheiro de entrada com os problemas (*.pal)
			:dicionario -> Vetor de conjuntos de palavras do mesmo tamanho lidas do dicionario fornecido
			:n_min 		-> Tamanho da menor palavra guardada
	Complexidade: O(Nº Problemas)*[O(Palavras existentes no caminho)+O(Nº de palavras do mesmo tamanho)+O(Nº de palavras do mesmo tamanho*logN)]
**/
void write_file(char* file_out, char * nome_prob, DICIONARIO * dicionario, int n_min)
{
	if( equal(file_out,NULL) || equal(nome_prob,NULL) ||equal(dicionario,NULL) )
		return;
	
	int *st=NULL;
	int path;
	int pos1,pos2, op;
	int size;

	char palA[PALMAX], palB[PALMAX];

	FILE *fp=NULL;
	FILE *prob=NULL;

	/*Abre os ficheiros*/
	fp=fopen(file_out,"w");
	prob=fopen(nome_prob, "r");
	/*Verifica se os ficheiros foram abertos*/
	nullexit(fp);
	nullexit(prob);
	/*Enquanto houverem problemas a serem lidos*/
	while(fscanf(prob, "%s %s %i", palA, palB, &op) ==3 )
	{
		/*Guarda o tamanho d aprimeira palavra*/
		size=strlen(palA);
		/*Caso as duas palavras sejam iguais*/
		if(equal(size, strlen(palB)))
		{
			/*Se não foi construido grafo para este problema, organiza as palavras alfabeticamente de modo a imprimir-las rapidamente*/
			if( equal( get_grafo(dicionario,realpos(size)),NULL ) )
				qsort( get_words(dicionario,realpos(size)), get_size(dicionario,realpos(size)) , sizeof(char *), string_cmp);
			/*Guarda as posições de ambas as palavras no vetor de palavras do mesmo tamanho*/
			pos1=get_position(dicionario, palA, n_min);
			pos2=get_position(dicionario, palB, n_min);
			/*Procura um caminho mais curto entre as duas palavras*/
			st=path_search(  get_grafo(dicionario,realpos(size)) , pos1 ,  pos2, op, st, &path); 
			/*Escreve no ficheiro de saida o resultado do problema*/
			fp=write_path( get_words(dicionario,realpos(size)), st , pos1,pos2, fp , path); 	
		}
		else /*O problema não tem solução*/
			fprintf(fp, "%s -1\n%s\n\n",palA, palB);
	}
	/*Fecha os ficheiros*/
	fclose(fp);
	fclose(prob);
}


int main(int argc, char * argv[] )
{
	if( less(argc , 3) )
		exit(0);

	char * nome_dic= argv[1];	char * nome_prob=argv[2];
	
	int n_max=0;
	int n_min=0;
	/*Obtem o nome do ficheiro de saida*/
	char * nome_out = (char *)calloc( (strlen(nome_prob) + 2),sizeof(char) );
		nullexit(nome_out);

 	strncpy(nome_out, nome_prob, (strlen(nome_prob)-3)*sizeof(char) );
 	strcat (nome_out, "path");

 	LISTA * grafo_fila=NULL;
	DICIONARIO * dicionario=NULL;

    get_problemas(nome_prob,&n_max, &n_min, &grafo_fila);
    /*Guarda o dicionario fornecido*/
	dicionario=get_dicionario(nome_dic, n_max, n_min, grafo_fila);
		nullexit(dicionario);
	/*Escreve o ficheiro de saida*/
	write_file(nome_out,nome_prob, dicionario, n_min);
	/*Liberta o dicionario guardado*/
	free_dic(dicionario, n_max, n_min);
	/*Liberta a memoria do nome do ficheiro de saida*/
	free(nome_out);
	exit(0);
}
