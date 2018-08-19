#include "clist.h"

#include <stdio.h>
#include <stdlib.h>

void clist_init(struct CList *list) {
	list->size = 0;
	list->head = NULL;
}

void clist_destroy(struct CList *list) {
	while (clist_size(list) > 0) {
		clist_remove_after(list, list->head);
	}
}

// TODO:
enum Status clist_insert_after(struct CList *list, struct CListNode *node,
	DataType data) {
	struct CListNode *new_node = malloc(sizeof(struct CListNode));
	if (new_node == NULL) {
		return STATUS_ERR_ALLOC;
	}
	new_node->data = data;
	if (clist_size(list) == 0) {
		list->head = new_node;
		new_node->next = new_node;
	}
	else {
		new_node->next = node->next;
		node->next = new_node;
	}
	list->size++;
	return STATUS_OK;
}

// TODO:
enum Status clist_remove_after(struct CList *list, struct CListNode *node) {
	struct CListNode *old_node;
	old_node = node->next;
	if (clist_size(list) == 0) {
		return STATUS_ERR_INVALID_RANGE;
	}
	
	else {
		if (node->next == list->head) {
			list->head = list->head->next;
		}
		if (clist_size(list) == 1) {
			list->head = NULL;
		}
		
		else {
			node->next = node->next->next;
		}
		list->size--;
		free(old_node);
	}
	return STATUS_OK;
}

// Get list size
int clist_size(struct CList *list) { return list->size; }