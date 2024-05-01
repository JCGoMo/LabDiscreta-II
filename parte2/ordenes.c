#include <stdlib.h>

#include "API2024Parte2.h"

// Definir la estructura para almacenar el color y los valores de m(x) y M(x)
typedef struct
{
    u32 color;
    u32 m;
    u32 M;
} ColorInfo;

typedef struct
{
    u32 color;
    u32 cantidad;
} ColorCantidad;

// Función de comparación para qsort
int compareBy4(const void *a, const void *b)
{
    ColorInfo *colorInfoA = (ColorInfo *)a;
    ColorInfo *colorInfoB = (ColorInfo *)b;
    if (colorInfoA->M != colorInfoB->M)
    {
        return colorInfoB->M - colorInfoA->M;
    }
    return colorInfoB->m - colorInfoA->m;
}

int compareByNot4(const void *a, const void *b)
{
    ColorInfo *colorInfoA = (ColorInfo *)a;
    ColorInfo *colorInfoB = (ColorInfo *)b;

    // Calcula la suma de M y m para cada estructura
    int sumA = colorInfoA->M + colorInfoA->m;
    int sumB = colorInfoB->M + colorInfoB->m;

    // Devuelve la diferencia de las sumas en orden descendente
    return sumB - sumA;
}

int compareOdd(const void *a, const void *b)
{
    ColorInfo *colorInfoA = (ColorInfo *)a;
    ColorInfo *colorInfoB = (ColorInfo *)b;
    // Devuelve la diferencia de los campos m en orden descendente
    return colorInfoB->m - colorInfoA->m;
}

int compareCantidad(const void *a, const void *b)
{
    u32 cantidadA = ((ColorCantidad *)a)->cantidad;
    u32 cantidadB = ((ColorCantidad *)b)->cantidad;
    if (cantidadA < cantidadB)
        return -1;
    if (cantidadA > cantidadB)
        return 1;
    return 0;
}

