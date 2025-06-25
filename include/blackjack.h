#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "carta.h"
#include "arbol.h"
#include "stats.h"
#include "historial.h"

typedef struct{
    int fichas;
    statsMap estadisticas;
    Historial historial;
    NodoDecision *arbol_actual;
}Jugador;

void mostrarMenu();
void jugarBlackJack(Jugador *jugador);
void inicializarEstadisticas(Jugador *jugador);
void mostrarEstadisticas(Jugador *jugador);

#endif
