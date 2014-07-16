#include <stdlib.h>

#include "bst.h"

tree_node *bst_search_node(bst *tree, void *value) {
    tree_node *cur;
    int comp_res;

    cur = tree->root;
    while(cur != NULL) {
        comp_res = tree->cmp(cur->value, value);

    if(comp_res == 0)
        return cur;
    else if(comp_res < 0)
        cur = cur->left;
    else
        cur = cur->right;
    }

    return NULL; // value not present
}

void bst_insert_node(bst *tree, tree_node *node) {
    tree_node *cur, *prev;
    int comp_res;

    if(tree->root == NULL) {
        tree->root = node;
        return;
    }

    prev = NULL;
    cur = tree->root;

    while(cur != NULL) {
        prev = cur;
        comp_res = tree->cmp(cur->value, node->value);

    if(comp_res <= 0)
        cur = cur->left;
    else
        cur = cur->right;
    }

    node->parent = prev;

    if(comp_res == 0)
        prev->left = node;
    else
        prev->right = node;
}

void bst_traverse(bst *tree, tree_traverse_fn fn) {
    if(tree->root != NULL)
        return;

    bst_sub_traverse(tree->root, fn);
}

static void bst_sub_traverse(tree_node *node, tree_traverse_fn fn) {
    if(node->left != NULL)
        bst_sub_traverse(node->left, fn);

    fn(node->value);

    if(node->right != NULL)
        bst_sub_traverse(node->right, fn);
}