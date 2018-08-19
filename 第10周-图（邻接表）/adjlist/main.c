#include "graph.h"

#include <stdio.h>

void init_undirected_graph(struct Graph *g) {
  graph_init(g, 6, UNDIRECTED_GRAPH);

  //此处创建的边权值均为1
  graph_add_edge(g, 0, 1, 1);
  graph_add_edge(g, 0, 2, 1);
  graph_add_edge(g, 0, 3, 1);
  graph_add_edge(g, 1, 2, 1);
  graph_add_edge(g, 4, 5, 1);
}

void test_undirected_graph() {
  struct Graph g;
  int i;
  init_undirected_graph(&g);

  printf("Degree: \n");
  for (int i = 0; i < 6; i++) {
    printf("%d => %d\n", i, graph_degree(&g, i));
  }

  printf("DFS:\n");
  graph_dfs(&g, 0);
  printf("\n");
  for (i = 0; i < g.v; i++) {
	  g.marked[i] = false;
  }

  printf("BFS:\n");
  graph_bfs(&g, 0);
  printf("\n");
  for (i = 0; i < g.v; i++) {
	  g.marked[i] = false;
  }

  graph_destroy(&g);
}

void init_directed_graph(struct Graph *g) {
  graph_init(g, 4, DIRECTED_GRAPH);

  //此处创建的边权值均为1
  graph_add_edge(g, 0, 3, 1);
  graph_add_edge(g, 0, 2, 1);
  graph_add_edge(g, 2, 1, 1);
  graph_add_edge(g, 1, 0, 1);
}

void test_directed_graph() {
  struct Graph g;
  int i;
  init_directed_graph(&g);

  printf("Degree: \n");
  for (int i = 0; i < 4; i++) {
    printf("%d => %d(%d in, %d out)\n", i, graph_degree(&g, i),
           graph_in_degree(&g, i), graph_out_degree(&g, i));
  }

  printf("DFS:\n");
  graph_dfs(&g, 0);
  printf("\n");
  for (i = 0; i < g.v; i++) {
	  g.marked[i] = false;
  }

  printf("BFS:\n");
  graph_bfs(&g, 0);
  printf("\n");
  for (i = 0; i < g.v; i++) {
	  g.marked[i] = false;
  }

  graph_destroy(&g);
}

void test_spanning_tree() {
  struct Graph g, t_prim, t_kruskal, t_dfs, t_bfs;
  graph_init(&g, 6, UNDIRECTED_GRAPH);
  graph_init(&t_prim, 6, UNDIRECTED_GRAPH);
  graph_init(&t_kruskal, 6, UNDIRECTED_GRAPH);
  graph_init(&t_dfs, 6, UNDIRECTED_GRAPH);
  graph_init(&t_bfs, 6, UNDIRECTED_GRAPH);

  //测试样例1，测试时请将所用到的图初始化大小为4
  /*graph_add_edge(&g, 0, 1, 1);
  graph_add_edge(&g, 0, 2, 2);
  graph_add_edge(&g, 0, 3, 3);
  graph_add_edge(&g, 1, 2, 4);*/

  //测试样例2，测试时请将所用到的图初始化大小为6
  graph_add_edge(&g, 0, 1, 6);
  graph_add_edge(&g, 0, 2, 1);
  graph_add_edge(&g, 0, 3, 5);
  graph_add_edge(&g, 1, 2, 5);
  graph_add_edge(&g, 2, 3, 5);
  graph_add_edge(&g, 1, 4, 3);
  graph_add_edge(&g, 2, 4, 6);
  graph_add_edge(&g, 3, 5, 2);
  graph_add_edge(&g, 2, 5, 4);
  graph_add_edge(&g, 4, 5, 6);


  graph_spanning_tree_bfs(&g, &t_bfs);
  printf("The t_bfs is:\n");
  graph_print(&t_bfs);

  graph_spanning_tree_dfs(&g, &t_dfs);
  printf("The t_dfs is:\n");
  graph_print(&t_dfs);

  graph_spanning_tree_prim(&g, &t_prim);
  printf("The t_prim is:\n");
  graph_print(&t_prim);

  graph_spanning_tree_kruskal(&g, &t_kruskal);
  printf("The t_kruskal is:\n");
  graph_print(&t_kruskal);

  graph_destroy(&g);
  graph_destroy(&t_prim);
  graph_destroy(&t_kruskal);
  graph_destroy(&t_dfs);
  graph_destroy(&t_bfs);
}

int main() {
  printf("Test undirected graph\n");
  test_undirected_graph();
  printf("Test directed graph\n");
  test_directed_graph();
  printf("Test spanning tree\n");
  test_spanning_tree();
}
