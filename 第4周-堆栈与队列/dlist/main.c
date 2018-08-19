#include "dlist.h"

#include <stdio.h>

void print_dlist(struct DList *list) {
	struct DListNode *p = list->head;

	while (p) {
		printf("%.1f ", p->data);
		p = p->next;
	}

	printf("\n");
}

int main() {
	struct DList list;
	struct DListNode *node;
	int i;
	dlist_init(&list);


	//dlist_insert_after_text
	/*for (i = 0; i < 5; i++) {
		dlist_push_back(&list, i);
	}
	node = list.head->next->next;
	for (i = 9; i < 12; i++) {
		dlist_insert_after(&list, node, i);
	}
	node = list.tail;
	dlist_insert_after(&list, node, 100);
	print_dlist(&list);
	printf("%d\n", list.size);
	dlist_destroy(&list);*/

	//dlist_insert_before_text
	/*for (i = 0; i < 5; i++) {
		dlist_push_back(&list, i);
	}
	node = list.head->next->next;
	for (i = 9; i < 11; i++) {
		dlist_insert_before(&list, node, i);
	}
	node = list.head;
	dlist_insert_before(&list, node, 100);
	print_dlist(&list);
	printf("%d\n", list.size);*/

	//dlist_remove_text
	for (i = 0; i < 5; i++) {
		dlist_push_back(&list, i);
	}
	node = list.head->next->next;
	dlist_remove(&list, node);
	print_dlist(&list);
	printf("%d\n", list.size);
	dlist_remove(&list, list.head);
	print_dlist(&list);
	printf("%d\n", list.size);
	dlist_remove(&list, list.tail);
	print_dlist(&list);
	printf("%d\n", list.size);

	return 0;
}