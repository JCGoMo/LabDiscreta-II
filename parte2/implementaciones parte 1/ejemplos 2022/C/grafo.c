#include <stdio.h>
#include "EstructuraGrafo.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "dimacs.h"

static void agregarVerticesCalculandoGrados(Grafo newGrafo, dimacsData* data) {
    newGrafo->numeroVertices = data->n;
    newGrafo->numeroDeLados = data->m;
    newGrafo->vertices = calloc(1, sizeof(vertice*) * data->n);
    u32 i = 0;
    for (u32 j=0; j<data->m; j++) {
        for(u32 k=0; k<2; k++) {
            u32 posV = posDeVerticeEnArreglo(newGrafo->vertices, i, data->lados[j][k]);
            if (posV == -1u) { // Vertice no fue guardado aún.
                /* printf("Encontré nuevo vértice: %u\n", data->lados[j][k]); */
                vertice* v = malloc(sizeof(vertice));
                v->grado = 1;
                v->nombre = data->lados[j][k];
                v->vecinos = NULL;
                newGrafo->vertices[i] = v;
                i += 1;
            } else { // Se encontró vértice en posV.
                newGrafo->vertices[posV]->grado += 1;
            }
        }
    }
}

Grafo ConstruccionDelGrafo() {
    printf("Leyendo stdin.\n");
    dimacsData* data = obtenerDimacsDataDesdeStdIn();
    Grafo newGrafo=malloc(sizeof(GrafoSt));
    printf("Agregando Vertices y Calculando sus grados.\n");
    agregarVerticesCalculandoGrados(newGrafo, data);
    printf("Ordenando vértices.\n");
    ordenarVertices(newGrafo->vertices, newGrafo->numeroVertices);
    printf("Asignando índices a los vértices.\n");
    asignarIndice(newGrafo->vertices, newGrafo->numeroVertices);
    printf("Inicializando vecinos y calculando Delta.\n");
    newGrafo->delta = inicializarVecinosYObtenerDelta(
            newGrafo->vertices,
            newGrafo->numeroVertices
            );
    printf("Agregando vecinos a cada vértices.\n");
    agregarVecinos(data, newGrafo->vertices, newGrafo->numeroVertices);

    printf("Limpiando.\n");
    destruirDimacsData(data);
    data = NULL;
    return newGrafo;
}

void DestruccionDelGrafo(Grafo G) {
    for (u32 i = 0; i < G->numeroVertices; i++) {
        free(G->vertices[i]->vecinos);
        free(G->vertices[i]);
    }
    free(G->vertices);
    free(G);
};

u32 NumeroDeVertices(Grafo G) {
    return G->numeroVertices;
};

u32 NumeroDeLados(Grafo G) {
    return G->numeroDeLados;
};

u32 Delta(Grafo G) {
    return G->delta;
};
