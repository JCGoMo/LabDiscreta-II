#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int list_elem;

typedef struct st_list *list;

// Crea una lista vacía
list empty_list();

// Libera memoria 
void destroy(list l);

// Devuelve True si l es vacía
bool is_empty(list l);

// Devuelve la lista con los elementos de l añadiendo al elemento e al final de la lista
list addr(list_elem e, list l);

// Devuelve la cantidad de elementos de la lista l
unsigned int length(list l);

// Devuelve el n-ésimo elemento de la lista l comenzando desde cero (PRE: length(l)>n)
list_elem list_index(list l, unsigned int n);

// Imprime la lista l
void list_dump(list l);

#endif
