#include <stdlib.h>
#include <stdio.h>
#include "adjlist.h"
#include "APIG24.h"

#include <stdbool.h>

#define MAX_U32 0xFFFFFFFF

static int load_nums(u32 *n, u32 *m)
{
  unsigned int res = 0;
  char buff[100];

  while (res != 2)
  {
    if (fgets(buff, 100, stdin) == NULL)
    {
      return -1;
    }
    res = sscanf(buff, "p edge %u %u", n, m);
  }
  return 0;
}

static adjlist save_data(u32 m) // guardo al arreglo como una lista de listas
{
  u32 v1, v2;
  char buff[100];
  adjlist data = empty_adjlist();

  for (unsigned int line = 0; line < m; ++line)
  {
    if (fgets(buff, 100, stdin) == NULL ||
        sscanf(buff, "e %u %u", &v1, &v2) != 2)
    {
      destroyadjl(data);
      return NULL;
    }

    if (adjlist_index(data, v1) == NULL)
    {
      printf("v1 = %u\n", v1);
      list *v1vecinos = empty_list();
      v1vecinos = addr(v2, v1vecinos);
      list_dump(v1vecinos);
      data = adjaddat(v1vecinos, v1, data);
      adjlist_dump(data);
    }
    /*else
    {
      data = adjaddrtoelem(data, v1, v2);
    }

    if (adjlist_index(data, v2) == NULL)
    {
      list v2vecinos = empty_list();
      v2vecinos = addr(v1, v2vecinos);
    }
    else
    {
      data = adjaddrtoelem(data, v1, v2);
    }*/
  }

  printf("-----------------------------\n");
  return data;
}

static void fill_degs_and_delta(Grafo graph, u32 n)
{
  for (unsigned int i = 0; i < n; ++i)
  {
    graph->degs[i] = length(graph->edges[i]);

    if (graph->degs[i] > graph->delta)
    {
      graph->delta = graph->degs[i];
    }
  }
}
/*
static u32 name_to_index(Grafo graph, u32 name)
{
  color *colors = graph->colors;
  u32 start_index = 0, end_index = graph->num_vertexs - 1;
  u32 middle = 0;

  while (start_index <= end_index)
  {
    middle = (start_index + end_index) / 2;
    if (colors[middle] == name)
      return middle;
    if (colors[middle] < name)
      start_index = middle + 1;
    else
      end_index = middle - 1;
  }
  return MAX_U32;
}

static list names_to_indexs(Grafo graph, list names_list)
{
  u32 list_len = length(names_list);
  list index_list = empty_list();
  u32 index = 0;

  for (unsigned int i = 0; i < list_len; ++i)
  {
    index = name_to_index(graph, list_index(names_list, i));
    index_list = addr(index, index_list);
  }
  return index_list;
}
*/
Grafo ConstruirGrafo()
{ // Parse n,m from file
  u32 n = 0, m = 0;
  int res = load_nums(&n, &m);
  if (res == -1)
  {
    return NULL;
  }

  // Initialize graph struct
  Grafo graph = malloc(sizeof(GrafoSt));
  if (graph == NULL)
  {
    return NULL;
  }
  graph->num_vertexs = n;
  graph->num_edges = m;
  graph->delta = 0;
  graph->colors = calloc(n, sizeof(u32));
  graph->edges = calloc(n, sizeof(list));
  graph->degs = calloc(n, sizeof(u32));

  if ((graph->colors == NULL) | (graph->edges == NULL) | (graph->degs == NULL))
  {
    free(graph);
    return NULL;
  }

  // Parse data from file, save in AVL tree data struct
  adjlist datalist = save_data(m);
  if (datalist == NULL || adjlength(datalist) > n)
  {
    DestruirGrafo(graph);
    return NULL;
  }

  // Fill graph->colors
  // Algoritmo de coloreo no creado
  // Fill graph->edges
  // graph->edges = getArray(datalist); //<- por esta linea puedo hacer un destroy de datalist sin preocuparme por memleaks (?)

  /*for (unsigned int i = 0; i < n; ++i)
  {
    graph->edges[i] = names_to_indexs(graph, graph->edges[i]);
  }*/

  // Compute degree for each vertex, calculate delta
  // fill_degs_and_delta(graph, n);

  // destroyadjl(datalist);

  return graph;
}

void DestruirGrafo(Grafo G)
{
  if (G == NULL)
    return;
  if (G->degs != NULL)
    free(G->degs);
  if (G->colors != NULL)
    free(G->colors);
  if (G->edges != NULL)
  {
    for (unsigned int i = 0; i < G->num_vertexs; ++i)
    {
      destroy(G->edges[i]);
    }
    free(G->edges);
  }
  free(G);
}

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
  return G->colors[i];
}

u32 Grado(u32 i, Grafo G)
{
  return G->degs[i];
}

u32 IndiceVecino(u32 j, u32 i, Grafo G)
{
  u32 res = MAX_U32;
  if (i < G->num_vertexs && j < G->degs[i])
  {
    res = list_index(G->edges[i], j);
  }
  return res;
}
