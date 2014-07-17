#include <stdlib.h>

#include "bst.h"

bst *bst_create(tree_cmp_fn cmp) {
    bst *tree;

    if((tree = calloc(1, sizeof(bst))) == NULL)
        return NULL;

    tree->cmp = cmp;

    return tree;
}

void bst_destroy(bst* tree) {
    if(tree->root != NULL)
        bst_subtree_destroy(tree->root);
    free(tree);
}

static void bst_subtree_destroy(tree_node *node) {
    if(node->left != NULL)
        bst_subtree_destroy(node->left);
    if(node->right != NULL)
        bst_subtree_destroy(node->right);

    free(node);
}

tree_node *bst_search_node(bst *tree, void *value) {
    tree_node *cur;
    int comp_res;

    cur = tree->root;
    while(cur != NULL) {
        comp_res = tree->cmp(cur->value, value);

    if(comp_res == 0)
        return cur;
    else if(comp_res < 0)
        cur = cur->left;
    else
        cur = cur->right;
    }

    return NULL; // value not present
}

void bst_insert_node(bst *tree, tree_node *node) {
    tree_node *cur, *prev;
    int comp_res;

    if(tree->root == NULL) {
        tree->root = node;
        return;
    }

    prev = NULL;
    cur = tree->root;

    while(cur != NULL) {
        prev = cur;
        comp_res = tree->cmp(cur->value, node->value);

        if(comp_res >= 0)
            cur = cur->left;
        else
            cur = cur->right;
    }

    node->parent = prev;

    if(comp_res >= 0)
        prev->left = node;
    else
        prev->right = node;
}

void bst_replace_node(bst *tree, tree_node *u, tree_node *v) {
    if(u->parent == NULL)
        tree->root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if(v != NULL)
        v->parent = u->parent;
}

tree_node *bst_predecessor(tree_node *x) {
  tree_node *y;

  if(x->left != NULL)
    return bst_maximum(x->left);

  y = x->parent;
  while(y != NULL && x == y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

tree_node *bst_successor(tree_node *x) {
  tree_node *y;

  if(x->right != NULL)
    return bst_minimum(x->right);

  y = x->parent;
  while(y != NULL && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

tree_node *bst_minimum(tree_node *node) {
  while(node->left != NULL)
    node = node->left;

  return node;
}

tree_node *bst_maximum(tree_node *node) {
  while(node->right != NULL)
    node = node->right;

  return node;
}

void bst_traverse(bst *tree, tree_traverse_fn fn) {
    if(tree->root == NULL)
        return;

    bst_sub_traverse(tree->root, fn);
}

static void bst_sub_traverse(tree_node *node, tree_traverse_fn fn) {
    if(node->left != NULL)
        bst_sub_traverse(node->left, fn);

    fn(node->value);

    if(node->right != NULL)
        bst_sub_traverse(node->right, fn);
}

void bst_left_rotate(bst *tree, tree_node *x) {
  tree_node *y;
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


void bst_right_rotate(bst *tree, tree_node *y) {
  tree_node *x;
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