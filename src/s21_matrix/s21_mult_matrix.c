#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;
  if (A->columns <= 0 || A->rows <= 0 || B->columns <= 0 || B->rows <= 0) {
    flag = INCORRECT_MATRIX;
  } else if (A->columns == B->rows) {
    s21_create_matrix(A->rows, B->columns, result);
    for (int m = 0; m < A->rows; m++) {
      for (int n = 0; n < B->columns; n++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[m][n] += A->matrix[m][k] * B->matrix[k][n];
        }
      }
    }
  } else {
    flag = CALC_ERROR;
  }
  return flag;
}