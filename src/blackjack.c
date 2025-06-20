#include <stdio.h>
#include "blackjack.h"
#include "mazo.h"
#include "carta.h"
#include "utils.h"


void mostrarMenu() {
    printf("=== BlackJack ===\n");
    printf("1. Jugar\n");
    printf("2. Salir\n");
}

void jugarBlackJack() {
    Mazo mazo;
    Carta jugador[12], banca[12];
    int num_jugador = 0, num_banca = 0;
    char opcion;

    inicializarMazo(&mazo);
    barajarMazo(&mazo);

    // Repartir 2 cartas a cada uno
    jugador[num_jugador++] = mazo_robar(&mazo);
    banca[num_banca++] = mazo_robar(&mazo);
    jugador[num_jugador++] = mazo_robar(&mazo);
    banca[num_banca++] = mazo_robar(&mazo);

    printf("\nTus cartas:\n");
    mostrarCartas("Jugador", jugador, num_jugador);
    printf("Carta visible de la banca:\n");
    mostrarCartas("Banca", &banca[0], 1);

    // Turno del jugador
    while (1) {
        printf("Tu total: %d\n", valorMano(jugador, num_jugador));
        printf("¿Pedir carta (p) o plantarse (s)? ");
        scanf(" %c", &opcion);
        if (opcion == 'p' || opcion == 'P') {
            jugador[num_jugador++] = mazo_robar(&mazo);
            mostrarCartas("Jugador", jugador, num_jugador);
            if (valorMano(jugador, num_jugador) > 21) {
                printf("Te pasaste de 21. ¡Pierdes!\n");
                return;
            }
        } else if (opcion == 's' || opcion == 'S') {
            break;
        } else {
            printf("Opción no válida.\n");
        }
    }

    // Turno de la banca
    printf("\nTurno de la banca...\n");
    mostrarCartas("Banca", banca, num_banca);
    while (valorMano(banca, num_banca) < 17) {
        banca[num_banca++] = mazo_robar(&mazo);
        mostrarCartas("Banca", banca, num_banca);
    }

    int total_jugador = valorMano(jugador, num_jugador);
    int total_banca = valorMano(banca, num_banca);

    printf("\nTotal jugador: %d\n", total_jugador);
    printf("Total banca: %d\n", total_banca);

    if (total_banca > 21 || total_jugador > total_banca) {
        printf("¡Ganaste!\n");
    } else if (total_jugador < total_banca) {
        printf("Perdiste.\n");
    } else {
        printf("Empate.\n");
    }
}