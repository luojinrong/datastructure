#include "graph.h"

//重置图中的marked与path数组
void graph_mark_path_init(struct Graph *g)
{
	int i;
	for (i = 0; i < g->v; i++) {
		g->marked[i] = false;
		g->path[i] = -1;
	}
}
//TODO:
void graph_init(struct Graph *g, int num_vertices, enum GraphType type)
{
	int i;
	g->v = num_vertices;
	g->e = 0;
	g->type = type;
	vector_init(&g->adjlist, num_vertices);
	g->marked = (bool*)malloc(sizeof(bool)*num_vertices);
	for (i = 0; i < num_vertices; i++) {
		g->marked[i] = false;
	}
	g->path = (int*)malloc(sizeof(int)*num_vertices);
	for (i = 0; i < num_vertices; i++) {
		g->path[i] = -1;
	}
}
//TODO:
void graph_destroy(struct Graph *g)
{
	g->v = g->e = 0;
	vector_destroy(&g->adjlist);
	free(g->marked);
	free(g->path);
}
//TODO:
void graph_add_edge(struct Graph *g, int u, int v, int value)
{
	list_push_back(&g->adjlist.buffer[u].adj_verts, v);
	g->adjlist.buffer[u].adj_verts.tail->value = value;
	g->e++;
	if (g->type == 0) {
		list_push_back(&g->adjlist.buffer[v].adj_verts, u);
		g->adjlist.buffer[v].adj_verts.tail->value = value;
	}
}
//TODO:
int graph_degree(struct Graph *g, int v)
{
	if (g->type) {
		return (graph_in_degree(g, v) + graph_out_degree(g, v));
	}
	return list_size(&g->adjlist.buffer[v].adj_verts);
}
//TODO:
int graph_in_degree(struct Graph *g, int v) {
	int num = 0;
	if (g->type) {
		int i;
		for (i = 0; i < g->v; i++) {
			struct ListNode *temp = g->adjlist.buffer[i].adj_verts.head;
			while (temp) {
				if (temp->data == v) {
					num++;
				}
				temp = temp->next;
			}
		}
	}
	else {
		num = graph_degree(g, v);
	}
	return num;
}
//TODO:
int graph_out_degree(struct Graph *g, int v) {
	return list_size(&g->adjlist.buffer[v].adj_verts);
}
//TODO:
// 判断是否连通图
bool graph_is_connected(struct Graph *g)
{
	int i, j;
	if (g->type) {
		for (i = 0; i < g->v; i++) {
			for (j = 0; j < g->v; j++) {
				if (!graph_is_vertex_connected(g, i, j)) {
					return false;
				}
			}
		}
		return true;
	}
	else {
		for (i = 0; i < g->v; i++) {
			for (j = i + 1; j < g->v; j++) {
				if (!graph_is_vertex_connected(g, i, j)) {
					return false;
				}
			}
		}
		return true;
	}
}
//TODO:
// 判断两个顶点是否连通
bool graph_is_vertex_connected(struct Graph *g, int u, int v)
{
	Queue Q;
	queue_init(&Q);
	queue_enqueue(&Q, u);
	g->marked[u] = true;
	while (!queue_empty(&Q)) {
		int temp = queue_dequeue(&Q);
		struct ListNode *t = g->adjlist.buffer[temp].adj_verts.head;
		if (temp == v) {
			graph_mark_path_init(g);
			return true;
		}
		while (t) {
			if (g->marked[t->data] == false) {
				queue_enqueue(&Q, t->data);
				g->marked[t->data] = true;
			}
			t = t->next;
		}
	}
	graph_mark_path_init(g);
	return false;
}
//TODO:
// 两个顶点之间的距离
DataType graph_vertex_distance(struct Graph *g, int u, int v)
{
	if (!graph_is_vertex_connected(g, u, v)) {
		return -1;
	}
	Queue Q;
	int *dis = (int*)malloc(sizeof(int)*g->v);
	queue_init(&Q);
	queue_enqueue(&Q, u);
	g->marked[u] = true;
	dis[u] = 0;
	while (queue_empty(&Q)) {
		int temp = queue_dequeue(&Q);
		struct ListNode *t = g->adjlist.buffer[temp].adj_verts.head;
		if (temp == v) {
			int i;
			for (i = 0; i < g->v; i++) {
				g->marked[i] = false;
			}
			return dis[temp];
		}
		while (t) {
			if (g->marked[t->data] == false) {
				queue_enqueue(&Q, t->data);
				g->marked[t->data] = true;
				dis[t->data] = dis[temp] + 1;
			}
			t = t->next;
		}
	}
}
//TODO:
void graph_dfs(struct Graph *g, int v)
{
	struct ListNode *t = g->adjlist.buffer[v].adj_verts.head;
	g->marked[v] = true;
	printf("%d ", v);
	while (t) {
		if (!g->marked[t->data]) {
			g->path[t->data] = v;
			graph_dfs(g, t->data);
		}
		t = t->next;
	}
}
//TODO:
void graph_bfs(struct Graph *g, int v)
{
	Queue Q;
	queue_init(&Q);
	queue_enqueue(&Q, v);
	g->marked[v] = true;
	while (!queue_empty(&Q)) {
		int temp = queue_dequeue(&Q);
		printf("%d ", temp);
		struct ListNode *t = g->adjlist.buffer[temp].adj_verts.head;
		while (t) {
			if (!g->marked[t->data]) {
				g->marked[t->data] = true;
				g->path[t->data] = temp;
				queue_enqueue(&Q, t->data);
			}
			t = t->next;
		}
	}
}
//TODO:
// 判断图g是不是树
bool graph_is_tree(struct Graph *g)
{
	int i, flag = 0;
	for (i = 0; i < g->v; i++) {
		struct ListNode *temp = g->adjlist.buffer[i].adj_verts.head;
		 while(temp) {
			if (g->marked[temp->data] == 1) {
				return false;
			}
			if (temp->data > i) {
				g->marked[temp->data] = 1;
			}
			temp = temp->next;
		}
	}
	graph_mark_path_init(g);
	return true;
}

