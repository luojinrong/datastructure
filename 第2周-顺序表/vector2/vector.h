
#ifndef DS_VECTOR_H_
#define DS_VECTOR_H_
typedef int ElemType;//可根据实际需要修改ElemType所代表的数据类型

struct vector {
	int capacity;
	int size;
	ElemType *data;
};

void vector_new(struct vector *vec, int cap);

void vector_destory(struct vector *vec);

void vector_print(struct vector *vec);

void vector_insert(struct vector *vec, int pos, ElemType value);

void vector_push_back(struct vector *vec, ElemType value);

void vector_push_front(struct vector *vec, ElemType value);

void vector_remove_at(struct vector *vec, int pos);

void vector_pop_front(struct vector *vec);

void vector_pop_back(struct vector *vec);

int vector_find_first(struct vector *vec, ElemType value);

int vector_find_next(struct vector *vec, ElemType value, int start_pos);

void vector_delete_value(struct vector *vec, ElemType value);

void vector_union(struct vector *c, struct vector *a, struct vector *b);

/* Methods to be implemented */
//void vector_reverse(struct vector *vec);
//
//void vector_swap(struct vector *a, struct vector *b);
//
//void vector_shrink_to_fit(struct vector *vec);
//
//int at(struct vector *vec, int index);

#endif  /*DS_VECTOR_H_ */