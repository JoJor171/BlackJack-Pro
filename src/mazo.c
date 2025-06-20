/*----------------------------------------------------
  src/mazo.c
----------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "mazo.h"
#include "utils.h"

static void fill_deck(Mazo *m,int n){
    int idx=0;
    for(int k=0;k<n;k++)
        for(int v=1;v<=13;v++)
            for(int p=0;p<4;p++){
                m->cartas[idx++] = (Carta){v,(Palo)p};
            }
    m->tope = m->capacidad = idx;
}

Mazo *mazo_crear(int n){
    Mazo *m = malloc(sizeof *m);
    if(!m) return NULL;
    m->cartas = malloc(sizeof(Carta)*52*n);
    fill_deck(m,n);
    mazo_barajar(m);
    return m;
}

void mazo_destruir(Mazo *m)
{
    if (!m) return;

    free(m->cartas);
    free(m);
}


void mazo_barajar(Mazo *m){
    for(int i=m->capacidad-1;i>0;i--){
        int j = rng_int(0,i);
        Carta tmp=m->cartas[i]; m->cartas[i]=m->cartas[j]; m->cartas[j]=tmp;
    }
    m->tope = m->capacidad;
}

Carta mazo_robar(Mazo *m){
    if(m->tope==0) mazo_barajar(m);          /* reshuffle auto */
    return m->cartas[--m->tope];
}

int mazo_restantes(const Mazo *m){ return m->tope; }
