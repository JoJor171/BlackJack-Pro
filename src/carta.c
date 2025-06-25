/*----------------------------------------------------
  src/carta.c
----------------------------------------------------*/
#include "carta.h"
static const char *pstr[]  = {"Corazon ","Diamante ","Trebol","Pica"};   /* Hearts, Diamonds... */
static const char *vstr[]  = {"?","A","2","3","4","5","6","7",
                              "8","9","10","J","Q","K"};
const char *palo_str(Palo p){ return pstr[p]; }
const char *valor_str(int v){ return vstr[v]; }
