#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API2024Parte2.h"

int main(void) {
    clock_t inicio, final;
    long span;
    u32 fallo = 0;

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
    printf("Coloreo con orden inicial:\n");
    fallo = Greedy(G, orden);
    finalNatural = clock();
    
    if (fallo != MAX_U32){
        for(u32 i = 0; i < NumeroDeVertices(G); i++){
            // printf("Color del vertice %d: %d\n", i, Color(i, G));
        }
    }
    
    
    span = (finalNatural - inicioNatural) / CLOCKS_PER_SEC;
    printf("Tiempo orden inicial: %lu\n", span);
    

    
    // Orden GulDukat
    clock_t inicioGulDukat, finalGulDukat;
    inicioGulDukat = clock();
    printf("GulDukat por ser llamado \n");
    GulDukat(G, orden);
    printf("Coloreo con orden GulDukat:\n");
    Greedy(G, orden);
    finalGulDukat = clock();
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        // printf("Color del vertice %d: %d\n", i, Color(i, G));
    }
    span = (finalGulDukat - inicioGulDukat) / CLOCKS_PER_SEC;
    printf("Tiempo orden GulDukat: %lu\n", span);

    /*
    // Orden ElimGarak
    clock_t inicioElimGarak, finalElimGarak;
    inicioElimGarak = clock();
    ElimGarak(G, orden);
    printf("Coloreo con orden ElimGarak:\n");
    Greedy(G, orden);
    finalElimGarak = clock();
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        printf("Color del vertice %d: %d\n", i, Color(i, G));
    }
    span = (finalElimGarak - inicioElimGarak) / CLOCKS_PER_SEC;
    printf("Tiempo orden ElimGarak: %lu\n", span);
    */

    final = clock();
    span = (final - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo total del programa: %lu\n", span);
    DestruirGrafo(G);
    return 0;
}