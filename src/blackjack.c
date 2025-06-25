#include <stdio.h>
#include "blackjack.h"
#include "mazo.h"
#include "carta.h"
#include "utils.h"
#include "apuestas_laterales.h"
#include "arbol.h"

void inicializarEstadisticas(Jugador *jugador) {
    jugador->fichas = jugador->fichas;
    stats_map_init(&jugador->estadisticas);
    stats_map_set(&jugador->estadisticas, "partidas_jugadas", 0);
    stats_map_set(&jugador->estadisticas, "ganadas", 0);
    stats_map_set(&jugador->estadisticas, "perdidas", 0);
    stats_map_set(&jugador->estadisticas, "empatadas", 0);
    stats_map_set(&jugador->estadisticas, "racha_actual", 0);
    stats_map_set(&jugador->estadisticas, "racha_maxima", 0);
    stats_map_set(&jugador->estadisticas, "split_usado", 0);
    stats_map_set(&jugador->estadisticas, "double_usado", 0);
    stats_map_set(&jugador->estadisticas, "surrender_usado", 0);
    stats_map_set(&jugador->estadisticas, "sidebets_ganadas", 0);
}

void mostrarEstadisticas(Jugador *jugador) {
    printf("\n=== Estadisticas del Jugador ===\n");
    printf("Fichas actuales: %d\n", jugador->fichas);
    printf("Partidas jugadas: %d\n", stats_map_get(&jugador->estadisticas, "partidas_jugadas"));
    printf("Ganadas: %d\n", stats_map_get(&jugador->estadisticas, "ganadas"));
    printf("Perdidas: %d\n", stats_map_get(&jugador->estadisticas, "perdidas"));
    printf("Empatadas: %d\n", stats_map_get(&jugador->estadisticas, "empatadas"));
    printf("Racha actual de victorias: %d\n", stats_map_get(&jugador->estadisticas, "racha_actual"));
    printf("Racha maxima de victorias: %d\n", stats_map_get(&jugador->estadisticas, "racha_maxima"));
    printf("Veces que usO Split: %d\n", stats_map_get(&jugador->estadisticas, "split_usado"));
    printf("Veces que usO Double Down: %d\n", stats_map_get(&jugador->estadisticas, "double_usado"));
    printf("Veces que se rindiO (Surrender): %d\n", stats_map_get(&jugador->estadisticas, "surrender_usado"));
    printf("Apuestas laterales ganadas: %d\n", stats_map_get(&jugador->estadisticas, "sidebets_ganadas"));
    printf("================================\n\n");
}

