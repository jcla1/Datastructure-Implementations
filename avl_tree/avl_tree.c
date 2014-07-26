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

void avl_insert(avl_tree *tree, void *value) {
    avl_node *node, *cur, *prev;

    if((node = calloc(1, sizeof(avl_node))) == NULL) {
        fprintf(stderr, "[avl_insert]: error allocating memory\n");
        return;
    }
    node->value = value;

    bst_insert_node((bst*)tree, (tree_node*)node);

    cur = node->parent;
    prev = node;

    while(cur != NULL) {
        if(prev == cur->left)
            cur->balance += 1;
        else
            cur->balance -= 1;

        if(cur->balance == 2) {
            if(cur->left->balance == -1)
                avl_left_rotate(tree, cur->left);
            avl_right_rotate(tree, cur);
            break;
        } else if(cur->balance == -2) {
            if(cur->right->balance == 1)
                avl_right_rotate(tree, cur->right);
            avl_left_rotate(tree, cur);
            break;
        }

        prev = cur;
        cur = cur->parent;
    }
}

static void avl_left_rotate(avl_tree *tree, avl_node *x) {
    avl_node *y;
    int x_left_balance, x_right_balance, y_right_balance;

    bst_left_rotate((bst*)tree, (tree_node*)x);
    y = x->parent;

    x_left_balance = x->left ? x->left->balance : 0;
    x_right_balance = x->right ? x->right->balance : 0;
    x->balance = x_left_balance - x_right_balance;

    y_right_balance = y->right ? y->right->balance : 0;
    y->balance = x->balance - y_right_balance;
}

static void avl_right_rotate(avl_tree *tree, avl_node *y) {
    avl_node *x;
    int y_left_balance, y_right_balance, x_right_balance;

    bst_right_rotate((bst*)tree, (tree_node*)y);
    x = y->parent;

    y_left_balance = y->left ? y->left->balance : 0;
    y_right_balance = y->right ? y->right->balance : 0;
    y->balance = y_left_balance - y_right_balance;

    x_right_balance = x->right ? x->right->balance : 0;

    x->balance = y->balance - x_right_balance;
}

static inline int max(int a, int b) {
    return (a > b) ? a : b;
}