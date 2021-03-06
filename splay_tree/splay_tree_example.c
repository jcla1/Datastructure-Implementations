#include <stdio.h>
#include "splay_tree.h"

int int_cmp(void *a, void *b) {
    double ia = *(int*)a;
    double ib = *(int*)b;

    return (ia > ib) - (ia < ib);
}

void my_print(void *a, void *param) {
    printf("%d\n", *(int*)a);
}

int main(void) {
    splay_tree *tree;
    tree = splay_tree_create(int_cmp);

    int nums[] = {40, 50, 30, 20, 45};

    for(int i = 0; i < 5; i++) {
        splay_tree_insert(tree, &nums[i]);
    }

    // bst_traverse(tree, my_print, NULL);
    // printf("-------\n");

    splay_node *cur = tree->root;
    while(cur != NULL) {
        printf("%d\n", *(int*)cur->value);
        cur = cur->left;
    }

    return 0;
}