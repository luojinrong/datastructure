#include <stdio.h>

// TODO:
void reverse_vowels(char *s) {
	typedef struct {//由于没有包含相应的头文件，这里只能实现十个长度以内的反转
		int top;
		char vowel[10];
	}stack;
	int i, len = 0, flag[10];
	stack S;
	S.top = 0;
	S.vowel[0] = 0;
	for (i = 0; s[i] != 0; i++) {
		len++;
	}
	for (i = 0; s[i] != 0; i++) {
		if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
			flag[i] = 1;
			S.vowel[S.top++] = s[i];
			S.vowel[S.top] = 0;
		}
		else {
			flag[i] = 0;	
		}
	}
	for (i = 0; s[i] != 0; i++) {
		if (flag[i]) {
			printf("%c",S.vowel[--S.top]);
		}
		else {
			printf("%c", s[i]);
		}
	}
	printf("\n");
}

int main() {
  reverse_vowels("hello");    // 打印  holle
  reverse_vowels("leetcode"); // 打印 leotcede
}
