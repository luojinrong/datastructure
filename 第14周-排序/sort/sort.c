#include "sort.h"

#define SWAP(x, y)                                                             \
  do {                                                                         \
    int tmp = x;                                                               \
    x = y;                                                                     \
    y = tmp;                                                                   \
  } while (0)

// TODO:
// 插入排序
void insertion_sort(int *a, int n, int (*comp)(const void *, const void *)) {
	int i,j,t,tmp;
	for(i=1;i<n;i++){
		for(j=0;j<i;j++){
			if(comp(&a[i],&a[j])<0){
				tmp=a[i];
				for(t=i;t>j;t--){
					a[t]=a[t-1];
				}
				a[j]=tmp;
				break;
			}
		}
	}
}

// TODO:
// 希尔排序
void shell_sort(int *a, int n, int (*comp)(const void *, const void *)) {
	int i, j, k, span, m, s;
	int D[3] = { 5,3,1 };
	for (m = 0; m < 3; m++) {
		span = D[m];
		for (k = 0; k < span; k++) {
			for (i = k; i < n - 1; i += span) {
				s = a[i + span];
				j = i;
				while (j > -1 && comp(&s, &a[j]) < 0) {
					a[j + span] = a[j];
					j -= span;
				}
				a[j + span] = s;
			}
		}
	}
}

// TODO: DONE
// 选择排序
void selection_sort(int *a, int n, int (*comp)(const void *, const void *)) {
  for (int i = 0; i < n; i++) {
    int k = i;
    for (int j = i + 1; j < n; j++) {
      if (comp(&a[j], &a[k]) < 0) {
        k = j;
      }
    }
    if (k != i) {
      SWAP(a[i], a[k]);
    }
  }
}

// TODO:
// 堆排序
static void adjust(int *a, int root, int n) {
	int child = (root + 1) * 2 - 1,temp=a[root];
	while (child <= n) {
		if ((child < n-1) && a[child] < a[child + 1]) {
			child++;
		}
		if (a[root] > a[child]) {
			break;
		}
		else {
			a[(child - 1) / 2] = a[child];
			a[child] = temp;
			root = child;
			child = (child + 1) * 2 - 1;
		}
	}
	a[(child - 1) / 2] = temp;
}

void heap_sort(int *a, int n, int (*comp)(const void *, const void *)) {
	int i;
	for (i = (n-1) / 2; i >= 0; i--) {
		adjust(a, i, n);
	}
	for (i = n - 1; i >= 0; i--) {
		SWAP(a[0], a[i]);
		adjust(a, 0, i - 1);
	}
}

// TODO:
// 冒泡排序
void bubble_sort(int *a, int n, int (*comp)(const void *, const void *)) {
	int i,j,flag=1;
	for(i=0;i<n&&flag;i++){
		flag=0;
		for(j=0;j<n-i-1;j++){
			if(comp(&a[j],&a[j+1])>0){
				SWAP(a[j],a[j+1]);
				flag=1;
			}
		}
	}
}

// TODO:
// 快速排序
void quick_sort(int *a, int n, int (*comp)(const void *, const void *)) {
	int i=0,j=n-1,t=0;
	while(i<j){
		while((comp(&a[t],&a[i])>0)&&i<n){
				i++;
		}
		while((comp(&a[t],&a[j])<=0)&&j>0){
				j--;
		}
		if (i < j) {
			SWAP(a[i], a[j]);
		}
	}
	SWAP(a[t], a[j]);
	if (j>1) {
		quick_sort(a, j, comp);
	}
	if (n - j - 1>1) {
		quick_sort(a + j + 1, n - j - 1, comp);
	}
}

// TODO:
// 归并排序
static void mergearray(int *a, int first, int mid, int last, int temp[], int(*comp)(const void*, const void *)) {
	int i = first, j = mid + 1,m = mid, n = last,k = 0;
	while (i <= m&&j <= n) {
		if (comp(&a[i], &a[j]) < 0) {
			temp[k++] = a[i++];
		}
		else {
			temp[k++] = a[j++];
		}
	}
	while (i <= m) {
		temp[k++] = a[i++];
	}
	while (j <= m) {
		temp[k++] = a[j++];
	}
	for (i = 0; i < k; i++) {
		a[first+i] = temp[i];
	}
}
static void mergesort(int *a, int first, int last, int *temp,int (*comp)(const void*,const void*)) {
	if (first < last) {
		int mid = (first + last) / 2;
		mergesort(a, first, mid, temp,comp);
		mergesort(a, mid+1, last, temp,comp);
		mergearray(a, first, mid, last, temp, comp);
	}
}

void merge_sort(int *a, int n, int (*comp)(const void *, const void *)) {
	int *p = (int*)malloc(sizeof(int)*n);
	mergesort(a, 0, n - 1, p, comp);
}

// TODO:
// 基数排序
void radixsort(int *a, int n, int t, int(*comp)(const void*, const void *)) {
	struct list {
		int num;
		struct list *next;
	}*front[10] = { NULL }, *head[10] = { NULL }, *tail[10] = { NULL };
	int i, k=0,flag=0;
	for (i = 0; i < n; i++) {
		int j = (a[i] / (int)pow(10, t)) % 10;
		if (front[j] == NULL) {
			front[j] = (struct list*)malloc(sizeof(struct list));
			head[j] = tail[j] = front[j];
		}
		else {
			tail[j]->next = (struct list*)malloc(sizeof(struct list));
			tail[j] = tail[j]->next;
		}
		tail[j]->num = a[i];
		tail[j]->next = NULL;
	}
	for (i = 0; i < 10; i++) {
		while (front[i] != NULL) {
			a[k++] = front[i]->num;
			front[i] = front[i]->next;
		}
	}
	for (i = 1; i < 10; i++) {
		if (head[i]) {
			flag = 1;
			break;
		}
	}
	if (flag) {
		radixsort(a, n, t + 1, comp);
	}
}

void radix_sort(int *a, int n, int (*comp)(const void *, const void *)) {
	radixsort(a, n, 0, comp);
}
