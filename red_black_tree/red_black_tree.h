#ifndef DATASTRUCTURES_RED_BLACK_TREE_H_
#define DATASTRUCTURES_RED_BLACK_TREE_H_

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

#endif // DATASTRUCTURES_RED_BLACK_TREE_H_