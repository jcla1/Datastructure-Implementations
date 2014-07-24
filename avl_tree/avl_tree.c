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

    if(prev == cur->left)
        cur->balance += 1;
    else
        cur->balance -= 1;

    if(cur->balance == 2) {
        if(cur->left->balance == -1)
            bst_left_rotate((bst*)tree, (tree_node*)cur->left);
        bst_right_rotate((bst*)tree, (tree_node*)cur);
    } else if(cur->balance == -2) {
        if(cur->right->balance == 1)
            bst_right_rotate((bst*)tree, (tree_node*)cur->right);
        bst_left_rotate((bst*)tree, (tree_node*)cur);
    }
}