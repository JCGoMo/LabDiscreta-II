#ifndef _ESTRUCTURAGRAFO
#define _ESTRUCTURAGRAFO

#include <stdlib.h>
#include "dimacs.h"

typedef unsigned int u32;

typedef struct vertice_s {
    u32 indice;
    u32 nombre;
    u32 grado;
    // Array de {grado} punteros a los vértices vecinos de este.
    struct vertice_s **vecinos;
} vertice;

typedef struct GrafoSt_s {
    u32 numeroVertices; // N
    u32 numeroDeLados; // M
    u32 delta;
    vertice **vertices; // Array de {numeroVertices} vertice's.
} GrafoSt;

/* Constructores y prototipos de la función de listas de vertice */

void ordenarVertices(vertice **vertices, u32 cantVertices);
void asignarIndice(vertice **vertices, u32 cantVertices);
u32 inicializarVecinosYObtenerDelta(vertice **vertices, u32 cantVertices);
vertice *obtenerVerticePorNombre(vertice **vertices, u32 cantVertices, u32 nombre);
void agregarVecinos(dimacsData *datos, vertice **vertices, u32 cantVertices);

/** Busca el vértice con nombre nombreVertice en el arreglo vertices
 * entre 0 y hasta.
 * @return la posición del vértice en el arreglo si lo encuentra.
 * @return 2^32-1 si no lo encuentra.
 **/
u32 posDeVerticeEnArreglo(vertice** vertices, u32 hasta, u32 nombreVertice);

/* listVertices *construccionLista(); */
/* listVertices *construccionVertices(); */
/* listVertices *agregarVertice(listVertices *l, u32 index, u32 name); */
/* int verticeEnLista(listVertices *l, u32 v); */
/* void dumpVertices(listVertices *l); */
/* listVertices *sumarGradoVertice(listVertices *l, u32 v1); */
/* void destroyListaVertices(listVertices *l); */

/* verticeConVecinos *construccionVerticesVecinos(); */
/* verticeConVecinos *agregarVerticeVecino(verticeConVecinos *l, u32 nameVertice, u32 nameVecino); */
/* void dumpVerticesVecinos(verticeConVecinos *l); */
/* void destroyListaVerticesVecinos(verticeConVecinos *l); */

/* u32 obtenerElGradoMaximo(listVertices *l); */


#endif
