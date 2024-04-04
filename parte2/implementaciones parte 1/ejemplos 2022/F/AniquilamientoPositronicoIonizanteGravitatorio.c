#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "avl.h"
#include "get_line.h"


typedef struct GrafoSt {
  u32 n;                  //número de nodos.
  u32 m;                  //número de aristas.
  u32 delta;              //Mayor Grado.
  u32 *orden;             // Orden en el que van ingresando los vertices.
  u32 *orden_real;        // Orden real para OrdenNatural.
  u32 *nombre_real;       // En la posicion i, esta el nombre real del vertice i.
  vector *vecinos;        // vecinos[i] vector con vecinos del nodo i
} GrafoSt;


bool checkspace(Grafo G) {
  return G->vecinos && G->orden && G->orden_real  && G->nombre_real;
}

Grafo ConstruccionDelGrafo() {
  Grafo G = (Grafo)malloc(sizeof(GrafoSt));
  G->n = 0;
  G->m = 0;
  G->delta = 0;
  
  
  char* line = NULL;
  line = get_line();
  while(line[0] == 'c'){
    free(line);
    line = get_line(); 
  }


  if (!checkline(line, true)) {
    DestruccionDelGrafo(G);
    printf("error en primera linea sin comentario\n");
    return NULL;
  }

  
  get_numbers(line, 7, &(G->n), &(G->m));
  free(line);

  
  G->vecinos = calloc(G->n,sizeof(vector));
  G->orden = calloc(G->n,sizeof(u32));
  G->orden_real = calloc(G->n,sizeof(u32));
  G->nombre_real = calloc(G->n,sizeof(u32));
  

  if(!checkspace(G)){
    DestruccionDelGrafo(G);
    return NULL;
  }

  
  for(u32 i = 0; i < (G->n); i++) {
    G->vecinos[i] = vector_init();
  }

  avlnode* avl = avl_init();
     
  u32 cantidad_de_nodos = 0;

  
  vector nodos = vector_init();
  if(!nodos){
    DestruccionDelGrafo(G);
    return NULL;
  }

  
  u32 lines = 0;
  for(u32 i = 0; i < G->m; i++) {
    u32 v, u;
    line = get_line();

   
    if (checkline(line, false)) {
      get_numbers(line, 2, &u, &v);
      if (!exists_in_avl(avl, u)) {
        avl = avl_insert(avl, u, cantidad_de_nodos);
        if(!vector_add(nodos, u)){
          DestruccionDelGrafo(G);
          return NULL;
        }
        G->nombre_real[cantidad_de_nodos] = u;
        cantidad_de_nodos++;
      }

      if (!exists_in_avl(avl, v)) {
        avl = avl_insert(avl, v, cantidad_de_nodos);
        if(!vector_add(nodos, v)){
          avl_destroy(avl);
          DestruccionDelGrafo(G);
          return NULL;
        }
        G->nombre_real[cantidad_de_nodos] = v;
        cantidad_de_nodos++;
      }
      
      if (cantidad_de_nodos > G->n) {
        printf("cantidad de vertices leidos no es la declarada\n");
        DestruccionDelGrafo(G);
        vector_free(nodos);
        avl_destroy(avl);
        free(line);
        return NULL;
      }
      
      if(!vector_add(G->vecinos[find_avl_value(avl, v)], find_avl_value(avl, u))){
        avl_destroy(avl);
        DestruccionDelGrafo(G);
        return NULL;
      }
      
      if(!vector_add(G->vecinos[find_avl_value(avl, u)], find_avl_value(avl, v))){
        avl_destroy(avl);
        DestruccionDelGrafo(G);
        return NULL;
      }
      lines++;
    } else {
      printf("error de lectura en lado %u\n", lines+1);
      DestruccionDelGrafo(G);
      vector_free(nodos);
      avl_destroy(avl);
      free(line);
      return NULL;
    }
    free(line);
  }


  line = get_line();
  if (line[0]) {
    printf("error de lectura en lado %u\n", G->m+1);
    DestruccionDelGrafo(G);
    vector_free(nodos);
    avl_destroy(avl);
    free(line);
    return NULL;
  }

  
  if (cantidad_de_nodos != G->n) {
    printf("cantidad de vertices leidos no es la declarada\n");
    DestruccionDelGrafo(G);
    vector_free(nodos);
    avl_destroy(avl);
    free(line);
    return NULL;
  }

  
  vector_sort(nodos);
  for(u32 i = 0; i < G->n; i++) {
    G->orden_real[i] = find_avl_value(avl, vector_get(nodos, i));
  }

  
  vector_free(nodos);
  avl_destroy(avl);
  OrdenNatural(G);
  free(line);
  for(u32 i = 0; i < G->n;i++){
    u32 d = Grado(i, G);
    if(G->delta < d)
      G->delta = d;
  }

  return G;
}



void DestruccionDelGrafo(Grafo G) {
  if(!G)
    return;
  if(G->vecinos){
    for(u32 i = 0; i < G->n; i++) {
      vector_free(G->vecinos[i]);
    }
    free(G->vecinos);
  }
  if (G->orden_real) free(G->orden_real);
  if (G->nombre_real) free(G->nombre_real);
  if (G->orden) free(G->orden);
  free(G);
}

u32 NumeroDeVertices(Grafo G) {
  return G->n;
}

u32 NumeroDeLados(Grafo G) {
  return G->m;
}

u32 Delta(Grafo G){
	return G->delta;
}

u32 Nombre(u32 i, Grafo G) {
  return G->nombre_real[G->orden[i]];
}


u32 Grado(u32 i, Grafo G) {
  if (i >= G->n) return ~0u;
  return vector_size(G->vecinos[G->orden[i]]);
}

u32 NombreJotaesimoVecino(Grafo G, u32 i, u32 j) {
  return vector_get(G->vecinos[G->orden[i]], j);
}


char OrdenNatural(Grafo G) {
  for(u32 i = 0; i < G->n; i++) {
    G->orden[i] = G->orden_real[i];
  }
  return '0';
}
