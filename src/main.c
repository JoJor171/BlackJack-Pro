#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
#include "historial.h"
#include "arbol.h"
#include "utils.h"

int main() {
    int opcion;
    Jugador jugador;
    if (cargarProgreso(&jugador)) {
        printf("Fichas cargadas de sesion anterior = ⛃ %i", jugador.fichas);
    } 
    else {
        printf("Iniciando Blackjack Pro\n");
        fichasIniciales(&jugador.fichas);
        inicializarEstadisticas(&jugador);
        historial_init(&jugador.historial);
    }

    srand(time(NULL)); // Inicializa la semilla para números aleatorios

    do {
        printf("\n===== BLACKJACK CASINO PRO =====\n\n");
        printf("1. Jugar nueva ronda\n");
        printf("2. Ver estadisticas \n");
        printf("3. Ver el ultimo arbol de decisiones\n");
        printf("4. Ver historial de apuestas\n");
        printf("5. Guardar progreso\n");
        printf("6. Salir\n");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                jugarBlackJack(&jugador);
                if (jugador.fichas == 0){
                    opcion = 6;
                    printf("Lo siento, te quedaste sin fichas no podras seguir jugando.");
                };
                break;
            case 2:
                mostrarEstadisticas(&jugador);
                break;
            case 3 :
                if (jugador.arbol_actual)
                    mostrarArbol(jugador.arbol_actual, 0); // Cambia 0 por 1 si quieres mostrar "ganó", o guarda ese valor en Jugador
                else
                    printf("No hay árbol de decisiones para mostrar.\n");
                break;
            case 4 :
                mostrarHistorial(&jugador.historial);
                break;
            case 5:
                guardarProgreso(&jugador);
                break;
            case 6:
                break;
            default:
                printf("Opcion no válida. Intenta de nuevo.\n");
        }
    } while(opcion != 6);

    return 0;
}