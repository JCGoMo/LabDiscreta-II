#ifndef __STRUCTGRAFO
#define __STRUCTGRAFO

#define MAXSIZE 0xFFFF // 1<<32 - 1 
#define MAXLINESIZE 1<<10

#include "dynamic_array.h"

struct GrafoSt {
    u32 numVertices;
    u32 numLados;
    array vertices;
    u32 delta;
};

struct Vertice{
    u32 grado;
    array vecinos;
    u32 nombre;
    u32 indice; 
};

typedef struct Vertice *vertex;


#endif