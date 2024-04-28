#include "avl.h"
#define max(a, b) ((a > b) ? a : b)

u32 
get_height(avlnode* node){
  if(!node)
    return 0;
  return(node->height);
}


//Se alloca la memoria de un nodo del arbol y se manejan los errores
avlnode* 
new_node(u32 key,u32 value ){
  avlnode* node = calloc(1,sizeof(avlnode));
  if(!node)return NULL;
  node->key = key;
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return(node);
}

//Devuelve el balance del nodo. i.e la diferencia de altura entre el subarbol izquierdo y el derecho
int
avl_balance(avlnode* node){
  if(node == NULL)
    return 0;
  else
    return(get_height(node->left) - get_height(node->right));  
}

u32 
get_avlkey(avlnode* node){
  return(node->key);
}

u32
get_avlvalue(avlnode* node){
  return(node->value);
}


//Dada una key, retorna el value si esa key existe el mapa

u32
find_avl_value(avlnode* tree, u32 key){
  if(!tree)
    return ((1LL << 32) -1);
  u32 tree_key = get_avlkey(tree);
  if(tree_key == key)
    return get_avlvalue(tree);
  else if (key < tree_key)
    return(find_avl_value(tree->left,key));
  else
    return(find_avl_value(tree->right,key));
}

bool
exists_in_avl(avlnode* tree, uint32_t key){
  if(!tree)
    return false;
  if(key < get_avlkey(tree))
    return(exists_in_avl(tree->left,key));
  if(key > get_avlkey(tree))
    return(exists_in_avl(tree->right,key));
  return(true);
}

//Rota los nodos del subarbol de manera horaria
avlnode* 
right_rotation(avlnode* node){
  //Saving the pointers
  avlnode* left_node = node->left;
  avlnode* left_node_right_subtree = left_node->right;
  //Rotation
  left_node->right = node;
  node->left = left_node_right_subtree; 
  //Update the heights
  node->height = 1 + max(get_height(node->left),
                         get_height(node->right));
  left_node->height = 1 + max(get_height(left_node->left),
                              get_height(left_node->right));
  return left_node;
  }

//Rota los nodos del subarbol de manera antihoraria
avlnode*
left_rotation(avlnode* node){
  //Saving the pointers
  avlnode* right_node = node->right;
  avlnode* right_node_left_subtree = right_node->left;
  //Rotation
  right_node->left = node;
  node->right = right_node_left_subtree;
  //Update heights
  node->height = 1 + max(get_height(node->left),
                         get_height(node->right));
  right_node->height = 1 + max(get_height(right_node->left),
                               get_height(right_node->right));
  return right_node;
  }

avlnode*
avl_init(void){
  return NULL;
}

//Inserta un nodo con una key y un valor, si esa key no existe 
avlnode*
avl_insert(avlnode* tree, u32 key, u32 value){

  //Insercion desbalanceada
  if(!tree)
    return(new_node(key,value));
  if(key < get_avlkey(tree))
    tree->left = avl_insert(tree->left,key,value);
  else if(key > get_avlkey(tree))
    tree->right = avl_insert(tree->right,key,value);
  else
    return(tree);

  //Se actualiza la altura 
  tree->height = 1 + max(get_height(tree->left),get_height(tree->right));

  //Si el arbol esta desbalanceado hace las rotaciones correspondientes
  int balance = avl_balance(tree);
  if(balance > 1){
    if(key < get_avlkey(tree->left))
      return(right_rotation(tree));
    else{
      tree->left = left_rotation(tree->left);
      return(right_rotation(tree));
    }
  }else if(balance < -1){
    if(key > get_avlkey(tree->right))
      return(left_rotation(tree));
    else{
      tree-> right = right_rotation(tree->right);
      return(left_rotation(tree));
    } 
  }
    
  return(tree);
}


void
avl_destroy(avlnode* tree){

  if(!tree)
    return;
  if(tree->right)
    avl_destroy(tree->right);
  if(tree->left)
    avl_destroy(tree->left);
  free(tree);
}