#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

static void next_line() {
    char initial;
    initial = fgetc(stdin);
    while(initial != '\n') {
        initial = fgetc(stdin);
    }
}

static bool is_edge() {
    bool b = false;
    char g[5];
    int res;
    res = scanf("%s", g);
    if (res == 1) {
        if (strcmp(g, "edge") == 0 && fgetc(stdin) == ' ') {
            b = true;
        }
    }
    return b;
}

static int is_cpline() {
    int b = -1;
    char g[2];
    int res;
    res = scanf("%s", g);
    if (res == 1) {
        if (strcmp(g, "c") == 0) {
            b = 0;
        }
        if (strcmp(g, "p") == 0) {
            b = 1;
        }
    }
    return b;
}

static bool is_eline() {
    bool b = false;
    char c = fgetc(stdin);
    if (c=='e') {
        c = fgetc(stdin);
        if (c==' ') {
            b = true;
        }
    }
    return b;
}

static int sort_tuple(const void *a, const void *b) {
    u32 l = ((struct tupla_s *)a)->v1;
    u32 r = ((struct tupla_s *)b)->v1;
    int res;
    if (l < r) {
        res = -1;
    }
    else if (l > r) {
        res = 1;
    }
    else {
        res = 0;
    }
    return res;
}

static void set_name_degree_neighbors_delta(u32 n_edge, u32 n_vertix, u32* t_name, u32* t_degree,
                                            u32** t_neighbors, tupla s_struct, GrafoSt* graph) {
    u32 i = 0u, j = 0u, init = 0u, c = 0u, max = 0u;
    while(i < n_vertix) {
        t_name[i] = s_struct[j].v1;
        init = j;
        while (j < n_edge*2u && t_name[i] == s_struct[j].v1) {
            j++;
        }
        t_neighbors[i] = calloc(j-init, sizeof(u32));
        c = init;
        for(u32 k = 0u; k < j-init; k++) {
            t_neighbors[i][k] = s_struct[c].v2;
            c++;
        }
        if (max < j-init) {
            max = j-init;
        }
        t_degree[i] = j-init;
        i++;
    }
    graph->delta = max;
    graph->nombres = t_name;
    graph->grados = t_degree;
    graph->vecinos = t_neighbors;
}

Grafo ConstruccionDelGrafo() {
    GrafoSt * grafo = NULL;
    u32 cant_vertices = 0u, cant_lados = 0u, v1 = 0u, v2 = 0u, res = 0u, i = 0u, t;

    int check = is_cpline();

    // ignorar los c
    while(check == 0) {
        next_line();
        check = is_cpline();
    }

    if (check != 1) {
        fprintf(stderr, "Invalid format.\n");
        return grafo;
    }

    // leer p sacar valores de m y n, no pedimos memoria
    if (is_edge()) {
        res = scanf("%u", &cant_vertices);
        if (res != 1) {
            fprintf(stderr, "Invalid format.\n");
            return grafo;
        }
        res = scanf("%u", &cant_lados);
        if (res != 1) {
            fprintf(stderr, "Invalid format.\n");
            return grafo;
        }
        res = scanf("%u", &t);
        if (res == 1) {
            fprintf(stderr, "Invalid format.\n");
            return grafo;
        }
    } else {
        fprintf(stderr, "Invalid format.\n");
        return grafo;
    }

    // leer los m lados: por cada linea e (lado), agregamos dos tuplas a la estructura
    tupla super_estructura = NULL;
    super_estructura = calloc(cant_lados*2u, sizeof(struct tupla_s));
    while (i < cant_lados*2u) {
        if (is_eline()) {
            res = scanf("%u", &v1);
            if (res != 1) {
                fprintf(stderr, "Invalid format..\n");
                free(super_estructura);
                return grafo;
            }
            res = scanf("%u", &v2);
            if (res != 1) {
                fprintf(stderr, "Invalid format...\n");
                free(super_estructura);
                return grafo;
            }
            super_estructura[i].v1 = v1;
            super_estructura[i].v2 = v2;
            super_estructura[i+1].v1 = v2;
            super_estructura[i+1].v2 = v1;
            res = scanf("%u", &t);
            if (res == 1) {
                fprintf(stderr, "Invalid format....\n");
                free(super_estructura);
                return grafo;
            }
        } else {
            fprintf(stderr, "Invalid format.....\n");
            free(super_estructura);
            return grafo;
        }
        i += 2u;
    }

    qsort((void*)super_estructura, cant_lados*2u, sizeof(struct tupla_s), sort_tuple);

    super_estructura = (struct tupla_s*) super_estructura;

    // pedir memoria para type Grafo (puntero a GrafoSt)
    grafo = malloc(sizeof(GrafoSt));

    // completamos los campos n y m del TAD
    grafo->n = cant_vertices;
    grafo->m = cant_lados;

    // pedir memoria para grafo->nombres
    u32* table_names = NULL;
    table_names = calloc(cant_vertices, sizeof(u32*));

    // pedir memoria para grafo->grados
    u32* degree_of = NULL;
    degree_of = calloc(cant_vertices, sizeof(u32));

    // pedir memoria para grafo->vecinos
    u32** neighbors_of = NULL;
    neighbors_of = calloc(cant_vertices, sizeof(u32*));

    // seteo de los campos grafo->nombres, grafo->grados, grafo->vecinos y grafo->delta
    set_name_degree_neighbors_delta(cant_lados, cant_vertices, table_names, degree_of, neighbors_of, super_estructura, grafo);

    //destruir la superestructura
    free(super_estructura);

    return grafo;
}

static void destroy_neighbors(Grafo G) {
    for(u32 i = 0u; i < G->n; i++) {
        free(G->vecinos[i]);
    }
    free(G->vecinos);
    G->vecinos = NULL;
}

void DestruccionDelGrafo(Grafo G) {
    if (G != NULL) {
        destroy_neighbors(G);
        free(G->nombres);
        G->nombres = NULL;
        free(G->grados);
        G->grados = NULL;
        free(G);
        G = NULL;
    }
}

u32 NumeroDeVertices(Grafo G) {
    return G->n;
}

u32 NumeroDeLados(Grafo G) {
    return G->m;
}

u32 Delta(Grafo G) {
    return G->delta;
}

u32 Nombre(u32 i,Grafo G) {
    return G->nombres[i];
}

u32 Grado(u32 i,Grafo G) {
    u32 r = 4294967295u;

    if (i < G->n) {
        r = G->grados[i];
    }

    return r;
}

u32 IndiceONVecino(u32 j,u32 k,Grafo G) {
    u32 r = 4294967295u;

    if (k < G->n && j < G->grados[k]) {
        r = G->vecinos[k][j]; 
    }

    return r;
}