#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historial.h"

void historial_init(Historial *h) {
    h->primero = NULL;
    h->total_partidas = 0;
}

void historial_agregar(Historial *h, int apuesta, int fichas_antes, int fichas_despues, const char *resultado) {
    NodoHistorial *nuevo = malloc(sizeof(NodoHistorial));
    if (!nuevo) return;
    nuevo->numero_partida = ++h->total_partidas;
    nuevo->apuesta = apuesta;
    nuevo->fichas_antes = fichas_antes;
    nuevo->fichas_despues = fichas_despues;
    strncpy(nuevo->resultado, resultado, 15);
    nuevo->resultado[15] = '\0';
    nuevo->sig = h->primero;
    h->primero = nuevo;
}

void mostrarHistorial(const Historial *h) {
    printf("\n=== Historial de Apuestas ===\n");
    NodoHistorial *n = h->primero;
    if (!n) {
        printf("No hay partidas registradas.\n");
        return;
    }
    while (n) {
        printf("Partida %d | Apuesta: %d | Fichas antes: %d | Fichas despues: %d | Resultado: %s\n",
            n->numero_partida, n->apuesta, n->fichas_antes, n->fichas_despues, n->resultado);
        n = n->sig;
    }
}

void historial_liberar(Historial *h) {
    NodoHistorial *n = h->primero;
    while (n) {
        NodoHistorial *tmp = n;
        n = n->sig;
        free(tmp);
    }
    h->primero = NULL;
}