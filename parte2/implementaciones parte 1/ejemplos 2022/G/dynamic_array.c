#include "dynamic_array.h"

struct Array{
    void **elems;    
    u32 size;
    u32 capacity;
};

array array_init(u32 cap_init){
    array n = malloc(sizeof(struct Array));
    if (n == NULL) {
        printf("MALLOC ERROR\n");
        return NULL;
    }
    n->elems = calloc(cap_init,sizeof(void*));
    n->size = 0u;
    n->capacity = cap_init;
    return n;
}

array array_append(array s, void* e, u32 m){
    if (s->size == s->capacity){
        s->capacity = s->capacity * 2 > 2*m ? 2*m : s->capacity * 2; //por hand-shaking lemma
        s->elems = realloc(s->elems,(s->capacity) * sizeof(void *));
    }
    s->elems[s->size] = e;
    ++s->size;
    return s;
}

void *array_take(array s,u32 i){
    assert(s != NULL);
    //assert(i < s->size);
    return s->elems[i];
}

void **array_elems(array s){
    return (s->elems);
}

array array_destroy(array s){
    if (s != NULL){
        for (u32 i = 0; i < s->size; i++){
            if (s->elems[i] != NULL){
                free(s->elems[i]);
                s->elems[i] = NULL; 
            }
        }
        free(s->elems);
        s->elems = NULL;
        free(s);
        s = NULL;
    }
    return s;
}

