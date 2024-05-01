#include <stdlib.h>

#include "API2024Parte2.h"

// Definir la estructura para almacenar el color y los valores de m(x) y M(x)
typedef struct {
    u32 color;
    u32 m;
    u32 M;
} ColorInfo;

typedef struct{
    u32 color;
    u32 cantidad;
} ColorCantidad;

//Función de comparación para qsort
int compareBy4(const void *a, const void *b) {
    ColorInfo *colorInfoA = (ColorInfo *)a;
    ColorInfo *colorInfoB = (ColorInfo *)b;
    if (colorInfoA->M != colorInfoB->M) {
        return colorInfoB->M - colorInfoA->M;
    }
    return colorInfoB->m - colorInfoA->m;
}

int compareByNot4(const void *a, const void *b) {
    ColorInfo *colorInfoA = (ColorInfo *)a;
    ColorInfo *colorInfoB = (ColorInfo *)b;

    // Calcula la suma de M y m para cada estructura
    int sumA = colorInfoA->M + colorInfoA->m;
    int sumB = colorInfoB->M + colorInfoB->m;

    // Devuelve la diferencia de las sumas en orden descendente
    return sumB - sumA;
}

int compareOdd(const void *a, const void *b) {
    ColorInfo *colorInfoA = (ColorInfo *)a;
    ColorInfo *colorInfoB = (ColorInfo *)b;
    // Devuelve la diferencia de los campos m en orden descendente
    return colorInfoB->m - colorInfoA->m;
}

int compareCantidad(const void *a, const void *b) {
    u32 cantidadA = ((ColorCantidad*)a)->cantidad;
    u32 cantidadB = ((ColorCantidad*)b)->cantidad;
    if (cantidadA < cantidadB) return -1;
    if (cantidadA > cantidadB) return 1;
    return 0;
}

