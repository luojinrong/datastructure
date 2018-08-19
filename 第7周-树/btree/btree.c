#include "btree.h"
#include"queue.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct BTree *btree_create(char root, struct BTree *left, struct BTree *right) {
  struct BTree *root_node = malloc(sizeof(struct BTree));
  root_node->data = root;
  root_node->left = left;
  root_node->right = right;

  return root_node;
}

void btree_destroy(struct BTree *root) {
  if (root == NULL) {
    return;
  }

  btree_destroy(root->left);
  btree_destroy(root->right);
  free(root);
}

struct BTree *btree_from_pre_mid(char *pre, char *mid, int len) {
  if (len == 0) {
    return NULL;
  }

  char *root = strchr(mid, pre[0]);
  if (root == NULL) {
    return NULL;
  }

  int ll = root - mid;
  struct BTree *left = btree_from_pre_mid(pre + 1, mid, ll);
  struct BTree *right =
      btree_from_pre_mid(pre + ll + 1, root + 1, len - ll - 1);

  return btree_create(*root, left, right);
}

// TODO:
// 根据后序`post`和中序`mid`遍历构建一棵二叉树
struct BTree *btree_from_post_mid(char *post, char *mid, int len) {
    struct BTree *root_node=(struct BTree*)malloc(sizeof(struct BTree));

    char root=post[len-1];
    int i;
    if(len==0){
        return NULL;
    }
    for(i=0;i<len;i++){
        if(mid[i]==root){
            break;
        }
    }
    if(i==len){
        return NULL;
    }
    root_node->data=root;
    root_node->left=btree_from_post_mid(post,mid,i);
    root_node->right=btree_from_post_mid(post+i,mid+i+1,len-i-1);
    return root_node;
}

// TODO:
// 根据层次`level`和中序`mid`遍历构建一棵二叉树
struct BTree *btree_from_level_mid(char *level, char *mid, int len) {
    char root=level[0],level1[20],level2[20];
    int i,j,m,l1=0,l2=0,flag[20];
    struct BTree* root_node=(struct BTree*)malloc(sizeof(struct BTree));
    if(len==0){
        return NULL;
    }
    for(i=0;i<len;i++){
        if(root==mid[i]){
            break;
        }
    }
    if(i==len){
        return NULL;
    }
    for(j=0;j<len;j++){
        for(m=i;m<len;m++){
            if(level[j]==mid[m]){
                break;
            }
        }
        if(m==len){
            level1[l1++]=level[j];
            level1[l1] = 0;
        }
        else{
            if (level[j] != root) {
                level2[l2++] = level[j];
                level2[l2] = 0;
                //level[j]='0';
            }
        }
    }
    root_node->data=root;
    root_node->left=btree_from_level_mid(level1,mid,l1);
    root_node->right=btree_from_level_mid(level2,mid+i+1,l2);
    return root_node;
}

// TODO:
// 根据字符串`s`构建一棵搜索二叉树
struct BTree *btree_build_search_tree(char *s) {
    int i;
    struct BTree *root=NULL;
    for(i=0;i<strlen(s);i++){
        struct BTree * root_node=(struct BTree*)malloc(sizeof(struct BTree));
        struct BTree *p=root;
        root_node->data=s[i];
        root_node->left=NULL;
        root_node->right=NULL;
        while(p){
            if(root_node->data<p->data){
                if(p->left){
                    p=p->left;
                }
                else{
                    p->left=root_node;
					break;
                }
            }
            else{
                if(p->right){
                    p=p->right;
                }
                else{
                    p->right=root_node;
					break;
                }
            }
        }
        if(root==NULL){
            root=root_node;
        }
    }
    return root;
}

// TODO:
// 在二叉搜索树`root`中查找`value`，如果找到返回相应节点，否则返回NULL
struct BTree *btree_find(struct BTree *root, char value) {
    if(root==NULL){
        return NULL;
    }
    if(root->data==value){
        return root;
    }
    else if(root->data<value){
        return btree_find(root->left,value);
    }
    else{
        return btree_find(root->right,value);
    }
}

void btree_pre_order(struct BTree *root) {
  if (root == NULL) {
    return;
  }

  putchar(root->data);
  btree_pre_order(root->left);
  btree_pre_order(root->right);
}

void btree_mid_order(struct BTree *root) {
  if (root == NULL) {
    return;
  }

  btree_mid_order(root->left);
  putchar(root->data);
  btree_mid_order(root->right);
}

void btree_post_order(struct BTree *root) {
  if (root == NULL) {
    return;
  }

  btree_post_order(root->left);
  btree_post_order(root->right);
  putchar(root->data);
}

// TODO:
// 对二叉树进行层次遍历
void btree_level_order(struct BTree *root) 
{
    struct Queue Q;
    if (root == NULL) {
        return;
    }
    queue_init(&Q,10);
    queue_enqueue(&Q, root);
    while (!queue_empty(&Q)) {
        struct BTree *p;
        p = queue_dequeue(&Q);
        printf("%c", p->data);
        if (p->left != NULL) {
            queue_enqueue(&Q, p->left);
        }
        if (p->right != NULL) {
            queue_enqueue(&Q, p->right);
        }
    }
}

int max(int a, int b) { return a > b ? a : b; }

int btree_depth(struct BTree *root) {
  if (root == NULL) {
    return 0;
  }

  return 1 + max(btree_depth(root->left), btree_depth(root->right));
}

int btree_leaves(struct BTree *root) {
  if (root == NULL) {
    return 0;
  }

  if (root->left == NULL && root->right == NULL) {
    return 1;
  }

  return btree_leaves(root->left) + btree_leaves(root->right);
}

void btree_flip(struct BTree *root) {
  if (root == NULL) {
    return;
  }

  struct BTree *tmp = root->left;
  root->left = root->right;
  root->right = tmp;

  btree_flip(root->left);
  btree_flip(root->right);
}

// TODO:
// 判断两棵树是否相同, 相同返回1， 不同返回0
int btree_is_same(struct BTree *a, struct BTree *b) {
	if (a == NULL && b == NULL) {
		return 1;
	}
	if (a->data == b->data&&btree_is_same(a->left, b->left) && btree_is_same(a->right, b->right)) {
		return 1;
	}
	return 0;
}

// TODO:
// 判断两棵树是否同构，即能够通过若干次左右子树的交换由a变为b，同构返回1，不同构返回2
int btree_is_isomorphic(struct BTree *a, struct BTree *b) {
	if (a == NULL && b == NULL) {
		return 1;
	}
	else if ((a == NULL && b != NULL) || (a != NULL && b == NULL)) {
		return 2;
	}
	else {
		if ((a->data == b->data) && ((btree_is_isomorphic(a->left, b->left)==1 && btree_is_isomorphic(a->right, b->right)==1) || (btree_is_isomorphic(a->left, b->right)==1 && btree_is_isomorphic(a->right, b->left)==1))) {
			return 1;
		}

		else {
			return 2;
		}
	}
}
