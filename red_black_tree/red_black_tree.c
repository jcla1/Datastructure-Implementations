#include <stdlib.h>
#include <stdio.h>

#include "bst/bst.h"
#include "red_black_tree.h"

rb_tree *rb_tree_create(tree_cmp_fn cmp) {
  return (rb_tree*)bst_create(cmp);
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
          bst_left_rotate((bst*)tree, (tree_node*)x);
        }

        x->parent->color = BLACK;
        x->parent->parent->color = RED;
        bst_right_rotate((bst*)tree, (tree_node*)x->parent->parent);
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
          bst_right_rotate((bst*)tree, (tree_node*)x);
        }

        x->parent->color = BLACK;
        x->parent->parent->color = RED;
        bst_left_rotate((bst*)tree, (tree_node*)x->parent->parent);
      }
    }
  }

  tree->root->color = BLACK;
}

// Delete operation adapted from: http://stackoverflow.com/a/12081824/678164
void *rb_tree_delete(rb_tree *tree, void *value) {
  rb_tree_node *node, *x, *x_parent, *y;
  int y_is_left;

  y_is_left = 0;

  if((node = (rb_tree_node*)bst_search_node((bst*)tree, value)) == NULL)
    return NULL;

  if(node->left == NULL || node->right == NULL)
    y = node;
  else
    bst_sucessor((tree_node*)node);

  if(y->left != NULL)
    x = y->left;
  else
    x = y->right;

  if(x != NULL)
    x->parent = y->parent;

  x_parent = y->parent;

  if(y->parent == NULL) {
    tree->root = x;
  } else if(y == y->parent->left) {
    y->parent->left = x;
    y_is_left = 1;
  } else {
    y->parent->right = x;
  }

  if(y != node)
    node->value = y->value;

  if(y->color == BLACK)
    rb_delete_fixup(tree, x, x_parent, y_is_left);

  return y->value;
}

static void rb_delete_fixup(rb_tree *tree, rb_tree_node *node, rb_tree_node *node_parent, int node_is_left) {
  rb_tree_node *w;

  while(node != tree->root && node->color == BLACK) {
    if(node_is_left) {
      w = node_parent->right;
      if(w->color == RED) {
        w->color = BLACK;
        node_parent->color = RED;
        bst_left_rotate((bst*)tree, (tree_node*)node_parent);
        w = node_parent->right;
      }

      if(w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        node = node_parent;
        node_parent = node->parent;
        node_is_left = (node_parent != NULL && node == node_parent->left);
      } else {
        if(w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          bst_right_rotate((bst*)tree, (tree_node*)w);
          w = node_parent->right;
        }

        w->color = node_parent->color;
        node_parent->color = BLACK;
        if(w->right != NULL) {
          w->right->color = BLACK;
        }
        bst_left_rotate((bst*)tree, (tree_node*)node_parent);
        node = tree->root;
        node_parent = NULL;
      }
    } else {
      w = node_parent->left;
      if(w->color == RED) {
        w->color = BLACK;
        node_parent->color = RED;
        bst_right_rotate((bst*)tree, (tree_node*)node_parent);
        w = node_parent->left;
      }

      if(w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        node = node_parent;
        node_parent = node->parent;
        node_is_left = (node_parent != NULL && node == node_parent->left);
      } else {
        if(w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          bst_left_rotate((bst*)tree, (tree_node*)w);
          w = node_parent->left;
        }

        w->color = node_parent->color;
        node_parent->color = BLACK;
        if(w->left != NULL) {
          w->left->color = BLACK;
        }
        bst_right_rotate((bst*)tree, (tree_node*)node_parent);
        node = tree->root;
        node_parent = NULL;
      }
    }
  }

  node->color = BLACK;
}

static rb_tree_node *rb_tree_new_node(void *value) {
  rb_tree_node *node;

  if((node = malloc(sizeof(rb_tree_node))) == NULL)
    return NULL;

  node->value = value;
  node->color = RED;

  return node;
}
