/*----------------------------------------------------
  src/stats.c
----------------------------------------------------*/
#include "blackjack.h"

#include "stats.h"
#include "blackjack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"

static unsigned hash(const char *str) {
    unsigned h = 0;
    while (*str) h = 31 * h + (unsigned char)(*str++);
    return h % TAM_MAPA;
}

void stats_map_init(statsMap *mapa) {
    for (int i = 0; i < TAM_MAPA; ++i)
        mapa->tabla[i] = NULL;
}

void stats_map_set(statsMap *mapa, const char *clave, int valor) {
    unsigned idx = hash(clave);
    statsNode *n = mapa->tabla[idx];
    while (n) {
        if (strcmp(n->clave, clave) == 0) {
            n->valor = valor;
            return;
        }
        n = n->sig;
    }
    n = malloc(sizeof(statsNode));
    strcpy(n->clave, clave);
    n->valor = valor;
    n->sig = mapa->tabla[idx];
    mapa->tabla[idx] = n;
}

int stats_map_get(statsMap *mapa, const char *clave) {
    unsigned idx = hash(clave);
    statsNode *n = mapa->tabla[idx];
    while (n) {
        if (strcmp(n->clave, clave) == 0)
            return n->valor;
        n = n->sig;
    }
    return 0; // Valor por defecto si no existe
}

void stats_map_sum(statsMap *mapa, const char *clave, int delta) {
    unsigned idx = hash(clave);
    statsNode *n = mapa->tabla[idx];
    while (n) {
        if (strcmp(n->clave, clave) == 0) {
            n->valor += delta;
            return;
        }
        n = n->sig;
    }
    // Si no existe, lo crea con valor delta
    stats_map_set(mapa, clave, delta);
}

void stats_map_free(statsMap *mapa) {
    for (int i = 0; i < TAM_MAPA; ++i) {
        statsNode *n = mapa->tabla[i];
        while (n) {
            statsNode *tmp = n;
            n = n->sig;
            free(tmp);
        }
        mapa->tabla[i] = NULL;
    }
}

void stats_map_print(const statsMap *mapa) {
    printf("=== Estadísticas ===\n");
    for (int i = 0; i < TAM_MAPA; ++i) {
        statsNode *n = mapa->tabla[i];
        while (n) {
            printf("%s: %d\n", n->clave, n->valor);
            n = n->sig;
        }
    }
}