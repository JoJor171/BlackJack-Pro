#ifndef HISTORIAL_H
#define HISTORIAL_H

typedef struct NodoHistorial {
    int numero_partida;
    int apuesta;
    int fichas_antes;
    int fichas_despues;
    char resultado[16]; 
    struct NodoHistorial *sig;
} NodoHistorial;

typedef struct {
    NodoHistorial *primero;
    int total_partidas;
} Historial;

void historial_init(Historial *h);
void historial_agregar(Historial *h, int apuesta, int fichas_antes, int fichas_despues, const char *resultado);void mostrarHistorial(const Historial *h);
void historial_liberar(Historial *h);

#endif