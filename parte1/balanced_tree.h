
#include <stdio.h>
#include <stdlib.h>
#include "APIG24.h"
#include "list.h"


typedef struct node* balanced_tree;

balanced_tree insert(balanced_tree tree, u32 key, u32 value);

void printInorder(balanced_tree tree);

void keys_to_array_inorder(balanced_tree tree, u32 *arr);
/* Crea un arreglo de keys en orden creciente. 
 * Guarda el tamaño del arreglo en i. El llamador debería asegurar que
 * su valor inicial sea 0. 
 */

void printInorder(balanced_tree tree);

u32 num_of_nodes(balanced_tree tree);
/* Retorna la cantidad de nodos del árbol
*/

void data_to_array_inorder(balanced_tree tree, list* adj_list);
/* Retorna un arreglo de listas con los vecinos de cada vértice.
 * Importante: Las listas serán las mismas que las de los nodos del árbol.
 */


balanced_tree destroy_tree(balanced_tree tree);
/* Destruye todo el árbol, con la excepción de la estructura que mantenga los
 * vecinos de cada vértice.
 *
 */
