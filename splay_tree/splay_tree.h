#ifndef DATASTRUCTURES_SPLAY_TREE_H_
#define DATASTRUCTURES_SPLAY_TREE_H_

#include "bst/bst.h"

typedef bst splay_tree;
typedef tree_node splay_node;

splay_tree *splay_tree_create(splay_cmp_fn cmp);
void splay_tree_destroy(splay_tree *tree);

void splay_tree_insert(splay_tree *tree, void *value);

static void splay(splay_node *node);

#endif // DATASTRUCTURES_SPLAY_TREE_H_