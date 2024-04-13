#include <stdio.h>
#include <stdbool.h>

#include "API2024Parte2.h"


// Encuentra el menor color faltante en un arreglo de colores
color encontrarMenorFaltante(color coloresVecinos[], color * maxColor, u32 deltaVertice) {
    bool presentes[(*maxColor)+1];     // presentes[0] se lo ignora para que los colores empiecen en 1 y entender mas facil
    // [0,1,2,3] maxColor = 3

    for (u32 i = 0; i <= (*maxColor)+1; i++) {
        presentes[i] = false; // Inicializar todos los números como no presentes
    }
    // [false, false, false]
    
    // Marcar como presentes los números que están en el arreglo
    for (u32 i = 0; i < deltaVertice; i++) {
        if (coloresVecinos[i] > 0 && coloresVecinos[i] <= (*maxColor)+1) {
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
    
    printf("Colores vecinos de %u: ", vertice);
    color next_color = encontrarMenorFaltante(colores_vecinos, maxColor, deltaVertice);
    AsignarColor(next_color, vertice, G);
}

// Algoritmo Greedy para colorear un grafo
u32 Greedy(Grafo G,u32* Orden){
    u32 numVertices = NumeroDeVertices(G);
    u32 resultado = 0;
    color * maxColor = malloc(sizeof(color));
    *maxColor = 0;
    
    if (maxColor == NULL) {
        return MAX_U32;
    }
    for (u32 i = 0; i < numVertices; i++) {
        printf("Inicio pintado de vertice %u\n", i);
        pintarVertice(G, Orden[i], maxColor);
    }
    
    resultado = *maxColor;
    free(maxColor);
    return resultado;
}

int main() {
    
    Grafo G = ConstruirGrafo();
    if(G == NULL){
        return 1;
    }

    u32 orden[NumeroDeVertices(G)];
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        orden[i] = i;
    }
    Greedy(G, orden);

    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        printf("Color del vertice %d: %d\n", i, Color(i, G));
    }
    return 0;
}