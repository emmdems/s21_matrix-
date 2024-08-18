#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = OK;
  if (A->columns <= 0 || A->rows <= 0) {
    flag = INCORRECT_MATRIX;
  } else if (A->columns == A->rows) {
    // s21_create_matrix(A->rows, A->columns, result);
    if (A->columns == 1) {
      result->matrix[0][0] = A->matrix[0][0];
    } else {
      matrix_t Temp = {0};
      double res = 0;
      for (int row = 0; row < result->rows; row++) {
        for (int column = 0; column < result->columns; column++) {
          s21_create_matrix_lower(*A, &Temp, row, column);
          s21_determinant(&Temp, &res);
          s21_remove_matrix(&Temp);
          result->matrix[row][column] = res * pow(-1, row + column + 2);
        }
      }
    }
  } else {
    flag = CALC_ERROR;
  }
  return flag;
}
