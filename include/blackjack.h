#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "carta.h"
#include "stats.h"

typedef struct{
    int fichas;
    statsMap estadisticas;
} Jugador;

void mostrarMenu();
void jugarBlackJack(Jugador *jugador);
void inicializarEstadisticas(Jugador *jugador);
void mostrarEstadisticas(Jugador *jugador);


#endif
