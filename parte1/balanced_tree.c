#include <stdio.h>
#include <stdlib.h>
#include "balanced_tree.h"
#include "list.h"

// An AVL tree node
struct node
{
    u32 key;
    list data;
    struct node *left;
    struct node *right;
    u32 height;
};

static int max(int a, int b);

static int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

static int max(int a, int b)
{
    return (a > b) ? a : b;
}

static struct node *newNode(int key)
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->key = key;
    node->data = empty_list();
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

static struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

static struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
static int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

balanced_tree insert(balanced_tree node, u32 key, u32 value)
{
    
    if (node == NULL)
    {
        node = newNode(key);
        node->data = addr(value, node->data);
        return (node);
    }
    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else
        node->data = addr(value, node->data);

    
    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

/* Given a binary tree, print its nodes in inorder*/
void printInorder(balanced_tree node)
{
    if (node == NULL)
        return;

    printInorder(node->left);
    printf("%d ", node->key);
    printInorder(node->right);
}

u32 num_of_nodes(balanced_tree tree)
{
    if (tree == NULL){
        return 0;
    }
    return 1 + num_of_nodes(tree->left) + num_of_nodes(tree->right);
}

static void keys_to_array_inorder_rec(balanced_tree tree, u32 *arr, u32 *i)
{
    if (tree == NULL)
        return;

    keys_to_array_inorder_rec(tree->left, arr, i);
    arr[*i] = tree->key;
    ++*i;
    keys_to_array_inorder_rec(tree->right, arr, i);
}

void keys_to_array_inorder(balanced_tree tree, u32 *arr)
{
    u32 i = 0;
    keys_to_array_inorder_rec(tree, arr, &i);
}


static void data_to_array_rec(balanced_tree tree, list *adj_list, u32 *i)
{
    if (tree == NULL)
        return;

    data_to_array_rec(tree->left, adj_list, i);
    adj_list[*i] = tree->data; 
    ++*i;
    data_to_array_rec(tree->right, adj_list, i);
}

void data_to_array_inorder(balanced_tree tree, list *adj_list)
{
    u32 i = 0;
    data_to_array_rec(tree, adj_list, &i);
}


balanced_tree destroy_tree(balanced_tree tree){
    if (tree != NULL){
        tree->left = destroy_tree(tree->left);
        tree->right = destroy_tree(tree->right);
        destroy(tree->data);
        free (tree);
        tree = NULL;
    }
    return NULL;
}
