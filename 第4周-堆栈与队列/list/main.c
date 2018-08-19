#include "list.h"
#include "sorted_list.h"
#include <stdio.h>
#include<stdlib.h>

void print_list(struct List *list) {
	struct ListNode *p = list->head;

	while (p) {
		printf("%d ", p->data);
		p = p->next;
	}

	printf("\n");
}


int main() {
	
	
	//merge_sorted_list_text
	/*struct List dst, src1, src2;
	int i;
	list_init(&dst);
	list_init(&src1);
	list_init(&src2);
	for (i = 0; i < 5; i++) {
		list_push_back(&src1, i);
	}
	for (i = 3; i < 8; i++) {
		list_push_back(&src2, i);
	}
	merge_sorted_lists(&dst, &src1, &src2);
	print_list(&dst);
	printf("%d\n", dst.size);*/

	//merge_multiple_lists_text
	struct List dst, *src;
	int i, n, j;
	scanf_s("%d", &n);
	list_init(&dst);
	src = (struct List*)malloc(sizeof(struct List)*n);
	for (i = 0; i < n; i++) {
		list_init(&src[i]);
		for (j = i; j < i + 5; j++) {
			list_push_back(&src[i], j);
		}
	}
	merge_multiple_lists(&dst, &src, n);
	print_list(&dst);
	printf("%d\n", dst.size);

	return 0;
}