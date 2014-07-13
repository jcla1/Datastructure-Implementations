#include <stdlib.h>

#include "red_black_tree.h"

rb_tree *rb_tree_create(rb_cmp_fn cmp) {}
void rb_tree_destroy(rb_tree *tree) {}
void *rb_tree_search(rb_tree *tree, void *val) {
  rb_tree_node *cur;
  int comp_res;

  cur = tree->root;
  while(cur != NULL) {
    comp_res = tree->cmp(cur->value, val);

    if(comp_res == 0)
      return cur->value;
    else if(comp_res < 0)
      cur = cur->left;
    else
      cur = cur->right;
  }

  return NULL; // value not present
}