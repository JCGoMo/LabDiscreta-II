#ifndef CGRAFO
#define CGRAFO

#include "EstructuraGrafo.h"


// funcion auxiliar para ir al final de una linea
FILE *eol(char, FILE *);

void FreeArrayLados(u32**, u32);

//funcion auxiliar de qsort
int ComSort(const void *, const void *);

//funcion auxiliar de bsearch
int ComSearch(const void *, const void *);

//carga todos los vecinos de un vertice en un arreglo
void CargarVecinos(u32 **, vertice*, u32);

//calcula el grado y el orden natural de los vertices
void CargaGradoNombre(u32**, vertice*, u32);

void CargaDeltaGrafo(GrafoSt*, u32);

u32** Parser(GrafoSt*);

Grafo CargarGrafo();

#endif
