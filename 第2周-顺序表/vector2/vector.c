#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

void vector_realloc(struct vector *vec) {
	ElemType *p = (ElemType *)realloc(vec->data, vec->capacity * 2 * sizeof(ElemType));
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

	vec->data = (ElemType *)malloc(cap * sizeof(ElemType));
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
		printf("%d ", vec->data[i]);//����ElemType���������޸������ʽ
	}
	printf("\n");
}

void vector_insert(struct vector *vec, int pos, ElemType value) {
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

void vector_push_back(struct vector *vec, ElemType value) {
	vector_insert(vec, vec->size, value);
}

void vector_push_front(struct vector *vec, ElemType value) {
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

void vector_delete_value(struct vector *vec, ElemType value) {
	int pos = 0;

	while ((pos = vector_find_next(vec, value, pos)) != -1) {
		vector_remove_at(vec, pos);
	}
}

int vector_find_next(struct vector *vec, ElemType value, int start_pos) {
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

int vector_find_first(struct vector *vec, ElemType value) {
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