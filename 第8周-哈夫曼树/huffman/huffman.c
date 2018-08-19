#include "huffman.h"
#include<string.h>
#include <stdio.h>
#include"heap.h"
#include<stdlib.h>

// TODO:
// 使用堆构建一个 Huffman 树
struct BTree *huffman_build_using_heap(char *s) {
	Heap h;
	DataType temp;
	int count[256] = { 0 }, i;
	for (i = 0; i < strlen(s); i++) {
		count[s[i]]++;
	}
	heap_init(&h);
	for (i = 0; i < 256; i++) {
		if (count[i] != 0) {
			temp = malloc(sizeof(struct BTree));
			temp->data.ch = i;
			temp->data.t = count[i];
			temp->left = temp->right = temp->parent = NULL;
			vector_push_back(&h, temp);
		}
	}
	heap_rebuild(&h);
	while (h.size > 2) {
		DataType small1, small2;
		TreeDataType root;
		small1 = heap_pop(&h);
		small2 = heap_pop(&h);
		root.ch = 0;
		root.t = small1->data.t + small2->data.t;
		vector_push_back(&h, btree_create(root, small1, small2));
		heap_rebuild(&h);
	}
	return h.buffer[1];
}

// TODO:
// 用数组构建一个 Huffman 树
struct BTree *huffman_build_using_array(char *s) {
	DataType *TreeNode;
	int count[256] = { 0 }, i, j, t = 0, size = 10, *flag, x1 = 9999, x2 = 9999, sm1 = -1, sm2 = -1;
	TreeNode = (DataType*)malloc(sizeof(DataType)*size);
	flag = (int*)malloc(sizeof(int)*size);
	for (i = 0; i < strlen(s); i++) {
		count[s[i]]++;
	}
	for (i = 0; i < 256; i++) {
		if (count[i] != 0) {
			if (t >= size) {
				TreeNode = (DataType*)realloc(TreeNode,sizeof(DataType)*size * 2);
				flag = (int*)realloc(flag,sizeof(int)*size * 2);
				size *= 2;
			}
			*(TreeNode + t) = (DataType)malloc(sizeof(struct BTree));
			(*(TreeNode + t))->data.ch = i;
			(*(TreeNode + t))->data.t = count[i];
			(*(TreeNode + t))->left = (*(TreeNode+t))->right = (*(TreeNode + t))->parent = NULL;
			flag[t] = 0;
			t++;
		}
	}
	TreeNode = (DataType*)realloc(TreeNode, sizeof(DataType) * 2 * t);
	flag = (int*)realloc(flag, sizeof(int) * 2 * t);
	for (i = 0; i < t - 1; i++) {//合并循环t-1次
		for (j = 0; j < t+i; j++) {//找出最小与次小
			if ((*(TreeNode + j))->data.t < x2&&flag[j]==0) {
				x1 = x2;
				sm1 = sm2;
				x2 = (*(TreeNode + j))->data.t;
				sm2 = j;
			}
			else if ((*(TreeNode + j))->data.t < x1&&flag[j] == 0) {
				x1 = (*(TreeNode + j))->data.t;
				sm1 = j;
			}
		}
		flag[sm1] = flag[sm2] = 1;
		*(TreeNode + t + i) = (DataType)malloc(sizeof(struct BTree));
		(*(TreeNode + sm1))->parent = (*(TreeNode + t + i));
		(*(TreeNode + sm2))->parent = (*(TreeNode + t + i));
		(*(TreeNode + t + i))->left = (*(TreeNode + sm1));
		(*(TreeNode + t + i)) ->right= (*(TreeNode + sm2));
		(*(TreeNode + t + i))->parent = NULL;
		(*(TreeNode + t + i))->data.t = (*(TreeNode + sm1))->data.t + (*(TreeNode + sm2))->data.t;
		(*(TreeNode + t + i))->data.ch = 0;
		flag[t + i] = 0;
		x1 = 9999; x2 = 9999; sm1 = -1; sm2 = -1;
	}
	for (i = 0; i < 2 * t - 1; i++) {
		if (flag[i] == 0) {
			return (*(TreeNode + i));
		}
	}
}

int ge;
void code_list(char **str, char *ch, struct BTree *ht)
{
	if (ht->left == NULL && ht->right == NULL) {
		int now = 0, i;
		ch[ge] = ht->data.ch;
		ch[ge + 1] = 0;
		while (ht->parent != NULL) {
			if (ht == ht->parent->left) {
				(*(*(str + ge) + now)) = '0';
				(*(*(str + ge) + now + 1)) = 0;
				now++;
			}
			else {
				(*(*(str + ge) + now)) = '1';
				(*(*(str + ge) + now + 1)) = 0;
				now++;
			}
			ht = ht->parent;
		}
		for (i = 0; i < strlen(*(str + ge))/2; i++) {
			char te = (*(*(str + ge) + i));
			(*(*(str + ge) + i)) = (*(*(str + ge) + strlen(*(str + ge)) -i- 1));
			(*(*(str + ge) + strlen(*(str + ge)) -i- 1)) = te;
		}
		ge++;
	}
	else {
		if (ht->left != NULL) {
			code_list(str, ch, ht->left);
		}
		if (ht->right != NULL) {
			code_list(str, ch, ht->right);
		}
	}
}

// TODO:
// 用 Huffman 树ht对字符串 s
// 进行编码，打印出编码结果（0、1字符串），并返回编码后的长度
int huffman_encode(struct BTree *ht, char *s) {
	int i, j, num=0;
	DataType temp;
	char **str, *ch;
	str = (char **)malloc(sizeof(*str) * 10);
	for (i = 0; i < 10; i++) {
		*(str + i) = (char*)malloc(sizeof(char) * 20);
	}
	ch = (char*)malloc(sizeof(char) * 10);
	ge = 0;
	code_list(str, ch, ht);
	printf("the code-list is:\n");
	for (i = 0; i < ge; i++) {
		printf("%c <-> ", ch[i]);
		puts(*(str + i));
	}
	printf("\nencoding:");
	for (i = 0; i < strlen(s); i++) {
		for (j = 0; j < ge; j++) {
			if (s[i] == ch[j]) {
				printf("%s", (*(str + j)));
				num += strlen(*(str + j));
				break;
			}
		}
	}
	printf("\n");
  return num;
}

// TODO:
// 用 Huffman 树 ht 对字符串 s
// （由0、1组成）进行解码，打印出解码结果，并返回解码后的长度
int huffman_decode(struct BTree *ht, char *s) {
	int i, num = 0;
	struct BTree *temp = ht;
	printf("\ndecoding:");
	for (i = 0; i < strlen(s); i++) {
		if (temp->left != NULL && temp->right != NULL) {
			if (s[i] == '0') {
				temp = temp->left;
			}
			else {
				temp = temp->right;
			}
		}
		else{
			printf("%c", temp->data.ch);
			i--;
			temp = ht;
		}
	}
	printf("\n");
  return num;
}
