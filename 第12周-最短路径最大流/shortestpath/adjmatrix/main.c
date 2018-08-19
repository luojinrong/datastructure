#include "graph.h"

#include <stdio.h>

void init_short(struct Graph *g)
{
	graph_init(g, 7, 1);
	matrix_set(&g->m, 0, 1, 2);
	matrix_set(&g->m, 1, 4, 10);
	matrix_set(&g->m, 1, 6, 6);
	matrix_set(&g->m, 6, 5, 1);
	matrix_set(&g->m, 2, 5, 5);
	matrix_set(&g->m, 2, 0, 4);
	matrix_set(&g->m, 0, 3, 1);
	matrix_set(&g->m, 1, 3, 3);
	matrix_set(&g->m, 3, 2, 2);
	matrix_set(&g->m, 3, 5, 8);
	matrix_set(&g->m, 3, 6, 4);
	matrix_set(&g->m, 3, 4, 2);
}

void test_dijikstra()
{
	struct Graph g;
	int i;
	init_short(&g);
	graph_dijikstra(&g, 0);
	for (i = 0; i < g.v; i++) {
		printf("the distanse of 0 to %d : %d\n", i,g.dists[i]);
	}
	printf("\n");
}

void test_floyd()
{
	struct Graph g;
	struct Matrix m;
	int i, j;
	init_short(&g);
	matrix_init(&m, g.v, g.v, 0);
	for (i = 0; i < m.rows; i++) {
		for (j = 0; j < m.cols; j++) {
			matrix_set(&m, i, j, 999);//假设任意两点间的最小距离不超过999
		}
		matrix_set(&m, i, i, 0);
	}
	graph_floyd(&g, &m);
	printf("     ");
	for (i = 0; i < g.v; i++) {
		printf("%5d", i);
	}
	printf("\n");
	for (i = 0; i < g.v; i++) {
		printf("%5d", i);
		for (j = 0; j < g.v; j++) {
			printf("%5d", matrix_get(&m, i, j));
		}
		printf("\n");
	}
	printf("\n");
}

void init_max_flow(struct Graph *g)
{
	graph_init(g, 6, 1);
	matrix_set(&g->m, 0, 1, 3);
	matrix_set(&g->m, 0, 2, 2);
	matrix_set(&g->m, 1, 2, 1);
	matrix_set(&g->m, 1, 3, 3);
	matrix_set(&g->m, 1, 4, 4);
	matrix_set(&g->m, 2, 4, 2);
	matrix_set(&g->m, 3, 5, 2);
	matrix_set(&g->m, 4, 5, 3);
}

void test_ford_fulkerson()
{
	struct Graph g, flow;
	int max;
	init_max_flow(&g);
	graph_init(&flow, 6, 1);
	max=graph_ford_fulkerson(&g, &flow, 0, 5);
	printf("%d\n", max);
}

int main()
{
	printf("test dojikstra:\n");
	test_dijikstra();
	printf("test floyd:\n");
	test_floyd();
	printf("test Ford Fulkerson:\n");
	test_ford_fulkerson();
}