char GulDukat(Grafo G, u32* Orden) {
    // Paso 1: Crear un array de listas verticesPorColor
    u32 cantColor = 0;
    printf("GulDukat\n");
    for (u32 i = 0; i < NumeroDeVertices(G); ++i) {
        u32 col = Color(i,G);
        if(col > cantColor){
            cantColor = col ;
        }
    }
    cantColor++;
    // sup colores = {1,2,3} => cantColor = 3 => size(verticesPorColor) = 3 * u32  
    // posiciones [0,1,2] cuando accedo al color 3 me daria error
    u32 **verticesPorColor = malloc(cantColor * sizeof(u32 *));
    if (verticesPorColor == NULL) {
        return '1';
    }
    //printf("GulDukat for 2\n");
    for (u32 i = 0; i < cantColor; ++i) {
        verticesPorColor[i] = malloc(NumeroDeVertices(G) * sizeof(u32));
        if (verticesPorColor[i] == NULL) {
            return '1';
        }
        verticesPorColor[i][0] = 0;
    }   // Puede hacerse un realloc y si la cantidad de memoria usada es demasiado grande

    // Paso 2: Llenar verticesPorColor
    //printf("GulDukat for 3 - %u, numVert = %u\n", Color(0, G), NumeroDeVertices(G));
    for (u32 i = 0; i < NumeroDeVertices(G); ++i) {
        //printf("GulDukat for 3 anidado - i : %u\n", i);
        //printf("Cant vertices: %u\n", NumeroDeVertices(G));
        u32 col = Color(i, G);
        //printf("GulDukat for 3 anidado sub 1, color = %u, cantidad de vertices del color = %u \n", col, verticesPorColor[col][0]);

        verticesPorColor[col][0]++;  // Incrementar el contador de vértices
        //printf("GulDukat for 3 anidado sub 2 - color = %u, cantidad de vertices del color = %u \n", col, verticesPorColor[col][0]);
        verticesPorColor[col][verticesPorColor[col][0]] = i;  // Agregar el vértice a la lista
    }   // verticesPorColor [Color][        3          , 0 , 3, 4 ]
        //                          contador del color  vertices de ese color
    for (u32 i = 1; i < cantColor; i++)
    {
        verticesPorColor[i] = realloc(verticesPorColor[i], (verticesPorColor[i][0] + 1) * sizeof(u32));
    }
    
    
    // printf("GulDukat entre 3 - 4\n");
    // Pasos 3 y 4: Crear y llenar las listas de colores
    ColorInfo *divisibleBy4 = malloc(cantColor * sizeof(ColorInfo));
    ColorInfo *evenNotDivisibleBy4 = malloc(cantColor * sizeof(ColorInfo));
    ColorInfo *odd = malloc(cantColor * sizeof(ColorInfo)); //odd = impares
    if (divisibleBy4 == NULL || evenNotDivisibleBy4 == NULL || odd == NULL) {
        return '1';
    }
     //printf("GulDukat for 4\n");
    u32 index4 = 0;
    u32 indexEvenNot4 = 0;
    u32 indexOdd = 0;
    
    for (u32 col = 1; col < cantColor; ++col) {
        u32 m = MAX_U32;
        u32 M = 0;
        
        //printf("GulDukat for 4 - anidado 1 col: %u\n", col);
        for(u32 i = 1; i <= verticesPorColor[col][0]; i++){
            u32 grado = Grado(verticesPorColor[col][i], G);
            if(grado < m){
                m = grado;
            }   
            if(grado > M){
                M = grado;
            }
        }

        // No tiene sentido que el primer vertice pintado sea igual al menor delta de los vertices de ese color
        // y la cantidad de vertices de ese color no tiene porque ser el delta mayor de los vertices de ese color
        
        //u32 m = verticesPorColor[color][1];  // El primer vértice tiene el grado mínimo
        //u32 M = verticesPorColor[color][verticesPorColor[color][0]];  // El último vértice tiene el grado máximo
        ColorInfo colorInfo = {col, m, M};
        //printf("Color: %u, m: %u, M: %u\n", col, m, M);
        if (col % 4 == 0) {
            divisibleBy4[index4] = colorInfo;
            index4++;
        } else if (col % 2 == 0) {
            evenNotDivisibleBy4[indexEvenNot4] = colorInfo;
            indexEvenNot4++;
        } else {
            odd[indexOdd] = colorInfo;
            indexOdd++;
        }
    }
    // for(u32 i = 0; i < index4; i++){
    //     printf(" Lleno pre sort evenNotDivisibleBy4 : color de elemn %u = %u\n", i, evenNotDivisibleBy4[i].color);
    // }

    // Paso 5: Ordenar las listas de colores
    qsort(divisibleBy4, index4, sizeof(ColorInfo), compareBy4);
    qsort(evenNotDivisibleBy4, indexEvenNot4, sizeof(ColorInfo), compareByNot4);
    qsort(odd, indexOdd, sizeof(ColorInfo), compareOdd);
    // for(u32 i = 0; i < index4; i++){
    //     printf("Post sort evenNotDivisibleBy4 : color de elemn %u = %u\n", i, evenNotDivisibleBy4[i].color);
    // }

    // Paso 6 y 7: Llenar el array Orden
    // Los for anidados no generan complejidad O(n^2) porque la suma de los tamaños de las listas es n
    u32 index = 0;
    //printf("GulDukat for 6\n");
    for (u32 i = 0; i < index4; ++i) {
        //printf("GulDukat for 7 - anidado 1\n");
        u32 colorDiv4 = divisibleBy4[i].color;
        //printf("color = %u\n", colorDiv4);
        for (u32 j = 1; j <= verticesPorColor[colorDiv4][0]; ++j) {
            //printf("GulDukat for 7 - anidado 2\n");
            Orden[index++] = verticesPorColor[colorDiv4][j];
        }
        
    }
    //printf("GulDukat for 8\n");
    for (u32 i = 0; i < indexEvenNot4; ++i) {
        u32 colorNotDiv4 = evenNotDivisibleBy4[i].color;
        //printf("GulDukat for 9- anidado 1\n");
        //printf("color = %u\n", colorNotDiv4);
        for (u32 j = 1; j <= verticesPorColor[colorNotDiv4][0]; ++j) {
            //printf("GulDukat for 9 - anidado 2\n");
            Orden[index++] = verticesPorColor[colorNotDiv4][j];
        }
    }
    //printf("GulDukat for 10\n");
    for (u32 i = 0; i < indexOdd; ++i) {
        //printf("GulDukat for 11 - anidado 1\n");
        u32 colorOdd = odd[i].color;
        for (u32 j = 1; j <= verticesPorColor[colorOdd][0]; ++j) {
            //printf("GulDukat for 11 - anidado 2\n");
            Orden[index++] = verticesPorColor[colorOdd][j];
        }
    }

    // Liberar la memoria
    //printf("GulDukat for free vertices\n");
    for(u32 i = 0; i < cantColor; ++i) {
        //printf("GulDukat for free vertices anidado\n");
        free(verticesPorColor[i]);
    }
    free(verticesPorColor);
    free(divisibleBy4);
    free(evenNotDivisibleBy4);
    free(odd);

    return '0';
}

