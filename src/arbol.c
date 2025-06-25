#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

NodoDecision* crearNodo(const char *decision) {
    NodoDecision *nuevo = (NodoDecision*)malloc(sizeof(NodoDecision));
    if (!nuevo) return NULL;
    strncpy(nuevo->decision, decision, 31);
    nuevo->decision[31] = '\0';
    nuevo->sig = NULL;
    return nuevo;
}

NodoDecision* insertarDecision(NodoDecision *head, const char *decision) {
    NodoDecision *nuevo = crearNodo(decision);
    if (!nuevo) return head;
    if (!head) return nuevo;
    NodoDecision *tmp = head;
    while (tmp->sig) tmp = tmp->sig;
    tmp->sig = nuevo;
    return head;
}

void mostrarArbol(NodoDecision *head, int gano) {
    NodoDecision *tmp = head;
    printf("\nSecuencia de decisiones: ");
    while (tmp) {
        printf("%s", tmp->decision);
        // Comentarios graciosos del crupier
        if (strcmp(tmp->decision, "Pedir") == 0)
            printf(" (¡Otra carta, valiente!)");
        else if (strcmp(tmp->decision, "Plantarse") == 0)
            printf(" (¿Te asustaste?)");
        else if (strcmp(tmp->decision, "Doblar") == 0)
            printf(" (¡Apostando fuerte, eh!)");
        else if (strcmp(tmp->decision, "Dividir") == 0)
            printf(" (¡Doble o nada!)");
        if (tmp->sig)
            printf(" -> ");
        tmp = tmp->sig;
    }
    printf("\n");
    if (gano)
        printf("¡Felicidades, ganaste esta ronda! El crupier te aplaude (por dentro).\n");
    else
        printf("Perdiste... El crupier intenta no sonreír demasiado.\n");
}

void destruirArbol(NodoDecision *head) {
    NodoDecision *tmp;
    while (head) {
        tmp = head;
        head = head->sig;
        free(tmp);
    }
}