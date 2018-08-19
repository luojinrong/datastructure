#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

void matrix_init(struct Matrix *m, int rows, int cols, int mode) {
	int i;
  m->rows = rows;
  m->cols = cols;
  m->mode = mode;
  m->buffer = (int*)malloc(sizeof(DataType) * rows * cols);
  for (i = 0; i < rows*cols; i++) {
	  m->buffer[i] = 0;
  }
}

void matrix_destroy(struct Matrix *m) {
  if (m->buffer != NULL) {
    free(m->buffer);
    m->buffer = NULL;
    m->rows = 0;
    m->cols = 0;
    m->mode = 0;
  }
}

int matrix_coord_to_index(struct Matrix *m, int row, int col) {
  return m->mode == 0 ? col + row * m->cols : row + col * m->rows;
}

DataType matrix_get(struct Matrix *m, int row, int col) {
  return m->buffer[matrix_coord_to_index(m, row, col)];
}

void matrix_set(struct Matrix *m, int row, int col, DataType data) {
  m->buffer[matrix_coord_to_index(m, row, col)] = data;
}

void matrix_print(struct Matrix *m) {
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      printf("%5d", matrix_get(m, i, j));
    }
    printf("\n");
  }
}