void jugarBlackJack(Jugador *jugador) {
    Mazo *mazo = mazo_crear(1);
    Carta mano1[12], banca[12], mano2[12];
    int num_mano1 = 0, num_banca = 0, num_mano2 = 0;
    int split = 0, double_down = 0, surrender = 0;
    int fichas_antes = jugador->fichas;
    char opcion;

    NodoDecision *arbol = NULL;  
    if (!mazo) {
        printf("Error al crear el mazo.\n");
        return;
    }
    int apuesta = 0;
    printf("Tienes %d fichas.\n", jugador->fichas);
    printf("Cuantas fichas deseas apostar? > ");
    scanf("%d", &apuesta);
    if (apuesta <= 0 || apuesta > jugador->fichas) {
        printf("Apuesta invalida. No tienes suficientes fichas.\n");
        mazo_destruir(mazo);
        return;
    }
    jugador->fichas -= apuesta;

    int apuesta_pareja = 0, apuesta_21mas3 = 0;

    // Apuesta lateral: Pareja Perfecta
    if (jugador->fichas > 0) {
        printf("\n--- Apuestas Laterales ---\n");
        printf("Pareja Perfecta: Ganas si tus dos primeras cartas son iguales en valor y palo (ejemplo: dos 7 de corazones).\n");
        do {
            printf("Cuantas fichas apuestas a 'Pareja Perfecta'? (0 para no apostar, tienes %d) > ", jugador->fichas);
            scanf("%d", &apuesta_pareja);
            if (apuesta_pareja < 0 || apuesta_pareja > jugador->fichas)
                printf("Cantidad invalida.\n");
        } while (apuesta_pareja < 0 || apuesta_pareja > jugador->fichas);
        jugador->fichas -= apuesta_pareja;
    }

    // Apuesta lateral: 21+3
    if (jugador->fichas > 0) {
        printf("\n21+3: Ganas si tus dos primeras cartas y la carta visible de la banca forman una combinaciOn de pOker (trio, escalera o color).\n");
        do {
            printf("Cuantas fichas apuestas a '21+3'? (0 para no apostar, tienes %d) > ", jugador->fichas);
            scanf("%d", &apuesta_21mas3);
            if (apuesta_21mas3 < 0 || apuesta_21mas3 > jugador->fichas)
                printf("Cantidad invalida.\n");
        } while (apuesta_21mas3 < 0 || apuesta_21mas3 > jugador->fichas);
        jugador->fichas -= apuesta_21mas3;
    }

    // Repartir 2 cartas a cada uno
    mano1[num_mano1++] = mazo_robar(mazo);
    banca[num_banca++] = mazo_robar(mazo);
    mano1[num_mano1++] = mazo_robar(mazo);
    banca[num_banca++] = mazo_robar(mazo);

    // Evaluar Pareja Perfecta
    if (apuesta_pareja > 0 && esParejaPerfecta(mano1[0], mano1[1])) {
        printf("Ganaste la apuesta 'Pareja Perfecta'! Premio: %d fichas\n", apuesta_pareja * 25);
        jugador->fichas += apuesta_pareja * 25;
        stats_map_sum(&jugador->estadisticas, "sidebets_ganadas", 1);
    } else if (apuesta_pareja > 0) {
        printf("No ganaste la apuesta 'Pareja Perfecta'.\n");
    }

    // Evaluar 21+3 (usando la carta visible de la banca)
    if (apuesta_21mas3 > 0 && esVeintiunoMasTres(mano1[0], mano1[1], banca[0])) {
        printf("Ganaste la apuesta '21+3'! Premio: %d fichas\n", apuesta_21mas3 * 30);
        jugador->fichas += apuesta_21mas3 * 30;
        stats_map_sum(&jugador->estadisticas, "sidebets_ganadas", 1);
    } else if (apuesta_21mas3 > 0) {
        printf("No ganaste la apuesta '21+3'.\n");
    }

    mostrarCartas("\nTus cartas:", mano1, num_mano1);
    printf("Total: %d\n", valorMano(mano1, num_mano1));
    mostrarCartas("\nCarta del crupier", &banca[0], 1);
    printf("Total: %d\n", valorMano(&banca[0], 1)); 

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
            arbol = insertarDecision(arbol, "Pediste");
            mano1[num_mano1++] = mazo_robar(mazo);
            printf("\nTus cartas ahora:\n");
            mostrarCartas("Tus cartas", mano1, num_mano1);
            printf("Total: %d\n", valorMano(mano1, num_mano1));
            if (valorMano(mano1, num_mano1) > 21) {
                printf("\nTe pasaste de 21. Pierdes!\n");
                historial_agregar(
                    &jugador->historial,
                    apuesta,                // cantidad apostada
                    fichas_antes,           // fichas antes de la partida (debes g2r al inicio)
                    jugador->fichas,        // fichas despues de la partida
                    "Derrota");       // cadena de texto con el resultado
                mazo_destruir(mazo);
                return;
            }
        } else if (opcion == '2') { // Stand
            arbol = insertarDecision(arbol, "Te plantaste");
            break;
        } else if (opcion == '3') { // Split
            arbol = insertarDecision(arbol, "Dividiste");
            if (num_mano1 == 2 && mano1[0].valor == mano1[1].valor) {
                split = 1;
                mano2[num_mano2++] = mano1[1];
                mano1[1] = mazo_robar(mazo);
                mano2[num_mano2++] = mazo_robar(mazo);
                printf("\nMano 1:\n");
                mostrarCartas("Jugador 1", mano1, num_mano1);
                printf("Mano 2:\n");
                mostrarCartas("Jugador 2", mano2, num_mano2);
                break;
            } else {
                printf("No puedes dividir. Solo puedes dividir si tus dos primeras cartas.\n");
            }
        } else if (opcion == '4') { // Double Down
            arbol = insertarDecision(arbol, "Doblaste");
            if (num_mano1 == 2) {
                double_down = 1;
                mano1[num_mano1++] = mazo_robar(mazo);
                printf("\nHas doblado. Tus cartas ahora:\n");
                mostrarCartas("Jugador", mano1, num_mano1);
                break;
            } else {
                printf("Solo puedes doblar con las dos primeras cartas.\n");
            }
        } else if (opcion == '5') { // Surrender
            arbol = insertarDecision(arbol, "Te rendiste");
            surrender = 1;
            printf("\nTe has rendido. Pierdes la mitad de tu apuesta.\n");
                            historial_agregar(
                    &jugador->historial,
                    apuesta,                // cantidad apostada
                    fichas_antes,           // fichas antes de la partida (debes g2r al inicio)
                    jugador->fichas,        // fichas despues de la partida
                    "Surrender");       // cadena con el resultado
            mazo_destruir(mazo);
            stats_map_sum(&jugador->estadisticas, "surrender_usado", 1);
            return;
        } else {
            printf("Opcion no valida. Intenta de nuevo.\n");
        }
    }

    // Si hubo split, jugar ambas manos (igual que antes, pero usa stats_map_sum p2
    if (split) {
    stats_map_sum(&jugador->estadisticas, "split_usado", 1);

    // Aqui deberias calcular el resultado real de la mano split.
    // Por simplicidad, supongamos que el jugador pierde la mano split:
    int resultado_split = -1; // Cambia esto según la logica real de tu juego

    historial_agregar(
        &jugador->historial,
        apuesta,
        fichas_antes,
        jugador->fichas,
        (resultado_split == 1) ? "Victoria" :
        (resultado_split == 0) ? "Empate" : "Derrota"
    );

    int gano = (resultado_split == 1) ? 1 : 0;
    printf("\nArbol de decisiones de esta partida:");
    mostrarArbol(arbol, gano);

    // Guarda el arbol en el jugador para mostrarlo despues
    if (jugador->arbol_actual)
        destruirArbol(jugador->arbol_actual);
    jugador->arbol_actual = arbol;

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

    // Bonificaciones (igual que antes, no afectan estadisticas)
    if (num_mano1 == 5 && valorMano(mano1, num_mano1) <= 21) {
        int bono = apuesta * 2;
        printf("\nBONIFICACION! Cinco cartas sin pasarte de 21. Ganas %d fichas extra.\n", bono);
        jugador->fichas += bono;
    }
    if (num_mano1 == 2 && valorMano(mano1, num_mano1) == 21) {
        int bono = apuesta;
        printf("\nBONIFICACION! ¡Blackjack natural! Ganas %d fichas extra.\n", bono);
        jugador->fichas += bono;
    }
    if (num_mano1 >= 3 &&
        mano1[0].valor == 7 &&
        mano1[1].valor == 7 &&
        mano1[2].valor == 7) {
        int bono = apuesta * 5;
        printf("\nBONIFICACION! ¡Tres sietes (777)! Ganas %d fichas extra.\n", bono);
        jugador->fichas += bono;
    }
    if (num_mano1 == 6 && valorMano(mano1, num_mano1) <= 21) {
        int bono = apuesta * 4;
        printf("\nBONIFICACION! ¡Seis cartas sin pasarte de 21! Ganas %d fichas extra.\n", bono);
        jugador->fichas += bono;
    }
    if (num_mano1 == 5 && valorMano(mano1, num_mano1) == 21) {
        int bono = apuesta * 3;
        printf("\nBONIFICACION! ¡21 exacto con cinco cartas! Ganas %d fichas extra.\n", bono);
        jugador->fichas += bono;
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
        stats_map_sum(&jugador->estadisticas, "double_usado", 1);
    }
    if (surrender) {
        printf("\nNota: Te rendiste, pierdes la mitad de tu apuesta.\n");
        stats_map_sum(&jugador->estadisticas, "surrender_usado", 1);
    } else if (total_banca > 21 || total_jugador > total_banca) {
        printf("\nGanaste!\n");
    } else if (total_jugador < total_banca) {
        printf("\nPerdiste.\n");
    } else {
        printf("\nEmpate.\n");
    }

    // Actualizar estadisticas usando el mapa
    int resultado = 0;
    if (surrender) {
        resultado = -1;
    } else if (total_banca > 21 || total_jugador > total_banca){
        resultado = 1;
    } else if (total_jugador < total_banca){
        resultado = -1;
    } else{
        resultado = 0;
    }

    stats_map_sum(&jugador->estadisticas, "partidas_jugadas", 1);

    if (resultado == 1) {
        printf("+%d fichas.\n", apuesta * 2);
        jugador->fichas += apuesta * 2;
        stats_map_sum(&jugador->estadisticas, "ganadas", 1);
        stats_map_sum(&jugador->estadisticas, "racha_actual", 1);
        int racha_actual = stats_map_get(&jugador->estadisticas, "racha_actual");
        int racha_maxima = stats_map_get(&jugador->estadisticas, "racha_maxima");
        if (racha_actual > racha_maxima)
            stats_map_set(&jugador->estadisticas, "racha_maxima", racha_actual);
        historial_agregar(
                    &jugador->historial,
                    apuesta,                // cantidad apostada
                    fichas_antes,           // fichas antes de la partida (debes guardar este valor al inicio)
                    jugador->fichas,        // fichas despues de la partida
                    "Victoria");
    } else if (resultado == 0) {
        printf("Empate. Recuperas tu apuesta.\n");
        jugador->fichas += apuesta;
        stats_map_sum(&jugador->estadisticas, "empatadas", 1);
        historial_agregar(
                    &jugador->historial,
                    apuesta,                // cantidad apostada
                    fichas_antes,           // fichas antes de la partida (debes guardar este valor al inicio)
                    jugador->fichas,        // fichas despues de la partida
                    "Empate");
    } else {
        printf("- %d fichas.\n", apuesta);
        stats_map_sum(&jugador->estadisticas, "perdidas", 1);
        stats_map_set(&jugador->estadisticas, "racha_actual", 0);
        historial_agregar(
                    &jugador->historial,
                    apuesta,                // cantidad apostada
                    fichas_antes,           // fichas antes de la partida (debes guardar este valor al inicio)
                    jugador->fichas,        // fichas despues de la partida
                    "Derrota");
    }

    printf("Ahora tienes %d fichas.\n", jugador->fichas);
    int gano = (resultado == 1) ? 1 : 0;
    printf("\nArbol de decisiones de esta partida:\n");
    mostrarArbol(arbol, gano);

    // Guarda el arbol en el jugador para mostrarlo despues
    if (jugador->arbol_actual)
        destruirArbol(jugador->arbol_actual);
    jugador->arbol_actual = arbol;

    mazo_destruir(mazo);
}