#include "stack.h"
#include<stdio.h>
extern int MaxSize;
void stack_init(Stack *S, int n) {
	list_init(S);
	MaxSize = n;
}
//链表头作为栈顶
void stack_push(Stack *S, DataType x) {
	list_push_front(S, x);
}

int stack_empty(Stack *S) {
	return !list_size(S);
}

int stack_pop(Stack *S) {
	DataType e;
	e = S->head->data;
	list_pop_front(S);
	return e;
}

void stack_destroy(Stack *S) {
	list_destroy(S);
}