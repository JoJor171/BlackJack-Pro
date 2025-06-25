#ifndef ARBOL_H
#define ARBOL_H

typedef struct NodoDecision {
    char decision[32];
    struct NodoDecision *sig;
} NodoDecision;

NodoDecision* crearNodo(const char *decision);
NodoDecision* insertarDecision(NodoDecision *head, const char *decision);
void mostrarArbol(NodoDecision *head , int gano);
void destruirArbol(NodoDecision *head);

#endif