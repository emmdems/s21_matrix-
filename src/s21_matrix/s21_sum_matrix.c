#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;
  if (A->columns <= 0 || A->rows <= 0 || B->columns <= 0 || B->rows <= 0) {
    flag = INCORRECT_MATRIX;
  } else if (A->rows == B->rows && A->columns == B->columns) {
    // s21_create_matrix(A->rows, A->columns, result);
    for (int row = 0; row < A->rows; row++) {
      for (int column = 0; column < A->columns; column++) {
        result->matrix[row][column] =
            A->matrix[row][column] + B->matrix[row][column];
      }
    }
  } else {
    flag = CALC_ERROR;
  }
  return flag;
}