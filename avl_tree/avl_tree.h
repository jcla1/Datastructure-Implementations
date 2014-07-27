#ifndef DATASTRUCTURES_AVL_TREE_H_
#define DATASTRUCTURES_AVL_TREE_H_

#include "bst/bst.h"

typedef struct avl_node avl_node;
struct avl_node {
    avl_node *left, *right, *parent;
    void *value;
    /* describes max(left_height, right_height) */
    short height;
};


typedef struct avl_tree avl_tree;
struct avl_tree {
    tree_cmp_fn cmp;
    avl_node *root;
};

avl_tree *avl_create(tree_cmp_fn cmp);
void avl_destroy(avl_tree *tree);

void avl_insert(avl_tree *tree, void *value);
void *avl_delete(avl_tree *tree, void *value);

int avl_get_height(avl_node *node);
int avl_get_balance(avl_node *node);

static void avl_destroy_nodes(avl_node *node);
static void avl_left_rotate(avl_tree *tree, avl_node *x);
static void avl_right_rotate(avl_tree *tree, avl_node *y);

#endif // DATASTRUCTURES_AVL_TREE_H_