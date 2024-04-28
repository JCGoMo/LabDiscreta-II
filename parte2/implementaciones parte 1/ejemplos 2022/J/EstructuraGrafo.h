#ifndef _ESTGRAFO_H
#define _ESTGRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int u32;

typedef struct VerticeSt *Vertices;
typedef struct VerticeSt Vertice;

typedef struct GrafoSt GrafoSt;
typedef struct GrafoSt *Grafo;

struct VerticeSt {
    u32 nombre;
    u32 color;
    u32 grado;
    u32 *vecinos;
};

struct GrafoSt {
    u32 n;
    u32 m;
    u32 delta;
    Vertices v;
    u32 *orden;
};

#endif
