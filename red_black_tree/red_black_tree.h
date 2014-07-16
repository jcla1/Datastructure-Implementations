#ifndef DATASTRUCTURES_RED_BLACK_TREE_H_
#define DATASTRUCTURES_RED_BLACK_TREE_H_

#include "bst/bst.h"

typedef struct rb_tree_node rb_tree_node;
struct rb_tree_node {
  rb_tree_node *left, *right, *parent;
  void *value;
  enum { RED, BLACK } color;
};

typedef struct rb_tree rb_tree;
struct rb_tree {
    tree_cmp_fn cmp;
    rb_tree_node *root;
};

rb_tree *rb_tree_create(tree_cmp_fn cmp);
void rb_tree_destroy(rb_tree *tree);
void *rb_tree_search(rb_tree *tree, void *value);
void rb_tree_insert(rb_tree *tree, void *value);
// void *rb_tree_delete(rb_tree *tree, void *val);

rb_tree_node *rb_minimum_node(rb_tree_node *node);
rb_tree_node *rb_maximum_node(rb_tree_node *node);
rb_tree_node *rb_successor_node(rb_tree_node *x);
rb_tree_node *rb_tree_search_node(rb_tree *tree, void *val);

static rb_tree_node *rb_tree_new_node(void *value);
static void rb_destroy_nodes(rb_tree_node *node);

static void rb_tree_left_rotate(rb_tree *tree, rb_tree_node *x);
static void rb_tree_right_rotate(rb_tree *tree, rb_tree_node *y);

#endif // DATASTRUCTURES_RED_BLACK_TREE_H_