
#ifndef __array_H__
#define __array_H__

#include "u32.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Array *array;

array array_init(u32 cap_init);

array array_append(array s, void* e,  u32 m);

array array_destroy(array s);

void *array_take(array s, u32 i);

void **array_elems(array s);

#endif