//1、申请内存空间失败时的错误较为复杂，暂时无法解决内存空间不够的问题
//但在编写过程中发现可能会在传参过程中发生错误 即传入的的空间大小远远超过正确需要的大小
//此时可能为传参过程中 特别是带有指针的参数传递 混淆了指针与值 继而导致内存空间分配失败的问题
//2、创建一个新的顺序表时 可能会遇到传入的表的容量大小为非正数
//此时可以返回一个值（这里这个值为0）至main函数中 使main函数重新传入一个合法的cap值
//而若合法 则可以返回另一不同值加以区分（这里这个值为1）
//3、在对表进行插入、删除等会传入具体元素位置（pos）的操作中 与第二点相同 判断pos的值是否合法
//接下来的操作则与第二点相似

#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

void vector_realloc(struct vector *vec) {
	int *p = (int *)realloc(vec->data, vec->capacity * 2 * sizeof(int));
	if (p == NULL) {
		printf("Reallocate failed\n");//not deal
		return;
	}

	vec->data = p;
	vec->capacity *= 2;
}

int vector_new(struct vector *vec, int cap) {
	if (cap <= 0) {
		printf("Wrong capacity!\n");
		return 0;		//容量不合法 返回main函数重新输入cap的值
	}

	vec->data = (int *)malloc(cap * sizeof(int));
	if (vec->data == NULL) {
		printf("Allocate vector failed\n");
		return -1;
	}

	vec->capacity = cap;
	vec->size = 0;
	return 1;
}

void vector_destory(struct vector *vec) {
	if (vec->data != NULL) {
		free(vec->data);
		vec->data = NULL;
		vec->capacity = 0;
		vec->size = 0;
	}
}

void vector_print(struct vector *vec) {
	int i;

	for (i = 0; i < vec->size; i++) {
		printf("%d ", vec->data[i]);
	}
	printf("\n");
}

int vector_insert(struct vector *vec, int pos, int value) {
	int i;

	if (pos < 0 || pos > vec->size) {
		printf("Wrong insert position\n");//位置不合法
		return 0;
	}

	if (vec->size == vec->capacity) {
		vector_realloc(vec);
	}

	for (i = vec->size - 1; i >= pos; i--) {
		vec->data[i + 1] = vec->data[i];
	}

	vec->data[pos] = value;
	vec->size++;
	return 1;
}

void vector_push_back(struct vector *vec, int value) {
	vector_insert(vec, vec->size, value);
}

void vector_push_front(struct vector *vec, int value) {
	vector_insert(vec, 0, value);
}

int vector_remove_at(struct vector *vec, int pos) {
	int i;

	if (pos < 0 || pos > vec->size - 1) {
		printf("Delete at wrong position\n");//位置不合法
		return 0;
	}

	for (i = pos + 1; i < vec->size; i++) {
		vec->data[i - 1] = vec->data[i];
	}

	vec->size--;
	return 1;
}

void vector_pop_front(struct vector *vec) { vector_remove_at(vec, 0); }

void vector_pop_back(struct vector *vec) {
	vector_remove_at(vec, vec->size - 1);
}

void vector_delete_value(struct vector *vec, int value) {
	int pos = 0;

	while ((pos = vector_find_next(vec, value, pos)) != -1) {
		vector_remove_at(vec, pos);
	}
}

int vector_find_next(struct vector *vec, int value, int start_pos) {
	int i;

	if (vec->size == 0) {
		return -1;
	}

	if (start_pos < 0 || start_pos >= vec->size) {
		printf("Invalid start position\n");//位置不合法
		return -1;
	}

	for (i = start_pos; i < vec->size; i++) {
		if (vec->data[i] == value) {
			return i;
		}
	}

	return -1;
}

int vector_find_first(struct vector *vec, int value) {
	return vector_find_next(vec, value, 0);
}

void vector_union(struct vector *c, struct vector *a, struct vector *b) {
	int i;

	for (i = 0; i < a->size; i++) {
		if (vector_find_first(c, a->data[i]) == -1) {
			vector_push_back(c, a->data[i]);
		}
	}

	for (i = 0; i < b->size; i++) {
		if (vector_find_first(c, b->data[i]) == -1) {
			vector_push_back(c, b->data[i]);
		}
	}
}