#include "graph.h"

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

static void graph_init_marked(struct Graph *g) {
  if (g->marked == NULL) {
    g->marked = malloc(g->v * sizeof(bool));
  }
  for (int i = 0; i < g->v; i++) {
    g->marked[i] = false;
  }

  if (g->path == NULL) {
    g->path = malloc(g->v * sizeof(int));
  }
  for (int i = 0; i < g->v; i++) {
    g->path[i] = -1;
  }
}

static void graph_destroy_marked(struct Graph *g) {
  if (g->marked != NULL) {
    free(g->marked);
  }
  if (g->path != NULL) {
    free(g->path);
  }
}

// TODO: DONE
void graph_init(struct Graph *g, int num_vertices, enum GraphType type) {
  g->v = num_vertices;
  g->e = 0;
  g->type = type;
  matrix_init(&g->m, num_vertices, num_vertices, ROW_MAJOR);
  g->marked = NULL;
  g->path = NULL;
}

// TODO: DONE
void graph_destroy(struct Graph *g) {
  g->v = 0;
  g->e = 0;
  matrix_destroy(&g->m);
  graph_destroy_marked(g);
}

// TODO: DONE
void graph_add_edge(struct Graph *g, int u, int v, DataType weight) {
  matrix_set(&g->m, u, v, weight);
  if (g->type == UNDIRECTED_GRAPH) {
    matrix_set(&g->m, v, u, weight);
  }
  g->e++;
}

// TODO: DONE
int graph_degree(struct Graph *g, int v) {
  if (g->type == UNDIRECTED_GRAPH) {
    return graph_in_degree(g, v);
  }

  return graph_in_degree(g, v) + graph_out_degree(g, v);
}

// TODO: DONE
int graph_in_degree(struct Graph *g, int v) {
  int n = 0;

  for (int i = 0; i < g->v; ++i) {
    if (matrix_get(&g->m, i, v) != 0) {
      n++;
    }
  }

  return n;
}

// TODO: DONE
int graph_out_degree(struct Graph *g, int v) {
  int n = 0;

  for (int i = 0; i < g->v; ++i) {
    if (matrix_get(&g->m, v, i) != 0) {
      n++;
    }
  }

  return n;
}

// TODO: DONE
// 判断是否连通图
bool graph_is_connected(struct Graph *g) {
  graph_dfs(g, 0);

  for (int i = 0; i < g->v; i++) {
    if (!g->marked[i]) {
      return false;
    }
  }

  if (g->type == UNDIRECTED_GRAPH) {
    return true;
  }

  // Flip edge direction
  g->m.mode = 1 - g->m.mode;
  graph_dfs(g, 0);
  bool connected = true;
  for (int i = 0; i < g->v; i++) {
    if (!g->marked[i]) {
      connected = false;
      break;
    }
  }
  g->m.mode = 1 - g->m.mode;

  return connected;
}

// TODO: DONE
// 判断两个顶点是否连通
bool graph_is_vertex_connected(struct Graph *g, int u, int v) {
  graph_dfs(g, u);
  return g->marked[v];
}

// TODO: DONE
// 两个顶点之间的距离
DataType graph_vertex_distance(struct Graph *g, int u, int v) {
  graph_dfs(g, u);

  if (!g->marked[v]) {
    return -1;
  }

  DataType dist = 0;
  while (g->path[v] >= 0) {
    dist += matrix_get(&g->m, g->path[v], v);
    v = g->path[v];
  }

  return dist;
}

// TODO: DONE
// 判断sg是否为g的子图
bool graph_is_subgraph(struct Graph *g, struct Graph *sg) {
  if (g->m.rows < sg->m.rows) {
    return false;
  }

  for (int i = 0; i < sg->m.rows; i++) {
    for (int j = 0; j < sg->m.cols; j++) {
      if (matrix_get(&sg->m, i, j) != 0 && matrix_get(&g->m, i, j) == 0) {
        return false;
      }
    }
  }
  return true;
}

// TODO: DONE
// 判断sg是否是g的（强）连通分量
bool graph_is_connected_component(struct Graph *g, struct Graph *sg) {
  return graph_is_subgraph(g, sg) && graph_is_connected(sg);
}

void graph_dfs_recursion(struct Graph *g, int v, int from) {
  g->marked[v] = true;
  g->path[v] = from;

  for (int i = 0; i < g->v; i++) {
    if (matrix_get(&g->m, v, i) != 0 && !g->marked[i]) {
      graph_dfs_recursion(g, i, v);
    }
  }
}

void graph_dfs(struct Graph *g, int v) {
  graph_init_marked(g);
  graph_dfs_recursion(g, v, -1);
}

void graph_bfs(struct Graph *g, int v) {
  graph_init_marked(g);

  Queue q;

  queue_init(&q);

  queue_enqueue(&q, v);
  g->marked[v] = true;
  g->path[v] = -1;

  while (!queue_empty(&q)) {
    int u = queue_dequeue(&q);

    for (int i = 0; i < g->v; i++) {
      if (matrix_get(&g->m, u, i) != 0 && !g->marked[i]) {
        queue_enqueue(&q, i);
        g->marked[i] = true;
        g->path[i] = u;
      }
    }
  }

  queue_destroy(&q);
}

void graph_save(struct Graph *g, const char *filename) {
  FILE *fp = fopen(filename, "w");

  fprintf(fp, "strict %sgraph {\n", g->type == DIRECTED_GRAPH ? "di" : "");

  for (int i = 0; i < g->v; i++) {
    for (int j = 0; j < g->v; j++) {
      int weight = matrix_get(&g->m, i, j);
      if (weight != 0) {
        fprintf(fp, "\t%d %s %d [label = %d]\n", i,
                g->type == DIRECTED_GRAPH ? "->" : "--", j, weight);
      }
    }
  }

  fprintf(fp, "}\n");

  fclose(fp);
}

