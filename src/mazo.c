#include <stdio.h>
#include <stdlib.h>
#include "mazo.h"
#include "utils.h"

Mazo *mazo_crear(int n) {
    Mazo *m = malloc(sizeof(Mazo));
    if (!m) return NULL;
    
    m->capacidad = 52 * n;
    m->cartas = malloc(sizeof(Carta) * m->capacidad);
    if (!m->cartas) {
        free(m);
        return NULL;
    }
    
    // Llenar el mazo
    int idx = 0;
    for (int k = 0; k < n; k++) {
        for (int v = 1; v <= 13; v++) {
            for (int p = 0; p < 4; p++) {
                m->cartas[idx++] = (Carta){v, (Palo)p};
            }
        }
    }
    
    m->frente = 0;
    m->final = m->capacidad - 1;
    m->restantes = m->capacidad;
    
    mazo_barajar(m);
    return m;
}

void mazo_destruir(Mazo *m) {
    if (!m) return;
    free(m->cartas);
    free(m);
}

void mazo_barajar(Mazo *m) {
    // Barajar usando Fisher-Yates
    for (int i = m->capacidad - 1; i > 0; i--) {
        int j = rng_int(0, i);
        Carta tmp = m->cartas[i];
        m->cartas[i] = m->cartas[j];
        m->cartas[j] = tmp;
    }
    
    // Resetear índices de la cola
    m->frente = 0;
    m->final = m->capacidad - 1;
    m->restantes = m->capacidad;
}

Carta mazo_robar(Mazo *m) {
    if (m->restantes == 0) {
        mazo_barajar(m);  // Auto-rellenar
    }
    
    Carta robada = m->cartas[m->frente];
    m->frente = (m->frente + 1) % m->capacidad;  // Circular
    m->restantes--;
    return robada;
}

int mazo_restantes(const Mazo *m) { 
    return m->restantes; 
}