#include "clist.h"

#include <stdio.h>

// TODO:
void print_clist(struct CList *list) {
	struct CListNode *node;
	node = list->head;
	if (node == NULL) {
		return;
	}
	else {
		do {
			printf("%lf ", node->data);
			node = node->next;
		} while (node != list->head);
		printf("\n");
	}
}

int main() {
	struct CList list;
	int i;

	clist_init(&list);

	//clist_insert_after_text
	for (i = 0; i < 5; i++) {
		clist_insert_after(&list, list.head, i);
	}
	print_clist(&list);
	printf("%d\n", list.size);


	//clist_remove_after_text
	for (i = 0; i < 5; i++) {
		clist_remove_after(&list, list.head);
		print_clist(&list);
		printf("%d\n", list.size);
	}
	return 0;
}