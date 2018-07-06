#ifndef lista_header
#define lista_header

#include "const_estru.h"

/** Definição do tipo de estrutura LISTA;
**/
typedef struct _lista LISTA;
/** isrt_lista :  Insere um novo nó na lista, no inicio desta (FILO)
                  Retorna o valor da head atualizado
      :head -> Ponteiro para a cabeça da lista
      :this -> Item que se pretende inserir na lista
**/
LISTA * isrt_lista(LISTA * head, Item this);
/** isrt_ord_lista: Insere um novo nó no final da lista (FIFO)
                    Retorna o valor da tail atualizado
                    Inicializa uma nova lista caso esteja vazia
      :head -> Ponteiro para a cabeça da lista
      :tail -> Ponteiro para o final da lista
      :this -> Item que se pretende inserir na lista
**/
LISTA * isrt_ord_lista(LISTA ** head, LISTA * tail, Item this);
/** getItem_lista : Retorna o item do presente nó da lista
      :node   : Nó que se quer extrair o conteudo
**/
Item getItem_lista(LISTA * node);
/** getNext_lista : Retorna o ponteiro para o proximo nó da lista
      : node  ->  Nó atual da lista
**/
LISTA * getNext_lista(LISTA * node);
/** free_lista  : Liberta toda a memória alocada utilizada para guardar a lista
      :head ->  Ponteiro para a cabeça da lista
      :freeItem -> Apontador para uma função que liberta a memória alocada para guardar o item da lista
**/
void free_lista(LISTA * first, void (* freeItemFnt)(Item));


#endif

