#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stack.h"
// TODO:
void decode_string(char *s)
{
	int i, num[10], pos[10], n = 0, j, p, cir, k;
	char str[10];
	Stack S;
	stack_init(&S, 20);
	for (i = 0; i < strlen(s); i++) {
		if (s[i] == '[') {
			stack_push(&S, s[i]);
			S.buffer[S.size] = '\0';
			pos[n++] = S.size-1;
		}
		else if (s[i] >= '0'&&s[i] <= '9') {
			num[n] = s[i] - '0';
		}
		else if (s[i] == ']') {
			p = 0;
			for (j = pos[n-1] + 1; j < S.size; j++) {
				str[p++] = S.buffer[j];
			}
			str[p] = '\0';
			S.size = pos[n-1];
			for (j = num[n-1]; j > 0; j--) {
				for (k = 0; k < strlen(str); k++) {
					
					stack_push(&S, str[k]);
					S.buffer[S.size] = '\0';
				}
			}
			n--;
		}
		else {
			stack_push(&S, s[i]);
			S.buffer[S.size] = '\0';
		}
	}
	puts(S.buffer);
}

int main()
{
  decode_string("3[a]2[bc]");  // 输出 aaabcbc
  decode_string("3[a2[c]]");  // 输出 accaccacc
  decode_string("2[abc]3[cd]ef");  // 输出 abcabccdcdcdef
}
