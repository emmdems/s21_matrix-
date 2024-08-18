#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = OK;
  double det = 0;
  s21_determinant(A, &det);
  if (A->columns <= 0 || A->rows <= 0) {
    flag = INCORRECT_MATRIX;
  } else if (det != 0) {
    if (A->columns == 1) {
      // s21_create_matrix(A->rows, A->columns, result);
      result->matrix[0][0] = 1.0 / A->matrix[0][0];
    } else {
      matrix_t Temp_calc_comp = {0};
      s21_create_matrix(A->rows, A->columns, &Temp_calc_comp);
      matrix_t Temp_calc_comp_transp = {0};
      s21_create_matrix(A->rows, A->columns, &Temp_calc_comp_transp);
      s21_calc_complements(A, &Temp_calc_comp);
      s21_transpose(&Temp_calc_comp, &Temp_calc_comp_transp);
      s21_remove_matrix(&Temp_calc_comp);
      s21_mult_number(&Temp_calc_comp_transp, 1.0 / det, result);
      s21_remove_matrix(&Temp_calc_comp_transp);
    }
  } else {
    flag = CALC_ERROR;
  }
  return flag;
}
