/*----------------------------------------------------
  include/mazo.h    (Pila)
----------------------------------------------------*/
#ifndef MAZO_H
#define MAZO_H
#include "carta.h"

typedef struct Mazo{
    Carta *cartas;        /* array de 52*n */
    int    tope;          /* índice del próximo slot libre  */
    int    capacidad;     /* 52*n  */
} Mazo;

/* API */
Mazo  *mazo_crear(int n_barajas);
void   mazo_destruir(Mazo *);
void   mazo_barajar(Mazo *);
Carta  mazo_robar(Mazo *);              /* pop  */
int    mazo_restantes(const Mazo *);

#endif
