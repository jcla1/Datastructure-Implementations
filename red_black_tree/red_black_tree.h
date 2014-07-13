#ifndef DATASTRUCTURES_RED_BLACK_TREE_H_
#define DATASTRUCTURES_RED_BLACK_TREE_H_

// Will be passed the RB-Tree node first then a value
// that might need to be extracted.
typedef int (*rb_cmp_fn)(void *, void *);

typedef struct rb_tree_node rb_tree_node;
struct rb_tree_node {
  void *value;
  enum { RED, BLACK } color;
  rb_tree_node *left, *right, *parent;
};

typedef struct rb_tree rb_tree;
struct rb_tree {
  rb_cmp_fn cmp;
  rb_tree_node *root;
};

rb_tree *rb_tree_create(rb_cmp_fn cmp);
void rb_tree_destroy(rb_tree *tree);
void *rb_tree_search(rb_tree *tree, void *val);

#endif // DATASTRUCTURES_RED_BLACK_TREE_H_