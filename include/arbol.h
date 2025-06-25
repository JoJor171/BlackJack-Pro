#ifndef ARBOL_H
#define ARBOL_H

typedef struct NodoDecision {
    char decision[32];
    struct NodoDecision *izq;
    struct NodoDecision *der;
} NodoDecision;

// Crear nodo nuevo
NodoDecision* crearNodo(const char *decision);

// Insertar en el árbol (simple: insertamos siempre a la izquierda primero)
NodoDecision* insertarDecision(NodoDecision *raiz, const char *decision);

// Mostrar árbol en orden
void mostrarArbol(NodoDecision *raiz);

// Liberar memoria del árbol
void destruirArbol(NodoDecision *raiz);

#endif