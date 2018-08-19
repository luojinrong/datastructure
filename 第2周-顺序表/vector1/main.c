#include "vector.h"
#include <stdio.h>

int main() {
	struct vector v, a, b;
	int i;

	vector_new(&v, 10);
	vector_new(&a, 10);
	vector_new(&b, 10);

	//at
	//for (i = 0; i < 5; i++)
	//	vector_push_back(&v, i);
	//for (i = -5; i < 7; i++)
	//	printf("%d\n",at(&v, i));

	//vector_shrink_to_fit
	/*for (i = 0; i < 5; i++)
		vector_push_back(&v, i);
	vector_shrink_to_fit(&v);
	printf("%d\n", v.capacity);*/

	//vector_swap text
	/*for (i = 0; i < 7; i++)
		vector_push_back(&a, i);
	for (i = 4; i < 18; i++)
		vector_push_back(&b, i);
	vector_swap(&a, &b);
	vector_print(&a);
	vector_print(&b);*/

	//vector_reverse test
	/*for (i = 0; i < 10; i++) {
		vector_push_back(&v, i);
	}
	vector_reverse(&v);
	vector_print(&v);*/

	/*for (i = 0; i < 5; i++) {
		vector_push_back(&a, i);
	}

	for (i = 2; i < 7; i++) {
		vector_push_back(&b, i);
	}

	vector_union(&v, &a, &b);*/



	/* for (i = 0; i < 10; i++) { */
	/*   vector_push_front(&v, i); */
	/* } */
	/* vector_print(&v); */

	/* for (i = 0 ; i < 5; i++) { */
	/*   vector_pop_back(&v); */
	/* } */

	/* vector_print(&v); */

	/* for (i = 0; i < 5; i++) { */
	/*   vector_push_back(&v, i); */
	/* } */
	/* for (i = 0; i < 5; i++) { */
	/*   vector_push_back(&v, i); */
	/* } */
	/* for (i = 0; i < 5; i++) { */
	/*   vector_push_back(&v, i); */
	/* } */

	/* vector_print(&v); */

	/* printf("Find all zero positions\n"); */
	/* i = vector_find_first(&v, 0); */
	/* printf("%d\n", i); */

	/* while ((i = vector_find_next(&v, 0, i+1)) != -1) { */
	/*   printf("%d\n", i); */
	/* } */

	/* vector_delete_value(&v, 0); */

	/*vector_print(&v);*/

	vector_destory(&v);
	vector_destory(&a);
	vector_destory(&b);

	return 0;
}