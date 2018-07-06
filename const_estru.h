#ifndef const_estru_header
#define const_estru_header

/*Número máximo de caracteres a ler numa palavra lida dum ficheiro*/
#define PALMAX 28
/*A menor que B*/
#define less(A,B) (A<B)
/*Troca A com B*/
#define exch(A,B) {int t=A; A=B; B=t;}
/*A igual a B*/
#define equal(A,B) (A==B)
/*Termina o programa caso A seja NULL*/
#define nullexit(A) {if( equal(A,NULL) ) exit(0);}
/*Determina a posição de um determinado indice no vetor de DICIONARIO's*/
#define realpos(A) (A-n_min)
/*Item -> ponteiro para void*/
typedef void * Item;

#endif