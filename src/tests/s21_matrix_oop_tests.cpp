#include <gtest/gtest.h>

#include "s21_matrix_oop.hpp"

TEST(S21MatrixTest, DefaultMatrixCreation) {
  // Test that the default matrix creation does not throw an exception
  EXPECT_NO_THROW(S21Matrix());
}

TEST(S21MatrixTest, DefaultMatrixSize) {
  // Test that the default matrix has the correct size (1x1)
  S21Matrix matrix;
  EXPECT_EQ(matrix.get_rows(), 1);
  EXPECT_EQ(matrix.get_cols(), 1);
}

TEST(S21MatrixTest, DefaultMatrixValues) {
  // Test that the default matrix has the correct values (0)
  S21Matrix matrix;
  EXPECT_EQ(matrix(0, 0), 0);
}

TEST(S21MatrixTest, DefaultMatrixCopy) {
  // Test that the copy constructor does not throw an exception
  S21Matrix matrix1;
  EXPECT_NO_THROW(S21Matrix matrix2(matrix1));
}

TEST(S21MatrixTest, DefaultMatrixMove) {
  // Test that the move constructor does not throw an exception
  S21Matrix matrix1;
  EXPECT_NO_THROW(S21Matrix matrix2(matrix1));
}

TEST(S21Matrix, Constructor_ValidDimensions) {
  // Arrange
  int rows = 3;
  int cols = 4;

  // Act
  S21Matrix matrix(rows, cols);

  // Assert
  EXPECT_EQ(matrix.get_rows(), rows);
  EXPECT_EQ(matrix.get_cols(), cols);
}

TEST(S21Matrix, Constructor_ZeroRows) {
  // Arrange
  int rows = 0;
  int cols = 4;

  // Act and Assert
  EXPECT_THROW(S21Matrix matrix(rows, cols), std::runtime_error);
}

TEST(S21Matrix, Constructor_ZeroCols) {
  // Arrange
  int rows = 3;
  int cols = 0;

  // Act and Assert
  EXPECT_THROW(S21Matrix matrix(rows, cols), std::runtime_error);
}

TEST(S21Matrix, Constructor_NegativeRows) {
  // Arrange
  int rows = -3;
  int cols = 4;

  // Act and Assert
  EXPECT_THROW(S21Matrix matrix(rows, cols), std::runtime_error);
}

TEST(S21Matrix, Constructor_NegativeCols) {
  // Arrange
  int rows = 3;
  int cols = -4;

  // Act and Assert
  EXPECT_THROW(S21Matrix matrix(rows, cols), std::runtime_error);
}

TEST(S21Matrix, CopyConstructor_SameSizeMatrix_Success) {
  S21Matrix matrix1(2, 2);

  S21Matrix matrix2(matrix1);

  EXPECT_EQ(matrix1.get_rows(), matrix2.get_rows());
  EXPECT_EQ(matrix1.get_cols(), matrix2.get_cols());
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(S21Matrix, CopyConstructor_No_ThrowsException) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);

  EXPECT_NO_THROW(S21Matrix matrix1(matrix2));
}

TEST(S21Matrix, CopyConstructor_MatrixWithZeroValues_Success) {
  S21Matrix matrix1(2, 2);

  S21Matrix matrix2(matrix1);

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(S21Matrix, CopyConstructor_MatrixWithNegativeValues_Success) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, -1);
  matrix1.set_element_matrix_(0, 1, -5);
  matrix1.set_element_matrix_(1, 0, -10);
  matrix1.set_element_matrix_(1, 1, -1);

  S21Matrix matrix2(matrix1);

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(S21Matrix, CopyConstructor_MatrixWithFloatingPointValues_Success) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, -1.0);
  matrix1.set_element_matrix_(0, 1, -5.3);
  matrix1.set_element_matrix_(1, 0, 10.09);
  matrix1.set_element_matrix_(1, 1, -1.67);

  S21Matrix matrix2(matrix1);

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(S21MatrixMoveConstructor, NoException) {
  S21Matrix matrix1(2, 3);
  matrix1.set_element_matrix_(0, 0, 1.0);
  matrix1.set_element_matrix_(0, 1, 2.0);
  matrix1.set_element_matrix_(0, 2, 3.0);
  matrix1.set_element_matrix_(1, 0, 4.0);
  matrix1.set_element_matrix_(1, 1, 5.0);
  matrix1.set_element_matrix_(1, 2, 6.0);

  S21Matrix matrix2(std::move(matrix1));

  EXPECT_EQ(matrix2.get_rows(), 2);
  EXPECT_EQ(matrix2.get_cols(), 3);
  EXPECT_EQ(matrix2.get_element_matrix_(0, 0), 1.0);
  EXPECT_EQ(matrix2.get_element_matrix_(0, 1), 2.0);
  EXPECT_EQ(matrix2.get_element_matrix_(0, 2), 3.0);
  EXPECT_EQ(matrix2.get_element_matrix_(1, 0), 4.0);
  EXPECT_EQ(matrix2.get_element_matrix_(1, 1), 5.0);
  EXPECT_EQ(matrix2.get_element_matrix_(1, 2), 6.0);
}

TEST(S21MatrixMoveConstructor, MatrixIsMoved) {
  S21Matrix matrix1(2, 3);
  matrix1.set_element_matrix_(0, 0, 1.0);
  matrix1.set_element_matrix_(0, 1, 2.0);
  matrix1.set_element_matrix_(0, 2, 3.0);
  matrix1.set_element_matrix_(1, 0, 4.0);
  matrix1.set_element_matrix_(1, 1, 5.0);
  matrix1.set_element_matrix_(1, 2, 6.0);

  S21Matrix matrix2(std::move(matrix1));

  // Check if matrix1 is in a valid state after moving
  EXPECT_EQ(matrix1.get_rows(), 0);
  EXPECT_EQ(matrix1.get_cols(), 0);
  EXPECT_THROW(matrix1.get_element_matrix_(0, 0), std::runtime_error);
}

TEST(S21MatrixMoveConstructor, MatrixIsCopied) {
  S21Matrix matrix1(2, 3);
  matrix1.set_element_matrix_(0, 0, 1.0);
  matrix1.set_element_matrix_(0, 1, 2.0);
  matrix1.set_element_matrix_(0, 2, 3.0);
  matrix1.set_element_matrix_(1, 0, 4.0);
  matrix1.set_element_matrix_(1, 1, 5.0);
  matrix1.set_element_matrix_(1, 2, 6.0);

  S21Matrix matrix2(matrix1);

  EXPECT_EQ(matrix2.get_rows(), 2);
  EXPECT_EQ(matrix2.get_cols(), 3);
  EXPECT_EQ(matrix2.get_element_matrix_(0, 0), 1.0);
  EXPECT_EQ(matrix2.get_element_matrix_(0, 1), 2.0);
  EXPECT_EQ(matrix2.get_element_matrix_(0, 2), 3.0);
  EXPECT_EQ(matrix2.get_element_matrix_(1, 0), 4.0);
  EXPECT_EQ(matrix2.get_element_matrix_(1, 1), 5.0);
  EXPECT_EQ(matrix2.get_element_matrix_(1, 2), 6.0);
}

