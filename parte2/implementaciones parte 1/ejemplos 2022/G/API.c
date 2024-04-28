#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

#define VECINOS_INIT 256
#define MAX_VERTEX 32

static u32 max(u32 i, u32 j, u32 k){
    u32 aux = (i <= j) ? j : i;
    return (aux <= k) ? k : aux;
}

static int cmp_func(const void *v1, const void *v2){
    vertex *v_1 = (vertex*) v1;
    vertex *v_2 = (vertex*) v2;
    //assert(v_1 != NULL && v_2 != NULL);
    return (*v_1)->nombre - (*v_2)->nombre;
}

Grafo ConstruccionDelGrafo(){
    Grafo G = malloc(sizeof(struct GrafoSt));
    if (G == NULL) { 
        printf("MALLOC ERROR\n");
        return NULL;
    }
    //assert(G != NULL);
    G->vertices = NULL;
    G->numVertices = 0;
    G->numLados = 0;
    G->delta = 0;
    u32 v1,v2;
    vertex v, v_1, v_2;

    char *buf = calloc(MAXLINESIZE,sizeof(char));
    if (buf == NULL){
        printf("CALLOC ERROR\n");
        //deberiamos hacer free en caso de error
        DestruccionDelGrafo(G);
        return NULL;
    }
    char *s_v1 = calloc(MAX_VERTEX,sizeof(char));
    if (s_v1 == NULL){
        printf("CALLOC ERROR\n");
        DestruccionDelGrafo(G);
        free(buf);
        //deberiamos hacer free en caso de error
        return NULL;
    }
    char *s_v2 = calloc(MAX_VERTEX,sizeof(char));
    if (s_v2 == NULL){
        printf("CALLOC ERROR");
        DestruccionDelGrafo(G);
        free(buf);
        free(s_v1);
        return NULL;
    }

    if (scanf("%s", buf) == -1) {
        printf("SCANF ERROR\n");
        DestruccionDelGrafo(G);
        free(buf);
        free(s_v1);
        free(s_v2);
        return NULL;
    }
    while (strcmp(buf, "c") == 0) {
        if (fgets(buf, MAXLINESIZE, stdin) == NULL) {
            printf("FGETS ERROR\n");
            DestruccionDelGrafo(G);
            free(buf);
            free(s_v1);
            free(s_v2);
            return NULL;
        }
        if (scanf("%s ", buf) == -1) {
            printf("SCANF ERROR\n");
            DestruccionDelGrafo(G);
            free(buf);
            free(s_v1);
            free(s_v2);
            return NULL;
        }
    }

    if (strcmp(buf, "p") == 0) {
        if (scanf("%s ", buf) == -1) {
            printf("SCANF ERROR\n");
            DestruccionDelGrafo(G);
            free(buf);
            free(s_v1);
            free(s_v2);
            return NULL;
        }
        if (strcmp(buf, "edge") == 0) {
            if (scanf("%s ", buf) == -1) {
                printf("SCANF ERROR\n");
                DestruccionDelGrafo(G);
                free(buf);
                free(s_v1);
                free(s_v2);
                return NULL;
            }
            G->numVertices = (u32)atoi(buf);
            if (scanf("%s ", buf) == -1) {
                printf("SCANF ERROR\n");
                DestruccionDelGrafo(G);
                free(buf);
                free(s_v1);
                free(s_v2);
                return NULL;
            }
            G->numLados = (u32)atoi(buf);
        } else {
            printf("Error: Grafo no válido\n");
            DestruccionDelGrafo(G);
            free(buf);
            free(s_v1);
            free(s_v2);
            return NULL;
        }
    } else {
        printf("Error: Grafo no válido\n");
        DestruccionDelGrafo(G);
        free(buf);
        free(s_v1);
        free(s_v2);
        return NULL;
    }
    G->vertices = array_init(G->numVertices);
    hash vertices_procesados = ht_create();
    for (u32 i = 0; i < G->numLados ; i++){

        if (scanf("%s ", buf) == -1) {
            printf("SCANF ERROR\n");
            ht_destroy(vertices_procesados);
            DestruccionDelGrafo(G);
            free(buf);
            free(s_v1);
            free(s_v2);
            return NULL;
        }
        if (strcmp(buf, "e") == 0) {
            if (scanf("%s ", s_v1) == -1) {
                printf("SCANF ERROR\n");
                ht_destroy(vertices_procesados);
                DestruccionDelGrafo(G);
                free(buf);
                free(s_v1);
                free(s_v2);
                return NULL;
            }
            v1 = (u32)atoi(s_v1);
            if (scanf("%s ", s_v2) == -1) {
                printf("SCANF ERROR\n");
                ht_destroy(vertices_procesados);
                DestruccionDelGrafo(G);
                free(buf);
                free(s_v1);
                free(s_v2);
                return NULL;
            }
            v2 = (u32)atoi(s_v2);
        } else {
            printf("Error de formato\n");
            ht_destroy(vertices_procesados);
            DestruccionDelGrafo(G);
            free(buf);
            free(s_v1);
            free(s_v2);
            return NULL;
        }

        v_1 = ht_get(vertices_procesados, (const char *) s_v1);
        v_2 = ht_get(vertices_procesados, (const char *) s_v2);
        if (v_1 == NULL){
            v_1 = malloc(sizeof(struct Vertice));
            if (v_1 == NULL){
                printf("MALLOC ERROR\n");
                ht_destroy(vertices_procesados);
                DestruccionDelGrafo(G);
                free(buf);
                free(s_v1);
                free(s_v2);
                return NULL;
            }
            v_1->vecinos = array_init(VECINOS_INIT);
            v_1->nombre = v1;
            v_1->grado = 0;
            ht_set(vertices_procesados, s_v1, v_1);

            G->vertices = array_append(G->vertices, v_1,G->numVertices/2);
        }
        if (v_2 == NULL){
            v_2 = malloc(sizeof(struct Vertice));
            v_2->vecinos = array_init(VECINOS_INIT);
            v_2->nombre = v2;
            v_2->grado = 0;
            ht_set(vertices_procesados, s_v2, v_2);

            G->vertices = array_append(G->vertices, v_2, G->numVertices/2);
        }
        //assert(v_1 != NULL);
        //assert(v_2 != NULL);
        v_1->grado++; v_2->grado++; //los lados no se repiten
        v_1->vecinos = array_append(v_1->vecinos, v_2,G->numLados); 
        v_2->vecinos = array_append(v_2->vecinos, v_1,G->numLados);
        G->delta = max(G->delta, v_1->grado, v_2->grado);

    }
    qsort(
        array_elems(G->vertices), 
        (size_t) G->numVertices, 
        sizeof(vertex), 
        cmp_func);

    for (u32 i = 0; i < G->numVertices ; i++){
        v = (vertex) array_take(G->vertices,i);
        v->indice = i;
    }
    ht_destroy(vertices_procesados);
    free(buf);
    buf = NULL;

    free(s_v1);
    s_v1 = NULL;

    free(s_v2);
    s_v2 = NULL;
    return G;
}

