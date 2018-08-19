#pragma once

#include <stdbool.h>

typedef struct{
	char ch;
	int t;
}TreeDataType;

struct BTree {
  TreeDataType data;
  struct BTree *left;
  struct BTree *right;
  struct BTree *parent;
};

struct BTree *btree_create(TreeDataType root, struct BTree *left, struct BTree *right);

void btree_destroy(struct BTree *root);

//struct BTree *btree_find(struct BTree *root, char value);

int btree_depth(struct BTree *root);

int btree_leaves(struct BTree *root);

bool btree_is_same(struct BTree *a, struct BTree *b);

bool btree_is_isomorphic(struct BTree *a, struct BTree *b);
