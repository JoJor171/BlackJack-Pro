#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
#include "estadisticas.h"

int main() {
    int opcion;
    Jugador jugador;
    if (cargarProgreso(&jugador)) {
        printf("¡Progreso cargado! Tienes %d fichas.\n", jugador.fichas);
    } else {
        printf("No se encontro progreso anterior. Iniciando con 300 fichas.\n");
        inicializarEstadisticas(&jugador);
    }

    srand(time(NULL)); // Inicializa la semilla para números aleatorios

    do {
        printf("\nSelecciona una opcion: \n");
        printf("1. Jugar\n");
        printf("2. Mostrar estadisticas\n");
        printf("3. Guardar progreso\n");
        printf("4. Salir\n");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                jugarBlackJack(&jugador);
                break;
            case 2:
                mostrarEstadisticas(&jugador);
                break;
            case 3 :
                guardarProgreso(&jugador);
                break;
            case 4 :
                printf("¡Gracias por jugar!\n");
                break;
            default:
                printf("Opcion no válida. Intenta de nuevo.\n");
        }
    } while(opcion != 4);

    return 0;
}