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

void iteracionColoreos(Grafo G, u32 *orden, /*color *coloreosOrdenamientos[5],*/ int j, ColoreoFinal coloreosFinales) {
    for (int i = 0; i < 100; i = i+2) {
        // sleep(1);
        DulkatOk(G, orden);
        GreedyOk(G, orden);
        //ExtraerColores(G, &coloreosOrdenamientos[j][i]);
        // printf("Delta parcial del coloreo Dulkat n %d del ordenamiento %d: %u\n", i, j, Delta(G));
        //  sleep(1);
        GarakOk(G, orden);
        resetearColoreo(G);
        GreedyOk(G, orden);
        //ExtraerColores(G, &coloreosOrdenamientos[j][i+1]);
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
    int index = 0;
    inicio = clock();
    Grafo G = ConstruirGrafo();
    if(G == NULL){
        return 1;
    }
    //u32 numVert = NumeroDeVertices(G);
    //printf("numVer %u = NumeroDeVertices(G) = %u\n", numVert, NumeroDeVertices(G));
    ColoreoFinal coloreosFinales;
    // color *coloreosOrdenamientos[5];
    // for (int i = 0; i < 5; i++) {
    //     coloreosOrdenamientos[i] = malloc(NumeroDeVertices(G) * sizeof(color));
    //     if(coloreosOrdenamientos[i] == NULL){
    //         return 1;
    //     }
    // }
    u32 *orden = malloc(NumeroDeVertices(G) * sizeof(u32));
    if(orden == NULL){
        return 1;
    }
    
    // Ordenamiento inicial: naturales
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        orden[i] = i;
    }
    GreedyOk(G, orden);
    iteracionColoreos(G, orden, /*coloreosOrdenamientos,*/ 0, coloreosFinales);

    // Ordenamiento inicial: naturales inverso
    
    for (int i = (int)NumeroDeVertices(G)-1; i >= 0; i--) {    
        orden[index] = (u32)i;
        index++;
        printf("Index %d", index);
        
    }
    printf("2do orden");
    GreedyOk(G, orden);
    iteracionColoreos(G, orden,/* coloreosOrdenamientos,*/ 1, coloreosFinales);
    

    // Ordenamiento inicial: pares decreciente, luego impares creciente
    
    //printf("Orden pares decrecientes: ["); 
    index = 0;                                                         
    for (u32 i = NumeroDeVertices(G) - 1 - ((NumeroDeVertices(G)-1) % 2 != 0); (int)i >= 0 ; i = i-2) {               // Pares decreciente              
        orden[index] = (u32)i;
        index++;
        
        //printf("%u, ", i);
    }
    
    //printf("]\n");
    //printf("Orden impares creciente: [");
    for (u32 i = 1; i <= NumeroDeVertices(G) - 1 - ((NumeroDeVertices(G)-1) % 2 == 0); i = i+2) {                // Impares creciente
        orden[index] = i;
        index++;
        printf("%u, ", i);
        
    }
    //printf("]\n");
    GreedyOk(G, orden);
    iteracionColoreos(G, orden, /*coloreosOrdenamientos,*/ 2, coloreosFinales);

    // Ordenamiento inicial: grado decreciente
    VerticeGrado vertices[NumeroDeVertices(G)];
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        vertices[i].numeroVertice = i;
        vertices[i].grado = Grado(i, G);
    }

    qsort(&vertices, NumeroDeVertices(G), sizeof(VerticeGrado), compare);
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        orden[i] = vertices[i].numeroVertice;
    }
    GreedyOk(G, orden);
    iteracionColoreos(G, orden, /*coloreosOrdenamientos,*/ 3, coloreosFinales);
    
    // Ordenamiento inicial: 0, n, 1, n-1, 2, n-2, ...
    // u32 mitad = NumeroDeVertices(G) / 2;
    // printf("Orden intercalado: ["); 
    // for (u32 i = 0; i < mitad; i++) {
    //     orden[i] = i;
    //     orden[i + 1] = NumeroDeVertices(G) - i - 1;
    //     printf("%u, %u, ", orden[i], orden[i + 1]);
    // }
    // if (NumeroDeVertices(G) % 2 != 0) {
    //     orden[NumeroDeVertices(G) - 1] = mitad;
    //     printf("%u", orden[NumeroDeVertices(G) - 1]);
    // }
    // printf("]\n");

    // for(u32 i = 0; i < NumeroDeVertices(G); i++){
    //     if((i % 2 != 0)&& i !=0){
    //         orden[i] = i-1;
    //     }
    //     else if(i % 2 == 0){ {
    //         orden[i] = NumeroDeVertices(G) - i;
    //     }
        
    // }

    //////...///////
    // Ordenamiento inicial: Divisibles por 3 primero
    index = 0;
    for (u32 i = 0; i < NumeroDeVertices(G); i += 3) {
        orden[index++] = i;
    }
    for (u32 i = 1; i < NumeroDeVertices(G); i++) {
        if (i % 3 != 0) {
            orden[index++] = i;
        }
    }
    //////...///////
    printf("Orden: [");
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        printf("%u, ", orden[i]);
    }
    printf("]\n");

    GreedyOk(G, orden);
    iteracionColoreos(G, orden, /*coloreosOrdenamientos,*/ 4, coloreosFinales);

    // Reordenamiento y coloreo x500 random con mejor coloreo
    
    // Reordenamiento con orden natural
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        orden[i] = i;
    }

    int mejorColoreo = 0;
    for (int i = 1; i < 5; i++) {
        if (coloreosFinales.cantidadColores[i] < coloreosFinales.cantidadColores[mejorColoreo]) {
            mejorColoreo = i;
        }
    }
    ImportarColores(&coloreosFinales.coloreo[mejorColoreo], G);
    printf("Mejor delta de los 5 ordenamientos: %u\n", coloreosFinales.cantidadColores[mejorColoreo]);

    // printf("Orden Pre Pre reorder: [");
    //     for (u32 i = 0; i < NumeroDeVertices(G); i++) {
    //         printf("%u, ", orden[i]);
    //     }
    // printf("]\n");

    for (int i = 0 ; i < 50 ; i++) {
        srand(time(NULL));
        int random_number = rand() % 2;
        // sleep(1);
        
        // printf("Orden Pre reorder: [");
        // for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        //     printf("%u, ", orden[i]);
        // }
        // printf("]\n");



        if (random_number) {
            DulkatOk(G, orden);
        }
        else {
            GarakOk(G, orden);
        }
        //printf("Orden post reorder: [");
        //for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        //    printf("%u, ", orden[i]);
        //}
        //printf("]\n");
        printf("\nDelta final: %u\n", Delta(G));
        GreedyOk(G, orden);
        // printf("Delta parcial del reordenamiento %d de 500: %u\n", i, Delta(G));
    }
    printf("\n\n\nDelta final: %u\n\n\n", Delta(G));

    // Tiempos finales y liberacion de memoria
    final = clock();
    span = (final - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo total: %lu\n", span);

    DestruirGrafo(G);
    // for (int i = 0; i < 5; i++) {
    //     free(coloreosOrdenamientos[i]);
    // }

    return 0;
}