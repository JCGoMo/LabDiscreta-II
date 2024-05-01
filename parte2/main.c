#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "API2024Parte2.h"

// Todo asumiendo que los vertices van del 0 al n
// Revisar, testear

typedef struct {
    color coloreo[5];
    u32 cantidadColores[5];
} ColoreoFinal;

typedef struct {
    u32 numeroVertice;
    u32 grado;
} VerticeGrado;


void DulkatOk (Grafo G, u32 *orden) {
    if (GulDukat(G, orden) == '1') {
        printf("Error en GulDukat\n");
        exit(EXIT_FAILURE);
    }
}

void GarakOk (Grafo G, u32 *orden) {
    if (ElimGarak(G, orden) == '1') {
        printf("Error en ElimGarak\n");
        exit(EXIT_FAILURE);
    }
}

void GreedyOk (Grafo G, u32 *orden) {
    if (Greedy(G, orden) == MAX_U32){
        printf("Error en Greedy orden natural\n");
        exit(EXIT_FAILURE);
    }
}

void resetearColoreo(Grafo G){
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        AsignarColor(0, i, G);
    }
}

void iteracionColoreos(Grafo G, u32 *orden, color *coloreosOrdenamientos[5], int j, ColoreoFinal coloreosFinales) {
    for (int i = 0; i < 10; i = i+2) {
        // sleep(1);
        DulkatOk(G, orden);
        GreedyOk(G, orden);
        ExtraerColores(G, &coloreosOrdenamientos[j][i]);
        // printf("Delta parcial del coloreo Dulkat n %d del ordenamiento %d: %u\n", i, j, Delta(G));
        //  sleep(1);
        GarakOk(G, orden);
        resetearColoreo(G);
        GreedyOk(G, orden);
        ExtraerColores(G, &coloreosOrdenamientos[j][i+1]);
        // printf("Delta parcial del coloreo Garak n %d del ordenamiento %d: %u\n", i, j, Delta(G));
    }
    ExtraerColores(G, &coloreosFinales.coloreo[j]);
    coloreosFinales.cantidadColores[j] = Delta(G);
    printf("Delta final del ordenamiento %d: %u\n", j, coloreosFinales.cantidadColores[j]);
}

int compararGrado(const void *a, const void *b) {
    const VerticeGrado *verticeA = (const VerticeGrado *)a;
    const VerticeGrado *verticeB = (const VerticeGrado *)b;
    return verticeB->grado - verticeA->grado;
}

int compare(const void *a, const void *b) {
    int num1 = *(int*)a;
    int num2 = *(int*)b;

    if (num1 % 2 == 0 && num2 % 2 == 0) {
        return num2 - num1;
    } else if (num1 % 2 != 0 && num2 % 2 != 0) {
        return num1 - num2;
    } else {
        return (num1 % 2 == 0) ? -1 : 1;
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
    u32 numVert = NumeroDeVertices(G);

    ColoreoFinal coloreosFinales;
    color *coloreosOrdenamientos[5];
    for (int i = 0; i < 5; i++) {
        coloreosOrdenamientos[i] = malloc(numVert * sizeof(color));
        if(coloreosOrdenamientos[i] == NULL){
            return 1;
        }
    }
    u32 *orden = malloc(numVert * sizeof(u32));
    if(orden == NULL){
        return 1;
    }

    // Ordenamiento inicial: naturales
    for (u32 i = 0; i < numVert; i++) {
        orden[i] = i;
    }
    GreedyOk(G, orden);
    iteracionColoreos(G, orden, coloreosOrdenamientos, 0, coloreosFinales);

    // Ordenamiento inicial: naturales inverso
    for (u32 i = 0; i < numVert; i++) {                         
        orden[i] = numVert - i - 1;
    }
    GreedyOk(G, orden);
    iteracionColoreos(G, orden, coloreosOrdenamientos, 1, coloreosFinales);

    // Ordenamiento inicial: pares decreciente, luego impares creciente
    int index = 0;
    //printf("Orden pares decrecientes: [");                                                          
    for (u32 i = numVert - 1 - ((numVert-1) % 2 != 0); (int)i >= 0 ; i = i-2) {               // Pares decreciente              
        orden[index] = (u32)i;
        index++;
        //printf("%u, ", i);
    }
    //printf("]\n");
    //printf("Orden impares creciente: [");
    for (u32 i = 1; i <= numVert - 1 - ((numVert-1) % 2 == 0); i = i+2) {                // Impares creciente
        orden[index] = i;
        index++;
        printf("%u, ", i);
        
    }
    //printf("]\n");
    GreedyOk(G, orden);
    iteracionColoreos(G, orden, coloreosOrdenamientos, 2, coloreosFinales);

    // Ordenamiento inicial: grado decreciente
    VerticeGrado vertices[numVert];
    for (u32 i = 0; i < numVert; i++) {
        vertices[i].numeroVertice = i;
        vertices[i].grado = Grado(i, G);
    }

    qsort(&vertices, numVert, sizeof(VerticeGrado), compare);
    for (u32 i = 0; i < numVert; i++) {
        orden[i] = vertices[i].numeroVertice;
    }
    GreedyOk(G, orden);
    iteracionColoreos(G, orden, coloreosOrdenamientos, 3, coloreosFinales);
    
    // Ordenamiento inicial: 0, n, 1, n-1, 2, n-2, ...
    u32 mitad = numVert / 2;
    printf("Orden intercalado: ["); 
    for (u32 i = 0; i < mitad; i++) {
        orden[i] = i;
        orden[i + 1] = numVert - i - 1;
        printf("%u, %u, ", orden[i], orden[i + 1]);
    }
    if (numVert % 2 != 0) {
        orden[numVert - 1] = mitad;
        printf("%u", orden[numVert - 1]);
    }
    printf("]\n");

    GreedyOk(G, orden);
    iteracionColoreos(G, orden, coloreosOrdenamientos, 4, coloreosFinales);

                                                            // MANTENEMOS EL ULTIMO ORDENAMIENTO O LO RESETEAMOS?

    // Reordenamiento y coloreo x500 random con mejor coloreo
    int mejorColoreo = 0;
    for (int i = 1; i < 5; i++) {
        if (coloreosFinales.cantidadColores[i] < coloreosFinales.cantidadColores[mejorColoreo]) {
            mejorColoreo = i;
        }
    }
    ImportarColores(&coloreosFinales.coloreo[mejorColoreo], G);
    printf("Mejor delta de los 5 ordenamientos: %u\n", coloreosFinales.cantidadColores[mejorColoreo]);

    for (int i = 0 ; i < 5 ; i++) {
        srand(time(NULL));
        int random_number = rand() % 2;
        // sleep(1);
        if (random_number) {
            DulkatOk(G, orden);
        }
        else {
            GarakOk(G, orden);
        }
        resetearColoreo(G);
        GreedyOk(G, orden);
        // printf("Delta parcial del reordenamiento %d de 500: %u\n", i, Delta(G));
    }
    printf("\n\n\nDelta final: %u\n\n\n", Delta(G));

    // Tiempos finales y liberacion de memoria
    final = clock();
    span = (final - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo total: %lu\n", span);

    DestruirGrafo(G);
    for (int i = 0; i < 5; i++) {
        free(coloreosOrdenamientos[i]);
    }

    return 0;
}