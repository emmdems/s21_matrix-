#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int flag = OK;
  if (A->columns <= 0 || A->rows <= 0) {
    flag = INCORRECT_MATRIX;
  } else {
    // s21_create_matrix(A->columns, A->rows, result);
    for (int row = 0; row < A->rows; row++) {
      for (int column = 0; column < A->columns; column++) {
        result->matrix[column][row] = A->matrix[row][column];
      }
    }
  }
  return flag;
}