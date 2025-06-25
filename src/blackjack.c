#include <stdio.h>
#include "blackjack.h"
#include "mazo.h"
#include "carta.h"
#include "utils.h"
#include "apuestas_laterales.h"
#include "arbol.h"




void mostrarMenu() {
    printf("=== BlackJack ===\n");
    printf("1. Jugar\n");
    printf("2. Salir\n");
}

// ...existing code...
void jugarBlackJack(Jugador *jugador) {
    Mazo *mazo = mazo_crear(1);

    // Nuevo árbol vacío para esta partida
    NodoDecision *arbol = NULL;  
    if (!mazo) {
        printf("Error al crear el mazo.\n");
        return;
    }
    // Manejo de fichas
    int apuesta = 0;
    printf("Tienes %d fichas.\n", jugador->fichas);
    printf("¿Cuántas fichas deseas apostar? > ");
    scanf("%d", &apuesta);
    if (apuesta <= 0 || apuesta > jugador->fichas) {
        printf("Apuesta inválida. No tienes suficientes fichas.\n");
        mazo_destruir(mazo);
        return;
    }
    jugador->fichas -= apuesta;

    Carta mano1[12], banca[12], mano2[12];
    int num_mano1 = 0, num_banca = 0, num_mano2 = 0;
    int split = 0, double_down = 0, surrender = 0;
    char opcion;

    // slide beats
    int apuesta_pareja = 0, apuesta_21mas3 = 0;
    char opcion_lateral;

    
    // Apuesta lateral: Pareja Perfecta
    if (jugador->fichas > 0) {
        printf("Pareja Perfecta: Ganas si tus dos primeras cartas son iguales en valor y palo (ejemplo: dos 7 de corazones).\n");
        printf("¿Deseas apostar a 'Pareja Perfecta'? (s/n): ");
        scanf(" %c", &opcion_lateral);
        if (opcion_lateral == 's' || opcion_lateral == 'S') {
            do {
                printf("¿Cuántas fichas apuestas a 'Pareja Perfecta'? (Tienes %d) > ", jugador->fichas);
                scanf("%d", &apuesta_pareja);
                if (apuesta_pareja < 0 || apuesta_pareja > jugador->fichas)
                    printf("Cantidad inválida.\n");
            } while (apuesta_pareja < 0 || apuesta_pareja > jugador->fichas);
            jugador->fichas -= apuesta_pareja;
        }
    }

    // Apuesta lateral: 21+3
    if (jugador->fichas > 0) {
        printf("21+3: Ganas si tus dos primeras cartas y la carta visible de la banca forman una combinación de póker (trío, escalera o color).\n\n");
        printf("¿Deseas apostar a '21+3'? (s/n): ");
        scanf(" %c", &opcion_lateral);
        if (opcion_lateral == 's' || opcion_lateral == 'S') {
            do {
                printf("¿Cuántas fichas apuestas a '21+3'? (Tienes %d) > ", jugador->fichas);
                scanf("%d", &apuesta_21mas3);
                if (apuesta_21mas3 < 0 || apuesta_21mas3 > jugador->fichas)
                    printf("Cantidad inválida.\n");
            } while (apuesta_21mas3 < 0 || apuesta_21mas3 > jugador->fichas);
            jugador->fichas -= apuesta_21mas3;
        }
    }


    // Repartir 2 cartas a cada uno
    mano1[num_mano1++] = mazo_robar(mazo);
    banca[num_banca++] = mazo_robar(mazo);
    mano1[num_mano1++] = mazo_robar(mazo);
    banca[num_banca++] = mazo_robar(mazo);

    // Evaluar Pareja Perfecta
    if (apuesta_pareja > 0 && esParejaPerfecta(mano1[0], mano1[1])) {
        printf("¡Ganaste la apuesta 'Pareja Perfecta'! Premio: %d fichas\n", apuesta_pareja * 25);
        jugador->fichas += apuesta_pareja * 25;
        jugador->sidebets_ganadas++;
    } else if (apuesta_pareja > 0) {
        printf("No ganaste la apuesta 'Pareja Perfecta'.\n");
    }

    // Evaluar 21+3 (usando la carta visible de la banca)
    if (apuesta_21mas3 > 0 && esVeintiunoMasTres(mano1[0], mano1[1], banca[0])) {
        printf("¡Ganaste la apuesta '21+3'! Premio: %d fichas\n", apuesta_21mas3 * 30);
        jugador->fichas += apuesta_21mas3 * 30;
        jugador->sidebets_ganadas++;
    } else if (apuesta_21mas3 > 0) {
        printf("No ganaste la apuesta '21+3'.\n");
    }
// ...continúa el juego normal...

    printf("\n=== Tus cartas ===\n");
    mostrarCartas("Jugador", mano1, num_mano1);
    printf("Total jugador: %d\n", valorMano(mano1, num_mano1));
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
            arbol = insertarDecision(arbol, "Hit");
            mano1[num_mano1++] = mazo_robar(mazo);
            printf("\nTus cartas ahora:\n");
            mostrarCartas("Jugador", mano1, num_mano1);
            printf("Total jugador: %d\n", valorMano(mano1, num_mano1));
            if (valorMano(mano1, num_mano1) > 21) {
                printf("\nTe pasaste de 21. Pierdes!\n");
                mazo_destruir(mazo);
                return;
            }
        } else if (opcion == '2') { // Stand
            arbol = insertarDecision(arbol, "Stand");
            break;
        } else if (opcion == '3') { // Split
            arbol = insertarDecision(arbol, "Split");
            if (num_mano1 == 2 && mano1[0].valor == mano1[1].valor) {
                split = 1;
                mano2[num_mano2++] = mano1[1];
                mano1[1] = mazo_robar(mazo);
                mano2[num_mano2++] = mazo_robar(mazo);
                printf("\nMano 1:\n");
                mostrarCartas("Jugador 1", mano1, num_mano1);
                printf("Mano 2:\n");
                mostrarCartas("Jugador 2", mano2, num_mano2);
                break; // Salimos para jugar ambas manos por separado
            } else {
                printf("No puedes dividir. Solo puedes dividir si tus dos primeras cartas son iguales.\n");
            }
        } else if (opcion == '4') { // Double Down
            arbol = insertarDecision(arbol, "Double Down");
            if (num_mano1 == 2) {
                double_down = 1;
                mano1[num_mano1++] = mazo_robar(mazo);
                printf("\nHas doblado. Tus cartas ahora:\n");
                mostrarCartas("Jugador", mano1, num_mano1);
                break; // Solo una carta extra y luego se planta
            } else {
                printf("Solo puedes doblar con las dos primeras cartas.\n");
            }
        } else if (opcion == '5') { // Surrender
            arbol = insertarDecision(arbol, "Surrender");
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
        int n1 = num_mano1;
        while (1) {
            printf("Mano 1 total: %d\n", valorMano(mano1, n1));
            printf("Pedir carta a Mano 1? (s/n): ");
            scanf(" %c", &opcion);
            if (opcion == 's' || opcion == 'S') {
                mano1[n1++] = mazo_robar(mazo);
                mostrarCartas("Jugador 1", mano1, n1);
                if (valorMano(mano1, n1) > 21) {
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
        int n2 = num_mano2;
        while (1) {
            printf("Mano 2 total: %d\n", valorMano(mano2, n2));
            printf("Pedir carta a Mano 2? (s/n): ");
            scanf(" %c", &opcion);
            if (opcion == 's' || opcion == 'S') {
                mano2[n2++] = mazo_robar(mazo);
                mostrarCartas("Jugador 2", mano2, n2);
                if (valorMano(mano2, n2) > 21) {
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

        int total1 = valorMano(mano1, n1);
        int total2 = valorMano(mano2, n2);

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
        printf("\nÁrbol de decisiones de esta partida:\n");
        mostrarArbol(arbol);
        printf("NULL\n");

        // Liberar memoria del árbol
        destruirArbol(arbol);
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

    int total_jugador = valorMano(mano1, num_mano1);
    int total_banca = valorMano(banca, num_banca);

    printf("\n=== Resultado final ===\n");
    printf("Tus cartas: ");
    mostrarCartas("", mano1, num_mano1);
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
    // Actualizar fichas del jugador
    int resultado = 0;
    if (surrender) {
        resultado = -1; // Pierde la Mitad de la apuesta
    } else if (total_banca > 21 || total_jugador > total_banca){
        resultado = 1; // Gana la apuesta 
    } else if (total_jugador < total_banca){
        resultado = -1; //Pierde la apuesta
    } else{
        resultado = 0; // Empate 
    }
    if (resultado == 1) {
        printf("¡Ganaste! Ganas %d fichas.\n", apuesta * 2);
        jugador->fichas += apuesta * 2;
    } else if (resultado == 0) {
        printf("Empate. Recuperas tu apuesta.\n");
        jugador->fichas += apuesta;
    } else {
        printf("Perdiste %d fichas.\n", apuesta);
    }

    printf("Ahora tienes %d fichas.\n", jugador->fichas);
    jugador->partidas_jugadas++;

    if (resultado == 1) { // Ganó
        jugador->ganadas++;
        jugador->racha_actual++;
        if (jugador->racha_actual > jugador->racha_maxima)
            jugador->racha_maxima = jugador->racha_actual;
    } else if (resultado == 0) { // Empate
        jugador->empatadas++;
    } else { // Perdió
        jugador->perdidas++;
        jugador->racha_actual = 0;
    }

    if (split) jugador->split_usado++;
    if (double_down) jugador->double_usado++;
    if (surrender) jugador->surrender_usado++;
    printf("\nÁrbol de decisiones de esta partida:\n");
    mostrarArbol(arbol);
    printf("NULL\n");

    // Liberar memoria del árbol
    destruirArbol(arbol);
    mazo_destruir(mazo);
}

    

// ...existing