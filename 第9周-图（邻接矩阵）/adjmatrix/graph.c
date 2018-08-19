#include "graph.h"

// TODO:
void graph_init(struct Graph *g, int num_vertices, enum GraphType type) 
{
	int i;
	g->type = type;
	g->v = num_vertices;
	g->e = 0;
	matrix_init(&g->m, num_vertices, num_vertices, 0);
	g->marked = (bool*)malloc(sizeof(bool)*num_vertices);
	for (i = 0; i<num_vertices; i++) {
		g->marked[i] = false;
	}
	g->path = (int *)malloc(sizeof(int)*num_vertices);
	for (i = 0; i<num_vertices; i++) {
		g->path[i] = -1;
	}
}

// TODO:
void graph_destroy(struct Graph *g) 
{
	g->v = 0;
	g->e = 0;
	matrix_destroy(&g->m);
}

// TODO:
void graph_add_edge(struct Graph *g, int u, int v, DataType weight) 
{
	g->e++;
	if (g->type) {
		matrix_set(&g->m, u, v, weight);
	}
	else {
		matrix_set(&g->m, u, v, weight);
		matrix_set(&g->m, v, u, weight);
	}
}

// TODO:
int graph_degree(struct Graph *g, int v) 
{ 
	if (g->type) {
		return graph_in_degree(g, v) + graph_out_degree(g, v);
	}
	else {
		int i, t = 0;
		for (i = 0; i<g->v; i++) {
			if (matrix_get(&g->m, v, i)) {
				t++;
			}
		}
		return t;
	}
}

// TODO:
int graph_in_degree(struct Graph *g, int v) 
{ 
	if (g->type) {
		int i, t = 0;
		for (i = 0; i<g->v; i++) {
			if (matrix_get(&g->m, i, v)) {
				t++;
			}
		}
		return t;
	}
	else {
		return graph_degree(g, v);
	}
}

// TODO:
int graph_out_degree(struct Graph *g, int v) 
{ 
	if (g->type) {
		int i, t = 0;
		for (i = 0; i<g->v; i++) {
			if (matrix_get(&g->m, v, i)) {
				t++;
			}
		}
		return t;
	}
	else {
		return graph_degree(g, v);
	}
}

// TODO:
// 判断是否连通图
bool graph_is_connected(struct Graph *g) 
{ 
	if (g->type) {
		int i, flag = 1, j;
		for (i = 0; i<g->v; i++) {
			for (j = 0; j<g->v; j++) {
				if (!graph_is_vertex_connected(g, i, j)) {
					flag = 0;
					break;
				}
			}
			if (flag == 0) {
				break;
			}
		}
		if (flag) {
			return true;
		}
	}
	else {
		int i, flag = 1, j;
		for (i = 0; i<g->v; i++) {
			for (j = i + 1; j<g->v; j++) {
				if (!graph_is_vertex_connected(g, i, j)) {
					flag = 0;
					break;
				}
			}
			if (flag == 0) {
				break;
			}
		}
		if (flag) {
			return true;
		}
	}
	return false;
}

// TODO:
// 判断两个顶点是否连通
bool graph_is_vertex_connected(struct Graph *g, int u, int v) 
{
	int *visited = (int *)malloc(sizeof(int)*(1 + g->v));
	int i;
	struct Queue Q;
	queue_init(&Q, g->v);
	queue_enqueue(&Q, u);
	for (i = 0; i <= g->v; i++) {
		visited[i] = 0;
	}
	visited[u] = 1;
	while (!queue_empty(&Q)) {
		int temp = queue_dequeue(&Q), flag = 0;
		if (temp == v) {
			return true;
		}
		for (i = 0; i<g->v; i++) {
			if (matrix_get(&g->m, temp, i)&&visited[i]==0) {
				queue_enqueue(&Q, i);
				visited[i] = 1;
			}
		}
	}
	return false;
}

// TODO:
// 两个顶点之间的距离
DataType graph_vertex_distance(struct Graph *g, int u, int v) 
{ 
	int *dis = (int*)malloc(sizeof(int)*(1 + g->v));
	int *visited = (int *)malloc(sizeof(int)*(1 + g->v));
	int i;
	struct Queue Q;
	queue_init(&Q, g->v);
	queue_enqueue(&Q, u);
	for (i = 0; i <= g->v; i++) {
		visited[i] = 0;
	}
	visited[u] = 1;
	dis[u] = 0;
	while (!queue_empty(&Q)) {
		int temp = queue_dequeue(&Q), flag = 0;
		if (temp == v) {
			return dis[temp];
		}
		for (i = 0; i<g->v; i++) {
			if (matrix_get(&g->m, temp, i)&&visited[i]==0) {
				queue_enqueue(&Q, i);
				visited[i] = 1;
				dis[i] = dis[temp] + 1;
			}
		}
	}
	return -1;
}

// TODO:
// 判断sg是否为g的子图
bool graph_is_subgraph(struct Graph *g, struct Graph *sg) 
{ 
	int flag = 1, i, j;
	if (sg->v > g->v || sg->e > g->e) {
		return false;
	}
	for (i = 0; i < sg->v; i++) {
		for (j = 0; j < sg->v; j++) {
			if (matrix_get(&g->m, i, j) < matrix_get(&sg->m, i, j)) {
				return false;
			}
		}
	}
	return true;
}

// TODO:
// 判断sg是否是g的（强）连通分量
bool graph_is_connected_component(struct Graph *g, struct Graph *sg) 
{
	if (graph_is_subgraph(g, sg) && graph_is_connected(sg)) {
		return true;
	}
	return false;
}

void graph_dfs(struct Graph *g, int v) {
	int i;
	g->marked[v] = true;
	for (i = 0; i<g->v; i++) {
		if (matrix_get(&g->m, v, i) && g->marked[i] == false) {
			g->marked[i] = true;
			g->path[i] = v;
			graph_dfs(g, i);
		}
	}
}

void graph_bfs(struct Graph *g, int v) {
	int i;
	struct Queue Q;
	queue_init(&Q,g->v);
	queue_enqueue(&Q, v);
	g->marked[v] = true;
	while (!queue_empty(&Q)) {
		DataType temp = queue_dequeue(&Q);
		for (i = 0; i<g->v; i++) {
			if (matrix_get(&g->m, v, i) && g->marked[i] == false) {
				g->marked[i] = true;
				g->path[i] = v;
				queue_enqueue(&Q, i);
			}
		}
	}
}