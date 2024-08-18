#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int flag = OK;
  if (A->columns <= 0 || A->rows <= 0) {
    flag = INCORRECT_MATRIX;
  } else if (A->columns == A->rows) {
    *result = 0.00;
    matrix_t Temp = {0};
    Temp.columns = 0;
    *result = s21_det(*A, Temp, *result, 0);
  } else {
    flag = CALC_ERROR;
  }
  return flag;
}

double s21_det(matrix_t A, matrix_t Temp, double result,
               int crossed_out_column) {
  if (A.columns == 1) {
    result = A.matrix[0][0];
  } else if (A.columns == 2) {
    result =
        (A.matrix[0][0] * A.matrix[1][1] - A.matrix[0][1] * A.matrix[1][0]);
  } else {
    crossed_out_column = (A.columns == Temp.columns) && (Temp.columns != 0)
                             ? 0
                             : crossed_out_column;
    s21_create_matrix_lower(A, &Temp, 0, crossed_out_column);
    result = s21_det(Temp, Temp, result, crossed_out_column);
    ++crossed_out_column;
    result *=
        pow(-1, crossed_out_column + 1) * A.matrix[0][crossed_out_column - 1];
    if (Temp.columns >= crossed_out_column) {
      result += s21_det(A, Temp, result, crossed_out_column);
    }
    s21_remove_matrix(&Temp);
  }
  return result;
}

void s21_create_matrix_lower(matrix_t A, matrix_t *Temp, int crossed_out_row,
                             int crossed_out_column) {
  s21_create_matrix(A.rows - 1, A.columns - 1, Temp);
  int row_temp = 0;
  for (int row = 0; row <= Temp->rows; row++) {
    if (crossed_out_row != row) {
      int column_temp = 0;
      for (int column = 0; column <= Temp->columns; column++) {
        if (crossed_out_column != column) {
          Temp->matrix[row_temp][column_temp] = A.matrix[row][column];
          column_temp++;
        }
      }
      row_temp++;
    }
  }
}
