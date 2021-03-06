#include <stdlib.h>
#include <stdio.h>

#include "splay_tree.h"

splay_tree *splay_tree_create(tree_cmp_fn cmp) {
    return (splay_tree*)bst_create(cmp);
}

void splay_tree_destroy(splay_tree *tree) {
    bst_destroy((bst*)tree);
}

void splay_tree_insert(splay_tree *tree, void *value) {
    splay_node *new_node;

    if((new_node = calloc(1, sizeof(splay_node))) == NULL) {
        fprintf(stderr, "[splay_tree_insert]: error allocating memory for new node\n");
        return;
    }

    new_node->value = value;

    bst_insert_node((bst*)tree, (tree_node*)new_node);
    splay(tree, new_node);
}

void splay_tree_delete(splay_tree *tree, void *value) {
    splay_node *x, *y;

    if((x = bst_search_node((bst*)tree, value)) == NULL)
        return;

    splay(tree, x);

    if(x->left == NULL) {
        bst_replace_node((bst*)tree, x, x->right);
    } else if(x->right == NULL) {
        bst_replace_node((bst*)tree, x, x->left);
    } else {
        y = bst_minimum(x->right);
        if(y->parent != x) {
            bst_replace_node((bst*)tree, y, y->right);
        }
        bst_replace_node((bst*)tree, x, y);
        y->left = x->left;
        y->left->parent = y;
    }

    free(x);
}

static void splay(splay_tree *tree, splay_node *x) {
    while(x->parent) {
        if(x->parent->parent == NULL) {
            if(x->parent->left == x)
                bst_right_rotate((bst*)tree, (tree_node*)x->parent);
            else
                bst_left_rotate((bst*)tree, (tree_node*)x->parent);
        } else if(x->parent->left == x && x->parent->parent->left == x->parent) {
            bst_right_rotate((bst*)tree, (tree_node*)x->parent->parent);
            bst_right_rotate((bst*)tree, (tree_node*)x->parent);
        } else if(x->parent->right == x && x->parent->parent->right == x->parent) {
            bst_left_rotate((bst*)tree, (tree_node*)x->parent->parent);
            bst_left_rotate((bst*)tree, (tree_node*)x->parent);
        } else if( x->parent->left == x && x->parent->parent->right == x->parent ) {
            bst_right_rotate((bst*)tree, (tree_node*)x->parent);
            bst_left_rotate((bst*)tree, (tree_node*)x->parent);
        } else {
            bst_left_rotate((bst*)tree, (tree_node*)x->parent);
            bst_right_rotate((bst*)tree, (tree_node*)x->parent);
        }
    }
}