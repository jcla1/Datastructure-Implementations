#include <stdlib.h>

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