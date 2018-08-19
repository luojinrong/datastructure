#include "sorted_list.h"
#include<stdio.h>

// TODO:
enum Status merge_sorted_lists(struct List *dst, struct List *src1, struct List *src2) {
	list_init(dst);
	while( src1->head != NULL&&src2->head != NULL) {
		if (src1->head->data <= src2->head->data) {
			if (dst->head == NULL) {
				dst->head = src1->head;
				dst->size++;
				src1->head = src1->head->next;
				src1->size--;
				dst->head->next = dst->tail;
				dst->tail = dst->head;
			}
			else {
				dst->tail->next = src1->head;
				dst->size++;
				dst->tail = src1->head;
				src1->head = src1->head->next;
				src1->size--;
			}
		}
		else {
			if (dst->head == NULL) {
				dst->head = src2->head;
				dst->size++;
				src2->head = src2->head->next;
				src2->size--;
				dst->head->next = dst->tail;
				dst->tail = dst->head;
			}
			else {
				dst->tail->next = src2->head;
				dst->size++;
				dst->tail = src2->head;
				src2->head = src2->head->next;
				src2->size--;
			}
		}
	}
	if (src1->head == NULL&&src2->head != NULL) {
		dst->tail->next = src2->head;
		dst->tail = src2->tail;
		dst->size += src2->size;
		src2->size = 0;
	}
	else {
		dst->tail->next = src2->head;
		dst->tail = src2->tail;
		dst->size += src2->size;
		src2->size = 0;
	}
	return STATUS_OK;
}

// TODO:
enum Status merge_multiple_lists(struct List *dst, struct List **srcs, int n) {
	int i;
	for (i = 0; i < n; i++) {
		struct ListNode *temp = dst->head, *from = ((*srcs)+i)->head;
		while (temp != NULL&&from != NULL) {
			if (temp == dst->head&&from->data <= temp->data) {
				((*srcs) + i)->head = ((*srcs) + i)->head->next;
				((*srcs) + i)->size--;
				from->next = dst->head;
				dst->size++;
				dst->head = from;
				from = ((*srcs) + i)->head;
			}
			if (from->data > temp->data && (temp->next == NULL || from->data <= temp->next->data)) {
				((*srcs) + i)->head = ((*srcs) + i)->head->next;
				((*srcs) + i)->size--;
				from->next = temp->next;
				temp->next = from;
				dst->size++;
				from = ((*srcs) + i)->head;
			}
			else {
				temp = temp->next;
			}
		}
		if (temp == NULL&&from != NULL) {
			if (dst->head == NULL) {
				dst->head = from;
				dst->tail = ((*srcs) + i)->tail;
				dst->size = ((*srcs) + i)->size;
				((*srcs) + i)->size = 0;
			}
			else {
				dst->tail->next = from;
				dst->tail = ((*srcs) + i)->tail;
				dst->size += ((*srcs) + i)->size;
				((*srcs) + i)->size = 0;
			}
		}
	}
	return STATUS_OK;
}