TEST(S21MatrixMoveConstructor, MatrixIsCopiedAfterMove) {
  S21Matrix matrix1(2, 3);
  matrix1.set_element_matrix_(0, 0, 1.0);
  matrix1.set_element_matrix_(0, 1, 2.0);
  matrix1.set_element_matrix_(0, 2, 3.0);
  matrix1.set_element_matrix_(1, 0, 4.0);
  matrix1.set_element_matrix_(1, 1, 5.0);
  matrix1.set_element_matrix_(1, 2, 6.0);

  S21Matrix matrix2(std::move(matrix1));
  S21Matrix matrix3(matrix2);

  EXPECT_EQ(matrix3.get_rows(), 2);
  EXPECT_EQ(matrix3.get_cols(), 3);
  EXPECT_EQ(matrix3.get_element_matrix_(0, 0), 1.0);
  EXPECT_EQ(matrix3.get_element_matrix_(0, 1), 2.0);
  EXPECT_EQ(matrix3.get_element_matrix_(0, 2), 3.0);
  EXPECT_EQ(matrix3.get_element_matrix_(1, 0), 4.0);
  EXPECT_EQ(matrix3.get_element_matrix_(1, 1), 5.0);
  EXPECT_EQ(matrix3.get_element_matrix_(1, 2), 6.0);
}

TEST(S21MatrixMoveConstructor, MatrixIsMovedAfterCopy) {
  S21Matrix matrix1(2, 3);
  matrix1.set_element_matrix_(0, 0, 1.0);
  matrix1.set_element_matrix_(0, 1, 2.0);
  matrix1.set_element_matrix_(0, 2, 3.0);
  matrix1.set_element_matrix_(1, 0, 4.0);
  matrix1.set_element_matrix_(1, 1, 5.0);
  matrix1.set_element_matrix_(1, 2, 6.0);

  S21Matrix matrix2(matrix1);
  S21Matrix matrix3(std::move(matrix2));

  EXPECT_EQ(matrix3.get_rows(), 2);
  EXPECT_EQ(matrix3.get_cols(), 3);
  EXPECT_EQ(matrix3.get_element_matrix_(0, 0), 1.0);
  EXPECT_EQ(matrix3.get_element_matrix_(0, 1), 2.0);
  EXPECT_EQ(matrix3.get_element_matrix_(0, 2), 3.0);
  EXPECT_EQ(matrix3.get_element_matrix_(1, 0), 4.0);
  EXPECT_EQ(matrix3.get_element_matrix_(1, 1), 5.0);
  EXPECT_EQ(matrix3.get_element_matrix_(1, 2), 6.0);
}

TEST(S21Matrix, DestructorValidMatrix) {
  S21Matrix matrix5(2, 3);  // Create a valid matrix
  // Fill the matrix with some values
  for (int i = 0; i < matrix5.get_rows(); i++) {
    for (int j = 0; j < matrix5.get_cols(); j++) {
      matrix5.set_element_matrix_(i, j, i * j);
    }
  }
  // Destructor should not throw any exceptions
  EXPECT_NO_THROW(matrix5.~S21Matrix());
}

TEST(S21MatrixTest, EqMatrix_IdenticalMatrices_ReturnTrue) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1.0);
  matrix1.set_element_matrix_(0, 1, 2.0);
  matrix1.set_element_matrix_(1, 0, 3.0);
  matrix1.set_element_matrix_(1, 1, 4.0);

  S21Matrix matrix2(matrix1);

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(S21MatrixTest, EqMatrix_DifferentElementValues_ReturnFalse) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1.0);
  matrix1.set_element_matrix_(0, 1, 2.0);
  matrix1.set_element_matrix_(1, 0, 3.0);
  matrix1.set_element_matrix_(1, 1, 4.0);

  S21Matrix matrix2(2, 2);
  matrix2.set_element_matrix_(0, 0, 5.0);
  matrix2.set_element_matrix_(0, 1, 6.0);
  matrix2.set_element_matrix_(1, 0, 7.0);
  matrix2.set_element_matrix_(1, 1, 8.0);

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(S21MatrixTest, EqMatrix_EmptyMatrices_ReturnTrue) {
  S21Matrix matrix1;
  S21Matrix matrix2;

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(S21MatrixTest, EqMatrix_DifferentSizes_ReturnFalse) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(S21MatrixTest, EqMatrix_SameMatrix_ReturnTrue) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1.0);
  matrix1.set_element_matrix_(0, 1, 2.0);
  matrix1.set_element_matrix_(1, 0, 3.0);
  matrix1.set_element_matrix_(1, 1, 4.0);

  EXPECT_TRUE(matrix1.EqMatrix(matrix1));
}

TEST(S21MatrixTest, SumMatrix_ValidAddition) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1.0);
  matrix1.set_element_matrix_(0, 1, 2.0);
  matrix1.set_element_matrix_(1, 0, 3.0);
  matrix1.set_element_matrix_(1, 1, 4.0);

  S21Matrix matrix2(2, 2);
  matrix2.set_element_matrix_(0, 0, 5.0);
  matrix2.set_element_matrix_(0, 1, 6.0);
  matrix2.set_element_matrix_(1, 0, 7.0);
  matrix2.set_element_matrix_(1, 1, 8.0);

  EXPECT_NO_THROW(matrix1.SumMatrix(matrix2));
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 6.0);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 8.0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 10.0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 12.0);
}

TEST(S21MatrixTest, SumMatrix_DifferentDimensions) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);

  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::runtime_error);
}

TEST(S21MatrixTest, SumMatrix_EmptyMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2;

  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::runtime_error);
}

TEST(S21MatrixTest, SumMatrix_ZeroMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1.0);
  matrix1.set_element_matrix_(0, 1, 2.0);
  matrix1.set_element_matrix_(1, 0, 3.0);
  matrix1.set_element_matrix_(1, 1, 4.0);

  S21Matrix zeroMatrix(2, 2);  // Automatically initialized to zero

  EXPECT_NO_THROW(matrix1.SumMatrix(zeroMatrix));
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 1.0);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 2.0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 3.0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 4.0);
}

TEST(S21MatrixTest, SumMatrix_SelfAddition) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1.0);
  matrix1.set_element_matrix_(0, 1, 2.0);
  matrix1.set_element_matrix_(1, 0, 3.0);
  matrix1.set_element_matrix_(1, 1, 4.0);

  EXPECT_NO_THROW(matrix1.SumMatrix(matrix1));
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 2.0);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 4.0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 6.0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 8.0);
}

TEST(S21MatrixTest, SubMatrix_ValidSubtraction) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 5.0);
  matrix1.set_element_matrix_(0, 1, 6.0);
  matrix1.set_element_matrix_(1, 0, 7.0);
  matrix1.set_element_matrix_(1, 1, 8.0);

  S21Matrix matrix2(2, 2);
  matrix2.set_element_matrix_(0, 0, 1.0);
  matrix2.set_element_matrix_(0, 1, 2.0);
  matrix2.set_element_matrix_(1, 0, 3.0);
  matrix2.set_element_matrix_(1, 1, 4.0);

  EXPECT_NO_THROW(matrix1.SubMatrix(matrix2));
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 4.0);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 4.0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 4.0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 4.0);
}

TEST(S21MatrixTest, SubMatrix_DifferentDimensions) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);

  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::runtime_error);
}

TEST(S21MatrixTest, SubMatrix_EmptyMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1.0);
  matrix1.set_element_matrix_(0, 1, 2.0);
  matrix1.set_element_matrix_(1, 0, 3.0);
  matrix1.set_element_matrix_(1, 1, 4.0);

  S21Matrix emptyMatrix;

  EXPECT_THROW(matrix1.SubMatrix(emptyMatrix), std::runtime_error);
}

