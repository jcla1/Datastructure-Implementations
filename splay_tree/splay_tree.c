#include <stdlib.h>

#include "splay_tree.h"

splay_tree *splay_tree_create(tree_cmp_fn cmp) {
    splay_tree *tree;

    if((tree = calloc(1, sizeof(splay_tree))) == NULL)
        return NULL;

    tree->cmp = cmp;

    return tree;
}

void splay_tree_destroy(splay_tree *tree) {}

void splay_tree_insert(splay_tree *tree, void *value) {}

static void splay(splay_node *node) {}