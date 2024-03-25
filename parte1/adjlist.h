#ifndef ADJLIST_H
#define ADJLIST_H

#include <stdio.h>
#include <stdlib.h>
#include "APIG24.h"
#include "list.h"

typedef struct st_adjlist *adjlist;

adjlist empty_adjlist();
/* Crea una lista vacía
 *
 */

void destroyadjl(adjlist l);
/* Libera memoria en caso que sea necesario
 *
 */

// Operations

bool adjis_empty(adjlist l);
/* Devuelve True si l es vacía
 *
 */

adjlist adjaddr(list e, adjlist l);
/* Devuelve la lista con los elementos de l añadiendo al elemento e al final de la lista
 *
 */

unsigned int adjlength(adjlist l);
/* Devuelve la cantidad de elementos de la lista l
 *
 */

list adjlist_index(adjlist l, unsigned int n);
/*
 * Devuelve el n-ésimo elemento de la lista l comenzando desde cero
 */

void adjlist_dump(adjlist l);

list *getArray(adjlist l);

adjlist adjaddrtoelem(adjlist l, unsigned int n, list_elem e);

adjlist adjaddat(list *e, unsigned int n, adjlist l);

#endif