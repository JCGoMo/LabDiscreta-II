#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "adjlist.h"
#include "list.h"

struct st_adjlist
{
    list *elems;           // Arreglo de elementos
    unsigned int size;     // Cantidad de elementos en la lista
    unsigned int capacity; // Capacidad actual del arreglo elems
};

adjlist empty_adjlist()
{
    struct st_adjlist *l;
    l = malloc(sizeof(struct st_adjlist));
    l->elems = calloc(50, sizeof(list));
    l->size = 0;
    l->capacity = 50;
    return l;
}
adjlist adjaddr(list e, adjlist l)
{
    if (l->size == l->capacity)
    {
        l->capacity += 2 * l->capacity;
        l->elems = realloc(l->elems, l->capacity * sizeof(list));
    }
    l->elems[l->size] = e;
    l->size++;
    return l;
}

adjlist adjaddat(list *e, unsigned int n, adjlist l)
{
    while (l->capacity < n || l->size == l->capacity)
    {
        l->capacity += 2 * l->capacity;
        l->elems = realloc(l->elems, l->capacity * sizeof(list));
    }
    l->elems[n] = e;
    l->size++;
    return l;
}

adjlist adjaddrtoelem(adjlist l, unsigned int n, list_elem e)
{
    l->elems[n] = addr(e, l->elems[e]);
    return l;
}

list adjlist_index(adjlist l, unsigned int n)
{
    if (n < l->size)
    {
        return NULL;
    }
    return l->elems[n];
}

unsigned int adjlength(adjlist l)
{
    return l->size;
}

bool adjis_empty(adjlist l)
{
    return l->size == 0;
}

void destroyadjl(adjlist l)
{
    if (l != NULL)
    {
        free(l->elems);
        free(l);
        l = NULL;
    }
}

void adjlist_dump(adjlist l)
{
    printf("length: %u\n", adjlength(l));
    for (unsigned int i = 0; i < l->capacity /*adjlength(l)*/; ++i)
    {
        printf("[%u]:", i);
        int j = i;
        while (adjlist_index(l, j) != NULL)
        {
            list_dump(adjlist_index(l, ));
        }
        // printf("%u", length(adjlist_index(l, i)));
        /*for (unsigned int j = 0; j < length(adjlist_index(l, i)); ++j)
         {

         }*/
        printf("\n");
    }
}

list *getArray(adjlist l)
{
    return l->elems;
}