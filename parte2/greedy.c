#include <stdio.h>
#include <stdbool.h>

#include "API2024Parte2.h"

// Encuentra el menor color faltante en un arreglo de colores
color encontrarMenorFaltante(color coloresVecinos[], color *maxColor, u32 deltaVertice)
{
    bool presentes[(*maxColor) + 1]; // presentes[0] se lo ignora para que los colores empiecen en 1 y entender mas facil

    for (u32 i = 0; i < (*maxColor) + 1; i++)
    {
        presentes[i] = false; // Inicializar todos los números como no presentes
    }

    // Marcar como presentes los números que están en el arreglo
    for (u32 i = 0; i < deltaVertice; i++)
    {
        if (coloresVecinos[i] > 0 && coloresVecinos[i] < (*maxColor) + 1)
        {
            presentes[coloresVecinos[i]] = true;
        }
    }

    // Encontrar el primer número faltante
    color menorFaltante = 0;
    for (u32 i = 1; i < (*maxColor) + 1; i++)
    {
        if (!presentes[i])
        {
            menorFaltante = i;
            break;
        }
    }

    // Si todos los números están presentes, devolver el siguiente número
    if (menorFaltante == 0)
    {
        (*maxColor)++;
        menorFaltante = *maxColor;
    }

    return menorFaltante;
}

// Pinta un vértice con el menor color posible
void pintarVertice(Grafo G, u32 vertice, color *maxColor)
{
    u32 deltaVertice = Grado(vertice, G);
    color colores_vecinos[deltaVertice];
    u32 vecino;

    for (u32 i = 0; i < deltaVertice; i++)
    {
        vecino = Vecino(i, vertice, G);
        colores_vecinos[i] = Color(vecino, G);
    }

    color next_color = encontrarMenorFaltante(colores_vecinos, maxColor, deltaVertice);
    AsignarColor(next_color, vertice, G);
}

bool verificaOrden(u32 *Orden, u32 n)
{
    // PRE: Orden apunta a un sector de memoria con n lugares
    bool *verificado = calloc(n, sizeof(bool));
    if (verificado == NULL)
    {
        return false;
    }

    for (u32 i = 0; i < n; ++i)
    {
        if (Orden[i] > n || verificado[Orden[i]])
        {
            printf("Lista de verificados: fallo [\n");
            for (u32 j = 0; j < n; j++)
            {
                printf("%u, ", verificado[j]);
            }
            printf("]\n");
            free(verificado);
            printf("Orden Invalido\n");
            return false;
        }

        verificado[Orden[i]] = true;
    }

    free(verificado);
    return true;
}

u32 Greedy(Grafo G, u32 *Orden)
{
    u32 numVertices = NumeroDeVertices(G);
    u32 resultado = 0;
    color *maxColor = malloc(sizeof(color));
    *maxColor = 0;

    if (maxColor == NULL)
    {
        return MAX_U32;
    }

    if (!verificaOrden(Orden, numVertices))
    {
        free(maxColor);
        return MAX_U32;
    }

    // Reseteo de coloreo
    for (u32 i = 0; i < NumeroDeVertices(G); i++)
    {
        AsignarColor(0, i, G);
    }

    for (u32 i = 0; i < numVertices; i++)
    {
        pintarVertice(G, Orden[i], maxColor);
    }
    resultado = *maxColor;
    free(maxColor);
    return resultado;
}
