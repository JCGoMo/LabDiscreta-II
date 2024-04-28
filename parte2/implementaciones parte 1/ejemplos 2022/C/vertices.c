#include <stdio.h>
#include <assert.h>
#include "EstructuraGrafo.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include <stdbool.h>
#include "dimacs.h"

u32 posDeVerticeEnArreglo(vertice** vertices, u32 hasta, u32 nombreVertice) {
    u32 resultado = -1u;
    u32 i = 0;
    while(i < hasta && resultado == -1u) {
        if (vertices[i]->nombre == nombreVertice) {
            resultado = i;
        }
        i++;
    }
    return resultado;
}

static void swap(vertice *a, vertice *b) {
    vertice aux = *a;
    *a = *b;
    *b = aux;
}

static u32 partition(vertice **vertices, u32 low, u32 high) {
    // select the rightmost element as pivot
    u32 pivot = vertices[high]->nombre;

    // pointer for greater element
    u32 i = low;

    // traverse each element of the array
    // compare them with the pivot
    for (u32 j = low; j < high; j++) {
        if (vertices[j]->nombre <= pivot) {
            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            // swap element at i with element at j
            swap(vertices[i], vertices[j]);
            i++;
        }
    }
    // swap the pivot element with the greater element at i
    swap(vertices[i], vertices[high]);

    // return the partition point
    return i;
}

static void quickSort(vertice **vertices, u32 low, u32 high) {
    if (low < high) {
        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        u32 pi = partition(vertices, low, high);

        if (pi > 0) {
            // recursive call on the left of pivot
            quickSort(vertices, low, pi - 1);
        }

        // recursive call on the right of pivot
        quickSort(vertices, pi + 1, high);
    }
}

void ordenarVertices(vertice **vertices, u32 cantVertices) {
    quickSort(vertices, 0, cantVertices - 1);
}

void asignarIndice(vertice **vertices, u32 cantVertices) {
    for (u32 i = 0; i < cantVertices; i++) {
        vertices[i]->indice = i;
    }
}

u32 inicializarVecinosYObtenerDelta(vertice **vertices, u32 cantVertices) {
    u32 delta = 0;
    for (u32 i = 0; i < cantVertices; i++) {
        vertices[i]->vecinos = calloc(vertices[i]->grado, sizeof(vertice));
        if (vertices[i]->grado > delta) {
            delta = vertices[i]->grado;
        }
    }
    return delta;
}

/** Búsqueda binaría sobre el arreglo ordenado vertices
 * @param vertices arreglo ordenado donde buscar.
 */
vertice *obtenerVerticePorNombre(vertice **vertices, u32 cantVertices, u32 nombre) {
    u32 low = 0;
    u32 high = cantVertices;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (vertices[mid]->nombre == nombre)
            return vertices[mid];

        if (vertices[mid]->nombre < nombre)
            low = mid + 1;
        else
            high = mid - 1;
    }
    assert(0);//TODO deleteee thisss
    return NULL;
}

void agregarVecinos(dimacsData *datos, vertice **vertices, u32 cantVertices) {
    /* u32 paso = datos->m >> 10; */
    /* u32 p = 0; */
    printf(" ");
    for (u32 i = 0; i < datos->m; i++) {
        vertice *v1 = obtenerVerticePorNombre(vertices, cantVertices, datos->lados[i][0]);
        vertice *v2 = obtenerVerticePorNombre(vertices, cantVertices, datos->lados[i][1]);
        u32 k = 0;
        while (v2->vecinos[k] != NULL && k < v2->grado) {
            k++;
        }
        v2->vecinos[k] = v1;
        k = 0;
        while (v1->vecinos[k] != NULL && k < v1->grado) {
            k++;
        }
        v1->vecinos[k] = v2;
        // SHOWING PROGRESS
        /* if (p == paso) { */
        /*     printf("\33[2K\r"); */
        /*     printf("%u de %u lados leídos.", i, datos->m); */
        /*     p = 0; */
        /* } else p ++; */
    }
}

u32 Nombre(u32 i, Grafo g) {
    return g->vertices[i]->nombre;
}

u32 Grado(u32 i, Grafo g) {
    if (i > g->numeroVertices) {
        return (u32) -1;
    }
    return g->vertices[i]->grado;
}

u32 IndiceONVecino(u32 j, u32 k, Grafo g) {
    if (k >= g->numeroVertices || (k < g->numeroVertices && j >= g->vertices[k]->grado)) {
        return (u32) -1;
    }
    return g->vertices[k]->vecinos[j]->indice;
}
