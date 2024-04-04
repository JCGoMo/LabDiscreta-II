#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdbool.h>

typedef struct verticeSt *list_elem;
typedef struct _node * list;

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "EstructuraGrafo.h"

//Constructors
list empty_list();
/* Create list of type list_elem */
list addl_list(list l, list_elem e);
/* add element e to the beginning of the list*/

//Operations
bool is_empty_list(list l);
/* Return True if list is empty */

list_elem head_list(list l);
/* Return first elem of list l */

list tail_list(list l);
/* remove first element of list l */

list addr_list(list l, list_elem e);
/* add an element to the end of the list */

unsigned int length_list(list l);
/* Return the size of list l*/

list concat_list(list l, list l1);
/* add to the end of the list l the elements of l1*/

list_elem index_list(list l, unsigned int n);
/* Returns the element of the n-posicion to list l*/

list take_list(list l, unsigned int n);
/* removes all elements from list l located in positions greater than or equal to n */

list drop_list(list l, unsigned int n);
/* removes all elements from list l located in positions less than to n*/

list_elem search_list(list l, u32 e);
/* function created to be used with graphs specifically */
/* Search for some vertex (list element) whose name is the value of e */
/* returns the vertex or null if not found */

list copy_list(list l);
/* returns a copy of list l*/

//Destroy
list destroy_list(list l);
/*Destroy list l*/

#endif