TEST(S21MatrixTest, SubMatrix_ZeroMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1.0);
  matrix1.set_element_matrix_(0, 1, 2.0);
  matrix1.set_element_matrix_(1, 0, 3.0);
  matrix1.set_element_matrix_(1, 1, 4.0);

  S21Matrix zeroMatrix(2, 2);  // Automatically initialized to zero

  EXPECT_NO_THROW(matrix1.SubMatrix(zeroMatrix));
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 1.0);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 2.0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 3.0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 4.0);
}

TEST(S21MatrixTest, SubMatrix_SelfSubtraction) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1.0);
  matrix1.set_element_matrix_(0, 1, 2.0);
  matrix1.set_element_matrix_(1, 0, 3.0);
  matrix1.set_element_matrix_(1, 1, 4.0);

  EXPECT_NO_THROW(matrix1.SubMatrix(matrix1));
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 0.0);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 0.0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 0.0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 0.0);
}

TEST(S21MatrixTest, MulNumber_PositiveNumber) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1.0);
  matrix.set_element_matrix_(0, 1, 2.0);
  matrix.set_element_matrix_(1, 0, 3.0);
  matrix.set_element_matrix_(1, 1, 4.0);
  double multiplier = 5.0;

  EXPECT_NO_THROW(matrix.MulNumber(multiplier));
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), 5.0);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), 10.0);
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), 15.0);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), 20.0);
}

TEST(S21MatrixTest, MulNumber_Zero) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1.0);
  matrix.set_element_matrix_(0, 1, 2.0);
  matrix.set_element_matrix_(1, 0, 3.0);
  matrix.set_element_matrix_(1, 1, 4.0);
  double multiplier = 0.0;

  EXPECT_NO_THROW(matrix.MulNumber(multiplier));
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), 0.0);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), 0.0);
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), 0.0);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), 0.0);
}

TEST(S21MatrixTest, MulNumber_NegativeNumber) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 2.0);
  matrix.set_element_matrix_(0, 1, 3.0);
  matrix.set_element_matrix_(1, 0, 4.0);
  matrix.set_element_matrix_(1, 1, 5.0);
  double multiplier = -2.0;

  EXPECT_NO_THROW(matrix.MulNumber(multiplier));
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), -4.0);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), -6.0);
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), -8.0);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), -10.0);
}

TEST(S21MatrixTest, MulNumber_One) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1.0);
  matrix.set_element_matrix_(0, 1, 2.0);
  matrix.set_element_matrix_(1, 0, 3.0);
  matrix.set_element_matrix_(1, 1, 4.0);
  double multiplier = 1.0;

  EXPECT_NO_THROW(matrix.MulNumber(multiplier));
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), 1.0);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), 2.0);
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), 3.0);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), 4.0);
}

TEST(S21MatrixTest, MulMatrix_ValidMultiplication) {
  S21Matrix matrix1(2, 3);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(0, 2, 3);
  matrix1.set_element_matrix_(1, 0, 4);
  matrix1.set_element_matrix_(1, 1, 5);
  matrix1.set_element_matrix_(1, 2, 6);

  S21Matrix matrix2(3, 2);
  matrix2.set_element_matrix_(0, 0, 1);
  matrix2.set_element_matrix_(1, 0, 2);
  matrix2.set_element_matrix_(2, 0, 3);
  matrix2.set_element_matrix_(0, 1, 4);
  matrix2.set_element_matrix_(1, 1, 5);
  matrix2.set_element_matrix_(2, 1, 6);

  EXPECT_NO_THROW(matrix1.MulMatrix(matrix2));
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 14);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 32);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 32);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 77);
}

TEST(S21MatrixTest, MulMatrix_IncompatibleSizes) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);

  EXPECT_THROW(matrix1.MulMatrix(matrix2), std::runtime_error);
}

TEST(S21MatrixTest, MulMatrix_IdentityMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix identityMatrix(2, 2);
  identityMatrix.set_element_matrix_(0, 0, 1);
  identityMatrix.set_element_matrix_(1, 1, 1);

  EXPECT_NO_THROW(matrix1.MulMatrix(identityMatrix));
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 1);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 2);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 3);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 4);
}

TEST(S21MatrixTest, MulMatrix_EmptyMatrix) {
  S21Matrix matrix1;
  S21Matrix matrix2;

  EXPECT_NO_THROW(matrix1.MulMatrix(matrix2));
  EXPECT_EQ(matrix1.get_rows(), 1);
  EXPECT_EQ(matrix1.get_cols(), 1);
}

TEST(S21MatrixTest, MulMatrix_SelfMultiplication) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(1, 0, 3);
  matrix.set_element_matrix_(1, 1, 4);
  S21Matrix matrix2(matrix);

  EXPECT_NO_THROW(matrix.MulMatrix(matrix2));
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), 7);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), 10);
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), 15);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), 22);
}

TEST(S21MatrixTest, Transpose_SquareMatrix) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1.0);
  matrix.set_element_matrix_(0, 1, 2.0);
  matrix.set_element_matrix_(1, 0, 3.0);
  matrix.set_element_matrix_(1, 1, 4.0);

  S21Matrix transposed = matrix.Transpose();

  EXPECT_EQ(transposed.get_rows(), 2);
  EXPECT_EQ(transposed.get_cols(), 2);
  EXPECT_EQ(transposed.get_element_matrix_(0, 0), 1.0);
  EXPECT_EQ(transposed.get_element_matrix_(0, 1), 3.0);
  EXPECT_EQ(transposed.get_element_matrix_(1, 0), 2.0);
  EXPECT_EQ(transposed.get_element_matrix_(1, 1), 4.0);
}

TEST(S21MatrixTest, Transpose_RectangularMatrix) {
  S21Matrix matrix(2, 3);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(0, 2, 3);
  matrix.set_element_matrix_(1, 0, 4);
  matrix.set_element_matrix_(1, 1, 5);
  matrix.set_element_matrix_(1, 2, 6);

  S21Matrix transposed = matrix.Transpose();

  EXPECT_EQ(transposed.get_rows(), 3);
  EXPECT_EQ(transposed.get_cols(), 2);
  EXPECT_EQ(transposed.get_element_matrix_(0, 0), 1);
  EXPECT_EQ(transposed.get_element_matrix_(0, 1), 4);
  EXPECT_EQ(transposed.get_element_matrix_(1, 0), 2);
  EXPECT_EQ(transposed.get_element_matrix_(1, 1), 5);
  EXPECT_EQ(transposed.get_element_matrix_(2, 0), 3);
  EXPECT_EQ(transposed.get_element_matrix_(2, 1), 6);
}

TEST(S21MatrixTest, Transpose_EmptyMatrix) {
  S21Matrix matrix;
  EXPECT_NO_THROW({
    S21Matrix transposed = matrix.Transpose();
    EXPECT_EQ(transposed.get_rows(), 1);
    EXPECT_EQ(transposed.get_cols(), 1);
  });
}

TEST(S21MatrixTest, Transpose_IncorrectMatrix) {
  S21Matrix matrix;  // Предположим, что матрица некорректно инициализирована
  EXPECT_THROW(matrix.set_rows(0), std::runtime_error);
  EXPECT_THROW(matrix.set_cols(-1),
               std::runtime_error);  // Некорректные значения
  EXPECT_NO_THROW(matrix.Transpose());
}

TEST(S21MatrixTest, Transpose_SelfTranspose) {
  S21Matrix matrix(1, 3);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(0, 2, 3);

  S21Matrix transposed = matrix.Transpose().Transpose();

  EXPECT_EQ(transposed.get_rows(), 1);
  EXPECT_EQ(transposed.get_cols(), 3);
  EXPECT_EQ(transposed.get_element_matrix_(0, 0), 1);
  EXPECT_EQ(transposed.get_element_matrix_(0, 1), 2);
  EXPECT_EQ(transposed.get_element_matrix_(0, 2), 3);
}