char GulDukat(Grafo G, u32 *Orden)
{
    // Paso 1: Crear un array de listas verticesPorColor
    u32 cantColor = 0;
    printf("GulDukat\n\n\n\n");
    for (u32 i = 0; i < NumeroDeVertices(G); ++i)
    {
        u32 col = Color(i, G);

        if (col > cantColor && col < NumeroDeVertices(G))
        {
            cantColor = col;
        }
    }
    cantColor++;

    u32 **verticesPorColor = malloc(cantColor * sizeof(u32 *));
    if (verticesPorColor == NULL)
    {
        printf(("Error malloc **verticesPorColor\n"));
        printf("CantColor: %u\n", cantColor);
        return '1';
    }

    for (u32 i = 0; i < cantColor; ++i)
    {
        if (cantColor == 0)
        {
            verticesPorColor[i] = malloc(NumeroDeVertices(G) / 5 * sizeof(u32));
        }
        else if (cantColor == 1)
        {
            verticesPorColor[i] = malloc((NumeroDeVertices(G) / cantColor) * sizeof(u32));
        }
        else
        {
            verticesPorColor[i] = malloc((NumeroDeVertices(G) / (cantColor - 1)) * sizeof(u32));
        }
        if (verticesPorColor[i] == NULL)
        {
            printf(("Error malloc verticesPorColor[i]\n"));
            return '1';
        }
        verticesPorColor[i][0] = 0;
    }

    // Paso 2: Llenar verticesPorColor
    for (u32 i = 0; i < NumeroDeVertices(G); ++i)
    {
        u32 col = Color(i, G);

        verticesPorColor[col][0]++; // Incrementar el contador de vértices
        if (cantColor == 0)
        {
            if (verticesPorColor[col][0] > ((NumeroDeVertices(G) / 5) - 1))
            {
                verticesPorColor[col] = realloc(verticesPorColor[col], ((NumeroDeVertices(G) / 5) * 2) * sizeof(u32));
            }
        }
        else if (cantColor == 1)
        {
            if (verticesPorColor[col][0] > ((NumeroDeVertices(G) / cantColor) - 1))
            {
                verticesPorColor[col] = realloc(verticesPorColor[col], ((NumeroDeVertices(G) / cantColor) * 2) * sizeof(u32));
            }
        }
        else
        {
            if (verticesPorColor[col][0] > ((NumeroDeVertices(G) / (cantColor - 1)) - 1))
            {
                verticesPorColor[col] = realloc(verticesPorColor[col], ((verticesPorColor[col][0]) * 2) * sizeof(u32));
            }
        }
        verticesPorColor[col][verticesPorColor[col][0]] = i; // Agregar el vértice a la lista
    }

    for (u32 i = 1; i < cantColor; i++)
    {
        verticesPorColor[i] = realloc(verticesPorColor[i], (verticesPorColor[i][0] + 1) * sizeof(u32));
    }

    //  Pasos 3 y 4: Crear y llenar las listas de colores
    ColorInfo *divisibleBy4 = malloc(cantColor * sizeof(ColorInfo));
    ColorInfo *evenNotDivisibleBy4 = malloc(cantColor * sizeof(ColorInfo));
    ColorInfo *odd = malloc(cantColor * sizeof(ColorInfo)); // odd = impares

    if (divisibleBy4 == NULL || evenNotDivisibleBy4 == NULL || odd == NULL)
    {
        printf(("Error malloc divisibleBy4 o evenNotDivisibleBy4 u odd\n"));
        return '1';
    }

    u32 index4 = 0;
    u32 indexEvenNot4 = 0;
    u32 indexOdd = 0;

    for (u32 col = 1; col < cantColor; ++col)
    {
        u32 m = MAX_U32;
        u32 M = 0;
        for (u32 i = 1; i <= verticesPorColor[col][0]; i++)
        {
            u32 grado = Grado(verticesPorColor[col][i], G);
            if (grado < m)
            {
                m = grado;
            }
            if (grado > M)
            {
                M = grado;
            }
        }

        ColorInfo colorInfo = {col, m, M};

        if (col % 4 == 0)
        {
            divisibleBy4[index4] = colorInfo;
            index4++;
        }
        else if (col % 2 == 0)
        {
            evenNotDivisibleBy4[indexEvenNot4] = colorInfo;
            indexEvenNot4++;
        }
        else
        {
            odd[indexOdd] = colorInfo;
            indexOdd++;
        }
    }

    // Paso 5: Ordenar las listas de colores
    qsort(divisibleBy4, index4, sizeof(ColorInfo), compareBy4);
    qsort(evenNotDivisibleBy4, indexEvenNot4, sizeof(ColorInfo), compareByNot4);
    qsort(odd, indexOdd, sizeof(ColorInfo), compareOdd);

    // Paso 6 y 7: Llenar el array Orden
    u32 index = 0;

    for (u32 i = 0; i < index4; ++i)
    {
        u32 colorDiv4 = divisibleBy4[i].color;
        for (u32 j = 1; j <= verticesPorColor[colorDiv4][0]; ++j)
        {
            Orden[index++] = verticesPorColor[colorDiv4][j];
        }
    }

    for (u32 i = 0; i < indexEvenNot4; ++i)
    {
        u32 colorNotDiv4 = evenNotDivisibleBy4[i].color;
        for (u32 j = 1; j <= verticesPorColor[colorNotDiv4][0]; ++j)
        {
            Orden[index++] = verticesPorColor[colorNotDiv4][j];
        }
    }

    for (u32 i = 0; i < indexOdd; ++i)
    {

        u32 colorOdd = odd[i].color;
        for (u32 j = 1; j <= verticesPorColor[colorOdd][0]; ++j)
        {
            Orden[index++] = verticesPorColor[colorOdd][j];
        }
    }

    // Liberar la memoria
    for (u32 i = 0; i < cantColor; ++i)
    {
        free(verticesPorColor[i]);
    }
    free(verticesPorColor);
    free(divisibleBy4);
    free(evenNotDivisibleBy4);
    free(odd);

    return '0';
}

