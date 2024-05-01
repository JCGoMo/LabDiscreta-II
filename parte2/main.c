#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "API2024Parte2.h"

typedef struct
{
    color coloreo[5];
    u32 cantidadColores[5];
} ColoreoFinal;

typedef struct
{
    u32 numeroVertice;
    u32 grado;
} VerticeGrado;

void DulkatOk(Grafo G, u32 *orden)
{
    if (GulDukat(G, orden) == '1')
    {
        printf("Error en GulDukat\n");
        exit(EXIT_FAILURE);
    }
}

void GarakOk(Grafo G, u32 *orden)
{
    if (ElimGarak(G, orden) == '1')
    {
        printf("Error en ElimGarak\n");
        exit(EXIT_FAILURE);
    }
}

void GreedyOk(Grafo G, u32 *orden)
{
    if (Greedy(G, orden) == MAX_U32)
    {
        printf("Error en Greedy orden natural\n");
        exit(EXIT_FAILURE);
    }
}

void iteracionColoreos(Grafo G, u32 *orden, /*color *coloreosOrdenamientos[5],*/ int j, ColoreoFinal coloreosFinales)
{
    for (int i = 0; i < 100; i = i + 2)
    {
        DulkatOk(G, orden);
        GreedyOk(G, orden);
        printf("Cantidad de colores para el ordenamiento %d en iteracion %d: %u\n", j, i + 1, Delta(G));

        GarakOk(G, orden);
        GreedyOk(G, orden);
        printf("Cantidad de colores para el ordenamiento %d en iteracion %d: %u\n", j, i + 2, Delta(G));
    }
    ExtraerColores(G, &coloreosFinales.coloreo[j]);
    coloreosFinales.cantidadColores[j] = Delta(G);
    printf("Cantidad de colores final para el ordenamiento %d: %u\n", j, coloreosFinales.cantidadColores[j]);
}

int compararGrado(const void *a, const void *b)
{
    const VerticeGrado *verticeA = (const VerticeGrado *)a;
    const VerticeGrado *verticeB = (const VerticeGrado *)b;
    return verticeB->grado - verticeA->grado;
}

int compare(const void *a, const void *b)
{
    int num1 = *(int *)a;
    int num2 = *(int *)b;

    if (num1 % 2 == 0 && num2 % 2 == 0)
    {
        return num2 - num1;
    }
    else if (num1 % 2 != 0 && num2 % 2 != 0)
    {
        return num1 - num2;
    }
    else
    {
        return (num1 % 2 == 0) ? -1 : 1;
    }
}

int main(void)
{
    int index = 0;
    Grafo G = ConstruirGrafo();
    if (G == NULL)
    {
        return 1;
    }
    ColoreoFinal coloreosFinales;
    u32 *orden = malloc(NumeroDeVertices(G) * sizeof(u32));
    if (orden == NULL)
    {
        return 1;
    }

    // Ordenamiento inicial: naturales
    for (u32 i = 0; i < NumeroDeVertices(G); i++)
    {
        orden[i] = i;
    }
    GreedyOk(G, orden);
    iteracionColoreos(G, orden, 0, coloreosFinales);

    // Ordenamiento inicial: naturales inverso
    for (int i = (int)NumeroDeVertices(G) - 1; i >= 0; i--)
    {
        if ((u32)index < NumeroDeVertices(G))
        {
            orden[index] = (u32)i;
            index++;
        }
        else
        {
            printf("Error: index out of bounds\n");
            break;
        }
    }
    GreedyOk(G, orden);
    iteracionColoreos(G, orden, 1, coloreosFinales);

    // Ordenamiento inicial: pares decreciente, luego impares creciente
    index = 0;
    for (u32 i = NumeroDeVertices(G) - 1 - ((NumeroDeVertices(G) - 1) % 2 != 0); (int)i >= 0; i = i - 2)
    {
        orden[index] = (u32)i;
        index++;
    }
    for (u32 i = 1; i <= NumeroDeVertices(G) - 1 - ((NumeroDeVertices(G) - 1) % 2 == 0); i = i + 2)
    {
        orden[index] = i;
        index++;
    }
    GreedyOk(G, orden);
    iteracionColoreos(G, orden, 2, coloreosFinales);

    // Ordenamiento inicial: grado decreciente
    VerticeGrado vertices[NumeroDeVertices(G)];
    for (u32 i = 0; i < NumeroDeVertices(G); i++)
    {
        vertices[i].numeroVertice = i;
        vertices[i].grado = Grado(i, G);
    }

    qsort(&vertices, NumeroDeVertices(G), sizeof(VerticeGrado), compare);
    for (u32 i = 0; i < NumeroDeVertices(G); i++)
    {
        orden[i] = vertices[i].numeroVertice;
    }
    GreedyOk(G, orden);
    iteracionColoreos(G, orden, 3, coloreosFinales);

    // Ordenamiento inicial: Divisibles por 3 primero
    index = 0;
    for (u32 i = 0; i < NumeroDeVertices(G); i += 3)
    {
        orden[index++] = i;
    }
    for (u32 i = 1; i < NumeroDeVertices(G); i++)
    {
        if (i % 3 != 0)
        {
            orden[index++] = i;
        }
    }

    GreedyOk(G, orden);
    iteracionColoreos(G, orden, 4, coloreosFinales);

    // Reordenamiento y coloreo x500 random con mejor coloreo

    // Reordenamiento con orden natural
    for (u32 i = 0; i < NumeroDeVertices(G); i++)
    {
        orden[i] = i;
    }

    int mejorColoreo = 0;
    for (int i = 1; i < 5; i++)
    {
        if (coloreosFinales.cantidadColores[i] < coloreosFinales.cantidadColores[mejorColoreo])
        {
            mejorColoreo = i;
        }
    }
    ImportarColores(&coloreosFinales.coloreo[mejorColoreo], G);

    srand(time(NULL));
    for (int i = 0; i < 500; i++)
    {
        int random_number = rand() % 2;
        if (random_number)
        {
            DulkatOk(G, orden);
        }
        else
        {
            GarakOk(G, orden);
        }
        GreedyOk(G, orden);
    }
    printf("Cantidad de colores final obtenida: %u", Delta(G));

    DestruirGrafo(G);
    return 0;
}