#ifndef GRAFO
#define GRAFO

#include <stdint.h>

typedef uint32_t u32;

typedef struct {
    // nombre del vertice
    u32 nombre;
    // grado del vertice
    u32 grado;
    // arreglo de vecinos del vertice
    u32 *vecinos;
} vertice;

typedef struct {
    // numero de vertices
    u32 num_vertices;
    // numero de lados
    u32 num_lados;
    //arreglo de vertices
    vertice *array_vertices;
    // vertice con mayor grado
    u32 delta;

} GrafoSt;

#endif