char ElimGarak(Grafo G, u32 *Orden)
{
    printf("ElimGarak \n");
    u32 cantColor = 0;
    for (u32 i = 0; i < NumeroDeVertices(G); ++i)
    {
        u32 col = Color(i, G);

        if (col > cantColor && col < NumeroDeVertices(G))
        {
            cantColor = col;
        }
    }

    cantColor++;

    //  Tiene los colores de menos presentas a más presentes
    ColorCantidad *presenciaColores = malloc((cantColor + 1) * sizeof(ColorCantidad));
    if (presenciaColores == NULL)
    {
        printf(("Error malloc presenciaColores\n"));
        printf("CantColor: %u\n", cantColor);
        return '1';
    }
    u32 **verticesPorColorElim = malloc(cantColor * sizeof(u32 *));
    if (verticesPorColorElim == NULL)
    {
        printf(("Error malloc verticesPorColorElim\n"));
        return '1';
    }
    for (u32 i = 0; i < cantColor; ++i)
    {
        if (cantColor == 0)
        {
            verticesPorColorElim[i] = malloc(NumeroDeVertices(G) / 5 * sizeof(u32));
        }
        else if (cantColor == 1)
        {
            verticesPorColorElim[i] = malloc((NumeroDeVertices(G) / cantColor) * sizeof(u32));
        }
        else
        {
            verticesPorColorElim[i] = malloc((NumeroDeVertices(G) / (cantColor - 1)) * sizeof(u32));
        }
        if (verticesPorColorElim[i] == NULL)
        {
            printf(("Error malloc verticesPorColorElim[i]\n"));
            return '1';
        }
        verticesPorColorElim[i][0] = 0;
    }

    //  Paso 2: Llenar verticesPorColorElim
    for (u32 i = 0; i < NumeroDeVertices(G); ++i)
    {
        u32 col = Color(i, G);
        verticesPorColorElim[col][0]++; // Incrementar el contador de vértices
        if (cantColor == 0)
        {
            if (verticesPorColorElim[col][0] > ((NumeroDeVertices(G) / 5) - 1))
            {
                verticesPorColorElim[col] = realloc(verticesPorColorElim[col], ((NumeroDeVertices(G) / 5) * 2) * sizeof(u32));
            }
        }
        else if (cantColor == 1)
        {
            if (verticesPorColorElim[col][0] > ((NumeroDeVertices(G) / cantColor) - 1))
            {
                verticesPorColorElim[col] = realloc(verticesPorColorElim[col], ((NumeroDeVertices(G) / cantColor) * 2) * sizeof(u32));
            }
        }
        else
        {
            if (verticesPorColorElim[col][0] > ((NumeroDeVertices(G) / (cantColor - 1)) - 1))
            {
                verticesPorColorElim[col] = realloc(verticesPorColorElim[col], ((verticesPorColorElim[col][0]) * 2) * sizeof(u32));
            }
        }
        verticesPorColorElim[col][verticesPorColorElim[col][0]] = i; // Agregar el vértice a la lista
    }

    // Mas complejidad, menos memoria
    for (u32 i = 0; i < cantColor; i++)
    {
        verticesPorColorElim[i] = realloc(verticesPorColorElim[i], (verticesPorColorElim[i][0] + 1) * sizeof(u32));
    }

    for (u32 i = 0; i < cantColor; i++)
    {
        presenciaColores[i].color = i;
        presenciaColores[i].cantidad = verticesPorColorElim[i][0];
    }

    qsort(presenciaColores, cantColor, sizeof(ColorCantidad), compareCantidad);
    int contador = 0;
    for (u32 i = 1; i < cantColor; i++)
    {
        for (u32 j = 1; j <= presenciaColores[i].cantidad; j++)
        {
            Orden[contador] = verticesPorColorElim[presenciaColores[i].color][j];
            contador++;
        }
    }

    for (u32 i = 0; i < cantColor; ++i)
    {
        free(verticesPorColorElim[i]);
    }
    free(verticesPorColorElim);
    free(presenciaColores);

    return '0';
}
