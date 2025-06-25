#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
#include "estadisticas.h"

int main() {
    int opcion;
    Jugador jugador;
    inicializarEstadisticas(&jugador);
    srand(time(NULL)); // Inicializa la semilla para números aleatorios

    do {
        mostrarMenu();
        printf("Selecciona una opcion: \n");
        printf("1. Jugar\n");
        printf("2. Mostrar estadísticas\n");
        printf("3. Salir\n");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                jugarBlackJack(&jugador);
                break;
            case 2:
                mostrarEstadisticas(&jugador);
                break;
            case 3 :
                printf("¡Gracias por jugar!\n");
                break;
            default:
                printf("Opcion no válida. Intenta de nuevo.\n");
        }
    } while(opcion != 2);

    return 0;
}