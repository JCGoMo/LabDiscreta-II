#include "APIG24.h"

#define MAX_U32 0xFFFFFFFF

// ------------------------------------------------------------------ Borrar innecesarias
/*
// Definiciones para la función OrdenNatural
#define ORDEN_NATURAL 0

// Definiciones para la función OrdenWelshPowell
#define ORDEN_WELSH_POWELL 1

// Definiciones para la función OrdenMatula
#define ORDEN_MATULA 2

// Definiciones para la función OrdenPorBloqueDeColores
#define ORDEN_POR_BLOQUE_DE_COLORES 3

// Definiciones para la función Greedy
#define GREEDY 0

// Definiciones para la función GulDukat
#define GUL_DUKAT 1

// Definiciones para la función ElimGarak
#define ELIM_GARAK 2

char Bipartito(Grafo G);

char OrdenNatural(Grafo G,u32* Orden);

char OrdenWelshPowell(Grafo G,u32* Orden);

char OrdenMatula(Grafo G,u32* Orden);

char OrdenPorBloqueDeColores(Grafo G,u32* Orden);
*/


u32 Greedy(Grafo G,u32* Orden);

char GulDukat(Grafo G,u32* Orden);

char ElimGarak(Grafo G,u32* Orden);