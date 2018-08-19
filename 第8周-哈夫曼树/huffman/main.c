#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btree.h"
//#include "btree_vis.h"
#include "huffman.h"

int main() {
  char *s = "go go gophers";
  char *t = "her sphere goes here";
  char *es = "0001100000110000011110110110111111100";

  printf("--------------------------------------------\n");
  printf("Building huffman-tree by array...\n\n");
  struct BTree *h1 = huffman_build_using_array(s);
  printf("--------------------------------------------\n");
  printf("Building huffman-tree by heap...\n\n");
  struct BTree *h2 = huffman_build_using_heap(s);
  printf("--------------------------------------------\n");

  /*printf("h1 %c= h2\n", btree_is_isomorphic(h1, h2) ? '~' : '^');*/
  printf("--------------------------------------------\n");
  printf("\nencode string s by arrayed huffman-tree...\n");
  int n1 = huffman_encode(h1, s);
  printf("--------------------------------------------\n");
  printf("\nencode string s by heaped huffman-tree...\n");
  int n2 = huffman_encode(h2, s);
  //printf("n1 %c= n2\n", n1 == n2 ? '=' : '!');

  printf("--------------------------------------------\n");
  printf("\nencode string s by arrayed huffman-tree...\n");
  n1 = huffman_encode(h1, t);
  printf("--------------------------------------------\n");
  printf("\nencode string s by heaped huffman-tree...\n");
  n2 = huffman_encode(h2, t);
  //printf("n1 %c= n2\n", n1 == n2 ? '=' : '!');

  printf("--------------------------------------------\n");
  printf("\ndecode string es by arrayed huffman-tree...\n");
  n1 = huffman_decode(h1, es);
  printf("--------------------------------------------\n");
  printf("\ndecode string es by heaped huffman-tree...\n");
  n2 = huffman_decode(h2, es);
  //printf("n1 %c= n2\n", n1 == n2 ? '=' : '!');
  printf("--------------------------------------------\n");
  btree_destroy(h1);
  btree_destroy(h2);
}
