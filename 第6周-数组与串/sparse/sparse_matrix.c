#include "sparse_matrix.h"
#include <math.h>

int sparse_matrix_item_position_compare(struct Item *lhs, struct Item *rhs) {
  return lhs->row == rhs->row ? lhs->col - rhs->col : lhs->row - rhs->row;
}

void sparse_matrix_init(SparseMatrix *m, int rows, int cols) {
  list_init(m);
  m->rows = rows;
  m->cols = cols;
}

// TODO:
// 将m的第row行第col列设置为value
// 如果下标越界返回 `STATUS_ERR_INVALID_RANGE`
enum Status sparse_matrix_set(SparseMatrix *m, int row, int col, double value) {
	if (row > m->rows || col > m->cols) {
		return STATUS_ERR_INVALID_RANGE;
	}
	else {
		if (value == 0) {
			return STATUS_OK;
		}
		DataType data;
		struct ListNode *p = NULL, *q = NULL;
		data.col = col;
		data.row = row;
		data.value = value;
		if (m->head == NULL) {
			list_push_back(m, data);
		}
		else {
			p = m->head;
			q = p->next;
			if (sparse_matrix_item_position_compare(&data, &m->head->data)<0) {
				list_push_front(m, data);
			}
			else {
				while (q != NULL) {
					if (sparse_matrix_item_position_compare(&data, &p->data)>0 && sparse_matrix_item_position_compare(&data, &q->data)<0) {
						list_insert_after(m, p, data);
						break;
					}
					p = q;
					q = q->next;
				}
				if (q == NULL && sparse_matrix_item_position_compare(&data, &p->data)>0) {
					list_push_back(m, data);
				}
			}
		}
	}
	return STATUS_OK;
}

// TODO:
// 返回m的第row行第col列
// 如果下标越界返回NAN
double sparse_matrix_get(SparseMatrix *m, int row, int col)
{ 
	int flag = 0;
	DataType data;
	struct ListNode *p = m->head;
	data.col = col;
	data.row = row;
	data.value = 0;
	while (p != NULL) {
		if (sparse_matrix_item_position_compare(&p->data, &data) == 0) {
			data.value = p->data.value;
			break;
		}
		else if (sparse_matrix_item_position_compare(&p->data, &data)<0) {
			p = p->next;
		}
		else {
			break;
		}
	}
	if (row < m->rows&&col < m->cols) {
		return data.value;
	}
	else {
		return NAN;
	}
}

// TODO:
// c = a + b
// 假设a，b有相同的行列
void sparse_matrix_add(SparseMatrix *c, SparseMatrix *a, SparseMatrix *b) 
{
	struct ListNode *a_node = a->head, *b_node = b->head;
	DataType data;
	while (a_node != a->tail->next&&b_node != b->tail->next) {
		if (sparse_matrix_item_position_compare(&a_node->data, &b_node->data) == 0) {
			data = a_node->data;
			data.value += b_node->data.value;
			a_node = a_node->next;
			b_node = b_node->next;
		}
		else if (sparse_matrix_item_position_compare(&a_node->data, &b_node->data)>0) {
			data = b_node->data;
			b_node = b_node->next;
		}
		else {
			data = a_node->data;
			a_node = a_node->next;
		}
		if (data.value != 0) {
			list_push_back(c, data);
		}
	}
	if (a_node == a->tail->next) {
		while (b_node != b->tail->next) {
			data = b_node->data;
			b_node = b_node->next;
			list_push_back(c, data);
		}
	}
	else {
		while (a_node != a->tail->next) {
			data = a_node->data;
			a_node = a_node->next;
			list_push_back(c, data);
		}
	}
}
