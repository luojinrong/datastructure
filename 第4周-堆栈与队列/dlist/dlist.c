#include "dlist.h"

#include <stdio.h>
#include <stdlib.h>

void dlist_init(struct DList *list) {
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
}

void dlist_destroy(struct DList *list) {
	while (dlist_size(list) > 0) {
		dlist_remove(list, list->tail);
	}

	dlist_init(list);
}

// TODO:
enum Status dlist_insert_after(struct DList *list, struct DListNode *node,
	DataType data) {
	struct DListNode *new_node = malloc(sizeof(struct DListNode));
	if (new_node == NULL) {
		return STATUS_ERR_ALLOC;
	}
	new_node->data = data;
	if (node == NULL) {
		if (dlist_size(list) == 0) {
			list->tail = new_node;
		}
		new_node->prev = NULL;
		new_node->next = list->head;
		list->head = new_node;
	}
	else {
		if (node->next == NULL) {
			list->tail = new_node;

		}
		else {
			node->next->prev = new_node;
		}
		new_node->next = node->next;
		node->next = new_node;
		new_node->prev = node;
	}
	list->size++;
	return STATUS_OK;
}

// TODO:
enum Status dlist_insert_before(struct DList *list, struct DListNode *node,
	DataType data) {
	struct DListNode *new_node = malloc(sizeof(struct DListNode));
	if (new_node == NULL) {
		return STATUS_ERR_ALLOC;
	}
	new_node->data = data;
	if (node == NULL) {
		if (dlist_size(list) != 0) {
			list->head->prev = new_node;
		}
		new_node->prev = NULL;
		new_node->next = list->head;
		list->head = new_node;
	}
	else {
		if (node->prev == NULL) {
			list->head = new_node;
			new_node->prev = NULL;
		}
		else {
			node->prev->next = new_node;
			new_node->prev = node->prev;
		}
		node->prev = new_node;
		new_node->next = node;
	}
	list->size++;
	return STATUS_OK;
}

enum Status dlist_push_front(struct DList *list, DataType data) {
	return dlist_insert_before(list, list->head, data);
}

enum Status dlist_push_back(struct DList *list, DataType data) {
	return dlist_insert_after(list, list->tail, data);
}

// TODO:
enum Status dlist_remove(struct DList *list, struct DListNode *node) {
	if (dlist_size(list) == 0) {
		return STATUS_ERR_INVALID_RANGE;
	}
	if (node == NULL) {
		return STATUS_OK;
	}
	else {
		if (dlist_size(list) == 1) {
			dlist_init(list);
		}
		else if (node == list->head) {
			list->head = node->next;
			list->head->prev = NULL;
			list->size--;
		}
		else if (node == list->tail) {
			list->tail = node->prev;
			list->tail->next = NULL;
			list->size--;
		}
		else {
			node->prev->next = node->next;
			node->next->prev = node->prev;
			list->size--;
		}
		free(node);
	}
	return STATUS_OK;
}

enum Status dlist_pop_front(struct DList *list) {
	return dlist_remove(list, list->head);
}

enum Status dlist_pop_back(struct DList *list) {
	return dlist_remove(list, list->tail);
}

int dlist_size(struct DList *list) {
	return list->size;
}