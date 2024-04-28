#ifndef VECTOR_H__
#define VECTOR_H__
#include "vector.h"


typedef struct vector_t* vector;

vector vector_init();
unsigned int vector_size(vector);
vector vector_add(vector, int);
int vector_get(vector, int);
void vector_free(vector);
void vector_sort(vector);
#endif