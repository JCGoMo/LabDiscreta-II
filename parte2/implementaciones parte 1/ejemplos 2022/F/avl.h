#ifndef AVL_
#define AVL_
#include <stdbool.h>
#include "EstructuraGrafo.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "avl.h"
#include "get_line.h"

typedef struct avlnode_t
{
  u32 key;
  u32 value;
  struct avlnode_t* left;
  struct avlnode_t* right;
  u32 height;
}avlnode;

avlnode*
avl_init(void);

avlnode*
new_node(u32 key, u32 pos);

avlnode*
avl_insert(avlnode* tree,u32 key,u32 pos);

u32 
get_avlkey(avlnode* node);

u32
get_avlvalue(avlnode* node);

u32
get_height(avlnode* tree);

int
avl_balance(avlnode* tree);

bool
exists_in_avl(avlnode* tree,u32 key);

u32
find_avl_value(avlnode* tree,u32 key);

void
avl_destroy(avlnode* tree);

#endif