#include <stdlib.h>
#include <stdio.h>

#include "APIG23.h"
#include "balanced_tree.h"
#include <stdbool.h> 

#define MAX_U32 0xFFFFFFFF

static int load_nums(u32 *n, u32 *m) {
  unsigned int res = 0;
  char buff[100];

  while (res != 2) {
    if (fgets(buff, 100, stdin) == NULL) {
      return -1;
    }
    res = sscanf(buff, "p edge %u %u", n, m);
  }
  return 0;
}

static balanced_tree save_in_tree(u32 m) {
  u32 v1, v2;
  char buff[100];
  balanced_tree tree = NULL;

  for (unsigned int line = 0; line < m; ++line) {
    if (fgets(buff, 100, stdin) == NULL ||
        sscanf(buff, "e %u %u", &v1, &v2) != 2) {
      destroy_tree(tree);
      return NULL;
    }
    tree = insert(tree, v1, v2);
    tree = insert(tree, v2, v1);
  }
  return tree;
}

static void fill_degs_and_delta(Grafo graph, u32 n) {
  for (unsigned int i = 0; i < n; ++i) {
    graph->degs[i] = length(graph->edges[i]);

    if (graph->degs[i] > graph->delta) {
      graph->delta = graph->degs[i];
    }
  }
}

static u32 name_to_index(Grafo graph, u32 name) {
  u32 *ids = graph->ids;
  u32 start_index = 0, end_index = graph->num_vertexs - 1;
  u32 middle = 0;

  while (start_index <= end_index) {
    middle = (start_index + end_index) / 2;
    if (ids[middle] == name)
      return middle;
    if (ids[middle] < name)
      start_index = middle + 1;
    else
      end_index = middle - 1;
  }
  return MAX_U32;
}

static list names_to_indexs(Grafo graph, list names_list) {
  u32 list_len = length(names_list);
  list index_list = empty_list();
  u32 index = 0;

  for (unsigned int i = 0; i < list_len; ++i) {
    index = name_to_index(graph, list_index(names_list, i));
    index_list = addr(index, index_list);
  }
  return index_list;
}

Grafo ConstruirGrafo()
{   // Parse n,m from file
    u32 n = 0, m = 0;
    int res = load_nums(&n, &m);
    if(res == -1){
        return NULL;
    }
    
    // Initialize graph struct
    Grafo graph = malloc(sizeof(GrafoSt));
    if(graph == NULL){
      return NULL;
    }
    graph->num_vertexs = n;
    graph->num_edges = m;
    graph->delta = 0;
    graph->ids = calloc(n, sizeof(u32));
    graph->edges = calloc(n, sizeof(list));
    graph->degs = calloc(n, sizeof(u32));

    if((graph->ids == NULL)
        | (graph->edges == NULL)
        | (graph->degs == NULL)){
      free(graph);
      return NULL;
    }

    // Parse data from file, save in AVL tree data struct
    balanced_tree tree = save_in_tree(m);
    if(tree == NULL || num_of_nodes(tree) > n){
        DestruirGrafo(graph);
        return NULL;
    }
    
    // Fill graph->ids
    keys_to_array_inorder(tree, graph->ids);
    // Fill graph->edges
    data_to_array_inorder(tree, graph->edges); 
    
    for(unsigned int i = 0; i < n; ++i){
        graph->edges[i] = names_to_indexs(graph, graph->edges[i]);
    }
    
    // Compute degree for each vertex, calculate delta
    fill_degs_and_delta(graph, n);
    
    tree = destroy_tree(tree);

    return graph;
}


void DestruirGrafo(Grafo G)
{
    if(G == NULL)
        return;
    if(G->degs != NULL)
        free(G->degs);
    if(G->ids != NULL)
        free(G->ids);
    if(G->edges != NULL){
        for(unsigned int i = 0; i < G->num_vertexs; ++i){
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
    return G->ids[i];
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