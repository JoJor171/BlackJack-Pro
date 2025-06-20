#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"

int main() {
    int opcion;
    srand(time(NULL)); // Inicializa la semilla para números aleatorios

    do {
        mostrarMenu();
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                jugarBlackJack();
                break;
            case 2:
                printf("¡Gracias por jugar!\n");
                break;
            default:
                printf("Opcion no válida. Intenta de nuevo.\n");
        }
    } while(opcion != 2);

    return 0;
}