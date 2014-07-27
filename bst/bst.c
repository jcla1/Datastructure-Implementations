#include <stdlib.h>
#include <stdio.h>

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

tree_node *bst_sucessor(tree_node *x) {
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

int bst_max_depth(tree_node *node) {
	int dl, dr;

	if(node == NULL)
		return 0;

	dl = bst_max_depth(node->left);
	dr = bst_max_depth(node->right);

	return (dl > dr ? dl : dr) + 1;
}

void bst_traverse(bst *tree, tree_traverse_fn fn, void *param) {
	if(tree->root == NULL)
		return;

	bst_sub_traverse(tree->root, fn, param);
}

void bst_print(bst *tree, tree_print_fn fn) {
	if(tree->root != NULL)
		bst_print_helper(tree->root, fn, 0);
}

static void bst_print_helper(tree_node *node, tree_print_fn fn, int indent) {
	fn(node);
	printf("\n");

	if(node->left == NULL && node->right == NULL)
		return;

	for (int i = 0; i <= indent; ++i)
			printf(BST_BLANK);
	if(node->left != NULL) {
		printf(BST_LINE_T);
		bst_print_helper(node->left, fn, indent+1);
	} else {
		puts(BST_LINE_I);
	}

	for (int i = 0; i <= indent; ++i)
			printf(BST_BLANK);
	if(node->right != NULL) {
		printf(BST_LINE_L);
		bst_print_helper(node->right, fn, indent+1);
	} else {
		puts(BST_LINE_I);
	}
}

static void bst_sub_traverse(tree_node *node, tree_traverse_fn fn, void *param) {
	if(node->left != NULL)
		bst_sub_traverse(node->left, fn, param);

	fn(node->value, param);

	if(node->right != NULL)
		bst_sub_traverse(node->right, fn, param);
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
	if(x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;

	if(y->parent == NULL)
		tree->root = x;
	else if(y == y->parent->right)
		y->parent->right = x;
	else
		y->parent->left = x;

	x->right = y;
	y->parent = x;
}