#include <stdlib.h>
#include <stdio.h>

#include "bst/bst.h"
#include "avl_tree.h"

avl_tree *avl_create(tree_cmp_fn cmp) {
    return (avl_tree*)bst_create(cmp);
}

void avl_destroy(avl_tree *tree) {
    if(tree->root != NULL)
        avl_destroy_nodes(tree->root);
    free(tree);
}

static void avl_destroy_nodes(avl_node *node) {
    if(node->left != NULL)
        avl_destroy_nodes(node->left);
    if(node->right != NULL)
        avl_destroy_nodes(node->right);

    free(node);
}

int avl_get_height(avl_node *node) {
    if(node == NULL)
        return 0;
    return node->height;
}

int avl_get_balance(avl_node *node) {
    if(node == NULL)
        return 0;

    if(node->left == NULL && node->right == NULL)
        return 0;
    else if(node->left == NULL)
        return -node->right->height;
    else if(node->right == NULL)
        return node->left->height;
    else
        return node->left->height - node->right->height;
}

static void avl_unwind(avl_tree *tree, avl_node *node) {
    avl_node *cur, *prev;

    cur = node->parent;
    prev = node;

    while(cur != NULL) {
        cur->height = max(avl_get_height(cur->left), avl_get_height(cur->right)) + 1;

        if(avl_get_balance(cur) >= 2) {
            if(avl_get_balance(node->left) <= -1)
                avl_left_rotate(tree, cur->left);
            avl_right_rotate(tree, cur);
        } else if(avl_get_balance(cur) <= -2) {
            if(avl_get_balance(cur->right) >= 1)
                avl_right_rotate(tree, cur->right);
            avl_left_rotate(tree, cur);
        }

        prev = cur;
        cur = cur->parent;
    }
}

void avl_insert(avl_tree *tree, void *value) {
    avl_node *node, *cur, *prev;

    if((node = calloc(1, sizeof(avl_node))) == NULL) {
        fprintf(stderr, "[avl_insert]: error allocating memory\n");
        return;
    }
    node->height = 1;
    node->value = value;

    bst_insert_node((bst*)tree, (tree_node*)node);

    avl_unwind(tree, node);
}

void *avl_delete(avl_tree *tree, void *value) {
    avl_node *node;
    void *val;

    if((node = (avl_node*)bst_search_node((bst*)tree, value)) == NULL)
        return NULL;

    if(node->left == NULL && node->right != NULL) {
        val = node->value;
        node->value = node->right->value;
        node->height -= 1;
        avl_unwind(tree, node);
    }

    return val;
}

static inline int max(int a, int b) {
    return (a > b) ? a : b;
}

static void avl_left_rotate(avl_tree *tree, avl_node *x) {
    avl_node *y, *parent;
    int xlb, xrb, yrb, plb, prb;

    bst_left_rotate((bst*)tree, (tree_node*)x);
    y = x->parent;

    x->height = max(avl_get_height(x->left), avl_get_height(x->right)) + 1;
    y->height = max(avl_get_height(x), avl_get_height(y->right)) + 1;
}

static void avl_right_rotate(avl_tree *tree, avl_node *y) {
    avl_node *x, *parent;
    int xlb, ylb, yrb, plb, prb;

    bst_right_rotate((bst*)tree, (tree_node*)y);
    x = y->parent;

    y->height = max(avl_get_height(y->left), avl_get_height(y->right)) + 1;
    x->height = max(avl_get_height(x->left), avl_get_height(y)) + 1;
}