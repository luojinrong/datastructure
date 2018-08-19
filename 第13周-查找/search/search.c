#include "search.h"

// TODO:
// 使用comp对students进行排序
void sort(struct Vector *students, StudentComp comp) {
	int i,j;
	for(i=0;i<students->size;i++){
		for(j=0;j<students->size-1-i;j++){
			if(comp(&students->buffer[j],&students->buffer[j+1])>0){
				struct Student tmp;
				tmp=students->buffer[j];
				students->buffer[j]=students->buffer[j+1];
				students->buffer[j+1]=tmp;
			}
		}
	}
}

// TODO:
// 在students中查找stu，使用comp进行比较
// 返回查找元素的下标，如果找不到返回-1
int search(struct Vector *students, struct Student *stu, StudentComp comp) {
	int i;
	for(i=0;i<students->size;i++){
		if(!comp(&students->buffer[i],stu)){
			return i;
		}
	}
	return -1;
}

// TODO:
// 在students中用二分查找stu，使用comp进行比较
// 返回查找元素的下标，如果找不到返回-1
int bin_search(struct Vector *students, struct Student *stu, StudentComp comp) {
	int up=students->size,down=0;
	while(1){
		if(up==down){
			if(!comp(&students->buffer[up],stu)){
				return up;
			}
			else{
				return -1;
			}
		}
		else{
			if(comp(&students->buffer[(up+down)/2],stu)>0){
				up=(up+down)/2;
			}
			else{
				if (comp(&students->buffer[(up + down) / 2], stu) == 0) {
					up = down = (up + down) / 2;
				}
				else {
					down = (up + down) / 2;
				}
			}
		}
	}
}
