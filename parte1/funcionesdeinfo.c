#include <stdlib.h>
#include <stdio.h>

#include "APIG23.h"

u32 NumeroDeVertices(Grafo G)
{
    return G->num_vertexs;
}

u32 NumeroDeLados(Grafo G)
{
    return G->num_edges;
}

u32 Delta(Grafo G)
{
    return G->delta;
}

u32 Nombre(u32 i, Grafo G)
{
    return G->ids[i];
}

u32 Grado(u32 i, Grafo G)
{
    return G->degs[i];
}

u32 IndiceVecino(u32 j, u32 i, Grafo G) //probablemente está mal
{
    u32 res = 0xFFFFFFFF;
    if (i < G->num_vertexs && j < G->degs[i])
    {
        res = list_index(list_index(G->edges,i), j);
    }
    return res;
}
