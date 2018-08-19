#include <stdio.h>
#include"stack.h"
#include<string.h>
// TODO:
void print_letters(char * digits)
{
	Stack S;
	stack_init(&S, 10);
	int i, max[10] = { 0,0,3,3,3,3,3,4,3,4 }, e = 0, a[10], pos, p[10] = { 0 }, now;
	char let[10][5] = { "","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" }, str[10] = "000000000";
	for (i = 0; i < strlen(digits); i++) {
		stack_push(&S, digits[i]);
	}
	S.buffer[S.size] = '\0';
	for (i = 0; i < S.size; i++) {//根据每位字母次序输出
		printf("%c", let[S.buffer[i] - '0'][0]);
	}
	printf(" ");
	while (!stack_empty(&S)) {
		a[e] = stack_pop(&S)-'0';//出栈 存到a中 当前对该串的后e个元素
		p[e++] = 1;//第e个元素后移一位
		//for (p[e - 1] = 1; p[e - 1] <= max[a[e - 1]]; p[e - 1]++) {
		//	for (now = 0; now < e - 1; now++) {//当前改变的值 后往前
		while (p[e - 1] != 0) {
			
			for (i = 0; i < e; i++) {//进位操作
				if (p[i] >= max[a[i]]) {
					p[i] -= max[a[i]];
					p[i + 1]++;
				}
				else {
					break;
				}
			}
			if (p[e - 1] == 0) {
				break;
			}
			for (i = 0; i < S.size; i++) {//根据每位字母次序输出
				printf("%c", let[S.buffer[i]-'0'][0]);
			}
			for (i = e - 1; i >= 0; i--) {
				printf("%c", let[a[i]][p[i]]);
			}
			p[0]++;
			printf(" ");
		}
		/*	}
		}*/
		for (i = 0; i < e; i++) {
			p[i] = 0;
		}
	}
}

int main()
{
  print_letters("23"); // 打印: ad, ae, af, bd, be, bf, cd, ce, cf.
}
