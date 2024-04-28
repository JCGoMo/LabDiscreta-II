#ifndef _ESTRUCTURAGRAFO_H
#define _ESTRUCTURAGRAFO_H

#include "u32.h"
#include <stdbool.h>
#define hashfunc(key, buckets) ((key) % (buckets))
/*
 * La representacion del grafo sera con una matriz de adyacencia ligeramente modificada
 * para que la misma admita indice de vertices distintos del habitual 0,...,n
 *
 * 
 */

typedef struct node *tree;

struct node{
  u32 name;
  u32 nat_ord_indx;
  tree 	left;
  tree right;
};

typedef struct vertices_aux{
	struct vertices_aux *next;	// Si el hash (clave) es el mismo, siga el relevo
	u32 key;			// Nombre del vertice
	u32 nat_pos;		// Indice en el orden natural
	bool is_occupyed;	// ¿Está ocupado?
	u32 grad;
}* vertices;

typedef struct GrafoSt_aux
{
	vertices *G;
	u32 n_vert;
    u32 m_lad;
	u32 delta;
	tree ord_nat;
} GrafoSt;

#endif
