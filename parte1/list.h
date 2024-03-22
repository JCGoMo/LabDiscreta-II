#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int list_elem;

typedef struct st_list *list;

list empty_list();
/* Crea una lista vacía
 *
 */

list addl(list_elem e, list l);
/* Devuelve la lista resultante de agregar el elemento e por la izquierda a la lista l
 *
 */

void destroy(list l);
/* Libera memoria en caso que sea necesario
 *
 */

// Operations

bool is_empty(list l);
/* Devuelve True si l es vacía
 *
 */

list addr(list_elem e, list l);
/* Devuelve la lista con los elementos de l añadiendo al elemento e al final de la lista
 *
 */

unsigned int length(list l);
/* Devuelve la cantidad de elementos de la lista l
 *
 */

list_elem list_index(list l, unsigned int n);
/* PRE: length(l)>n
 * Devuelve el n-ésimo elemento de la lista l comenzando desde cero
 */

void list_dump(list l);

#endif
