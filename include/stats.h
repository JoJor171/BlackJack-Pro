#ifndef STATS_H
#define STATS_H

#define TAM_MAPA 23

typedef struct statsNode {
    char clave[32];
    int valor;
    struct statsNode *sig;
} statsNode;

typedef struct {
    statsNode *tabla[TAM_MAPA];
} statsMap;

void stats_map_init(statsMap *mapa);

void stats_map_set(statsMap *mapa, const char *clave, int valor);

int  stats_map_get(statsMap *mapa, const char *clave);

void stats_map_sum(statsMap *mapa, const char *clave, int delta);

void stats_map_free(statsMap *mapa);

void stats_map_print(const statsMap *mapa);

#endif