/*----------------------------------------------------
  src/utils.c
----------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "carta.h"


void mostrarCartas(const char *nombre, Carta *mano, int num_cartas) {
    printf("%s: ", nombre);
    for (int i = 0; i < num_cartas; i++) {
        printf("%s%s ", valor_str(mano[i].valor), palo_str(mano[i].palo));
    }
    printf("\n");
}

int valorMano(Carta *mano, int num_cartas) {
    int total = 0, ases = 0;
    for (int i = 0; i < num_cartas; i++) {
        int v = mano[i].valor;
        if (v > 10) v = 10;
        if (v == 1) ases++;
        total += v;
    }
    while (ases > 0 && total <= 11) {
        total += 10;
        ases--;
    }
    return total;
}

int rng_int(int a, int b) {
    return a + rand() % (b - a + 1);
}

void guardarProgreso(Jugador *jugador) {
    FILE *f = fopen("progreso.dat", "wb");
    if (!f) {
        printf("Error al guardar progreso.\n");
        return;
    }
    fwrite(jugador, sizeof(Jugador), 1, f);
    fclose(f);
    printf("Progreso guardado correctamente.!!!\n\n\n");
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

void fichasIniciales(int *fichas) {
    float dinero;
    int cantidad;

    printf("Cuanto dinero quieres introducir en el casino? (minimo 100) :");
    while (scanf("%f", &dinero) != 1 || dinero < 100) {
        printf("Por favor, introduce una cantidad válida: ");
        // Limpiar el buffer de entrada
        while (getchar() != '\n');
    }

    cantidad = (dinero / 100);
    printf("Tienes %d fichas (taza de convercion[$100 = 1 ficha]).\n", cantidad);

    *fichas = cantidad;
}