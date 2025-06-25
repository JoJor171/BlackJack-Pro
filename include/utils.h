/*----------------------------------------------------
  include/utils.h
----------------------------------------------------*/
#ifndef UTILS_H
#define UTILS_H

#include "blackjack.h"
#include "carta.h"

int rng_int(int a, int b); // uniforme [a,b]
void mostrarCartas(const char *nombre, Carta *mano, int num_cartas);
int valorMano(Carta *mano, int num_cartas);
void fichasIniciales(int *fichas);
void guardarProgreso(Jugador *jugador);
int cargarProgreso(Jugador *jugador);

#endif