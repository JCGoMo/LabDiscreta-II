#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef unsigned int u32;

typedef struct
{
    list *edges; // lista de ady
    u32 *ids;       // nombres
    u32 *degs;      // grados
    u32 num_vertexs;
    u32 num_edges;
    u32 delta;
} GrafoSt;
