#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btree.h"

int main() {
	char *pre = "ABCDEFGHIJKL";
	char *mid = "CBEFDGAJIKLH";
	char *post = "CFEGDBJLKIHA";
	char *level = "ABHCDIEGJKFL";

	struct BTree *root = btree_from_pre_mid(pre, mid, strlen(pre));
	printf("前序中序-后序遍历：");
	btree_post_order(root);
	printf("\n");
	//btree_level_order_test
	printf("\nbtree_level_order_test\n");
	printf("层次遍历：");
	btree_level_order(root);

	putchar('\n');

	printf("叶子数：%d leaves\n", btree_leaves(root));

	btree_destroy(root);
	//btree_from_post_mid_test
	printf("\nbtree_from_post_mid_test\n");
	printf("后序中序-前序遍历：");
	root = btree_from_post_mid(post, mid, strlen(post));
	btree_pre_order(root);
	printf("\n");
	btree_destroy(root);

	//btree_from_level_mid_test
	printf("\nbtree_from_level_mid_test\n");
	printf("层次中序-前序遍历：");
	root = btree_from_level_mid(level, mid, strlen(mid));
	btree_pre_order(root);
	printf("\n");
	btree_destroy(root);

	//btree_build_search_tree_test
	printf("\nbtree_build_search_tree_test\n");
	root=btree_build_search_tree(mid);
	printf("build a search tree:");
	btree_pre_order(root);
	printf("\n");
	btree_destroy(root);

	//btree_is_same_test
	printf("\nbtree_is_same_test\n");
	struct BTree *root1, *root2;
	root1 = btree_from_level_mid(level, mid, strlen(mid));
	root2 = btree_from_post_mid(post, mid, strlen(mid));
	printf("btree is same?:%d\n", btree_is_same(root1, root2));
	btree_destroy(root1);
	btree_destroy(root2);

	//btree_is_isomorphic_test
	printf("\nbtree_is_isomorphic_test\n");
	char *pre1 = "AHIKLJBDGEFC";
	char *level1 = "AHBIDCKJGELF";
	char *mid1 = "LKIJHAGDFEBC";
	//build a isomorphic tree in root1
	root1 = btree_from_pre_mid(pre1, mid1, strlen(mid1));
	printf("the isomorphic tree's level order is:");
	btree_level_order(root1);
	printf("\n");
	root2 = btree_from_level_mid(level, mid, strlen(mid));
	printf("btree is isomorphic?:%d\n", btree_is_isomorphic(root1, root2));
	btree_destroy(root1);
	btree_destroy(root2);
}
