#ifndef DATASTRUCTURES_SPLAY_TREE_H_
#define DATASTRUCTURES_SPLAY_TREE_H_

typedef int (*splay_cmp_fn)(void *, void *);

typedef struct splay_node splay_node;
struct splay_node {
    splay_node *left, *right, *parent;
    void *value;
};

typedef struct splay_tree splay_tree;
struct splay_tree {
    splay_cmp_fn cmp_fn;
    splay_node *root;
};

splay_tree *splay_tree_create(splay_cmp_fn cmp);
void splay_tree_destroy(splay_tree *tree);

void *splay_tree_search(splay_tree *tree, void *value);
void splay_tree_insert(splay_tree *tree, void *value);

static void splay(splay_node *node);

#endif // DATASTRUCTURES_SPLAY_TREE_H_