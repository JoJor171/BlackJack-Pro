/*----------------------------------------------------
  include/mazo.h    (Cola)
----------------------------------------------------*/
#ifndef MAZO_H
#define MAZO_H
#include "carta.h"

typedef struct Mazo {
    Carta *cartas;      // Arreglo dinámico de cartas
    int    frente;       // Índice del frente de la cola
    int    final;        // Índice del final de la cola
    int    capacidad;    // Capacidad total del arreglo
    int    restantes;    // Cartas restantes en el mazo
} Mazo;

/* API */
Mazo  *mazo_crear(int n_barajas);
void   mazo_destruir(Mazo *);
void   mazo_barajar(Mazo *);
Carta  mazo_robar(Mazo *);  // Extrae del frente (FIFO)
int    mazo_restantes(const Mazo *);

#endif