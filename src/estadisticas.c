#include <stdio.h>
#include "estadisticas.h"

void inicializarEstadisticas(Jugador *jugador) {
    jugador->fichas = 300;
    jugador->partidas_jugadas = 0;
    jugador->ganadas = 0;
    jugador->perdidas = 0;
    jugador->empatadas = 0;
    jugador->racha_actual = 0;
    jugador->racha_maxima = 0;
    jugador->split_usado = 0;
    jugador->double_usado = 0;
    jugador->surrender_usado = 0;
    jugador->sidebets_ganadas = 0;
}

void mostrarEstadisticas(Jugador *jugador) {
    printf("\n=== Estadísticas del Jugador ===\n");
    printf("Fichas actuales: %d\n", jugador->fichas);
    printf("Partidas jugadas: %d\n", jugador->partidas_jugadas);
    printf("Ganadas: %d\n", jugador->ganadas);
    printf("Perdidas: %d\n", jugador->perdidas);
    printf("Empatadas: %d\n", jugador->empatadas);
    printf("Racha actual de victorias: %d\n", jugador->racha_actual);
    printf("Racha máxima de victorias: %d\n", jugador->racha_maxima);
    printf("Veces que usó Split: %d\n", jugador->split_usado);
    printf("Veces que usó Double Down: %d\n", jugador->double_usado);
    printf("Veces que se rindió (Surrender): %d\n", jugador->surrender_usado);
    printf("Apuestas laterales ganadas: %d\n", jugador->sidebets_ganadas);
    printf("================================\n\n");
}

void guardarProgreso(Jugador *jugador) {
    FILE *f = fopen("progreso.dat", "wb");
    if (!f) {
        printf("Error al guardar progreso.\n");
        return;
    }
    fwrite(jugador, sizeof(Jugador), 1, f);
    fclose(f);
    printf("Progreso guardado correctamente.\n");
}

int cargarProgreso(Jugador *jugador) {
    FILE *f = fopen("progreso.dat", "rb");
    if (!f) {
        // No existe progreso previo
        return 0;
    }
    fread(jugador, sizeof(Jugador), 1, f);
    fclose(f);
    return 1;
}