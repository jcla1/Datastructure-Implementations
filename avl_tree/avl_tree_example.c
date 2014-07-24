#include <stdio.h>
#include "avl_tree.h"

int int_cmp(void *a, void *b) {
    double ia = *(int*)a;
    double ib = *(int*)b;

    return (ia > ib) - (ia < ib);
}

void tree_print(tree_node *tn) {
    avl_node *node = (avl_node*)tn;
    printf("%d", *(int*)node->value);
}

int main(void) {
    avl_tree *tree;
    avl_node *cur;
    tree = avl_create(int_cmp);

    int nums[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    for(int i = 0; i < 10; i++) {
        // printf("inserting: %d\n", nums[i]);
        avl_insert(tree, &nums[i]);

        // printf("left:");
        // cur = tree->root;
        // while(cur != NULL) {
        //     printf("\t%d :: %d\n", cur->balance, *(int*)cur->value);
        //     cur = cur->left;
        // }

        // printf("right:");
        // cur = tree->root;
        // while(cur != NULL) {
        //     printf("\t%d :: %d\n", cur->balance, *(int*)cur->value);
        //     cur = cur->right;
        // }

        // printf("--------\n");
    }

    // bst_traverse((bst*)tree, my_print, NULL);
    // printf("--------\n");

    // avl_node *cur = tree->root;
    // while(cur != NULL) {
    //     printf("%d :: %d\n", cur->balance, *(int*)cur->value);
    //     cur = cur->left;
    // }
    bst_print((bst*)tree, tree_print);
    return 0;
}