#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API2024Parte2.h"

//! ToDo: Definir el ordenamiento para cada caso

typedef struct {
    color coloreo[5];
    u32 cantidadColores[5];
} ColoreoFinal;

void resetearColoreo(Grafo G){
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        AsignarColor(0, i, G);
    }
}

void iteracionColoreos(Grafo G, u32 *orden, color *coloreosOrdenamientos[5], int j, ColoreoFinal coloreosFinales) {
    for (int i = 0; i < 100; i = i+2) {
        if (GulDukat(G, orden) == '1') {
            printf("Error en GulDukat\n");
            return 1;
        }
        resetearColoreo(G);
        if (Greedy(G, orden) == MAX_U32){
            printf("Error en Greedy orden natural\n");
            return 1;
        }
        ExtraerColores(G, coloreosOrdenamientos[j][i]);
        printf("Cantidad de colores GulDukat: %u\n", Delta(G));

        if (ElimGarak(G, orden) == '1') {
            printf("Error en ElimGarak\n");
            return 1;
        }
        resetearColoreo(G);
        if (Greedy(G, orden) == MAX_U32){
            printf("Error en Greedy orden natural\n");
            return 1;
        }
        ExtraerColores(G, coloreosOrdenamientos[j][i+1]);
        printf("Cantidad de colores Elim Garak: %u\n", Delta(G));
    }
    ExtraerColores(G, coloreosFinales.coloreo[j]);
    coloreosFinales.cantidadColores[j] = Delta(G);
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
    if (Greedy(G, orden) == MAX_U32){
        printf("Error en Greedy orden natural\n");
        return 1;
    }
    iteracionColoreos(G, orden, coloreosOrdenamientos, 0, coloreosFinales);

    // Ordenamiento inicial: naturales inverso
    for (u32 i = NumeroDeVertices(G); i > 0; i--) {         // REVISAR
        // orden[i] = // ToDo
    }
    if (Greedy(G, orden) == MAX_U32){
        printf("Error en Greedy orden natural\n");
        return 1;
    }
    iteracionColoreos(G, orden, coloreosOrdenamientos, 1, coloreosFinales);

    // Ordenamiento inicial: pares decreciente, luego impares creciente
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        // orden[i] = // ToDo
    }
    if (Greedy(G, orden) == MAX_U32){
        printf("Error en Greedy orden natural\n");
        return 1;
    }
    iteracionColoreos(G, orden, coloreosOrdenamientos, 2, coloreosFinales);

    // Ordenamiento inicial: grado decreciente
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        // orden[i] = // ToDo
    }
    if (Greedy(G, orden) == MAX_U32){
        printf("Error en Greedy orden natural\n");
        return 1;
    }
    iteracionColoreos(G, orden, coloreosOrdenamientos, 3, coloreosFinales);
    
    // Ordenamiento inicial: ??? (a determinar por nosotros)
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        // orden[i] = // ToDo
    }
    if (Greedy(G, orden) == MAX_U32){
        printf("Error en Greedy orden natural\n");
        return 1;
    }
    iteracionColoreos(G, orden, coloreosOrdenamientos, 4, coloreosFinales);

    // Reordenamiento x500 con mejor coloreo
    int mejorColoreo = 0;
    for (int i = 1; i < 5; i++) {
        if (coloreosFinales.cantidadColores[i] < coloreosFinales.cantidadColores[mejorColoreo]) {
            mejorColoreo = i;
        }
    }
    ImportarColores(G, coloreosFinales.coloreo[mejorColoreo]);
    printf("Delta del mejor coloreo: %u\n", coloreosFinales.cantidadColores[mejorColoreo]);

    for (int i = 0 ; i < 500 ; i++) {
        srand(time(NULL));
        int random_number = rand() % 2;

        if (random_number) {
            if (GulDukat(G, orden) == '1') {
                printf("Error en GulDukat\n");
                return 1;
            }
            resetearColoreo(G);
            if (Greedy(G, orden) == MAX_U32){
                printf("Error en Greedy orden natural\n");
                return 1;
            }
            printf("Cantidad de colores GulDukat: %u\n", Delta(G));
        }
        else {
            if (ElimGarak(G, orden) == '1') {
                printf("Error en ElimGarak\n");
                return 1;
            }
            resetearColoreo(G);
            if (Greedy(G, orden) == MAX_U32){
                printf("Error en Greedy orden natural\n");
                return 1;
            }
            printf("Cantidad de colores Elim Garak: %u\n", Delta(G));
        }
    }

    printf("\n\n\nCantidad de colores final: %u\n\n\n", Delta(G));

    // Tiempos finales y liberacion de memoria
    final = clock();
    span = (final - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo total: %lu\n", span);

    DestruirGrafo(G);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < NumeroDeVertices(G); j++) {
            free(coloreosOrdenamientos[i][j]);
        }
    }

    return 0;
}