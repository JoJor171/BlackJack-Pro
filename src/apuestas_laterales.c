#include "apuestas_laterales.h"

// Pareja perfecta: mismo valor y mismo palo
int esParejaPerfecta(Carta c1, Carta c2) {
    return (c1.valor == c2.valor) && (c1.palo == c2.palo);
}

// 21+3: las dos del jugador y la visible de la banca forman trío, escalera o color
int esVeintiunoMasTres(Carta c1, Carta c2, Carta c3) {
    // Ejemplo simple: trío (los tres valores iguales)
    if (c1.valor == c2.valor && c2.valor == c3.valor)
        return 1;
    // Puedes agregar más lógica para escalera y color aquí
    return 0;
}