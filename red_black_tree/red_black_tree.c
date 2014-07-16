#include <stdlib.h>
#include <stdio.h>

#include "bst/bst.h"
#include "red_black_tree.h"

rb_tree *rb_tree_create(tree_cmp_fn cmp) {
  rb_tree *tree;

  if((tree = calloc(1, sizeof(rb_tree))) == NULL)
    return NULL;

  tree->cmp = cmp;

  return tree;
}

void rb_tree_destroy(rb_tree *tree) {
  if(tree->root != NULL)
    rb_destroy_nodes(tree->root);
  free(tree);
}

static void rb_destroy_nodes(rb_tree_node *node) {
  if(node->left != NULL)
    rb_destroy_nodes(node->left);
  if(node->right != NULL)
    rb_destroy_nodes(node->right);

  free(node);
}

void *rb_tree_search(rb_tree *tree, void *value) {
  rb_tree_node *node;
  if((node = (rb_tree_node*)bst_search_node((bst*)tree, value)) == NULL)
    return NULL;
  return node->value;
}

void rb_tree_insert(rb_tree *tree, void *value) {
  rb_tree_node *y, *x;
  int comp_res;

  if((x = rb_tree_new_node(value)) == NULL) {
    fprintf(stderr, "[rb_tree_insert]: error allocating memory for new node.\n");
    return;
  }

  bst_insert_node((bst*)tree, (tree_node*)x);
  if(tree->root == x)
    x->color = BLACK;

  while(x != tree->root && x->parent->color == RED) {
    if(x->parent == x->parent->parent->left) {
      y = x->parent->parent->right;

      if (y != NULL && y->color == RED) {
        x->parent->color = BLACK;
        y->color = BLACK;
        x->parent->parent->color = RED;
        x = x->parent->parent;
      } else {
        if(x == x->parent->right) {
          x = x->parent;
          rb_tree_left_rotate(tree, x);
        }

        x->parent->color = BLACK;
        x->parent->parent->color = RED;
        rb_tree_right_rotate(tree, x->parent->parent);
      }
    } else {
      y = x->parent->parent->left;

      if (y != NULL && y->color == RED) {
        x->parent->color = BLACK;
        y->color = BLACK;
        x->parent->parent->color = RED;
        x = x->parent->parent;
      } else {
        if(x == x->parent->left) {
          x = x->parent;
          rb_tree_right_rotate(tree, x);
        }

        x->parent->color = BLACK;
        x->parent->parent->color = RED;
        rb_tree_left_rotate(tree, x->parent->parent);
      }
    }
  }

  tree->root->color = BLACK;
}

static rb_tree_node *rb_tree_new_node(void *value) {
  rb_tree_node *node;

  if((node = malloc(sizeof(rb_tree_node))) == NULL)
    return NULL;

  node->value = value;
  node->color = RED;

  return node;
}

rb_tree_node *rb_successor_node(rb_tree_node *x) {
  rb_tree_node *y;

  if(x->right != NULL)
    return rb_minimum_node(x->right);

  y = x->parent;
  while(y != NULL && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

rb_tree_node *rb_minimum_node(rb_tree_node *node) {
  while(node->left != NULL)
    node = node->left;

  return node;
}

rb_tree_node *rb_maximum_node(rb_tree_node *node) {
  while(node->right != NULL)
    node = node->right;

  return node;
}

static void rb_tree_right_rotate(rb_tree *tree, rb_tree_node *y) {
  rb_tree_node *x;
  x = y->left;

  y->left = x->right;
  if(y->left != NULL)
    y->left->parent = y;

  x->parent = y->parent;

  if(y == tree->root)
    tree->root = x;
  else if(y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;

  x->right = y;
  y->parent = x;
}

static void rb_tree_left_rotate(rb_tree *tree, rb_tree_node *x) {
  rb_tree_node *y;
  y = x->right;

  x->right = y->left;
  if(y->left != NULL)
    y->left->parent = x;

  y->parent = x->parent;

  if(x->parent == NULL)
    tree->root = y;
  else if(x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;

  y->left = x;
  x->parent = y;
}
