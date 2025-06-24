#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "carta.h"


typedef struct{
    int fichas;
} jugador;

void mostrarMenu();
void jugarBlackJack(jugador *jugador);

#endif
