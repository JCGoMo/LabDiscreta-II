#ifndef APIG24_H
#define APIG24_H

#include <stdio.h>
#include <stdlib.h>
#include "EstructuraGrafo24.h" // Debe tener definida GrafoSt, u32 y color.

// Grafo es un puntero a una estructura GrafoSt, la cual debe estar definida en el .h de arriba
typedef GrafoSt *Grafo;

// Construccion/destruccion (debe leer desde stdin)
Grafo ConstruirGrafo();
void DestruirGrafo(Grafo G);

// Funciones para extraer datos del grafo. u32 debe estar definida en el .h de arriba
u32 NumeroDeVertices(Grafo G);
u32 NumeroDeLados(Grafo G);
u32 Delta(Grafo G);

// Funciones de extraccion de informacion de vertices
u32 Grado(u32 i, Grafo G);
color Color(u32 i, Grafo G);
u32 Vecino(u32 j, u32 i, Grafo G);

// Funciones con colores
void AsignarColor(color x, u32 i, Grafo G);
void ExtraerColores(Grafo G, color *Color);
void ImportarColores(color *Color, Grafo G);

#endif
