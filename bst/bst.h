#ifndef DATASTRUCTURES_BS_TREE_H_
#define DATASTRUCTURES_BS_TREE_H_

typedef int (*tree_cmp_fn)(void *, void *);
typedef void (*tree_traverse_fn)(void *);

typedef struct tree_node tree_node;
struct tree_node {
    tree_node *left, *right, *parent;
    void *value;
};

typedef struct bst bst;
struct bst {
    tree_cmp_fn cmp;
    tree_node *root;
};

tree_node *bst_search_node(bst *tree, void *value);
void bst_insert_node(bst *tree, tree_node *node);

void bst_traverse(bst *tree, tree_traverse_fn fn);
static void bst_sub_traverse(tree_node *node, tree_traverse_fn fn);

#endif // DATASTRUCTURES_BS_TREE_H_