#include <stdlib.h>

#include "splay_tree.h"

splay_tree *splay_tree_create(splay_cmp_fn cmp) {}

void splay_tree_destroy(splay_tree *tree) {}

void *splay_tree_search(splay_tree *tree, void *value) {}

void splay_tree_insert(splay_tree *tree, void *value) {}

static void splay(splay_node *node) {}