// 用Dijikstra算法计算顶点v到其它顶点的距离,
// 并将距离记录在dists中，路径记录在path中
void graph_dijikstra(struct Graph *g, int v) {
  int i;
  Queue q;
  queue_init(&q);
  g->dists=(DataType*)malloc(sizeof(DataType)*g->v);
  g->marked = (bool*)malloc(sizeof(bool)*g->v);
  g->path = (int*)malloc(sizeof(int)*g->v);
  for(i=0;i<g->v;i++){
	  g->dists[i]=INT_MAX;
	  g->marked[i] = false;
	  g->path[i] = -1;
  }
  g->dists[v]=0;
  queue_enqueue(&q,v);
  g->marked[v]=true;
  while(!queue_empty(&q)){
	  DataType temp=queue_dequeue(&q);
	  for(i=0;i<g->v;i++){
		  if(matrix_get(&g->m,temp,i)){
			  if(matrix_get(&g->m,temp,i)+g->dists[temp]<g->dists[i]){
				  g->path[i]=temp;
				  g->dists[i]=matrix_get(&g->m,temp,i)+g->dists[temp];
			  }
			  if(!g->marked[i]){
				  g->path[i]=temp;
			      queue_enqueue(&q,i);
				  g->marked[i] = true;
			  }
		  }
	  }
  }
  graph_init_marked(g);
}

// 用Floyd算法计算顶点两两之间的距离, 将其记录在dists矩阵中
void floyd_help(struct Graph *g,DataType v1,DataType v2,struct Matrix *dists)
{
	int i;
	g->marked[v1]=g->marked[v2]=true;
	if(matrix_get(&g->m, v1, v2)&&matrix_get(&g->m,v1,v2)<matrix_get(dists,v1,v2)){
		matrix_set(dists,v1,v2,matrix_get(&g->m,v1,v2));
	}
	for(i=0;i<g->v;i++){
		if (i != v1 && i != v2) {
			if (!g->marked[i]) {
				floyd_help(g, v1, i, dists);
				g->marked[v1] = true;
				floyd_help(g, i, v2, dists);
				g->marked[v2] = true;
				if ((matrix_get(dists, v1, i) + matrix_get(dists, i, v2)) < matrix_get(dists, v1, v2)) {
					matrix_set(dists, v1, v2, (matrix_get(dists, v1, i) + matrix_get(dists, i, v2)));
				}
			}
		}
	}
	g->marked[v1] = g->marked[v2] = false;
}

void graph_floyd(struct Graph *g, struct Matrix *dists) {
  int i,j;
  g->marked = (bool*)malloc(sizeof(bool)*g->v);
  for (i = 0; i<g->v; i++) {
	  g->marked[i] = false;
  }
  for(i=0;i<g->v;i++){
	  for(j=0;j<g->v;j++){
		  if (i != j) {
			  floyd_help(g, i, j, dists);
			  graph_init_marked(g);
		  }
	  }
  }
}

// 用Ford Fulkerson算法计算从s到t的最大流，返回最大流的值，并将流量记录在flow中
DataType graph_ford_fulkerson(struct Graph *g, struct Graph *flow, DataType s,DataType t) {
	int i,j,flag=1,max_flow=0;
	struct Graph g_r;
	graph_init(&g_r,g->v,g->type);
	for(i=0;i<g->v;i++){
		for(j=0;j<g->v;j++){
			matrix_set(&g_r.m,i,j,matrix_get(&g->m,i,j)-matrix_get(&flow->m,i,j));
		}
	}
	while(flag){
		int min = 999;
		flag=0;
		if(graph_is_vertex_connected(&g_r,s,t)){
			int from = -1, i;
			for (i = 0; i < g_r.v; i++) {
				g_r.marked[i] = false;
			}
			flag=1;
			while (from != t) {
				for (i = 0; i < g_r.v; i++) {
					if (g_r.path[i] == from&&(!g_r.marked[i])) {
						if (matrix_get(&g_r.m, from, i)&&matrix_get(&g_r.m, from, i) < min) {
							min = matrix_get(&g_r.m, from, i);
						}
						from = i;
						g_r.marked[i] = true;
						break;
					}
				}
				if (i == g_r.v) {
					from = g_r.path[from];
				}
			}
			from = -1;
			for (i = 0; i < g_r.v; i++) {
				g_r.marked[i] = false;
			}
			while (from != t) {
				for (i = 0; i < g_r.v; i++) {
					if (g_r.path[i] == from&&(!g_r.marked[i])) {
						if (from == -1) {
							from = i;
							g_r.marked[i] = true;
							break;
						}
						else {
							matrix_set(&g_r.m, from, i, matrix_get(&g_r.m, from, i) - min);
							matrix_set(&g_r.m, i, from, matrix_get(&g_r.m, i, from) + min);
							matrix_set(&flow->m, from, i, matrix_get(&flow->m, from, i) + min);
							from = i;
							g_r.marked[i] = true;
							break;
						}
					}
				}
				if (i == g_r.v) {
					matrix_set(&g_r.m, from, g_r.path[from], matrix_get(&g_r.m, from, g_r.path[from]) - min);
					matrix_set(&g_r.m, g_r.path[from], from, matrix_get(&g_r.m, g_r.path[from], from) + min);
					matrix_set(&flow->m, g_r.path[from], from, matrix_get(&flow->m, g_r.path[from], from) - min);
					from = g_r.path[from];
				}
			}
		}
	}
	for (i = 0; i < flow->v; i++) {
		max_flow += matrix_get(&flow->m, i, t);
	}
  return max_flow;
}
