#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "carta.h"


typedef struct{
    int fichas;
} Jugador;

void mostrarMenu();
void jugarBlackJack(Jugador *jugador);

#endif
