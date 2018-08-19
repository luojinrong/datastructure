#include "string_matching.h"
#include "string.h"
#include <stdio.h>

int BF_matching(char *s, char *pat) {
  int i, j;

  int M = strlen(s);
  int N = strlen(pat);

  for (i = 0; i < M - N; i++) {
    for (j = 0; j < N; j++) {
      if (pat[j] != s[i + j]) {
        break;
      }
    }

    if (j == N) {
      return i;
    }
  }

  return -1;
}

void compute_prefix(char *pat, int *prefix, int n) {
  prefix[0] = 0;

  for (int i = 1; i < n; i++) {
    int prev = prefix[i - 1];
    while (pat[i] != pat[prev] && prev > 0) {
      prev = prefix[prev - 1];
    }

    if (pat[i] == pat[prev]) {
      prev++;
    }
    prefix[i] = prev;
  }

  for (int i = 0; i < n; i++) {
    printf("%d ", prefix[i]);
  }
  printf("\n");
}

int KMP_matching(char *s, char *pat) {
  int s_len = strlen(s);
  int pat_len = strlen(pat);
  int prefix[10];

  compute_prefix(pat, prefix, pat_len);

  int i = 0;
  int j = 0;
  while (i < s_len && j < pat_len) {
    if (s[i] == pat[j]) {
      i++;
      j++;
    } else if (j == 0) {
      i++;
    } else {
      j = prefix[j - 1];
    }
  }

  return j == pat_len ? (i - pat_len) : -1;
}

// TODO:
// 实现Boyer-Moore算法
int BM_matching(char *s, char* pat) {
	int s_len = strlen(s);
	int pat_len = strlen(pat);
	int i = 0, j = pat_len - 1, bad_move, good_move,n,max_move;
	int bmBc[256], suff[10];
	for (i = 0; i < 256; i++) {
		bmBc[i] = pat_len;
	}
	for (i = 0; i < pat_len; i++) {
		bmBc[pat[i]] = pat_len - i - 1;
	}//坏字符与模式串尾距离 若模式串中不存在坏字符则为模式串长度
	suff[pat_len - 1] = pat_len;
	for (i = pat_len - 2; i >= 0; i--) {
		int m = i;
		while (m >= 0 && pat[m] == pat[pat_len - i - 1 + m]) {
			m--;
		}
		suff[i] = i - m;
	}
	i = 0;
	while ((i + j) < s_len) {
		int flag = 0;
		j = pat_len - 1;
		while (j >= 0) {
			if (s[i + j] == pat[j]) {
				j--;
			}
			else {
				bad_move = bmBc[s[i + j]];
				for (n = pat_len-1; n>=0; n--) {
					if (suff[n] == pat_len - j) {
						good_move = pat_len - n;
						flag = 1;
						break;
					}
				}
				if (!flag) {
					int m;
					for (n = pat_len - j; n >= 0; n--) {
						m = n;
						while (m>=0&&pat[m - 1] == pat[pat_len - 1 - n + m]) {
							m--;
						}
						if (m < 0) {
							good_move = pat_len - n;
							flag = 1;
							break;
						}
					}
				}
				if (!flag) {
					good_move = pat_len;
				}
				max_move = good_move > bad_move ? good_move : bad_move;
				i += max_move;
				break;
			}
		}
		if (j < 0) {
			return i;
		}
	}
	return -1;
}
