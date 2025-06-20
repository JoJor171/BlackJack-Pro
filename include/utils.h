/*----------------------------------------------------
  include/utils.h
----------------------------------------------------*/
#ifndef UTILS_H
#define UTILS_H

#include "carta.h"

int rng_int(int a, int b); // uniforme [a,b]
void mostrarCartas(const char *nombre, Carta *mano, int num_cartas);
int valorMano(Carta *mano, int num_cartas);

#endif