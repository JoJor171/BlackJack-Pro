/*----------------------------------------------------
  src/lista.c
----------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "carta.h"

Lista *lista_crear(void){ return calloc(1,sizeof(Lista)); }

void lista_push(Lista *l,Carta c){
    Nodo *n = malloc(sizeof *n);
    n->carta=c; n->sig=NULL;
    if(!l->head) l->head=l->tail=n;
    else{ l->tail->sig=n; l->tail=n; }
    l->largo++;
}

static void print_card(const Carta *c){
    printf("[%s%s]", valor_str(c->valor), palo_str(c->palo));
}

void lista_print(const Lista *l){
    for(Nodo *n=l->head;n;n=n->sig){ print_card(&n->carta); putchar(' ');}
}

int lista_valor(const Lista *l){
    int total=0, ases=0;
    for(Nodo *n=l->head;n;n=n->sig){
        int v=n->carta.valor;
        if(v>10) v=10;                  /* figuras valen 10 */
        if(v==1) { ases++; v=11; }      /* as cuenta 11 por ahora */
        total+=v;
    }
    while(total>21 && ases){ total-=10; ases--; } /* algunos As valen 1 */
    return total;
}

void lista_limpiar(Lista *l){
    Nodo *n=l->head;
    while(n){ Nodo *tmp=n->sig; free(n); n=tmp; }
    l->head=l->tail=NULL; l->largo=0;
}

void lista_destruir(Lista *l){ if(!l) return; lista_limpiar(l); free(l); }
