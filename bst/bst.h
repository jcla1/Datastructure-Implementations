#ifndef DATASTRUCTURES_BS_TREE_H_
#define DATASTRUCTURES_BS_TREE_H_

typedef int (*tree_cmp_fn)(void *, void *);
typedef void (*tree_traverse_fn)(void *, void *);

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

bst *bst_create(tree_cmp_fn cmp);
void bst_destroy(bst* tree);

tree_node *bst_search_node(bst *tree, void *value);
void bst_insert_node(bst *tree, tree_node *node);
void bst_replace_node(bst *tree, tree_node *u, tree_node *v);

tree_node *bst_minimum(tree_node *node);
tree_node *bst_maximum(tree_node *node);
tree_node *bst_predecessor(tree_node *x);
tree_node *bst_sucessor(tree_node *x);

int bst_max_depth(tree_node *node);

void bst_traverse(bst *tree, tree_traverse_fn fn, void *param);
// void bst_print(bst *tree);

static void bst_sub_traverse(tree_node *node, tree_traverse_fn fn, void *param);
static void bst_subtree_destroy(tree_node *node);

void bst_left_rotate(bst *tree, tree_node *x);
void bst_right_rotate(bst *tree, tree_node *y);

#endif // DATASTRUCTURES_BS_TREE_H_