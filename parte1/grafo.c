#include <stdlib.h>
#include <stdio.h>

#include "APIG24.h"
#include <stdbool.h>

#define MAX_U32 0xFFFFFFFF // 2^32 - 1

// Carga los numeros n y m del archivo
static int load_nums(u32 *n, u32 *m) {
    unsigned int res = 0;
    char buff[1000];
    while (res != 2) {
        if (fgets(buff, 1000, stdin) == NULL) {
            return -1;
        }
        res = sscanf(buff, "p edge %u %u", n, m);
    }
    return 0;
}

// Obtenemos el grado de cada vertice y el delta del grafo
static void fill_degs_and_delta(Grafo graph, u32 n) {
    for (unsigned int i = 0; i < n; ++i) {
        graph->degs[i] = length(graph->edges[i]);

        if (graph->degs[i] > graph->delta) {
            graph->delta = graph->degs[i];
        }
    }
}

// Carga la lista de vecinos de cada vertice
int fill_edges(list *edges, u32 amount_of_edges) {
    u32 v1, v2;
    char buff[1000];
    for (unsigned int line = 0; line<amount_of_edges && (fgets(buff, 1000, stdin) != NULL); ++line) {
        if (sscanf(buff, "e %u %u", &v1, &v2) != 2) {
            return -1;
        }
        edges[v1] = addr(v2, edges[v1]);
        edges[v2] = addr(v1, edges[v2]);
    }
    return 0;
}

Grafo ConstruirGrafo()
{   // Obtenemos n, m del archivo
    u32 n = 0, m = 0;
    int res = load_nums(&n, &m);
    if(res == -1){
        return NULL;
    }
    
    // Inicializamos la estructura del grafo
    Grafo graph = malloc(sizeof(GrafoSt));
    if(graph == NULL){
        return NULL;
    }
    graph->num_vertexs = n;
    graph->num_edges = m;
    graph->delta = 0;
    graph->colors = calloc(n, sizeof(color));
    graph->edges = calloc(n, sizeof(list));
    graph->degs = calloc(n, sizeof(u32));

    if((graph->colors == NULL)
        | (graph->edges == NULL)
        | (graph->degs == NULL)){
        free(graph);
        return NULL;
    }
 
    // Crea la lista de vecinos de cada vertice y 
    for (unsigned int i = 0; i < n; ++i) {
        graph->edges[i] = empty_list();
    }
    
    // Llena la lista de vecinos de cada vertice
    int error = fill_edges(graph->edges, m);
    if (error != 0) {
        DestruirGrafo(graph);
        return NULL;
    }
    
    // Llena los grados de cada vertice y el delta
    fill_degs_and_delta(graph, n);
    if(graph->delta == 0){
        DestruirGrafo(graph);
        return graph;
    }

    return graph;
}

// Dado un grafo, libera la memoria utilizada por el grafo
void DestruirGrafo(Grafo G)
{
    if(G == NULL)
        return;
    if(G->degs != NULL)
        free(G->degs);
    if(G->colors != NULL)
        free(G->colors);
    if(G->edges != NULL){
        for(unsigned int i = 0; i < G->num_vertexs; ++i){
            destroy(G->edges[i]);
        }
        free(G->edges);
    }
    free(G);
    G = NULL;
}

// Dado un grafo, devuelve la cantidad de vertices del grafo
u32 NumeroDeVertices(Grafo G)
{
    return G->num_vertexs;
}

// Dado un grafo, devuelve la cantidad de lados del grafo
u32 NumeroDeLados(Grafo G)
{
    return G->num_edges;
}

// Dado un grafo, devuelve el delta del grafo
u32 Delta(Grafo G)
{
    return G->delta;
}

// Dado un vertice i, devuelve la cantidad de vecinos que tiene
u32 Grado(u32 i, Grafo G)
{
    return G->degs[i];
}

// Dado un grafo, extrae los colores de los vertices y los guarda en un arreglo
void ExtraerColores(Grafo G, color* Color){
    for(unsigned int i = 0; i < G->num_vertexs; ++i){
        Color[i] = G->colors[i];
    }
}

// Dado un arreglo de colores, importa los colores al grafo
void ImportarColores(color* Color, Grafo G) {
    for(unsigned int i = 0; i < G->num_vertexs; ++i){
        G->colors[i] = Color[i];
    }
}

// Pinta el vertice i con el color x
void AsignarColor(color x, u32 i, Grafo G) {
    if (i < G->num_vertexs) {
        G->colors[i] = x;
    }
}

// Dado un vertice i, devuelve el color del vertice
color Color(u32 i, Grafo G) {
    if (i < G->num_vertexs) {
        return G->colors[i];
    } else {
        return MAX_U32; 
    }
}

// Dado un vertice i y un vecino j, devuelve el indice del vecino en la lista de vecinos de i
// El indice del j-esimo vecino de i en la lista de vecinos de i
u32 Vecino(u32 j,u32 i, Grafo G){
    if (i < G->num_vertexs && j < G->degs[i]) {
        return list_index(G->edges[i], j);      // Comenzando desde 0, si no, hacer +1
    }
    else{
        return MAX_U32;
    }
}
