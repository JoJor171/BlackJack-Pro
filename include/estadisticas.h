#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

#include "blackjack.h"

void mostrarEstadisticas(Jugador *jugador);
void inicializarEstadisticas(Jugador *jugador);
void guardarProgreso(Jugador *jugador);
int cargarProgreso(Jugador *jugador);
#endif