TEST(S21MatrixTest, CalcComplements_SmallSquareMatrix) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1);  // a
  matrix.set_element_matrix_(0, 1, 2);  // b
  matrix.set_element_matrix_(1, 0, 3);  // c
  matrix.set_element_matrix_(1, 1, 4);  // d

  S21Matrix complements = matrix.CalcComplements();

  // Calculate expected cofactors:
  // Cofactor for a is  d = 4
  // Cofactor for b is -c = -3
  // Cofactor for c is -b = -2
  // Cofactor for d is  a = 1

  EXPECT_EQ(complements.get_element_matrix_(0, 0), 4);   // Cofactor of a
  EXPECT_EQ(complements.get_element_matrix_(0, 1), -3);  // Cofactor of b
  EXPECT_EQ(complements.get_element_matrix_(1, 0), -2);  // Cofactor of c
  EXPECT_EQ(complements.get_element_matrix_(1, 1), 1);   // Cofactor of d
}

TEST(S21MatrixTest, CalcComplements_NonSquareMatrix) {
  S21Matrix matrix(2, 3);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(0, 2, 3);
  matrix.set_element_matrix_(1, 0, 4);
  matrix.set_element_matrix_(1, 1, 5);
  matrix.set_element_matrix_(1, 2, 6);

  EXPECT_THROW(matrix.CalcComplements(), std::runtime_error);
}

TEST(S21MatrixTest, CalcComplements_ZeroSquareMatrix) {
  S21Matrix matrix(3, 3);
  // Initialize all elements to 0
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix.set_element_matrix_(i, j, 0);
    }
  }

  S21Matrix complements = matrix.CalcComplements();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(complements.get_element_matrix_(i, j), 0);
    }
  }
}

TEST(S21MatrixTest, CalcComplements_SingleElement) {
  S21Matrix matrix(1, 1);
  matrix.set_element_matrix_(0, 0, 42);

  S21Matrix complements = matrix.CalcComplements();
  EXPECT_EQ(complements.get_element_matrix_(0, 0),
            42);  // Cofactor of a 1x1 matrix is 1
}

TEST(S21MatrixTest, CalcComplements_LargerSquareMatrix) {
  S21Matrix matrix(3, 3);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(0, 2, 3);
  matrix.set_element_matrix_(1, 0, 0);
  matrix.set_element_matrix_(1, 1, 4);
  matrix.set_element_matrix_(1, 2, 2);
  matrix.set_element_matrix_(2, 0, 5);
  matrix.set_element_matrix_(2, 1, 2);
  matrix.set_element_matrix_(2, 2, 1);

  S21Matrix complements = matrix.CalcComplements();
  EXPECT_EQ(complements.get_element_matrix_(0, 0), 0);
  EXPECT_EQ(complements.get_element_matrix_(0, 1), 10);
  EXPECT_EQ(complements.get_element_matrix_(0, 2), -20);
  EXPECT_EQ(complements.get_element_matrix_(1, 0), 4);
  EXPECT_EQ(complements.get_element_matrix_(1, 1), -14);
  EXPECT_EQ(complements.get_element_matrix_(1, 2), 8);
  EXPECT_EQ(complements.get_element_matrix_(2, 0), -8);
  EXPECT_EQ(complements.get_element_matrix_(2, 1), -2);
  EXPECT_EQ(complements.get_element_matrix_(2, 2), 4);
}

TEST(S21MatrixTest, Determinant_SquareMatrix2x2) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(1, 0, 3);
  matrix.set_element_matrix_(1, 1, 4);
  EXPECT_NO_THROW({
    double result = matrix.Determinant();
    EXPECT_DOUBLE_EQ(
        result, -2);  // Детерминант для [[1, 2], [3, 4]] равен 1*4 - 2*3 = -2
  });
}

TEST(S21MatrixTest, Determinant_SquareMatrix3x3) {
  S21Matrix matrix(3, 3);
  matrix.set_element_matrix_(0, 0, 6);
  matrix.set_element_matrix_(0, 1, 1);
  matrix.set_element_matrix_(0, 2, 1);
  matrix.set_element_matrix_(1, 0, 4);
  matrix.set_element_matrix_(1, 1, -2);
  matrix.set_element_matrix_(1, 2, 5);
  matrix.set_element_matrix_(2, 0, 2);
  matrix.set_element_matrix_(2, 1, 8);
  matrix.set_element_matrix_(2, 2, 7);
  EXPECT_NO_THROW({
    double result = matrix.Determinant();
    EXPECT_DOUBLE_EQ(result, -306);  // Детерминант для заданной матрицы
  });
}

TEST(S21MatrixTest, Determinant_NonSquareMatrix) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(matrix.Determinant(), std::runtime_error);
}

TEST(S21MatrixTest, Determinant_SingleElementMatrix) {
  S21Matrix matrix(1, 1);
  matrix.set_element_matrix_(0, 0, 5);
  EXPECT_NO_THROW({
    double result = matrix.Determinant();
    EXPECT_DOUBLE_EQ(
        result,
        5);  // Детерминант для матрицы 1x1 равен её единственному элементу
  });
}

TEST(S21MatrixTest, Determinant_LargeSquareMatrix) {
  S21Matrix matrix(4, 4);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(0, 2, 3);
  matrix.set_element_matrix_(0, 3, 4);
  matrix.set_element_matrix_(1, 0, 5);
  matrix.set_element_matrix_(1, 1, 6);
  matrix.set_element_matrix_(1, 2, 7);
  matrix.set_element_matrix_(1, 3, 8);
  matrix.set_element_matrix_(2, 0, 9);
  matrix.set_element_matrix_(2, 1, 10);
  matrix.set_element_matrix_(2, 2, 11);
  matrix.set_element_matrix_(2, 3, 12);
  matrix.set_element_matrix_(3, 0, 13);
  matrix.set_element_matrix_(3, 1, 14);
  matrix.set_element_matrix_(3, 2, 15);
  matrix.set_element_matrix_(3, 3, 16);
  EXPECT_NO_THROW({
    double result = matrix.Determinant();
    EXPECT_DOUBLE_EQ(
        result, 0);  // Детерминант для этой конкретной матрицы должен быть 0
  });
}

TEST(S21MatrixTest, InverseMatrix_SquareMatrixWithInverse) {
  S21Matrix matrix(3, 3);
  matrix.set_element_matrix_(0, 0, 1.0);
  matrix.set_element_matrix_(0, 1, -1.0);
  matrix.set_element_matrix_(0, 2, 1.0);
  matrix.set_element_matrix_(1, 0, -38.0);
  matrix.set_element_matrix_(1, 1, 41.0);
  matrix.set_element_matrix_(1, 2, -34.0);
  matrix.set_element_matrix_(2, 0, 27.0);
  matrix.set_element_matrix_(2, 1, -29.0);
  matrix.set_element_matrix_(2, 2, 24.0);

  S21Matrix result = matrix.InverseMatrix();  // Убедитесь, что функция
                                              // возвращает правильные значения
  EXPECT_NEAR(result.get_element_matrix_(0, 0), 2.0, 1e-5);
  EXPECT_NEAR(result.get_element_matrix_(0, 1), 5.0, 1e-5);
  EXPECT_NEAR(result.get_element_matrix_(0, 2), 7.0, 1e-5);
  EXPECT_NEAR(result.get_element_matrix_(1, 0), 6.0, 1e-5);
  EXPECT_NEAR(result.get_element_matrix_(1, 1), 3.0, 1e-5);
  EXPECT_NEAR(result.get_element_matrix_(1, 2), 4.0, 1e-5);
  EXPECT_NEAR(result.get_element_matrix_(2, 0), 5.0, 1e-5);
  EXPECT_NEAR(result.get_element_matrix_(2, 1), -2.0, 1e-5);
  EXPECT_NEAR(result.get_element_matrix_(2, 2), -3.0, 1e-5);
}

