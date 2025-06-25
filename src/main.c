#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
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
    }

    srand(time(NULL)); // Inicializa la semilla para números aleatorios

    do {
        printf("\n===== BLACKJACK CASINO PRO =====\n\n");
        printf("1. Jugar nueva ronda\n");
        printf("2. Ver estadisticas y logros\n");
        printf("3. Ver arbol de decisiones\n");
        printf("4. Ver historial de apuestas\n");
        printf("5. Guardar progreso\n");
        printf("6. Salir\n");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                jugarBlackJack(&jugador);
                break;
            case 2:
                mostrarEstadisticas(&jugador);
                break;
            case 3 :
                //mostrarArbol();
                break;
            case 4 :
                //mostrarHistorial;
                break;
            case 5:
                guardarProgreso(&jugador);
                printf("Proceso Guardado Exitosamente!!");
                break;
            case 6:
                break;
            default:
                printf("Opcion no válida. Intenta de nuevo.\n");
        }
    } while(opcion != 6);

    return 0;
}