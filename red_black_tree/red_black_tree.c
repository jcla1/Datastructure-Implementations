#include <stdlib.h>

#include "red_black_tree.h"

rb_tree *rb_tree_create(rb_cmp_fn cmp) {

}

void rb_tree_destroy(rb_tree *tree) {

}

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

void rb_tree_insert(rb_tree *tree, void *value) {
  rb_tree_node *cur;
  int comp_res;

  cur = tree->root;

  if(cur == NULL) { // tree is empty
    if((tree->root = rb_tree_new_node(value)) == NULL) {
      fprintf(stderr, "[rb_tree_insert]: error allocating memory for new node.\n");
    } else {
      tree->root->color = BLACK;
    }
    return;
  }

}

static rb_tree_node *rb_tree_new_node(void *value) {
  rb_tree_node *node;

  if((node = malloc(sizeof(rb_tree_node))) == NULL)
    return NULL;

  node->value = value;
  node->color = RED;

  return node;
}

void *rb_tree_delete(rb_tree *tree, void *val) {
  void *value;
  return value;
}

static void rb_tree_right_rotate(rb_tree *tree, rb_tree_node *y) {
  rb_tree_node *x;
  x = y->left;

  y->left = x->right;
  if(y->left != NULL)
    y->left->parent = y;

  if(y == tree->root)
    tree->root = x;
  else if(y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;

  y->parent = x;
  x->right = y;
}

static void rb_tree_left_rotate(rb_tree *tree, rb_tree_node *x) {
  rb_tree_node *y;
  y = x->right;

  x->right = y->left;
  if(x->right != NULL)
    x->left->parent = x;

  if(x == tree->root)
    tree->root = y;
  else if(x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;

  x->parent = y;
  y->left = x;
}
