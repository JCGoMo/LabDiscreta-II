#ifndef _ESTRUCTURA_GRAFO_H
#define _ESTRUCTURA_GRAFO_H

#include <stdio.h>
#include <stdbool.h>

#include "list.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

typedef struct verticeSt *Vertice;

struct GrafoSt {
    u32 cant_v;
    u32 cant_l;
    u32 delta;
    list *hashTable; //Hashtable de vertices
    Vertice *orden; //El orden inicial es el que se ingresa a la Hashtable
};


struct verticeSt{
    u32 indice;
    u32 nombre;
    u32 grado;
    Vertice *vecinos;
    u32 tamArray;
};

u32 funcion_hash(u32 cantidad, u32 nombre);

Vertice crearVertice(u32 nombre);

void agregarVecinos(Vertice v1, Vertice v2);

//void imprimirVecinos(Vertice v);

void agregarLado(Grafo G, u32 nombre1, u32 nombre2, u32* indice);

int compOrdenNatural(const void *a, const void *b);

/*
Funciones del grafo
*/

/*2 problemas:
* Representacion interna de vertices
* Una estructura que agrupe todos los vertices
*/

/*
hash codifica cualquier tipo de dato en una codificacion
*/

/*
representacion de los vertices
busqueda de los vecinos
el orden artificial y natural
*/

#endif