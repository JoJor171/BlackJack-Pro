/*----------------------------------------------------
  src/utils.c
----------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "carta.h"

void mostrarCartas(const char *nombre, Carta *mano, int num_cartas) {
    printf("%s: ", nombre);
    for (int i = 0; i < num_cartas; i++) {
        printf("%s%s ", valor_str(mano[i].valor), palo_str(mano[i].palo));
    }
    printf("\n");
}

int valorMano(Carta *mano, int num_cartas) {
    int total = 0, ases = 0;
    for (int i = 0; i < num_cartas; i++) {
        int v = mano[i].valor;
        if (v > 10) v = 10;
        if (v == 1) ases++;
        total += v;
    }
    while (ases > 0 && total <= 11) {
        total += 10;
        ases--;
    }
    return total;
}

int rng_int(int a, int b) {
    return a + rand() % (b - a + 1);
}