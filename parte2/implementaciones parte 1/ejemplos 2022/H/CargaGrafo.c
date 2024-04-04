#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "EstructuraGrafo.h"
#define FILEPATH "grafo_prueba.txt";

FILE *eol(char ch, FILE *fp)
{
  do
  {
    ch = fgetc(fp);
  } while (ch != '\n');
  return fp;
}

void FreeArrayLados(u32** array_lados, u32 num_lados) {
  for (u32 h = 0; h < 2*num_lados; h++) {
    free(array_lados[h]);
  }
  free(array_lados);
}

int ComSort(const void *a, const void *b) {
  const u32 *aInt = *(const u32 **) a;
  const u32 *bInt = *(const u32 **) b;
  return aInt[0] - bInt[0];
}

int ComSearch(const void *a, const void *b) {
  const u32 aInt = *(const u32 *) a;
  const vertice bInt = *(const vertice *) b;
  return (aInt - bInt.nombre);
}

void CargarVecinos(u32** array_lados, vertice* array_vertices, u32 num_vertices){
  vertice *puntero_aux = NULL;
  int indice_nat;
  int k = 0;
  for (u32 i = 0; i < num_vertices; i++){
    array_vertices[i].vecinos = (u32 *)calloc(array_vertices[i].grado, sizeof(u32));
    for (u32 j = 0; j < array_vertices[i].grado; j++){
      puntero_aux = bsearch(&array_lados[k][1], array_vertices, num_vertices, sizeof(vertice), ComSearch);
      indice_nat = (puntero_aux - array_vertices);
      array_vertices[i].vecinos[j] = indice_nat;
      k++;
    }
  }
}

void CargaGradoNombre(u32** array_lados, vertice* array_vertices, u32 num_lados) {
  array_vertices[0].nombre = array_lados[0][0];
  array_vertices[0].grado = 0;
  for (u32 i = 0, j = 0; i < 2*num_lados; i++) {
    if (array_lados[i][0] == array_vertices[j].nombre) {
      array_vertices[j].grado++;
    } else {
      j++;
      array_vertices[j].nombre = array_lados[i][0];
      array_vertices[j].grado = 1;
    }
  }
}

void CargaDeltaGrafo(GrafoSt* G, u32 num_vertices){
  G->delta = 0;
  for (u32 i = 0; i < num_vertices; i++) {
    if (G->delta < G->array_vertices[i].grado) {
      G->delta = G->array_vertices[i].grado;
    }
  }
}


u32** Parser(GrafoSt *G){
  const char *fname = FILEPATH;
  FILE *fp = fopen(fname, "r");
  if (!fp)
  {
    perror("File opening failed");
    return 0;
  }

  u32 **array_lados = NULL;
  char ch;
  u32 vertice_aux1;
  u32 vertice_aux2;
  int control_sacanf;

  ch = fgetc(fp);
  if (ch == 'c' || ch == 'p')
  {
    while (ch == 'c') // salteamos las lineas de comentarios
    {
      fp = eol(ch, fp);
      ch = fgetc(fp);
    }
    if (ch == 'p')
    {
      // extraemos el numero de lados y de vertices del array_lados
      control_sacanf = fscanf(fp, " edge %u %u", &G->num_vertices, &G->num_lados);
      if (control_sacanf == 0) {
        printf("Error en formato del archivo\n");
        return NULL;
      }
      fp = eol(ch, fp);
      // creamos un arreglo 2xnum_lados
      array_lados = (u32 **)calloc((2 * G->num_lados), sizeof(u32*));

      for (u32 i = 0; i < (2 * G->num_lados); i++){
        array_lados[i] = calloc(2, sizeof(u32));
      }
      // cargamos los lados del array_lados en una arreglo temporal
      for (u32 i = 0; i < 2 * G->num_lados; i = i+2){
        control_sacanf = fscanf(fp, "%c %d %d", &ch, &vertice_aux1, &vertice_aux2);
        if (control_sacanf == 0) {
          printf("Error al leer archivo\n");
          return NULL;
        }
        if (ch == 'e') {
          array_lados[i][0] = vertice_aux1;
          array_lados[i][1] = vertice_aux2;
          array_lados[i+1][0] = vertice_aux2;
          array_lados[i+1][1] = vertice_aux1;
          fp = eol(ch, fp);
        }
        else{
          FreeArrayLados(array_lados, G->num_lados);
          printf("Error en el formato del archivo, declaracion de lados insuficiente\n");
          return NULL;
        }
      }
      qsort(array_lados, 2 * G->num_lados, sizeof(array_lados[0]), ComSort);
    }
  }
  fclose(fp);
  return array_lados;
}


GrafoSt* CargarGrafo(){
  GrafoSt* G = calloc(1,sizeof(GrafoSt));
  u32** array_lados = NULL;

  array_lados = Parser(G);

  if (array_lados == NULL) {
    printf("%s\n", "NULL");
    free(G);
    return NULL;
  }
  G->array_vertices = calloc(G->num_vertices, sizeof(vertice));

  CargaGradoNombre(array_lados, G->array_vertices, G->num_lados);

  CargarVecinos(array_lados, G->array_vertices, G->num_vertices);

  FreeArrayLados(array_lados, G->num_lados);

  CargaDeltaGrafo(G, G->num_vertices);

  return G;
}