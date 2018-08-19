#pragma once

#include "vector.h"

typedef struct {
	struct Vector v;
	int head;
	int tail;
}Queue;

void queue_init(Queue *q, int n);

void queue_enqueue(Queue *q,int x);

DataType queue_dequeue(Queue *q);

DataType queue_size(Queue *q);

void queue_destroy(Queue *q);