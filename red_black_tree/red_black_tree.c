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

static rb_tree_node *rb_tree_new_node(void *value) {
  rb_tree_node *node;

  if((node = malloc(sizeof(rb_tree_node))) == NULL)
    return NULL;

  node->value = value;
  node->color = RED;

  return node;
}
