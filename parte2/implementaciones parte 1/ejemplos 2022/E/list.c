#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"
 
struct _node {
    list_elem elem;
    list next;
};

list empty_list(){
    return NULL;
}

list addl_list(list l, list_elem e){
    list p = malloc(sizeof(struct _node));
    p->elem = e;
    p->next = l;
    return p;
}

bool is_empty_list(list l){
    bool b = l == NULL;
    return b;
}

list destroy_list(list l){
    list rm = l;
    while(!is_empty_list(l)){
        l = rm->next;
        free(rm->elem->vecinos);
        free(rm->elem);
        free(rm);
        rm = l;
    }
    return NULL;
}

list_elem search_list(list l, u32 e){
    list aux = l;
    while(aux != NULL){
        if(e == aux->elem->nombre){
            return aux->elem;
        }
        aux = aux->next;
    }
    return NULL;
}

list copy_list_list(list l){
    list l_copy = malloc(sizeof(struct _node));
    list init = l_copy;
    while (l != NULL){
        l_copy->next = malloc(sizeof(struct _node));
        l_copy->elem = l->elem;
        l = l->next;
        l_copy = l_copy->next;
    }
    free(l_copy);
    l_copy = NULL;
    return init;
}

list_elem head_list(list l){
    assert(!is_empty_list(l));
    return l->elem;
}

list tail_list(list l){
    assert(!is_empty_list(l));
    list p = l->next;
    free(l);
    l = NULL;
    return p;
}

list addr_list(list l, list_elem e){
    list p, q;
    p = malloc(sizeof(struct _node));
    p->next = NULL;
    p->elem = e;
    if(!is_empty_list(l)){
        q = l;
        while(q!=NULL){
            q = q->next;
        }
        q = p;
    }
    else{
        l = p;
    }   
    return l;
} 

unsigned int length_list(list l){
    unsigned int i = 0u;
    list p = l;
    while(p != NULL){
        p = p->next;
        i = i + 1u;
    }
    return i;
}

list concat_list(list l,list l1){
    list p = copy_list(l);
    list ret = p;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = copy_list(l1); 
    return ret;
}

list_elem index_list(list l, unsigned int n){
    assert(n < length_list(l));
    list p = l;
    unsigned int i = 0u;
    while(i < n)
    {
        p = p->next;
        i = i + 1u;
    }
    return p->elem;
}

list take_list(list l, unsigned int n){
    list p =l;
    list t = empty_list();
    for (unsigned int i = 0u; i < n ;i++){
        t = addr_list(t,l->elem);
        p = p->next;
    }
    return t;
}

list drop_list(list l, unsigned int n){
    list d = empty_list();
    list p = l;
    for(unsigned int i=0u;i < n; i++){
        p = p->next;
    }
    for (unsigned int i=n; i < length_list(l); i++){
        d = addr_list(d,p->elem);
        p = p->next;
    }
    return d;
}

list copy_list(list l){
    list l_copy = malloc(sizeof(struct _node));
    list init = l_copy;
    while (l != NULL){
        l_copy->next = malloc(sizeof(struct _node));
        l_copy->elem = l->elem;
        l = l->next;
        l_copy = l_copy->next;
    }
    free(l_copy);
    l_copy = NULL;
    return init;
}
