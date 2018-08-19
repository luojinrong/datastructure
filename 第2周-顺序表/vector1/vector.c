#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

void vector_realloc(struct vector *vec) {
	int *p = (int *)realloc(vec->data, vec->capacity * 2 * sizeof(int));
	if (p == NULL) {
		printf("Reallocate failed\n");
		return;
	}

	vec->data = p;
	vec->capacity *= 2;
}

void vector_new(struct vector *vec, int cap) {
	if (cap <= 0) {
		printf("Wrong capacity!\n");
		return;
	}

	vec->data = (int *)malloc(cap * sizeof(int));
	if (vec->data == NULL) {
		printf("Allocate vector failed\n");
		return;
	}

	vec->capacity = cap;
	vec->size = 0;
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

void vector_insert(struct vector *vec, int pos, int value) {
	int i;

	if (pos < 0 || pos > vec->size) {
		printf("Wrong insert position\n");
		return;
	}

	if (vec->size == vec->capacity) {
		vector_realloc(vec);
	}

	for (i = vec->size - 1; i >= pos; i--) {
		vec->data[i + 1] = vec->data[i];
	}

	vec->data[pos] = value;
	vec->size++;
	return;
}

void vector_push_back(struct vector *vec, int value) {
	vector_insert(vec, vec->size, value);
}

void vector_push_front(struct vector *vec, int value) {
	vector_insert(vec, 0, value);
}

void vector_remove_at(struct vector *vec, int pos) {
	int i;

	if (pos < 0 || pos > vec->size - 1) {
		printf("Delete at wrong position\n");
		return;
	}

	for (i = pos + 1; i < vec->size; i++) {
		vec->data[i - 1] = vec->data[i];
	}

	vec->size--;
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
		printf("Invalid start position\n");
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
// 将vec中的元素反过来，比如原来是1、2、3，调用后变成3、2、1
void vector_reverse(struct vector *vec)
{
	int i, temp;
	for (i = 0; i < (vec->size / 2); i++)
	{
		temp = vec->data[i];
		vec->data[i] = vec->data[vec->size - 1 - i];
		vec->data[vec->size - 1 - i] = temp;
	}
}
// 交换a和b两个向量的内容
void vector_swap(struct vector *a, struct vector *b)
{
	int i;
	struct vector temp;
	vector_new(&temp, a->capacity);
	for (i = 0; i < a->size; i++)
		temp.data[i] = a->data[i];
	temp.size = a->size;

	while (a->capacity < b->size)
		vector_realloc(a);
	for (i = 0; i < b->size; i++)
		a->data[i] = b->data[i];
	a->size = b->size;
	while (b->capacity < temp.size)
		vector_realloc(b);
	for (i = 0; i < temp.size; i++)
		b->data[i] = temp.data[i];
	b->size = temp.size;
}
// 将vec的内存缩小到恰好能存放所有元素
void vector_shrink_to_fit(struct vector *vec)
{
	int *p = (int *)realloc(vec->data, vec->size * sizeof(int));
	if (p == NULL) {
		printf("Reallocate failed\n");
		return;
	}
	vec->data = p;
	vec->capacity = vec->size;
}
// 取出向量的第index个元素，允许index越界：如果vec有5个元素，index为-1返回倒数第一个，index为5返回第一个，即越界时从向量另一边开始数
int at(struct vector *vec, int index)
{
	index %= vec->size;
	if (index < 0)
		index += 5;
	return vec->data[index];
}