#include "s21_matrix_oop.hpp"

S21Matrix::S21Matrix() : matrix_(nullptr), rows_(1), cols_(1) {
  matrix_ = new matrix_t;
  s21_create_matrix(rows_, cols_, this->matrix_);
}

S21Matrix::S21Matrix(int rows, int cols)
    : matrix_(nullptr), rows_(rows), cols_(cols) {
  matrix_ = new matrix_t;
  int error = s21_create_matrix(rows_, cols_, this->matrix_);
  if (error == 1) throw std::runtime_error("Incorrect matrix");
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : matrix_(nullptr), rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new matrix_t;
  s21_create_matrix(other.rows_, other.cols_, this->matrix_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_->matrix[i][j] = other.matrix_->matrix[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : matrix_(other.matrix_), rows_(other.rows_), cols_(other.cols_) {
  other.matrix_ =
      nullptr;  // Обеспечиваем, что деструктор `other` не освободит память
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (this->matrix_ != nullptr) {
    s21_remove_matrix(this->matrix_);  // Вызываем функцию удаления только если
                                       // указатель валиден
    delete this->matrix_;  // Удаляем объект matrix_t
    this->matrix_ = nullptr;  // Обеспечиваем, что указатель нулевой
  }
  this->rows_ = 0;
  this->cols_ = 0;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  return s21_eq_matrix(other.matrix_, matrix_);
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  int error = s21_sum_matrix(matrix_, other.matrix_, this->matrix_);
  if (error == 2) throw std::runtime_error("Different matrix dimensions");
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  int error = s21_sub_matrix(matrix_, other.matrix_, this->matrix_);
  if (error == 2) throw std::runtime_error("Different matrix dimensions");
}

void S21Matrix::MulNumber(const double num) {
  int error = s21_mult_number(matrix_, num, this->matrix_);
  if (error == 1) throw std::runtime_error("Incorrect matrix");
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  S21Matrix matrix_temp(*this);
  S21Matrix matrix_temp2(other);
  int error =
      s21_mult_matrix(matrix_temp.matrix_, matrix_temp2.matrix_, this->matrix_);
  matrix_temp.~S21Matrix();
  matrix_temp2.~S21Matrix();
  if (error == 2)
    throw std::runtime_error(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  s21_transpose(this->matrix_, result.matrix_);
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix result(rows_, cols_);
  int error = s21_calc_complements(this->matrix_, result.matrix_);
  if (error == 2) throw std::runtime_error("The matrix is not square");
  return result;
}

double S21Matrix::Determinant() const {
  double result = 0;
  int error = s21_determinant(this->matrix_, &result);
  if (error == 2) throw std::runtime_error("The matrix is not square");
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  S21Matrix result(rows_, cols_);
  int error = s21_inverse_matrix(this->matrix_, result.matrix_);
  if (error == 2) throw std::runtime_error("Matrix determinant is 0");
  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return (*this).EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {  // Проверка на самоприсваивание
    // Освобождаем текущие ресурсы
    s21_remove_matrix(this->matrix_);
    // Выделяем новую память и копируем данные
    s21_create_matrix(other.rows_, other.cols_, this->matrix_);
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    *this += other;
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  (*this).SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  (*this).SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  (*this).MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  (*this).MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if ((row < 0 || row >= this->rows_) || (col < 0 || col >= this->cols_)) {
    throw std::runtime_error("Index is outside the matrix");
  } else {
    return this->matrix_->matrix[row][col];
  }
}

int S21Matrix::get_rows() const { return rows_; }
int S21Matrix::get_cols() const { return cols_; }
double S21Matrix::get_element_matrix_(int row, int col) const {
  if ((row < 0 || row >= this->rows_) || (col < 0 || col >= this->cols_)) {
    throw std::runtime_error("Index is outside the matrix");
  } else {
    return this->matrix_->matrix[row][col];
  }
}
void S21Matrix::set_rows(int rows) {
  if (rows <= 0) {
    throw std::runtime_error("Incorrect rows");
  } else if (rows < this->rows_) {
    S21Matrix result(rows, this->cols_);
    this->rows_ = rows;
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        result.matrix_->matrix[i][j] = this->matrix_->matrix[i][j];
      }
    }
    *this = std::move(result);
  } else if (rows > this->rows_) {
    S21Matrix result(rows, this->cols_);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        result.matrix_->matrix[i][j] = this->matrix_->matrix[i][j];
      }
    }
    this->rows_ = rows;
    *this = std::move(result);
  }
}
void S21Matrix::set_cols(int cols) {
  if (cols <= 0) {
    throw std::runtime_error("Incorrect cols");
  } else if (cols < this->cols_) {
    S21Matrix result(this->rows_, cols);
    this->cols_ = cols;
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        result.matrix_->matrix[i][j] = this->matrix_->matrix[i][j];
      }
    }
    *this = std::move(result);
  } else if (cols > this->cols_) {
    S21Matrix result(this->rows_, cols);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        result.matrix_->matrix[i][j] = this->matrix_->matrix[i][j];
      }
    }
    this->cols_ = cols;
    *this = std::move(result);
  }
}
void S21Matrix::set_element_matrix_(int row, int col, double element) {
  if ((row < 0 || row >= this->rows_) || (col < 0 || col >= this->cols_)) {
    throw std::runtime_error("Index is outside the matrix");
  } else {
    this->matrix_->matrix[row][col] = element;
  }
}
