#include <stdio.h>
#include <stdlib.h>
#include "APIG23.h"
#include <time.h>

void printGrafo(Grafo G)
{
    for (unsigned int i = 0; i < G->num_vertexs; ++i)
    {
        printf("[%u:%u] -> ", i, G->ids[i]);
        list_dump(G->edges[i]);
        printf("\n");
    }
}

int main(void)
{
    // printf("expected: 1999999 vertices y 10123123 lados\n"); <- si es R1999999_10123123_1

    clock_t inicio, final;

    long span;
    inicio = clock(); // Tiempo de cpu usado por proceso

    Grafo G = ConstruirGrafo();

    final = clock();

    if (G != NULL)
    {
        // printGrafo(G);
        printf("se obtuvo: %u vertices y %u lados\n", NumeroDeVertices(G), NumeroDeLados(G));
    }

    span = (final - inicio) / CLOCKS_PER_SEC;

    printf("Tardaste %lu seg en cargar el grafo\n", span);

    printf(span <= 30 ? "tiempo aceptable\n" : "fracaso, tardo banda\n");

    DestruirGrafo(G);

    return 0;
}