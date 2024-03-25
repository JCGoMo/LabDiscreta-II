#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "list.h"

struct st_list
{
    list_elem *elems;      // Arreglo de elementos
    unsigned int size;     // Cantidad de elementos en la lista
    unsigned int capacity; // Capacidad actual del arreglo elems
};

list empty_list()
{
    struct st_list *l;
    l = malloc(sizeof(struct st_list));
    l->elems = calloc(50, sizeof(list_elem));
    l->size = 0;
    l->capacity = 50;
    return l;
}
list addr(list_elem e, list l)
{
    if (l->size == l->capacity)
    {
        l->capacity += 2 * l->capacity;
        l->elems = realloc(l->elems, l->capacity * sizeof(list_elem));
    }
    l->elems[l->size] = e;
    l->size++;
    return l;
}

list_elem list_index(list l, unsigned int n)
{
    assert(n < l->size);
    return l->elems[n];
}

unsigned int length(list l)
{
    return l->size;
}

bool is_empty(list l)
{
    return l->size == 0;
}

void destroy(list l)
{
    if (l != NULL)
    {
        free(l->elems);
        free(l);
        l = NULL;
    }
}

void list_dump(list l)
{
    printf("[");
    for (unsigned int i = 0; i < l->size - 1; ++i)
    {
        printf("%u,", l->elems[i]);
    }
    printf("%u]\n", l->elems[l->size - 1]);
}