char ElimGarak(Grafo G, u32* Orden) {
    printf("ElimGarak \n");
    u32 n = NumeroDeVertices(G);
    u32 cantColor = 0;
    for (u32 i = 0; i < n; ++i) {
        u32 col = Color(i,G);
        if(col > cantColor){
            cantColor = col ;
        }
    }
    //printf("ElimGarak 1\n");
    cantColor++;
    //printf("CantColor: %u\n", cantColor);
    // Tiene los colores de menos presentas a más presentes
    ColorCantidad *presenciaColores = malloc(cantColor * sizeof(ColorCantidad));
    if (presenciaColores == NULL) {
        return  '1';
    }
    u32 **verticesPorColorElim = malloc(cantColor * sizeof(u32 *));
    if (verticesPorColorElim == NULL) {
        return '1';
    }
    for (u32 i = 0; i < cantColor; ++i) {
        verticesPorColorElim[i] = malloc(NumeroDeVertices(G) * sizeof(u32));
        if (verticesPorColorElim[i] == NULL) {
            return '1';
        }
        verticesPorColorElim[i][0] = 0;
    }   // Puede hacerse un realloc y si la cantidad de memoria usada es demasiado grande

    //printf("ElimGarak 2 for 1\n");
    // Paso 2: Llenar verticesPorColorElim
    for (u32 i = 0; i < n; ++i) {
        //printf("ElimGarak 2 anidado\n");
        u32 col = Color(i, G);
        //printf("ElimGarak 2 anidado 2 - %u\n", col);
        //printf("verticesPorColorElim[col][0] = %u\n", verticesPorColorElim[col][0]);
        verticesPorColorElim[col][0]++;  // Incrementar el contador de vértices
        //printf("verticesPorColorElim[col][0] = %u\n", verticesPorColorElim[col][0]);
        verticesPorColorElim[col][verticesPorColorElim[col][0]] = i;  // Agregar el vértice a la lista
    }

    for (u32 i = 0; i < cantColor; i++)
    {   
        verticesPorColorElim[i] = realloc(verticesPorColorElim[i], (verticesPorColorElim[i][0] + 1) * sizeof(u32));
    }
    // printf("ElimGarak 3 for 2\n");
    for(u32 i = 0; i < cantColor; i++){ // inicializado en 1, cantColor ya es +1
        presenciaColores[i].color = i;
        //printf("i = %u\n", i);
        //printf("presenciaColores[i].color = %u\n", presenciaColores[i].color);
        presenciaColores[i].cantidad = verticesPorColorElim[i][0];
        //printf("verticesPorColorElim[i][0] = %u\n", verticesPorColorElim[i][0]);
        //printf("presenciaColores[i].cantidad = %u\n", presenciaColores[i].cantidad);
        
        //printf("verticesPorColorElim[i][0] = %u  i = %u\n", verticesPorColorElim[i][0], i);
        //printf("presenciaColores[i].color = %u\n", presenciaColores[i].color);
        
    }
    //printf("presenciaColores[3].cantidad = %u\n", presenciaColores[3].cantidad);
    //printf("ElimGarak 4 qsort\n");
    //printf("Presencia Col pre sort: [");
    //for(u32 i = 0; i < cantColor; i++){
    //    printf(" (Color %u; ", presenciaColores[i].color);
    //    printf(" Cantidad %u), ", presenciaColores[i].cantidad);
    //}
    //printf("]\n");
    qsort(presenciaColores, cantColor, sizeof(ColorCantidad), compareCantidad);
    //printf("Presencia Col Post Sort: [");
    //for(u32 i = 0; i < cantColor; i++){
    //    printf(" (Color %u; ", presenciaColores[i].color);
    //    printf(" Cantidad %u), ", presenciaColores[i].cantidad);
    //}
    //printf("]\n");
    //printf("\n\nCantColor: %u\n\n", cantColor);
    int contador = 0;
    //printf("ElimGarak 5 for 3\n");
    for(u32 i = 1; i < cantColor; i++){ // inicializado en 1, cantColor ya es +1
        //printf("ElimGarak 5 for 3 anidado 1\n");
        for(u32 j = 1; j <= presenciaColores[i].cantidad; j++){
            //printf("i = %u, j = %u,  ColPresencia = %u \n", i, j, presenciaColores[i].color);
            Orden[contador] = verticesPorColorElim[presenciaColores[i].color][j];
            // printf("verticesPorColorElim[presenciaColores[i].color][j] = %u\n", verticesPorColorElim[presenciaColores[i].color][j]);
            // printf("Contador = %u\n", contador);
            // printf("Orden[contador] = %u\n", Orden[contador]);
            contador++;
            
        }
    }

    //printf("ElimGarak FIN\n");
    for(u32 i = 0; i < cantColor; ++i) {
        //printf("GulDukat for free vertices anidado\n");
        free(verticesPorColorElim[i]);
    }
    free(verticesPorColorElim);
    //free(verticesPorColorElim);
    free(presenciaColores);
    
    return '0';
}

