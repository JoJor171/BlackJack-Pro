/*----------------------------------------------------
  src/utils.c
----------------------------------------------------*/
#include <stdlib.h>
#include <time.h>
#include "utils.h"
int rng_int(int a,int b){
    static int ready=0;
    if(!ready){ srand((unsigned)time(NULL)); ready=1; }
    return a + rand()%(b-a+1);
}