TEST(S21MatrixTest, InverseMatrix_SingularMatrix) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(1, 0, 2);
  matrix.set_element_matrix_(1, 1, 4);
  EXPECT_THROW(matrix.InverseMatrix(), std::runtime_error);
}

TEST(S21MatrixTest, InverseMatrix_OneByOneMatrix) {
  S21Matrix matrix(1, 1);
  matrix.set_element_matrix_(0, 0, 3);
  EXPECT_NO_THROW({
    S21Matrix result = matrix.InverseMatrix();
    EXPECT_DOUBLE_EQ(result.get_element_matrix_(0, 0), 1.0 / 3.0);
  });
}

TEST(S21MatrixTest, InverseMatrix_LargeSquareMatrix) {
  S21Matrix matrix(3, 3);
  matrix.set_element_matrix_(0, 0, 2);
  matrix.set_element_matrix_(0, 1, -1);
  matrix.set_element_matrix_(0, 2, 0);
  matrix.set_element_matrix_(1, 0, -1);
  matrix.set_element_matrix_(1, 1, 2);
  matrix.set_element_matrix_(1, 2, -1);
  matrix.set_element_matrix_(2, 0, 0);
  matrix.set_element_matrix_(2, 1, -1);
  matrix.set_element_matrix_(2, 2, 2);
  EXPECT_NO_THROW({
    S21Matrix result = matrix.InverseMatrix();
    EXPECT_NEAR(result.get_element_matrix_(0, 0), 0.75, 1e-5);
    EXPECT_NEAR(result.get_element_matrix_(0, 1), 0.5, 1e-5);
    EXPECT_NEAR(result.get_element_matrix_(0, 2), 0.25, 1e-5);
    EXPECT_NEAR(result.get_element_matrix_(1, 1), 1, 1e-5);
    EXPECT_NEAR(result.get_element_matrix_(2, 2), 0.75, 1e-5);
  });
}

TEST(S21MatrixTest, InverseMatrix_NonSquareMatrix) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(matrix.InverseMatrix(), std::runtime_error);
}

TEST(S21MatrixTest, OperatorPlus_ValidMatrices) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix matrix2(2, 2);
  matrix2.set_element_matrix_(0, 0, 5);
  matrix2.set_element_matrix_(0, 1, 6);
  matrix2.set_element_matrix_(1, 0, 7);
  matrix2.set_element_matrix_(1, 1, 8);

  S21Matrix result = matrix1 + matrix2;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 6);
  EXPECT_EQ(result.get_element_matrix_(0, 1), 8);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 10);
  EXPECT_EQ(result.get_element_matrix_(1, 1), 12);
}

TEST(S21MatrixTest, OperatorPlus_AddZeroMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix matrix2(2, 2);  // Нулевая матрица по умолчанию

  S21Matrix result = matrix1 + matrix2;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 1);
  EXPECT_EQ(result.get_element_matrix_(0, 1), 2);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 3);
  EXPECT_EQ(result.get_element_matrix_(1, 1), 4);
}

TEST(S21MatrixTest, OperatorPlus_DifferentSizes) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  EXPECT_THROW(matrix1 + matrix2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorPlus_LargeMatrices) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  // Заполнение матриц значений для тестирования
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1.set_element_matrix_(i, j, i * j + 1);
      matrix2.set_element_matrix_(i, j, i + j + 1);
    }
  }

  S21Matrix result = matrix1 + matrix2;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(result.get_element_matrix_(i, j), i * j + i + j + 2);
    }
  }
}

TEST(S21MatrixTest, OperatorPlus_AddSelf) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix result = matrix1 + matrix1;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 2);
  EXPECT_EQ(result.get_element_matrix_(0, 1), 4);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 6);
  EXPECT_EQ(result.get_element_matrix_(1, 1), 8);
}

TEST(S21MatrixTest, OperatorMinus_ValidMatrices) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 5);
  matrix1.set_element_matrix_(0, 1, 6);
  matrix1.set_element_matrix_(1, 0, 7);
  matrix1.set_element_matrix_(1, 1, 8);

  S21Matrix matrix2(2, 2);
  matrix2.set_element_matrix_(0, 0, 1);
  matrix2.set_element_matrix_(0, 1, 2);
  matrix2.set_element_matrix_(1, 0, 3);
  matrix2.set_element_matrix_(1, 1, 4);

  S21Matrix result = matrix1 - matrix2;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 4);
  EXPECT_EQ(result.get_element_matrix_(0, 1), 4);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 4);
  EXPECT_EQ(result.get_element_matrix_(1, 1), 4);
}

TEST(S21MatrixTest, OperatorMinus_SubtractZeroMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix matrix2(2, 2);  // Нулевая матрица по умолчанию

  S21Matrix result = matrix1 - matrix2;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 1);
  EXPECT_EQ(result.get_element_matrix_(0, 1), 2);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 3);
  EXPECT_EQ(result.get_element_matrix_(1, 1), 4);
}

TEST(S21MatrixTest, OperatorMinus_DifferentSizes) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  EXPECT_THROW(matrix1 - matrix2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorMinus_SubtractSelf) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix result = matrix1 - matrix1;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 0);
  EXPECT_EQ(result.get_element_matrix_(0, 1), 0);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 0);
  EXPECT_EQ(result.get_element_matrix_(1, 1), 0);
}

TEST(S21MatrixTest, OperatorMinus_ChangeSigns) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, -2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, -4);

  S21Matrix matrix2(2, 2);
  matrix2.set_element_matrix_(0, 0, -1);
  matrix2.set_element_matrix_(0, 1, 2);
  matrix2.set_element_matrix_(1, 0, -3);
  matrix2.set_element_matrix_(1, 1, 4);

  S21Matrix result = matrix1 - matrix2;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 2);
  EXPECT_EQ(result.get_element_matrix_(0, 1), -4);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 6);
  EXPECT_EQ(result.get_element_matrix_(1, 1), -8);
}

TEST(S21MatrixTest, OperatorMultiply_ValidMatrices) {
  S21Matrix matrix1(2, 3);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(0, 2, 3);
  matrix1.set_element_matrix_(1, 0, 4);
  matrix1.set_element_matrix_(1, 1, 5);
  matrix1.set_element_matrix_(1, 2, 6);

  S21Matrix matrix2(3, 2);
  matrix2.set_element_matrix_(0, 0, 1);
  matrix2.set_element_matrix_(0, 1, 2);
  matrix2.set_element_matrix_(1, 0, 3);
  matrix2.set_element_matrix_(1, 1, 4);
  matrix2.set_element_matrix_(2, 0, 5);
  matrix2.set_element_matrix_(2, 1, 6);

  S21Matrix result = matrix1 * matrix2;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 22);
  EXPECT_EQ(result.get_element_matrix_(0, 1), 28);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 49);
  EXPECT_EQ(result.get_element_matrix_(1, 1), 64);
}

