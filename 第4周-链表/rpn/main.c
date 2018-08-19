#include"stack.h"

#include <stdio.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

// TODO:
DataType rpn(char **tokens, int len) {
	Stack S;
	S.size = 0;
	S.buffer = (DataType*)malloc(len * sizeof(DataType));
	int i, j, n, p1, p2;
	for (i = 0; i < len; i++) {
		if (**(tokens + i) == '+') {
			p1 = S.buffer[--S.size];
			p2 = S.buffer[--S.size];
			S.buffer[S.size++] = p2 + p1;
		}
		else if (**(tokens + i) == '-') {
			p1 = S.buffer[--S.size];
			p2 = S.buffer[--S.size];
			S.buffer[S.size++] = p2 - p1;
		}
		else if (**(tokens + i) == '*') {
			p1 = S.buffer[--S.size];
			p2 = S.buffer[--S.size];
			S.buffer[S.size++] = p2 * p1;
		}
		else if (**(tokens + i) == '/') {
			p1 = S.buffer[--S.size];
			p2 = S.buffer[--S.size];
			S.buffer[S.size++] = p2 / p1;
		}
		else {
			n = 0;
			for (j = 0; *(*(tokens + i)+j) != 0; j++) {
				n = n * 10 + *(*(tokens + i) + j) - '0';
			}
			S.buffer[S.size++] = n;
		}
	}
	return S.buffer[0];
}

int main() {
  char *s1[] = {"2", "1", "+", "3", "*"};
  char *s2[] = {"4", "13", "5", "/", "+"};

  printf("%d\n", rpn(s1, ARRAY_SIZE(s1))); // 9
  printf("%d\n", rpn(s2, ARRAY_SIZE(s2))); // 6
}
