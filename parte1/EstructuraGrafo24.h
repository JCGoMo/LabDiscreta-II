#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef unsigned int u32;
typedef u32 color;

typedef struct
{
    u32 num_vertexs;
    u32 num_edges;
    u32 *degs;      // grados de todos los vertices
    color *colors;  // colores de todos los vertices
    u32 delta;
    list *edges; // lista de adyacencia (vecinos)
} GrafoSt;