TEST(S21MatrixTest, OperatorMultiply_IdentityMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix identity(2, 2);
  identity.set_element_matrix_(0, 0, 1);
  identity.set_element_matrix_(0, 1, 0);
  identity.set_element_matrix_(1, 0, 0);
  identity.set_element_matrix_(1, 1, 1);

  S21Matrix result = matrix1 * identity;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 1);
  EXPECT_EQ(result.get_element_matrix_(0, 1), 2);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 3);
  EXPECT_EQ(result.get_element_matrix_(1, 1), 4);
}

TEST(S21MatrixTest, OperatorMultiply_IncompatibleSizes) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  EXPECT_THROW(matrix1 * matrix2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorMultiply_ZeroMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix zeroMatrix(2, 2);  // По умолчанию инициализируется нулями

  S21Matrix result = matrix1 * zeroMatrix;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 0);
  EXPECT_EQ(result.get_element_matrix_(0, 1), 0);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 0);
  EXPECT_EQ(result.get_element_matrix_(1, 1), 0);
}

TEST(S21MatrixTest, OperatorMultiply_SelfMultiplication) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix result = matrix1 * matrix1;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 7);
  EXPECT_EQ(result.get_element_matrix_(0, 1), 10);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 15);
  EXPECT_EQ(result.get_element_matrix_(1, 1), 22);
}

TEST(S21MatrixTest, OperatorMultiplyByPositiveNumber) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(1, 0, 3);
  matrix.set_element_matrix_(1, 1, 4);

  double multiplier = 5;
  S21Matrix result = matrix * multiplier;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 5);
  EXPECT_EQ(result.get_element_matrix_(0, 1), 10);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 15);
  EXPECT_EQ(result.get_element_matrix_(1, 1), 20);
}

TEST(S21MatrixTest, OperatorMultiplyByZero) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(1, 0, 3);
  matrix.set_element_matrix_(1, 1, 4);

  double multiplier = 0;
  S21Matrix result = matrix * multiplier;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 0);
  EXPECT_EQ(result.get_element_matrix_(0, 1), 0);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 0);
  EXPECT_EQ(result.get_element_matrix_(1, 1), 0);
}

TEST(S21MatrixTest, OperatorMultiplyByNegativeNumber) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(1, 0, 3);
  matrix.set_element_matrix_(1, 1, 4);

  double multiplier = -3;
  S21Matrix result = matrix * multiplier;
  EXPECT_EQ(result.get_element_matrix_(0, 0), -3);
  EXPECT_EQ(result.get_element_matrix_(0, 1), -6);
  EXPECT_EQ(result.get_element_matrix_(1, 0), -9);
  EXPECT_EQ(result.get_element_matrix_(1, 1), -12);
}

TEST(S21MatrixTest, OperatorMultiplyByFractionalNumber) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(1, 0, 3);
  matrix.set_element_matrix_(1, 1, 4);

  double multiplier = 0.5;
  S21Matrix result = matrix * multiplier;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 0.5);
  EXPECT_EQ(result.get_element_matrix_(0, 1), 1);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 1.5);
  EXPECT_EQ(result.get_element_matrix_(1, 1), 2);
}

TEST(S21MatrixTest, OperatorMultiplyZeroMatrixByNumber) {
  S21Matrix matrix(2, 2);  // Нулевая матрица по умолчанию

  double multiplier = 10;
  S21Matrix result = matrix * multiplier;
  EXPECT_EQ(result.get_element_matrix_(0, 0), 0);
  EXPECT_EQ(result.get_element_matrix_(0, 1), 0);
  EXPECT_EQ(result.get_element_matrix_(1, 0), 0);
  EXPECT_EQ(result.get_element_matrix_(1, 1), 0);
}

TEST(S21MatrixTest, OperatorEqual_IdenticalMatrices) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 5);
  matrix1.set_element_matrix_(0, 1, 6);
  matrix1.set_element_matrix_(1, 0, 7);
  matrix1.set_element_matrix_(1, 1, 8);

  S21Matrix matrix2(matrix1);  // Копия matrix1
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(S21MatrixTest, OperatorEqual_DifferentByOneElement) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 5);
  matrix1.set_element_matrix_(0, 1, 6);
  matrix1.set_element_matrix_(1, 0, 7);
  matrix1.set_element_matrix_(1, 1, 8);

  S21Matrix matrix2(2, 2);
  matrix2.set_element_matrix_(0, 0, 5);
  matrix2.set_element_matrix_(0, 1, 6);
  matrix2.set_element_matrix_(1, 0, 7);
  matrix2.set_element_matrix_(1, 1, 9);  // Изменённый элемент

  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(S21MatrixTest, OperatorEqual_ZeroMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 0);
  matrix1.set_element_matrix_(0, 1, 0);
  matrix1.set_element_matrix_(1, 0, 0);
  matrix1.set_element_matrix_(1, 1, 0);

  S21Matrix matrix2(2, 2);  // Нулевая матрица по умолчанию
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(S21MatrixTest, OperatorEqual_DifferentSizes) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(S21MatrixTest, OperatorEqual_SelfComparison) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 5);
  matrix1.set_element_matrix_(0, 1, 6);
  matrix1.set_element_matrix_(1, 0, 7);
  matrix1.set_element_matrix_(1, 1, 8);

  EXPECT_TRUE(matrix1 == matrix1);
}

TEST(S21MatrixTest, OperatorAssignment_SelfAssignment) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  matrix1 = matrix1;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 1);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 2);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 3);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 4);
}

TEST(S21MatrixTest, OperatorAssignment_ValidAssignment) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix2.set_element_matrix_(0, 0, 5);
  matrix2.set_element_matrix_(0, 1, 6);
  matrix2.set_element_matrix_(1, 0, 7);
  matrix2.set_element_matrix_(1, 1, 8);

  matrix1 = matrix2;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 5);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 6);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 7);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 8);
}

TEST(S21MatrixTest, OperatorAssignment_Reassignment) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);

  S21Matrix matrix2(2, 2);
  matrix2.set_element_matrix_(0, 0, 3);
  matrix2.set_element_matrix_(0, 1, 4);

  matrix1 = matrix2;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 3);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 4);
}

TEST(S21MatrixTest, OperatorAssignment_ChainAssignment) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix matrix3(2, 2);
  matrix3.set_element_matrix_(0, 0, 9);
  matrix3.set_element_matrix_(0, 1, 8);
  matrix3.set_element_matrix_(1, 0, 7);
  matrix3.set_element_matrix_(1, 1, 6);

  matrix1 = matrix2 = matrix3;
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 6);
  EXPECT_EQ(matrix2.get_element_matrix_(1, 1), 6);
}

TEST(S21MatrixTest, OperatorAssignment_DifferentSizeAssignment) {
  S21Matrix matrix1(2, 2);  // Создаём матрицу размером 2x2

  // Создаём матрицу размером 3x3 и заполняем её значением 1.0
  S21Matrix matrix2(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix2.set_element_matrix_(i, j, 1.0);
    }
  }

  matrix1 = matrix2;  // Присваиваем matrix2 к matrix1
  EXPECT_EQ(matrix1.get_rows(), 3);  // Проверяем количество строк
  EXPECT_EQ(matrix1.get_cols(), 3);  // Проверяем количество столбцов
  EXPECT_EQ(matrix1.get_element_matrix_(2, 2),
            1.0);  // Проверяем конкретный элемент
}

TEST(S21MatrixTest, OperatorPlusEquals_ValidMatrices) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix matrix2(2, 2);
  matrix2.set_element_matrix_(0, 0, 5);
  matrix2.set_element_matrix_(0, 1, 6);
  matrix2.set_element_matrix_(1, 0, 7);
  matrix2.set_element_matrix_(1, 1, 8);

  matrix1 += matrix2;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 6);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 8);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 10);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 12);
}

