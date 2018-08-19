#include"queue.h"

void queue_init(Queue *q, int n) {
	vector_init(&q->v, n);
	q->head = q->tail = 0;
}

void queue_enqueue(Queue *q,int x) {
	vector_push_back(&q->v, x);
	q->tail = (q->tail + 1) % q->v.capacity;
}

DataType queue_dequeue(Queue *q) {
	DataType e;
	if (q->head == q->tail) {
		return -1;
	}
	e = q->v.buffer[q->head];
	vector_pop_front(&q->v);
	return e;
}

int queue_size(Queue *q) {
	return q->v.size;
}

void queue_destroy(Queue *q) {
	q->head = q->tail = 0;
	vector_destroy(&q->v);
}