#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;
  if (A->rows == B->rows && A->columns == B->columns) {
    for (int row = 0; row < A->rows; row++) {
      for (int column = 0; column < A->columns; column++) {
        if (fabs(A->matrix[row][column] - B->matrix[row][column]) >= 1e-7) {
          flag = FAILURE;
        }
      }
    }
  } else {
    flag = FAILURE;
  }
  return flag;
}