TEST(S21MatrixTest, OperatorPlusEquals_DifferentSizes) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);
  EXPECT_THROW(matrix1 += matrix2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorPlusEquals_ZeroMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix zeroMatrix(2, 2);  // По умолчанию нули

  matrix1 += zeroMatrix;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 1);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 2);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 3);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 4);
}

TEST(S21MatrixTest, OperatorPlusEquals_NegativeValues) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix matrix2(2, 2);
  matrix2.set_element_matrix_(0, 0, -1);
  matrix2.set_element_matrix_(0, 1, -2);
  matrix2.set_element_matrix_(1, 0, -3);
  matrix2.set_element_matrix_(1, 1, -4);

  matrix1 += matrix2;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 0);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 0);
}

TEST(S21MatrixTest, OperatorPlusEquals_SelfAddition) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  matrix1 += matrix1;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 2);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 4);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 6);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 8);
}

TEST(S21MatrixTest, OperatorMinusEquals_ValidMatrices) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 5);
  matrix1.set_element_matrix_(0, 1, 6);
  matrix1.set_element_matrix_(1, 0, 7);
  matrix1.set_element_matrix_(1, 1, 8);

  S21Matrix matrix2(2, 2);
  matrix2.set_element_matrix_(0, 0, 1);
  matrix2.set_element_matrix_(0, 1, 2);
  matrix2.set_element_matrix_(1, 0, 3);
  matrix2.set_element_matrix_(1, 1, 4);

  matrix1 -= matrix2;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 4);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 4);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 4);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 4);
}

TEST(S21MatrixTest, OperatorMinusEquals_DifferentSizes) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  EXPECT_THROW(matrix1 -= matrix2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorMinusEquals_ZeroMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix zeroMatrix(2, 2);  // Нулевая матрица по умолчанию

  matrix1 -= zeroMatrix;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 1);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 2);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 3);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 4);
}

TEST(S21MatrixTest, OperatorMinusEquals_SelfSubtraction) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 5);
  matrix1.set_element_matrix_(0, 1, 6);
  matrix1.set_element_matrix_(1, 0, 7);
  matrix1.set_element_matrix_(1, 1, 8);

  matrix1 -= matrix1;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 0);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 0);
}

TEST(S21MatrixTest, OperatorMinusEquals_NegativeValues) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix matrix2(2, 2);
  matrix2.set_element_matrix_(0, 0, -1);
  matrix2.set_element_matrix_(0, 1, -2);
  matrix2.set_element_matrix_(1, 0, -3);
  matrix2.set_element_matrix_(1, 1, -4);

  matrix1 -= matrix2;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 2);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 4);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 6);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 8);
}

TEST(S21MatrixTest, OperatorMultiplyEquals_ValidMatrices) {
  S21Matrix matrix1(2, 3);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(0, 2, 3);
  matrix1.set_element_matrix_(1, 0, 4);
  matrix1.set_element_matrix_(1, 1, 5);
  matrix1.set_element_matrix_(1, 2, 6);

  S21Matrix matrix2(3, 2);
  matrix2.set_element_matrix_(0, 0, 7);
  matrix2.set_element_matrix_(1, 0, 8);
  matrix2.set_element_matrix_(2, 0, 9);
  matrix2.set_element_matrix_(0, 1, 10);
  matrix2.set_element_matrix_(1, 1, 11);
  matrix2.set_element_matrix_(2, 1, 12);

  matrix1 *= matrix2;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 50);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 68);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 122);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 167);
}

TEST(S21MatrixTest, OperatorMultiplyEquals_IncompatibleSizes) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  EXPECT_THROW(matrix1 *= matrix2, std::runtime_error);
}

TEST(S21MatrixTest, OperatorMultiplyEquals_IdentityMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix identity(2, 2);
  identity.set_element_matrix_(0, 0, 1);
  identity.set_element_matrix_(1, 1, 1);

  matrix1 *= identity;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 1);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 2);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 3);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 4);
}

TEST(S21MatrixTest, OperatorMultiplyEquals_ZeroMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  S21Matrix zeroMatrix(2, 2);  // По умолчанию нули

  matrix1 *= zeroMatrix;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 0);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 0);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 0);
}

TEST(S21MatrixTest, OperatorMultiplyEquals_SelfMultiplication) {
  S21Matrix matrix1(2, 2);
  matrix1.set_element_matrix_(0, 0, 1);
  matrix1.set_element_matrix_(0, 1, 2);
  matrix1.set_element_matrix_(1, 0, 3);
  matrix1.set_element_matrix_(1, 1, 4);

  matrix1 *= matrix1;
  EXPECT_EQ(matrix1.get_element_matrix_(0, 0), 7);
  EXPECT_EQ(matrix1.get_element_matrix_(0, 1), 10);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 0), 15);
  EXPECT_EQ(matrix1.get_element_matrix_(1, 1), 22);
}

TEST(S21MatrixTest, OperatorMultiplyEquals_PositiveNumber) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(1, 0, 3);
  matrix.set_element_matrix_(1, 1, 4);

  double multiplier = 3;
  matrix *= multiplier;
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), 3);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), 6);
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), 9);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), 12);
}

TEST(S21MatrixTest, OperatorMultiplyEquals_Zero) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(1, 0, 3);
  matrix.set_element_matrix_(1, 1, 4);

  double multiplier = 0;
  matrix *= multiplier;
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), 0);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), 0);
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), 0);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), 0);
}

TEST(S21MatrixTest, OperatorMultiplyEquals_NegativeNumber) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(1, 0, 3);
  matrix.set_element_matrix_(1, 1, 4);

  double multiplier = -2;
  matrix *= multiplier;
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), -2);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), -4);
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), -6);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), -8);
}

TEST(S21MatrixTest, OperatorMultiplyEquals_FractionalNumber) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 5);
  matrix.set_element_matrix_(0, 1, 10);
  matrix.set_element_matrix_(1, 0, 15);
  matrix.set_element_matrix_(1, 1, 20);

  double multiplier = 0.5;
  matrix *= multiplier;
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), 2.5);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), 5);
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), 7.5);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), 10);
}

TEST(S21MatrixTest, OperatorMultiplyEquals_One) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 7);
  matrix.set_element_matrix_(0, 1, 8);
  matrix.set_element_matrix_(1, 0, 9);
  matrix.set_element_matrix_(1, 1, 10);

  double multiplier = 1;
  matrix *= multiplier;
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), 7);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), 8);
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), 9);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), 10);
}

TEST(S21MatrixTest, GetRows) {
  // Тест с матрицей 2x3
  S21Matrix matrix1(2, 3);
  EXPECT_EQ(matrix1.get_rows(), 2);

  // Тест с матрицей 3x2
  S21Matrix matrix2(3, 2);
  EXPECT_EQ(matrix2.get_rows(), 3);

  // Тест с матрицей 5x5
  S21Matrix matrix3(5, 5);
  EXPECT_EQ(matrix3.get_rows(), 5);

  // Тест с матрицей 1x10
  S21Matrix matrix4(1, 10);
  EXPECT_EQ(matrix4.get_rows(), 1);

  // Тест с матрицей 10x1
  S21Matrix matrix5(10, 1);
  EXPECT_EQ(matrix5.get_rows(), 10);
}

