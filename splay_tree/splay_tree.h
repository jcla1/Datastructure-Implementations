#ifndef DATASTRUCTURES_SPLAY_TREE_H_
#define DATASTRUCTURES_SPLAY_TREE_H_

typedef int (*splay_cmp_fn)(void *, void *);

typedef struct splay_tree_node splay_tree_node;
struct splay_tree_node {
    splay_tree_node *left, *right, *parent;
    void *value;
};

typedef struct splay_tree splay_tree;
struct splay_tree {
    splay_cmp_fn cmp_fn;
    splay_tree_node *root;
};

splay_tree *splay_tree_create(splay_cmp_fn cmp);
void splay_tree_destroy(splay_tree *tree);

#endif // DATASTRUCTURES_SPLAY_TREE_H_