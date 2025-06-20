/*----------------------------------------------------
  include/carta.h
----------------------------------------------------*/
#ifndef CARTA_H
#define CARTA_H

typedef enum Palo   { CORAZON, DIAMANTE, TREBOL, PICA } Palo;

typedef struct Carta{
    int  valor;   /* 1-13  (A=1, J=11, Q=12, K=13) */
    Palo palo;
} Carta;

const char *palo_str(Palo p);     /* ♥ ♦ ♣ ♠ */
const char *valor_str(int v);     /* A 2 … K */

#endif
