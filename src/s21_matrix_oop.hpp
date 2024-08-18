#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <iostream>
#include <stdexcept>

#include "s21_matrix/s21_matrix.h"

#pragma once  // Предотвращает многократное включение файла

class S21Matrix {
 private:
  matrix_t* matrix_;
  int rows_, cols_;

 public:
  // Constructors & Destructor
  S21Matrix();  // Конструктор по умолчанию
  S21Matrix(int rows, int cols);  // Параметрический конструктор
  S21Matrix(const S21Matrix& other);  // Конструктор копирования
  S21Matrix(S21Matrix&& other) noexcept;  // Конструктор перемещения
  ~S21Matrix();                           // Деструктор

  // Basic Operations
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  // Operator Overloads
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int row, int col);

  // Accessors and Mutators
  int get_rows() const;
  int get_cols() const;
  double get_element_matrix_(int row, int col) const;
  void set_rows(int rows);
  void set_cols(int cols);
  void set_element_matrix_(int row, int col, double element);
};

#endif  // S21_MATRIX_H_
