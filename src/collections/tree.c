#include <stdlib.h>
#include "collections.h"

static tNode find(tNode, int);
static int exact = 0;

int tput(Tree tree, int key, int value) {
	tNode last = find(tree->root, key);
	if (last->key == key) {
		last->value = value;
		return tree->size;	
	}
	
	tNode node = malloc(TNODESIZE);
	node->left = NULL;
	node->right = NULL;
	node->key = key;
	node->value = value;
	
	if (last->key < key)
		last->left = node;
	else
		last->right = node;
		
	return ++(tree->size);
}

int tget(Tree tree, int key) {
	tNode tmp = find(tree->root, key);
	exact = tmp->key == key;
	return tmp->value;
}

int isexact() {
	return exact;
}

tNode find(tNode root, int key) {
	tNode parent;
	tNode tmp = root;
	while (tmp != NULL) {
		parent = tmp;
		if (tmp->key == key)
			return tmp;
		if (tmp->key < key)
			tmp = tmp->left;
		else
			tmp = tmp->right;	
	}
	return parent;
}

void initTree(Tree tree) {
	tNode node = malloc(TNODESIZE);
	node->left = NULL;
	node->right = NULL;
	tree->root = node;
	tree->size = 0;
}
