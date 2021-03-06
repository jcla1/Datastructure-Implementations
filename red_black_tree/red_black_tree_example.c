#include <stdio.h>

#include "bst/bst.h"
#include "red_black_tree.h"

int int_cmp(void *a, void *b) {
    int ia = *(int*)a;
    int ib = *(int*)b;

    return (ia > ib) - (ia < ib);
}

void my_trav(void *i1) {
  printf("%d ", *(int*)i1);
}

int main() {
    rb_tree *tree;

    if((tree = rb_tree_create(int_cmp)) == NULL) {
      fprintf(stderr, "[main]: tree creation failed\n");
      return -1;
    }

    int nums[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    for (int i = 0; i < 10; i++) {
      rb_tree_insert(tree, &nums[i]);
    }

    for (int i = 0; i < 10; i++) {
      printf("Removing: %d.\n", nums[i]);
      rb_tree_delete(tree, &nums[i]);

      rb_tree_node *cur = tree->root;
      while(cur != NULL) {
        printf("%s :: %d\n", (int)cur->color ? "BLACK" : "RED", *(int*)cur->value);
        cur = cur->left;
      }

      printf("\n\n");
    }

    return 0;
}