//TODO:
// 判断t是不是g的生成树
bool graph_is_spanning_tree(struct Graph *g, struct Graph *t)
{
	if (graph_is_tree(t) && t->e < t->v) {
		return true;
	}
	return false;
}
//TODO:
// 用dfs生成g的一棵最小生成树
void graph_spanning_tree_dfs(struct Graph *g, struct Graph *t) 
{
	int i, ti;
	graph_dfs(g, 0);
	printf("\n");
	for (i = 0; i < g->v; i++) {
		if (g->path[i] != -1) {
			struct ListNode *temp = g->adjlist.buffer[i].adj_verts.head;
			while(temp) {
				if (temp->data == g->path[i]) {
					ti = temp->value;
				}
				temp = temp->next;
			}
			graph_add_edge(t, g->path[i], i, ti);
		}
	}
	graph_mark_path_init(g);
}

//TODO:
// 用bfs生成g的一棵最小生成树
void graph_spanning_tree_bfs(struct Graph *g, struct Graph *t) 
{
	int i, ti;
	graph_bfs(g, 0);
	printf("\n");
	for (i = 0; i < g->v; i++) {
		if (g->path[i] != -1) {
			struct ListNode *temp = g->adjlist.buffer[i].adj_verts.head;
			while (temp) {
				if (temp->data == g->path[i]) {
					ti = temp->value;
				}
				temp = temp->next;
			}
			graph_add_edge(t, g->path[i], i, ti);
		}
	}
	graph_mark_path_init(g);
}

//TODO:
// 用prim算法生成g的一棵最小生成树
void graph_spanning_tree_prim(struct Graph *g, struct Graph *t) 
{
	sort_edge min;int i;
	while (1) {
		min.next = NULL;
		min.value = INT_MAX;
		int flag = 0;
		if (t->e == 0) {
			for (i = 0; i < g->v; i++) {
				struct ListNode *temp = g->adjlist.buffer[i].adj_verts.head;
				while (temp) {
					if (temp->value < min.value) {
						min.value = temp->value;
						min.v1 = temp->data;
						min.v2 = i;
					}
					temp = temp->next;
				}
			}
			graph_add_edge(t, min.v1, min.v2, min.value);
		}
		else {
			int i;
			for (i = 0; i < g->v; i++) {
				if (t->adjlist.buffer[i].adj_verts.head) {
					struct ListNode *temp = g->adjlist.buffer[i].adj_verts.head;
					while (temp) {
						if (temp->value < min.value && (!graph_is_vertex_connected(t, i, temp->data))) {
							min.value = temp->value;
							min.v1 = temp->data;
							min.v2 = i;
						}
						temp = temp->next;
					}
				}
			}
			graph_add_edge(t, min.v1, min.v2, min.value);
		}
		for (i = 0; i < t->v; i++) {
			struct ListNode *temp = t->adjlist.buffer[i].adj_verts.head;
			if (!temp) {
				flag = 1;
				break;
			}
		}
		if (!flag) {
			break;
		}
	}
}

//TODO:
// 用kruskal算法生成g的一棵最小生成树
void graph_spanning_tree_kruskal(struct Graph *g, struct Graph *t) 
{
	int i, j, flag;
	sort_edge *head=NULL,*tail=NULL;
	for (i = 0; i < g->v; i++) {
		struct ListNode *temp = g->adjlist.buffer[i].adj_verts.head;
		while (temp) {
			sort_edge *ti = (sort_edge*)malloc(sizeof(sort_edge));
			ti->v1 = i;
			ti->v2 = temp->data;
			ti->value = temp->value;
			if (head == NULL) {
				head = ti;
				head->next = NULL;
				tail = head;
			}
			else {
				flag = 0;
				if (ti->value <= head->value) {
					ti->next = head;
					head = ti;
					flag = 1;
				}
				else {
					sort_edge *tm = head;
					while (tm->next) {
						if (ti->value >= tm->value&&ti->value <= tm->next->value) {
							ti->next = tm->next;
							tm->next = ti;
							flag = 1;
							break;
						}
						tm = tm->next;
					}
				}
				if (!flag) {
					tail->next = ti;
					tail = tail->next;
					tail->next = NULL;
				}
			}
			temp = temp->next;
		}
	}
	sort_edge *zj = head;
	/*while (zj) {
		printf("%d -> %d ; value: %d\n", zj->v1, zj->v2, zj->value);
		zj = zj->next;
	}*/
	while (zj) {
		if (!graph_is_vertex_connected(t, zj->v1, zj->v2)) {
			graph_add_edge(t, zj->v1, zj->v2, zj->value);
		}
		zj = zj->next;
	}
}

void graph_print(struct Graph *g)
{
	int i;
	for (i = 0; i < g->v; i++) {
		struct ListNode *temp = g->adjlist.buffer[i].adj_verts.head;
		while (temp) {
			if (i < temp->data) {
				printf("%d -> %d ; value: %d\n", i, temp->data, temp->value);
			}
			temp = temp->next;
		}
	}
}