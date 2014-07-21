#include <stdio.h>
#include "avl_tree.h"

int int_cmp(void *a, void *b) {
    double ia = *(int*)a;
    double ib = *(int*)b;

    return (ia > ib) - (ia < ib);
}

void my_print(void *a, void *param) {
    printf("%d\n", *(int*)a);
}

int main(void) {
    avl_tree *tree;
    tree = avl_create(int_cmp);

    int nums[] = {40, 50, 30, 20, 45};

    for(int i = 0; i < 5; i++) {
        printf("inserting: %d\n", nums[i]);
        avl_insert(tree, &nums[i]);
    }

    bst_traverse((bst*)tree, my_print, NULL);
    printf("--------\n");

    avl_node *cur = tree->root;
    while(cur != NULL) {
        printf("%d\n", *(int*)cur->value);
        cur = cur->left;
    }

    return 0;
}