#pragma once


#include "list.h"

// Merge sorted list src1 and src2 to dst
// src1��src2�Ǵ�С�����ź�����������������нڵ��Ƶ�dst�У������մ�С�����˳������
enum Status merge_sorted_lists(struct List *dst, struct List *src1, struct List *src2);

// Merge k lists
// srcs��n����С�����ź�����������������нڵ��Ƶ�dst�У������մ�С�����˳������
enum Status merge_multiple_lists(struct List *dst, struct List **srcs, int n);