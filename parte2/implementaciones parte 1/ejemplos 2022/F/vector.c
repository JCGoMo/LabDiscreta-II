#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"

typedef struct vector_t {
    int* data;
    int size;
    int count;
} vector_t;

vector vector_init() {
	vector v = (vector)malloc(sizeof(vector_t));
	if(!v) return NULL;
	v->data = NULL;
	v->size = 0;
	v->count = 0;
	return v;
}

unsigned int vector_size(vector v) {
	if (v == NULL || v->data == NULL) return 0;
	return v->count;
}

vector vector_add(vector v, int e) {
	if(!v){
		return NULL;
	}
	if (v->size == 0) {
		v->size = 10;
		v->data = calloc(v->size,sizeof(int));
		if(!v->data){
			return NULL;
		}
	}

	if (v->size == v->count) {
		v->size *= 2;
		int* temp = realloc(v->data, sizeof(int) * v->size);
		if(temp){
			v->data = temp; 
		}else{
			free(v->data);
			return NULL;
		}
	}

	v->data[v->count] = e;
	v->count++;
	return v;
}


int vector_get(vector v, int index) {
	if (v == NULL || v->data == NULL) return 2147483647;
	return v->data[index];
}

void vector_free(vector v) {
	if(!v) return;
	if(v->data != NULL)	free(v->data);
	free(v);
}

vector vector_copy(vector v) {
	vector r = vector_init();
	for(unsigned int i = 0; i < vector_size(v); i++) {
		vector_add(r, vector_get(v, i));
	}
	return r;
}


int compare(const void *_a, const void *_b) {
 
        unsigned int *a, *b;
        
        a = (unsigned int *) _a;
        b = (unsigned int *) _b;
        if (*a < *b )
        	return -1;
        else if (*a>*b)
        	return 1;
        else
        	return 0;
}

void vector_sort(vector v) {
	qsort(v->data, vector_size(v), sizeof(unsigned int), &compare);
}
