BlackJack Pro - Casino
Descripción
BlackJack Pro es un juego de casino completo que simula la experiencia del blackjack con múltiples funcionalidades avanzadas. El programa permite a los jugadores administrar fichas, realizar apuestas, tomar decisiones estratégicas durante el juego y realizar un seguimiento de su desempeño a través de estadísticas detalladas.

Características Principales
✅ Sistema de apuestas completo con fichas virtuales

✅ Apuestas laterales (Pareja Perfecta y 21+3)

✅ Bonificaciones por jugadas especiales

✅ Estadísticas detalladas del jugador

✅ Historial completo de partidas

✅ Árbol de decisiones que muestra las jugadas

✅ Sistema de guardado de progreso


--Compilación y Ejecución

Requisitos:
Compilador GCC
Sistema: Linux,Windows o macOS


Compilación:
bash
gcc -o BlackJack-Pro \
src/main.c \
src/blackjack.c \
src/mazo.c \
src/carta.c \
src/utils.c \
src/arbol.c \
src/stats.c \
src/apuestas_laterales.c \
src/historial.c \
-Iinclude


Ejecución:
bash
./BlackJack-Pro

Funcionalidades:

Sistema de apuestas principal:



-Apostar fichas

-Doblar apuesta

-Rendirse (Surrender)



Apuestas laterales:

-Pareja Perfecta

-21+3 



Mecánicas de juego:

-Pedir carta (Hit)

-Plantarse (Stand)

-Dividir (Split) - implementación básica



Gestión de jugador:

-Estadísticas detalladas

-Historial de partidas

-Guardar/cargar progreso



Bonificaciones:

-5 cartas sin pasarse

-Blackjack natural

-Tres sietes (777)



Ejemplo de Interacción:

    ===== BLACKJACK CASINO PRO =====

    1. Jugar nueva ronda
    2. Ver estadisticas 
    3. Ver el ultimo arbol de decisiones
    4. Ver historial de apuestas
    5. Guardar progreso
    6. Salir
    > 1

    Tienes 100 fichas.
    Cuantas fichas deseas apostar? > 10

    --- Apuestas Laterales ---
    Pareja Perfecta: Ganas si tus dos primeras cartas son iguales...
    Cuantas fichas apuestas a 'Pareja Perfecta'? > 5

    21+3: Ganas si tus cartas forman trio, escalera o color...
    Cuantas fichas apuestas a '21+3'? > 0

    Tus cartas: A♥ 7♦ 
    Total: 18

    Carta del crupier: J♠ 
    Total: 10

    Elige una opcion:
    1. Pedir carta (Hit)
    2. Plantarse (Stand)
    3. Dividir (Split)
    4. Doblar (Double Down)
    5. Rendirse (Surrender)
    Opcion > 2

    === Turno de la banca ===
    Banca: J♠ 8♦ 
    Total: 18

    === Resultado final ===
    Tus cartas: A♥ 7♦ 
    Total jugador: 18
    Cartas banca: J♠ 8♦ 
    Total banca: 18

    Empate.
    Empate. Recuperas tu apuesta.
    Ahora tienes 95 fichas.

    Secuencia de decisiones: Te plantaste 
    Empate... El crupier muestra una sonrisa discreta.


Estructuras de Datos Utilizadas:


-Cola (FIFO): Para el mazo de cartas

-Lista Enlazada: Para historial de partidas y árbol de decisiones

-Mapa (Tabla Hash): Para estadísticas del jugador

-Arreglos: Para manejar las manos de cartas

Autores:


-José Jorquera

-Rafael Cortes

-Etian Vargas

-Antonio Arancibia
