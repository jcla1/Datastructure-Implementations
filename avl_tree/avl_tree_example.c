#include <stdio.h>
#include "avl_tree.h"

int int_cmp(void *a, void *b) {
    double ia = *(int*)a;
    double ib = *(int*)b;

    return (ia > ib) - (ia < ib);
}

void tree_print(tree_node *tn) {
    avl_node *node = (avl_node*)tn;
    printf("%d :: %d -> %d", avl_get_height(node), avl_get_balance(node), *(int*)node->value);
}

void my_print(void *val, void *_) {
    printf("%d ", *(int*)val);
}

int main(void) {
    avl_tree *tree;
    avl_node *cur;
    tree = avl_create(int_cmp);

    int nums[] = {58, 98, 43, 74, 74, 65, 93, 81, 76, 6, 78, 73, 62, 84, 48, 21, 15, 41, 36, 98};
    // int nums[] = {1,2,3,4,5,6,7};

    for(int i = 0; i < 20; i++) {
        bst_print((bst*)tree, tree_print);

        printf("\ninserting: %d\n\n", nums[i]);
        avl_insert(tree, &nums[i]);

        bst_print((bst*)tree, tree_print);
        printf("\n===========================\n\n");
    }

    // bst_traverse((bst*)tree, my_print, NULL);
    // puts("");

    return 0;
}