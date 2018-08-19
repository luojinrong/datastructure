#pragma once


#include "list.h"

typedef struct List Stack;

struct LStack {
	int top;
	Stack S;
};

void stack_init(Stack *S, int n);

void stack_push(Stack *S, DataType x);

int stack_empty(Stack *S);

int stack_pop(Stack *S);

void stack_destroy(Stack *S);