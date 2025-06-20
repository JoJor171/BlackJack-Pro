/*----------------------------------------------------
  include/lista.h    (Mano del jugador / dealer)
----------------------------------------------------*/
#ifndef LISTA_H
#define LISTA_H
#include "carta.h"

typedef struct Nodo{
    Carta carta;
    struct Nodo *sig;
} Nodo;

typedef struct Lista{
    Nodo *head, *tail;
    int   largo;
} Lista;

Lista *lista_crear(void);
void   lista_push(Lista *, Carta c);  /* inserta al final */
void   lista_print(const Lista *);
int    lista_valor(const Lista *);    /* cuenta As = 1 u 11 */
void   lista_limpiar(Lista *);
void   lista_destruir(Lista *);

#endif
