#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "carta.h"


typedef struct{
    int fichas;
    int partidas_jugadas;
    int ganadas;
    int perdidas;
    int empatadas;
    int racha_actual;
    int racha_maxima;
    int split_usado;
    int double_usado;
    int surrender_usado;
    int sidebets_ganadas;
} Jugador;

void mostrarMenu();
void jugarBlackJack(Jugador *jugador);

#endif
