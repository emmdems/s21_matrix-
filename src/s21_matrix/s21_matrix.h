#ifdef __cplusplus
extern "C" {
#endif

#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#define SUCCESS 1
#define FAILURE 0

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum { OK = 0, INCORRECT_MATRIX = 1, CALC_ERROR = 2 };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(const int rows, const int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *const A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

void s21_create_matrix_lower(matrix_t A, matrix_t *Temp, int crossed_out_row,
                             int crossed_out_column);
double s21_det(matrix_t A, matrix_t Temp, double result,
               int crossed_out_column);

#endif  // SRC_S21_MATRIX_H_

#ifdef __cplusplus
}
#endif