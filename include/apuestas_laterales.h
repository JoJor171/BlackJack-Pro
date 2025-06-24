#ifndef APUESTAS_LATERALES_H
#define APUESTAS_LATERALES_H

#include "carta.h"

// Retorna 1 si hay pareja perfecta, 0 si no
int esParejaPerfecta(Carta c1, Carta c2);

// Retorna 1 si hay 21+3, 0 si no
int esVeintiunoMasTres(Carta c1, Carta c2, Carta c3);

#endif