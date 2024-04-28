#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "APIG24.h"

void printGrafo(Grafo G)
{
    for (unsigned int i = 0; i < G->num_vertexs; ++i)
    {
        printf("Vertice %u -> Cantidad de vecinos: ", i);
        printf("%u \n Lista de vecinos:", length(G->edges[i]));
        list_dump(G->edges[i]);
        printf("\n");
        printf("Color vertice %u = %u ", i, G->colors[i]);
        printf("\n");
        
    }
    printf("Delta: %u \n",G->delta);

}

int main(void)
{
    // printf("expected: 1999999 vertices y 10123123 lados\n"); <- si es R1999999_10123123_1

    clock_t inicio, final;
    color *export_colores = NULL;
    color *import_colores = NULL;

    long span;
    inicio = clock(); // Tiempo de cpu usado por proceso

    Grafo G = ConstruirGrafo();

    export_colores = calloc(G->num_vertexs, sizeof(color));
    import_colores = calloc(G->num_vertexs, sizeof(color));

    for(u32 i = 0; i < G->num_vertexs; i++){
        import_colores[i] = i+100;
    }

    for(u32 i = 0; i < G->num_vertexs; i++){
        AsignarColor(i+10,i,G);
    }

    ExtraerColores(G,export_colores);
    printf("Colores exportados: \n");
    printf("[");
    for(u32 i = 0; i < G->num_vertexs; i++){
        if(i < G->num_vertexs){
            printf("%u ,", export_colores[i]);
        }
        else{
            printf("%u ]\n", export_colores[i]);
        }
    }

    ImportarColores(import_colores,G);
    printf("Colores importados: \n");
    printf("[");
    for(u32 i = 0; i < G->num_vertexs-1; i++){
        printf("%u, ", import_colores[i]);
    }
    printf("%u]\n", import_colores[G->num_vertexs-1]);


    u32 index = Vecino(1, 1, G);    // Harcoded
    printf("Vecino numero 2 del vertice 1: %u \n", index);

    if (G != NULL)
    {
        printGrafo(G);
        printf("se obtuvo: %u vertices y %u lados\n\n\n", NumeroDeVertices(G), NumeroDeLados(G));  
    }
    else
    {
        printf("No se pudo cargar el grafo G\n");
    }
    
    final = clock();

    span = (final - inicio) / CLOCKS_PER_SEC;

    printf("Tardaste %lu seg en cargar el grafo\n", span);
    printf(span <= 30 ? "tiempo aceptable\n" : "fracaso, tardo banda\n");

    DestruirGrafo(G);
    free(export_colores);
    free(import_colores);
    

    return 0;
}
