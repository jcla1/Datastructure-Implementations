#ifndef DATASTRUCTURES_AVL_TREE_H_
#define DATASTRUCTURES_AVL_TREE_H_

#include "bst/bst.h"

typedef struct avl_node avl_node;
struct avl_node {
    avl_node *left, *right, *parent;
    void *value;
    short balance;
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

#endif // DATASTRUCTURES_AVL_TREE_H_