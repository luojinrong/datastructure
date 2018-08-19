#include "vector.h"
#include <stdio.h>


int main() {
	struct vector v;
	int i,cap;
	while (scanf_s("%d", &cap)) {
		if (vector_new(&v, cap) == 1)
			break;
		else
			printf("Please enter a valid value.\n");
	}
	
	

	for (i = 0; i < 5; i++) {
		vector_push_back(&v, i);
	}




	vector_print(&v);

	vector_destory(&v);
	

	return 0;
}