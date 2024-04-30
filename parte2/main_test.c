#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API2024Parte2.h"

void printGrafo(Grafo G)
{
    // for (unsigned int i = 0; i < G->num_vertexs; ++i)
    // {
    //     printf("Vertice %u -> Cantidad de vecinos: ", i);
    //     printf("%u \n Lista de vecinos:", length(G->edges[i]));
    //     list_dump(G->edges[i]);
    //     printf("\n");
    //     printf("Color vertice %u = %u ", i, G->colors[i]);
    //     printf("\n");
    //     
    // }
    // printf("Delta: %u \n",G->delta);

    for(u32 i = 0; i < 10; i++){
        printf(" (V %u : C%u) ", i, Color(i,G));
    }
    printf("\n");
}

void resetearColoreo(Grafo G){
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        AsignarColor(0, i, G);
        //printf(" (V %u : C%u) \n", i, Color(i,G));
    }
}

int main(void) {
    clock_t inicio, final;
    long span;

    inicio = clock();
    Grafo G = ConstruirGrafo();
    if(G == NULL){
        return 1;
    }
    u32 *orden = malloc(NumeroDeVertices(G) * sizeof(u32));
    if(orden == NULL){
        return 1;
    }

    // Orden naturales
    clock_t inicioNatural, finalNatural;
    inicioNatural = clock();
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        orden[i] = i;
    }
    // printf("Coloreo con orden inicial:\n");
    // printf("Orden: [ ");
    // for(u32 i = 0; i < NumeroDeVertices(G); i++){
    //     printf(" %u: ", orden[i]);
    // }
    // printf("]\n");
    if (Greedy(G, orden) == MAX_U32){
        printf("Error en Greedy orden natural\n");
        return 1;
    }
    else {  // Borrar al entregar
        printGrafo(G);
    }
    finalNatural = clock();
    
    span = (finalNatural - inicioNatural) / CLOCKS_PER_SEC;
    printf("Tiempo orden inicial: %lu\n", span);
    
    // Orden GulDukat
    clock_t inicioGulDukat, finalGulDukat;
    inicioGulDukat = clock();
    printf("GULDUKAT\n");
    if (GulDukat(G, orden) == '1') {
        printf("Error en GulDukat\n");
        return 1;
    }
    // printf("Orden Gul: ");
    // for(u32 i = 0; i < NumeroDeVertices(G); i++){
    //     printf(" %u: ", orden[i]);
    // }
    // printf("\n");
    printf("Coloreo con orden GulDukat:\n");
    resetearColoreo(G);
    if (Greedy(G, orden) != MAX_U32){
        printGrafo(G);
    }
    finalGulDukat = clock();
    span = (finalGulDukat - inicioGulDukat) / CLOCKS_PER_SEC;
    printf("Tiempo orden GulDukat: %lu\n", span);

    // Orden ElimGarak
    clock_t inicioElimGarak, finalElimGarak;
    inicioElimGarak = clock();
    if (ElimGarak(G, orden) == '1') {
        printf("Error en ElimGarak\n");
        return 1;
    }
    printf("Orden Elim: ");
    for(u32 i = 0; i < 30; i++){
        printf(" %u, ", orden[i]);
    }
    printf("\n");
    printf("Coloreo con orden ElimGarak:\n");
    resetearColoreo(G);
    if (Greedy(G, orden) == MAX_U32){
        printf("Error en Greedy orden natural\n");
        return 1;
    }
    else {  // Borrar al entregar
        printGrafo(G);
    }
    finalElimGarak = clock();
    span = (finalElimGarak - inicioElimGarak) / CLOCKS_PER_SEC;
    printf("Tiempo orden ElimGarak: %lu\n", span);

    final = clock();
    span = (final - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo total del programa: %lu\n", span);
    DestruirGrafo(G);
    return 0;
}