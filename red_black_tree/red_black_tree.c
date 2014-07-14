#include <stdlib.h>
#include <stdio.h>

#include "red_black_tree.h"

rb_tree *rb_tree_create(rb_cmp_fn cmp) {
  rb_tree *tree;

  if((tree = calloc(1, sizeof(rb_tree)) == NULL))
    return NULL;

  tree->cmp = cmp;

  return tree;
}

void rb_tree_destroy(rb_tree *tree) {
  if(tree->root != NULL)
    rb_tree_destroy_nodes(tree->root);
  free(tree);
}

static void rb_tree_destroy_nodes(rb_tree_node *node) {
  if(node->left != NULL)
    rb_tree_destroy_nodes(node->left)
  if(node->right != NULL)
    rb_tree_destroy_nodes(node->right)

  free(node);
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
  rb_tree_node *cur, *prev, new_node;
  int comp_res;

  if((new_node = rb_tree_new_node(value)) == NULL) {
    fprintf(stderr, "[rb_tree_insert]: error allocating memory for new node.\n");
    return;
  }

  // Normal BST insert ---
  if(tree->root == NULL) { // tree is empty
    tree->root = new_node;
    tree->root->color = BLACK;
    return;
  }

  prev = NULL;
  cur = tree->root;

  while(cur != NULL) {
    prev = cur;
    comp_res = tree->cmp(cur, value);

    if(comp_res < 0)
      cur = cur->left;
    else
      cur = cur->right
  }

  new_node->parent = prev;

  if(comp_res < 0)
    prev->left = new_node;
  else
    prev->right = new_node;
  // End normal BST insert

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
