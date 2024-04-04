#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "CargaGrafo.h"


Grafo ConstruccionDelGrafo() {
  Grafo G = cargarGrafo();
  return G;
}

void DestruccionDelGrafo(Grafo G) {
  for (u32 i = 0; i < G->num_vertices; i++) {
    free(G->array_vertices[i].vecinos)
  }
  free(G->array_vertices);
  free(G);
}

u32 NumeroDeVertices(Grafo G) {
  return G->num_vertices;
}

u32 NumeroDeLados(Grafo G) {
  return G->num_lados;
}

u32 Delta(Grafo G) {
  return G->delta;
}

u32 Nombre(u32 i,Grafo G) {
  return G->array_vertices[i].nombre;
}

u32 Grado(u32 i,Grafo G) {
  return G->array_vertices[i].grado;
}

u32 IndiceONVecino(u32 j,u32 k,Grafo G) {
  return G->array_vertices[k].vecinos[j];
}
