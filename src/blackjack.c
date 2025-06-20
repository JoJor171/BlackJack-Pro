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
    Mazo *mazo = mazo_crear(1);
    if (!mazo) {
        printf("Error al crear el mazo.\n");
        return;
    }

    Carta jugador[12], banca[12], jugador2[12];
    int num_jugador = 0, num_banca = 0, num_jugador2 = 0;
    int split = 0, double_down = 0, surrender = 0;
    char opcion;

    // Repartir 2 cartas a cada uno
    jugador[num_jugador++] = mazo_robar(mazo);
    banca[num_banca++] = mazo_robar(mazo);
    jugador[num_jugador++] = mazo_robar(mazo);
    banca[num_banca++] = mazo_robar(mazo);

    printf("\n=== Tus cartas ===\n");
    mostrarCartas("Jugador", jugador, num_jugador);
    printf("Total jugador: %d\n", valorMano(jugador, num_jugador));
    printf("\nCarta visible de la banca:\n");
    mostrarCartas("Banca", &banca[0], 1);
    printf("Total banca (visible): %d\n", valorMano(&banca[0], 1));
    // Opciones del jugador
    while (1) {
        printf("\nElige una opcion:\n");
        printf("1. Pedir carta (Hit)\n");
        printf("2. Plantarse (Stand)\n");
        printf("3. Dividir (Split)\n");
        printf("4. Doblar (Double Down)\n");
        printf("5. Rendirse (Surrender)\n");
        printf("Opcion > ");
        scanf(" %c", &opcion);

        if (opcion == '1') { // Hit
            jugador[num_jugador++] = mazo_robar(mazo);
            printf("\nTus cartas ahora:\n");
            mostrarCartas("Jugador", jugador, num_jugador);
            printf("Total jugador: %d\n", valorMano(jugador, num_jugador));
            if (valorMano(jugador, num_jugador) > 21) {
                printf("\nTe pasaste de 21. Pierdes!\n");
                mazo_destruir(mazo);
                return;
            }
        } else if (opcion == '2') { // Stand
            break;
        } else if (opcion == '3') { // Split
            if (num_jugador == 2 && jugador[0].valor == jugador[1].valor) {
                split = 1;
                jugador2[num_jugador2++] = jugador[1];
                jugador[1] = mazo_robar(mazo);
                jugador2[num_jugador2++] = mazo_robar(mazo);
                printf("\nMano 1:\n");
                mostrarCartas("Jugador 1", jugador, num_jugador);
                printf("Mano 2:\n");
                mostrarCartas("Jugador 2", jugador2, num_jugador2);
                break; // Salimos para jugar ambas manos por separado
            } else {
                printf("No puedes dividir. Solo puedes dividir si tus dos primeras cartas son iguales.\n");
            }
        } else if (opcion == '4') { // Double Down
            if (num_jugador == 2) {
                double_down = 1;
                jugador[num_jugador++] = mazo_robar(mazo);
                printf("\nHas doblado. Tus cartas ahora:\n");
                mostrarCartas("Jugador", jugador, num_jugador);
                break; // Solo una carta extra y luego se planta
            } else {
                printf("Solo puedes doblar con las dos primeras cartas.\n");
            }
        } else if (opcion == '5') { // Surrender
            surrender = 1;
            printf("\nTe has rendido. Pierdes la mitad de tu apuesta.\n");
            mazo_destruir(mazo);
            return;
        } else {
            printf("Opcion no valida. Intenta de nuevo.\n");
        }
    }

    // Si hubo split, jugar ambas manos
    if (split) {
        printf("\n--- Jugando Mano 1 ---\n");
        int bust1 = 0;
        int n1 = num_jugador;
        while (1) {
            printf("Mano 1 total: %d\n", valorMano(jugador, n1));
            printf("Pedir carta a Mano 1? (s/n): ");
            scanf(" %c", &opcion);
            if (opcion == 's' || opcion == 'S') {
                jugador[n1++] = mazo_robar(mazo);
                mostrarCartas("Jugador 1", jugador, n1);
                if (valorMano(jugador, n1) > 21) {
                    printf("Mano 1 se paso de 21!\n");
                    bust1 = 1;
                    break;
                }
            } else {
                break;
            }
        }
        printf("\n--- Jugando Mano 2 ---\n");
        int bust2 = 0;
        int n2 = num_jugador2;
        while (1) {
            printf("Mano 2 total: %d\n", valorMano(jugador2, n2));
            printf("Pedir carta a Mano 2? (s/n): ");
            scanf(" %c", &opcion);
            if (opcion == 's' || opcion == 'S') {
                jugador2[n2++] = mazo_robar(mazo);
                mostrarCartas("Jugador 2", jugador2, n2);
                if (valorMano(jugador2, n2) > 21) {
                    printf("Mano 2 se paso de 21!\n");
                    bust2 = 1;
                    break;
                }
            } else {
                break;
            }
        }
        // Turno de la banca
        printf("\n=== Turno de la banca ===\n");
        mostrarCartas("Banca", banca, num_banca);
        printf("Total banca: %d\n", valorMano(banca, num_banca));
        while (valorMano(banca, num_banca) < 17) {
            printf("La banca pide carta...\n");
            banca[num_banca++] = mazo_robar(mazo);
            mostrarCartas("Banca", banca, num_banca);
        }
        int total_banca = valorMano(banca, num_banca);
        printf("\n=== Resultado final ===\n");
        printf("Cartas banca: ");
        mostrarCartas("", banca, num_banca);
        printf("Total banca: %d\n", total_banca);

        int total1 = valorMano(jugador, n1);
        int total2 = valorMano(jugador2, n2);

        printf("\nMano 1: ");
        if (bust1)
            printf("Perdiste (te pasaste de 21)\n");
        else if (total_banca > 21 || total1 > total_banca)
            printf("Ganaste!\n");
        else if (total1 < total_banca)
            printf("Perdiste.\n");
        else
            printf("Empate.\n");

        printf("Mano 2: ");
        if (bust2)
            printf("Perdiste (te pasaste de 21)\n");
        else if (total_banca > 21 || total2 > total_banca)
            printf("Ganaste!\n");
        else if (total2 < total_banca)
            printf("Perdiste.\n");
        else
            printf("Empate.\n");

        mazo_destruir(mazo);
        return;
    }

    // Turno de la banca
    printf("\n=== Turno de la banca ===\n");
    mostrarCartas("Banca", banca, num_banca);
    while (valorMano(banca, num_banca) < 17) {
        printf("La banca pide carta...\n");
        banca[num_banca++] = mazo_robar(mazo);
        mostrarCartas("Banca", banca, num_banca);
    }

    int total_jugador = valorMano(jugador, num_jugador);
    int total_banca = valorMano(banca, num_banca);

    printf("\n=== Resultado final ===\n");
    printf("Tus cartas: ");
    mostrarCartas("", jugador, num_jugador);
    printf("Total jugador: %d\n", total_jugador);
    printf("Cartas banca: ");
    mostrarCartas("", banca, num_banca);
    printf("Total banca: %d\n", total_banca);

    if (double_down) {
        printf("\nNota: Doblaste tu apuesta.\n");
    }
    if (surrender) {
        printf("\nNota: Te rendiste, pierdes la mitad de tu apuesta.\n");
    } else if (total_banca > 21 || total_jugador > total_banca) {
        printf("\nGanaste!\n");
    } else if (total_jugador < total_banca) {
        printf("\nPerdiste.\n");
    } else {
        printf("\nEmpate.\n");
    }

    mazo_destruir(mazo);
}