TEST(S21MatrixTest, GetCols) {
  // Тест с матрицей 2x3
  S21Matrix matrix1(2, 3);
  EXPECT_EQ(matrix1.get_cols(), 3);

  // Тест с матрицей 3x2
  S21Matrix matrix2(3, 2);
  EXPECT_EQ(matrix2.get_cols(), 2);

  // Тест с квадратной матрицей 5x5
  S21Matrix matrix3(5, 5);
  EXPECT_EQ(matrix3.get_cols(), 5);

  // Тест с матрицей 1x10
  S21Matrix matrix4(1, 10);
  EXPECT_EQ(matrix4.get_cols(), 10);

  // Тест с матрицей 10x1
  S21Matrix matrix5(10, 1);
  EXPECT_EQ(matrix5.get_cols(), 1);
}

TEST(S21MatrixTest, GetElementMatrix_ValidIndex) {
  S21Matrix matrix(3, 3);
  matrix.set_element_matrix_(1, 1, 5.5);
  EXPECT_DOUBLE_EQ(matrix.get_element_matrix_(1, 1), 5.5);
}

TEST(S21MatrixTest, GetElementMatrix_RowIndexOutOfBounds) {
  S21Matrix matrix(3, 3);
  EXPECT_THROW(matrix.get_element_matrix_(3, 1), std::runtime_error);
}

TEST(S21MatrixTest, GetElementMatrix_ColIndexOutOfBounds) {
  S21Matrix matrix(3, 3);
  EXPECT_THROW(matrix.get_element_matrix_(1, 3), std::runtime_error);
}

TEST(S21MatrixTest, GetElementMatrix_NegativeIndex) {
  S21Matrix matrix(3, 3);
  EXPECT_THROW(matrix.get_element_matrix_(-1, 1), std::runtime_error);
  EXPECT_THROW(matrix.get_element_matrix_(1, -1), std::runtime_error);
}

TEST(S21MatrixTest, GetElementMatrix_MultipleValidIndices) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1.1);
  matrix.set_element_matrix_(0, 1, 1.2);
  matrix.set_element_matrix_(1, 0, 2.1);
  matrix.set_element_matrix_(1, 1, 2.2);

  EXPECT_DOUBLE_EQ(matrix.get_element_matrix_(0, 0), 1.1);
  EXPECT_DOUBLE_EQ(matrix.get_element_matrix_(0, 1), 1.2);
  EXPECT_DOUBLE_EQ(matrix.get_element_matrix_(1, 0), 2.1);
  EXPECT_DOUBLE_EQ(matrix.get_element_matrix_(1, 1), 2.2);
}

TEST(S21MatrixTest, SetRows_DecreaseRows) {
  S21Matrix matrix(3, 2);
  matrix.set_element_matrix_(0, 0, 1.0);
  matrix.set_element_matrix_(0, 1, 2.0);
  matrix.set_element_matrix_(1, 0, 3.0);
  matrix.set_element_matrix_(1, 1, 4.0);
  matrix.set_element_matrix_(2, 0, 5.0);
  matrix.set_element_matrix_(2, 1, 6.0);

  matrix.set_rows(2);
  EXPECT_EQ(matrix.get_rows(), 2);
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), 1.0);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), 2.0);
}

TEST(S21MatrixTest, SetRows_IncreaseRows) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1.0);
  matrix.set_element_matrix_(0, 1, 2.0);
  matrix.set_element_matrix_(1, 0, 3.0);
  matrix.set_element_matrix_(1, 1, 4.0);

  matrix.set_rows(3);
  EXPECT_EQ(matrix.get_rows(), 3);
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), 1.0);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), 2.0);
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), 3.0);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), 4.0);
  EXPECT_EQ(matrix.get_element_matrix_(2, 0),
            0.0);  // Проверка, что новые строки инициализированы нулями
}

TEST(S21MatrixTest, SetRows_NegativeRows) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.set_rows(-1), std::runtime_error);
}

TEST(S21MatrixTest, SetRows_ZeroRows) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.set_rows(0), std::runtime_error);
}

TEST(S21MatrixTest, SetRows_SameRows) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1.0);
  matrix.set_element_matrix_(0, 1, 2.0);
  matrix.set_element_matrix_(1, 0, 3.0);
  matrix.set_element_matrix_(1, 1, 4.0);

  matrix.set_rows(2);  // Текущее количество строк
  EXPECT_EQ(matrix.get_rows(), 2);
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), 1.0);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), 2.0);
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), 3.0);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), 4.0);
}

TEST(S21MatrixTest, SetCols_DecreaseCols) {
  S21Matrix matrix(2, 3);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(0, 2, 3);
  matrix.set_element_matrix_(1, 0, 4);
  matrix.set_element_matrix_(1, 1, 5);
  matrix.set_element_matrix_(1, 2, 6);

  matrix.set_cols(2);
  EXPECT_EQ(matrix.get_cols(), 2);
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), 1);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), 2);
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), 4);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), 5);
}

TEST(S21MatrixTest, SetCols_IncreaseCols) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(1, 0, 3);
  matrix.set_element_matrix_(1, 1, 4);

  matrix.set_cols(3);
  EXPECT_EQ(matrix.get_cols(), 3);
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), 1);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), 2);
  EXPECT_EQ(matrix.get_element_matrix_(0, 2),
            0);  // Новые столбцы инициализируются нулями
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), 3);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), 4);
  EXPECT_EQ(matrix.get_element_matrix_(1, 2), 0);
}

TEST(S21MatrixTest, SetCols_NegativeCols) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.set_cols(-1), std::runtime_error);
}

TEST(S21MatrixTest, SetCols_ZeroCols) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.set_cols(0), std::runtime_error);
}

TEST(S21MatrixTest, SetCols_SameCols) {
  S21Matrix matrix(2, 2);
  matrix.set_element_matrix_(0, 0, 1);
  matrix.set_element_matrix_(0, 1, 2);
  matrix.set_element_matrix_(1, 0, 3);
  matrix.set_element_matrix_(1, 1, 4);

  matrix.set_cols(2);  // Текущее количество столбцов
  EXPECT_EQ(matrix.get_cols(), 2);
  EXPECT_EQ(matrix.get_element_matrix_(0, 0), 1);
  EXPECT_EQ(matrix.get_element_matrix_(0, 1), 2);
  EXPECT_EQ(matrix.get_element_matrix_(1, 0), 3);
  EXPECT_EQ(matrix.get_element_matrix_(1, 1), 4);
}

TEST(S21MatrixTest, SetElementMatrix_ValidIndices) {
  S21Matrix matrix(2, 2);
  EXPECT_NO_THROW(matrix.set_element_matrix_(1, 1, 5.5));
  EXPECT_DOUBLE_EQ(matrix.get_element_matrix_(1, 1), 5.5);
}

TEST(S21MatrixTest, SetElementMatrix_RowIndexOutOfBounds) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.set_element_matrix_(2, 1, 10.0), std::runtime_error);
}

TEST(S21MatrixTest, SetElementMatrix_ColIndexOutOfBounds) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.set_element_matrix_(0, 2, 10.0), std::runtime_error);
}

TEST(S21MatrixTest, OperatorCall_ValidIndices) {
  S21Matrix matrix(3, 3);
  matrix.set_element_matrix_(1, 1, 5.5);
  double value = matrix(1, 1);
  EXPECT_DOUBLE_EQ(value, 5.5);
}

TEST(S21MatrixTest, OperatorCall_RowIndexOutOfBounds) {
  S21Matrix matrix(3, 3);
  EXPECT_THROW(matrix(3, 1), std::runtime_error);
}

TEST(S21MatrixTest, OperatorCall_ColIndexOutOfBounds) {
  S21Matrix matrix(3, 3);
  EXPECT_THROW(matrix(1, 3), std::runtime_error);
}