void DestruccionDelGrafo(Grafo G){
    if (G != NULL){

        vertex v; 
        vertex *vecinos;

        for (u32 i=0; i < G->numVertices; i++){
            v = array_take(G->vertices, i);
            if (v != NULL && v->vecinos != NULL) {
                vecinos = (vertex *) array_elems(v->vecinos);
                free(vecinos);
                vecinos = NULL;
                free(v->vecinos);
                v->vecinos = NULL;
            }
        }
        if (G->vertices != NULL){
            G->vertices = array_destroy(G->vertices);
            G->vertices = NULL;
        }
        
        free(G); 
        G = NULL;
    }
    ////assert(G == NULL);
}

u32 NumeroDeVertices(Grafo G){
    //assert(G != NULL);
    return G->numVertices;
}
u32 NumeroDeLados(Grafo G){
    //assert(G != NULL);
    return G->numLados;
}
u32 Delta(Grafo G){
    //assert(G != NULL);
    return G->delta;
}

u32 Nombre(u32 i, Grafo G){
    assert(G != NULL);
    vertex vertice = (vertex) array_take(G->vertices, i);
    assert(vertice != NULL);
    return vertice->nombre;
}
u32 Grado(u32 i, Grafo G){
    //assert(G != NULL);
    vertex vertice = (vertex) array_take(G->vertices, i);
    //assert(vertice != NULL);
    return vertice->grado;
}

// Devuelve el indice del j-esimo vecino del vertice con index k 
u32 IndiceONVecino(u32 j, u32 k, Grafo G){
    if (k < G->numVertices){
        vertex vertice = (vertex) array_take(G->vertices, k);
        if (j < vertice->grado){
            vertex jVecino = (vertex) array_take(vertice->vecinos, j);
            return jVecino->indice;
        }
    }
    return (u32) MAXSIZE;
}
