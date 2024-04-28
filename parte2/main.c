#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API2024Parte2.h"

//! ToDo: Definir el ordenamiento para cada caso + Modularizar

typedef struct {
    color coloreo[5];
    int cantidadColores[5];
} ColoreoFinal;

void iteracionColoreos(Grafo G, u32 *orden, color *coloreosOrdenamientos[5], int j) {
    for (int i = 0; i < 100; i = i+2) {
        printf("Iteracion %d\n", i);
        
        orden = GulDukat(G, orden);
        Greedy(G, orden);
        ExtraerColores(G, coloreosOrdenamientos[j][i]);
        printf("Cantidad de colores GulDukat: %u\n", G->delta);

        orden = ElimGarak(G, orden);
        Greedy(G, orden);
        ExtraerColores(G, coloreosOrdenamientos[j][i+1]);
        printf("Cantidad de colores Elim Garak: %u\n", G->delta);
    }
}

int main(void) {

    clock_t inicio, final;
    long span;
    u32 error = 0;
    inicio = clock();
    Grafo G = ConstruirGrafo();
    if(G == NULL){
        return 1;
    }

    ColoreoFinal coloreosFinales;
    color *coloreosOrdenamientos[5];
    for (int i = 0; i < 5; i++) {
        coloreosOrdenamientos[i] = malloc(NumeroDeVertices(G) * sizeof(color));
        if(coloreosOrdenamientos[i] == NULL){
            return 1;
        }
    }
    u32 *orden = malloc(NumeroDeVertices(G) * sizeof(u32));
    if(orden == NULL){
        return 1;
    }

    // Ordenamiento inicial: naturales
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        orden[i] = i;
    }
    error = Greedy(G, orden);
    if (error = MAX_U32) {
        printf("Error en Greedy\n");
        return 1;
    }
    iteracionColoreos(G, orden, coloreosOrdenamientos, 0);
    ExtraerColores(G, coloreosFinales.coloreo[0]);
    coloreosFinales.cantidadColores[0] = G->delta;

    // Ordenamiento inicial: naturales inverso
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        // orden[i] = // ToDo
    }
    error = Greedy(G, orden);
    if (error = MAX_U32) {
        printf("Error en Greedy\n");
        return 1;
    }
    iteracionColoreos(G, orden, coloreosOrdenamientos, 0);
    ExtraerColores(G, coloreosFinales.coloreo[1]);
    coloreosFinales.cantidadColores[1] = G->delta;

    // Ordenamiento inicial: pares decreciente, luego impares creciente
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        // orden[i] = // ToDo
    }
    error = Greedy(G, orden);
    if (error = MAX_U32) {
        printf("Error en Greedy\n");
        return 1;
    }
    iteracionColoreos(G, orden, coloreosOrdenamientos, 0);
    ExtraerColores(G, coloreosFinales.coloreo[2]);
    coloreosFinales.cantidadColores[2] = G->delta;

    // Ordenamiento inicial: grado decreciente
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        // orden[i] = // ToDo
    }
    error = Greedy(G, orden);
    if (error = MAX_U32) {
        printf("Error en Greedy\n");
        return 1;
    }
    iteracionColoreos(G, orden, coloreosOrdenamientos, 0);
    ExtraerColores(G, coloreosFinales.coloreo[3]);
    coloreosFinales.cantidadColores[3] = G->delta;
    
    // Ordenamiento inicial: ??? (a determinar por nosotros)
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        // orden[i] = // ToDo
    }
    error = Greedy(G, orden);
    if (error = MAX_U32) {
        printf("Error en Greedy\n");
        return 1;
    }
    iteracionColoreos(G, orden, coloreosOrdenamientos, 0);
    ExtraerColores(G, coloreosFinales.coloreo[4]);
    coloreosFinales.cantidadColores[4] = G->delta;

    final = clock();
    span = (final - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo total: %lu\n", span);

    // Se libera la memoria
    DestruirGrafo(G);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < NumeroDeVertices(G); j++) {
            free(coloreosOrdenamientos[i][j]);
        }
    }

    return 0;
}