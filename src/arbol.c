#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

NodoDecision* crearNodo(const char *decision) {
    NodoDecision *nuevo = (NodoDecision*)malloc(sizeof(NodoDecision));
    if (!nuevo) return NULL;
    strcpy(nuevo->decision, decision);
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

NodoDecision* insertarDecision(NodoDecision *raiz, const char *decision) {
    if (!raiz) {
        return crearNodo(decision);
    } else {
        // Si hay espacio en izq, insertamos a la izquierda
        if (!raiz->izq) {
            raiz->izq = insertarDecision(raiz->izq, decision);
        }
        // Si izquierda está ocupada, insertamos a la derecha
        else {
            raiz->der = insertarDecision(raiz->der, decision);
        }
        return raiz;
    }
}

void mostrarArbol(NodoDecision *raiz) {
    if (!raiz) return;
    mostrarArbol(raiz->izq);
    printf("%s -> ", raiz->decision);
    mostrarArbol(raiz->der);
}

void destruirArbol(NodoDecision *raiz) {
    if (!raiz) return;
    destruirArbol(raiz->izq);
    destruirArbol(raiz->der);
    free(raiz);
}