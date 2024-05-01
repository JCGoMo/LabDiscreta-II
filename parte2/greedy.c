#include <stdio.h>
#include <stdbool.h>

#include "API2024Parte2.h"


// Encuentra el menor color faltante en un arreglo de colores
color encontrarMenorFaltante(color coloresVecinos[], color * maxColor, u32 deltaVertice) {
    bool presentes[(*maxColor)+1];     // presentes[0] se lo ignora para que los colores empiecen en 1 y entender mas facil
    // [F,F,F,F] maxColor = 3
   // printf("Colores vecinos de %u :", vertice);
    for (u32 i = 0; i < (*maxColor)+1; i++) {
        presentes[i] = false; // Inicializar todos los números como no presentes
        
    }
    // printf("Colores vecinos:");
    // for(u32 i = 0; i < deltaVertice; i++){
    //     printf(" %u ", coloresVecinos[i]);
    // }
    // printf("\n");

    // [false, false, false]
    //printf("\n");
    // Marcar como presentes los números que están en el arreglo
    for (u32 i = 0; i < deltaVertice; i++) {
        if (coloresVecinos[i] > 0 && coloresVecinos[i] < (*maxColor)+1) {
            presentes[coloresVecinos[i]] = true;
        }
    }
    // vecinos = [ v1, v2, v3, v4, v5, v6, v7]
    // colores = [ 0, 2, 0, 2, 0, 0, 0]
    // presentes = [true, false, true ]
    // Encontrar el primer número faltante
    color menorFaltante = 0;
    for (u32 i = 1; i < (*maxColor)+1; i++) {
        if (!presentes[i]) {
            menorFaltante = i;
            break;
        }
    }

    // Si todos los números están presentes, devolver el siguiente número
    if (menorFaltante == 0) {
        (*maxColor)++;
        menorFaltante = *maxColor;
    }
    //printf("Menor faltante: %u\n", menorFaltante);

    return menorFaltante;
}

// Pinta un vértice con el menor color posible
void pintarVertice(Grafo G, u32 vertice, color * maxColor){
    u32 deltaVertice = Grado(vertice, G);
    color colores_vecinos[deltaVertice];
    u32 vecino;
    
    for (u32 i = 0; i < deltaVertice; i++){
        vecino = Vecino(i, vertice, G);
        colores_vecinos[i] = Color(vecino, G);
    }
    
    //printf("Colores vecinos de %u: ", vertice);
    color next_color = encontrarMenorFaltante(colores_vecinos, maxColor, deltaVertice);
    AsignarColor(next_color, vertice, G);
}

// Algoritmo Greedy para colorear un grafo

/*
Esta funci ́on asume que Orden apunta a un sector de memoria con n lugares. Uds no necesitan verificar esto.
Pero, lo primero que debe hacer esta funci ́on es verificar que Orden provee efectivamente un orden de los elementos
{0, 1, ..., n −1}. Es decir, que Orden induce una biyecci ́on en {0, 1, ..., n −1}.
*/

bool verificaOrden(u32 *Orden, u32 n) {
    // PRE: Orden apunta a un sector de memoria con n lugares
    bool *verificado = calloc(n, sizeof(bool));
    if (verificado == NULL) {
        return false;
    }
    // printf("n = %u\n", n);
    //printf("Verificando orden\n");
    
    for (u32 i = 0; i < n; ++i) {
        // printf("Ver. Or. - Dentro for \n");
        if (Orden[i] > n || verificado[Orden[i]]) {
            //printf("Orden[%u] = %u\n", i, Orden[i]);
            //printf("verificado[%u] = %u  \n",i, verificado[i]);
            printf("Lista de verificados: fallo [\n");
            for(u32 j = 0; j < n; j++){
                printf("%u, ", verificado[j]);
            }
            printf("]\n");
            free(verificado);
            printf("Orden Invalido\n");
            return false;
        }

        //printf("Ver. Or. - Mid for \n");
        verificado[Orden[i]] = true;
        //printf("Ver. Or. - Final for \n");
        /*
        [0, 7, 1, 6, 2, 5, 3, 4 ]
        [F, F, F, F, F, F, F, F ]
        
        i = 7, orden[i] = 4 n = 8
        verificado[orden[i]] = 
        [t, t, t, t, t, t, t, t ]
        

        */
    }

    free(verificado);
    return true;
}

u32 Greedy(Grafo G,u32* Orden) {
    //printf("Entro a greedy\n");
    u32 numVertices = NumeroDeVertices(G);
    u32 resultado = 0;
    color * maxColor = malloc(sizeof(color));
    *maxColor = 0;
    
    if (maxColor == NULL) {
        return MAX_U32;
    }
    //printf("Por verificar orden\n");
    if (!verificaOrden(Orden, numVertices)) {
        free(maxColor);
        return MAX_U32;
    }
    // Reseteo de coloreo
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        AsignarColor(0, i, G);
    }
    //printf("Orden verificado\n");
    for (u32 i = 0; i < numVertices; i++) {
        //printf("Inicio pintado de vertice %u\n", i);
        pintarVertice(G, Orden[i], maxColor);
    }
    resultado = *maxColor;
    free(maxColor);
    return resultado;
}
