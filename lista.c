/** lista.c
**  
**  Ficheiro que contem todas as operações relacionadas com listas simplesmente ligadas
**  
**    Foi utilizado o ficheiro LinkedList.c do laboratório 4 como base para esta implementação
**  tendo sido utilizadas algumas funções do mesmo e acrescentadas ou modificadas outras
**/

#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
/*_lista
  this -> Conteudo da lista ligada
  next -> Ponteiro para o proximo no da lista
*/
struct _lista{
  Item * this;
  struct _lista *next;
};
/** isrt_lista :  Insere um novo nó na lista, no inicio desta (FILO)
                  Retorna o valor da head atualizado
      :head -> Ponteiro para a cabeça da lista
      :this -> Item que se pretende inserir na lista
**/
LISTA * isrt_lista(LISTA * head, Item this)
{
  LISTA * new_node= NULL;
  /*Aloca memória para o novo no*/
  new_node = (LISTA *) malloc(sizeof(LISTA));
    /*Verifica a alocação*/
    nullexit(new_node);
  /*Inicialização e inserção do novo nó*/
  new_node->this = this;
  new_node->next = head;

  return new_node;
}
/** isrt_ord_lista: Insere um novo nó no final da lista (FIFO)
                    Retorna o valor da tail atualizado
                    Inicializa uma nova lista caso esteja vazia
      :head -> Ponteiro para a cabeça da lista
      :tail -> Ponteiro para o final da lista
      :this -> Item que se pretende inserir na lista
**/
LISTA * isrt_ord_lista(LISTA ** head, LISTA * tail, Item this)
{
  LISTA * new_node= NULL;
  /*  Alocação de memória para o novo nó*/
  new_node = (LISTA *) malloc(sizeof(LISTA));
    nullexit(new_node);

  /*Inicialização do novo nó*/
  new_node->this = this;
  new_node->next = NULL;
  /*Iserção do novo nó*/
  /*Caso a lista esteja vazia*/
  if( equal(*head,NULL) )
    *head=new_node;
  else
   tail->next = new_node;  
  /*Atualiza a tail*/
  tail=new_node; 

  return tail;
}
/** getItem_lista : Retorna o item do presente nó da lista
      :node   : Nó que se quer extrair o conteudo
**/
Item getItem_lista(LISTA * node)
{
  if( equal(node , NULL) )
    return NULL;

  return node->this;
}
/** getNext_lista : Retorna o ponteiro para o proximo nó da lista
      : node  ->  Nó atual da lista
**/
LISTA * getNext_lista(LISTA * node)
{
  return ( equal(node , NULL) ? NULL : node->next);
}
/** free_lista  : Liberta toda a memória alocada utilizada para guardar a lista
      :head ->  Ponteiro para a cabeça da lista
      :freeItem -> Apontador para uma função que liberta a memória alocada para guardar o item da lista
**/
void free_lista(LISTA * head, void (* freeItem)(Item))
{
  LISTA * aux=head;
  /*Enquanto houver elementos na lista*/
  while( !equal(head,NULL) )
  {/*Remove o ultimo elemento da lista*/
    aux=head;
    head=getNext_lista(head);

    freeItem(aux->this);
    free(aux);

  }
}