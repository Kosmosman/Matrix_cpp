#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(MatrixTest, DefaultConstructor) {
  S21Matrix one;

  EXPECT_EQ(one.GetRows(), 0);
  EXPECT_EQ(one.GetColumns(), 0);
  EXPECT_EQ(one.GetMatrix(), nullptr);
}

TEST(MatrixTest, ConstructorRowCols) {
  S21Matrix one(10, 20);

  EXPECT_EQ(one.GetRows(), 10);
  EXPECT_EQ(one.GetColumns(), 20);
}

TEST(MatrixTest, ConstructorCopy) {
  S21Matrix one(10, 20);
  S21Matrix two(one);

  EXPECT_EQ(two.GetRows(), 10);
  EXPECT_EQ(two.GetColumns(), 20);
  EXPECT_EQ(one == two, true);
}

TEST(MatrixTest, ConstructorMove) {
  S21Matrix one(10, 20);
  S21Matrix two(std::move(one));

  EXPECT_EQ(two.GetRows(), 10);
  EXPECT_EQ(two.GetColumns(), 20);
  EXPECT_EQ(one.GetMatrix(), nullptr);
}

TEST(MatrixTest, MatrixEqCorrect) {
  S21Matrix one(5, 5);
  S21Matrix two(5, 5);

  one(0, 0) = 1;
  one(0, 1) = 5;
  one(3, 4) = 2;

  two(0, 0) = 1;
  two(0, 1) = 5;
  two(3, 4) = 2;

  EXPECT_EQ(one == two, true);
}

TEST(MatrixTest, MatrixEqIncorrect1) {
  S21Matrix one(5, 5);
  S21Matrix two(5, 5);

  one(0, 0) = 1;
  one(0, 1) = 5;
  one(3, 4) = 2;

  two(0, 0) = 2;
  two(0, 1) = 5;
  two(3, 4) = 2;

  EXPECT_EQ(one == two, false);
}

TEST(MatrixTest, MatrixEqIncorrect2) {
  S21Matrix one(5, 5);
  S21Matrix two(6, 10);

  one(0, 0) = 1;
  one(0, 1) = 5;
  one(3, 4) = 2;

  two(0, 0) = 1;
  two(0, 1) = 5;
  two(3, 4) = 2;

  EXPECT_EQ(one == two, false);
}

TEST(MatrixTest, MatrixSumCorrect) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 3);
  S21Matrix result(3, 3);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;
  one(2, 0) = 7;
  one(2, 1) = 8;
  one(2, 2) = 9;

  two(0, 0) = 9;
  two(0, 1) = 8;
  two(0, 2) = 7;
  two(1, 0) = 6;
  two(1, 1) = 5;
  two(1, 2) = 4;
  two(2, 0) = 3;
  two(2, 1) = 2;
  two(2, 2) = 1;

  two.SumMatrix(one);

  result(0, 0) = 10;
  result(0, 1) = 10;
  result(0, 2) = 10;
  result(1, 0) = 10;
  result(1, 1) = 10;
  result(1, 2) = 10;
  result(2, 0) = 10;
  result(2, 1) = 10;
  result(2, 2) = 10;

  EXPECT_EQ(two == result, true);
}

TEST(MatrixTest, MatrixSumIncorrectSize) {
  S21Matrix one(3, 3);
  S21Matrix two(4, 3);
  EXPECT_THROW(two.SumMatrix(one), std::length_error);
}

TEST(MatrixTest, MatrixSubCorrect) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 3);
  S21Matrix result(3, 3);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;
  one(2, 0) = 7;
  one(2, 1) = 8;
  one(2, 2) = 9;

  two(0, 0) = 9;
  two(0, 1) = 8;
  two(0, 2) = 7;
  two(1, 0) = 6;
  two(1, 1) = 5;
  two(1, 2) = 4;
  two(2, 0) = 3;
  two(2, 1) = 2;
  two(2, 2) = 1;

  two.SubMatrix(one);

  result(0, 0) = 8;
  result(0, 1) = 6;
  result(0, 2) = 4;
  result(1, 0) = 2;
  result(1, 1) = 0;
  result(1, 2) = -2;
  result(2, 0) = -4;
  result(2, 1) = -6;
  result(2, 2) = -8;

  EXPECT_EQ(two == result, true);
}

TEST(MatrixTest, MatrixSubIncorrectSize) {
  S21Matrix one(3, 2);
  S21Matrix two(5, 3);
  EXPECT_THROW(two.SubMatrix(one), std::length_error);
}

TEST(MatrixTest, MatrixMulNumber) {
  S21Matrix one(2, 2);
  S21Matrix result(2, 2);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(1, 0) = 3;
  one(1, 1) = 4;

  result(0, 0) = 3;
  result(0, 1) = 6;
  result(1, 0) = 9;
  result(1, 1) = 12;

  one.MulNumber(3);
  EXPECT_EQ(one == result, true);
}

TEST(MatrixTest, MatrixMulCorrect) {
  S21Matrix one(2, 3);
  S21Matrix two(3, 2);
  S21Matrix result(2, 2);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;

  two(0, 0) = 1;
  two(0, 1) = 2;
  two(1, 0) = 3;
  two(1, 1) = 4;
  two(2, 0) = 5;
  two(2, 1) = 6;

  result(0, 0) = 22;
  result(0, 1) = 28;
  result(1, 0) = 49;
  result(1, 1) = 64;

  one.MulMatrix(two);
  EXPECT_EQ(one == result, true);
}

TEST(MatrixTest, MatrixMulIncorrectSize) {
  S21Matrix one(5, 5);
  S21Matrix two(6, 5);
  EXPECT_THROW(one.MulMatrix(two), std::length_error);
}

TEST(MatrixTest, MatrixTranspose) {
  S21Matrix one(5, 5);
  S21Matrix two;
  S21Matrix result(5, 5);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;
  one(2, 0) = 7;
  one(2, 1) = 8;
  one(2, 2) = 9;

  result(0, 0) = 1;
  result(0, 1) = 4;
  result(0, 2) = 7;
  result(1, 0) = 2;
  result(1, 1) = 5;
  result(1, 2) = 8;
  result(2, 0) = 3;
  result(2, 1) = 6;
  result(2, 2) = 9;

  two = one.Transpose();
  EXPECT_EQ(two == result, true);
}

TEST(MatrixTest, MatrixComplementCorrect) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 3);
  S21Matrix result(3, 3);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 0;
  one(1, 1) = 4;
  one(1, 2) = 2;
  one(2, 0) = 5;
  one(2, 1) = 2;
  one(2, 2) = 1;

  result(0, 0) = 0;
  result(0, 1) = 10;
  result(0, 2) = -20;
  result(1, 0) = 4;
  result(1, 1) = -14;
  result(1, 2) = 8;
  result(2, 0) = -8;
  result(2, 1) = -2;
  result(2, 2) = 4;

  two = one.CalcComplements();
  EXPECT_EQ(two == result, true);
}

TEST(MatrixTest, MatrixComplementIncorrect) {
  S21Matrix one(3, 4);
  EXPECT_THROW(one.CalcComplements(), std::length_error);
}

TEST(MatrixTest, MatrixDeterminantCorrect) {
  S21Matrix one(4, 4);
  one(0, 0) = 8;
  one(0, 1) = 9;
  one(0, 2) = 2;
  one(0, 3) = 4;
  one(1, 0) = 0;
  one(1, 1) = 9;
  one(1, 2) = 8;
  one(1, 3) = 7;
  one(2, 0) = 5;
  one(2, 1) = 9;
  one(2, 2) = 6;
  one(2, 3) = 5;
  one(3, 0) = 4;
  one(3, 1) = 6;
  one(3, 2) = 7;
  one(3, 3) = 8;

  double det = one.Determinant();
  EXPECT_DOUBLE_EQ(651, det);
}

TEST(MatrixTest, MatrixDeterminantCorrect2) {
  S21Matrix one(1, 1);
  one(0, 0) = 8;

  double det = one.Determinant();
  EXPECT_DOUBLE_EQ(8, det);
}

TEST(MatrixTest, MatrixInverseCorrect) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 3);
  S21Matrix result(3, 3);

  one(0, 0) = 2;
  one(0, 1) = 5;
  one(0, 2) = 7;
  one(1, 0) = 6;
  one(1, 1) = 3;
  one(1, 2) = 4;
  one(2, 0) = 5;
  one(2, 1) = -2;
  one(2, 2) = -3;

  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;
  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;
  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;

  two = one.InverseMatrix();
  EXPECT_EQ(two == result, true);
}

TEST(MatrixTest, MatrixInverseCorrect2) {
  S21Matrix one(1, 1);
  S21Matrix two(1, 1);
  S21Matrix result(1, 1);

  one(0, 0) = 2;

  result(0, 0) = 0.5;
  two = one.InverseMatrix();
  std::cout << "result = " << two(0, 0);
  EXPECT_EQ(two == result, true);
}

TEST(MatrixTest, MatrixInverseIncorrect) {
  S21Matrix one(3, 3);
  EXPECT_THROW(one.InverseMatrix(), std::domain_error);
}

TEST(MatrixTest, MatrixInverseIncorrectSize) {
  S21Matrix one(3, 4);
  EXPECT_THROW(one.InverseMatrix(), std::length_error);
}

TEST(MatrixTest, MatrixOperatorPlus) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 3);
  S21Matrix three(3, 3);
  S21Matrix result(3, 3);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;
  one(2, 0) = 7;
  one(2, 1) = 8;
  one(2, 2) = 9;

  two(0, 0) = 9;
  two(0, 1) = 8;
  two(0, 2) = 7;
  two(1, 0) = 6;
  two(1, 1) = 5;
  two(1, 2) = 4;
  two(2, 0) = 3;
  two(2, 1) = 2;
  two(2, 2) = 1;

  three = one + two;

  result(0, 0) = 10;
  result(0, 1) = 10;
  result(0, 2) = 10;
  result(1, 0) = 10;
  result(1, 1) = 10;
  result(1, 2) = 10;
  result(2, 0) = 10;
  result(2, 1) = 10;
  result(2, 2) = 10;

  EXPECT_EQ(three == result, true);
}

TEST(MatrixTest, MatrixOperatorPlusIncorrect) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 4);
  EXPECT_THROW(one + two, std::invalid_argument);
}

TEST(MatrixTest, MatrixOperatorMinus) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 3);
  S21Matrix three(3, 3);
  S21Matrix result(3, 3);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;
  one(2, 0) = 7;
  one(2, 1) = 8;
  one(2, 2) = 9;

  two(0, 0) = 9;
  two(0, 1) = 8;
  two(0, 2) = 7;
  two(1, 0) = 6;
  two(1, 1) = 5;
  two(1, 2) = 4;
  two(2, 0) = 3;
  two(2, 1) = 2;
  two(2, 2) = 1;

  three = two - one;
  result(0, 0) = 8;
  result(0, 1) = 6;
  result(0, 2) = 4;
  result(1, 0) = 2;
  result(1, 1) = 0;
  result(1, 2) = -2;
  result(2, 0) = -4;
  result(2, 1) = -6;
  result(2, 2) = -8;

  EXPECT_EQ(three == result, true);
}

TEST(MatrixTest, MatrixOperatorMinusIncorrect) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 4);
  EXPECT_THROW(one - two, std::invalid_argument);
}

TEST(MatrixTest, MatrixOperatorMulNum) {
  S21Matrix one(2, 2);
  S21Matrix two(2, 2);
  S21Matrix three(2, 2);
  S21Matrix result(2, 2);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(1, 0) = 3;
  one(1, 1) = 4;

  result(0, 0) = 3;
  result(0, 1) = 6;
  result(1, 0) = 9;
  result(1, 1) = 12;

  two = one * 3;
  three = 3 * one;
  EXPECT_EQ(two == result, true);
  EXPECT_EQ(three == result, true);
}

TEST(MatrixTest, MatrixOperatorMulMatrix) {
  S21Matrix one(2, 3);
  S21Matrix two(3, 2);
  S21Matrix three(2, 2);
  S21Matrix result(2, 2);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;

  two(0, 0) = 1;
  two(0, 1) = 2;
  two(1, 0) = 3;
  two(1, 1) = 4;
  two(2, 0) = 5;
  two(2, 1) = 6;

  result(0, 0) = 22;
  result(0, 1) = 28;
  result(1, 0) = 49;
  result(1, 1) = 64;

  three = one * two;
  EXPECT_EQ(three == result, true);
}

TEST(MatrixTest, MatrixOperatorMulNumIncorrect) {
  S21Matrix one(3, 3);
  S21Matrix two(4, 3);
  EXPECT_THROW(one * two, std::length_error);
}

TEST(MatrixTest, MatrixOperatorEq) {
  S21Matrix one(5, 5);
  S21Matrix two(5, 5);

  one(0, 0) = 1;
  one(0, 1) = 5;
  one(3, 4) = 2;

  two(0, 0) = 1;
  two(0, 1) = 5;
  two(3, 4) = 2;

  bool result = one == two;

  EXPECT_EQ(result, true);
}

TEST(MatrixTest, MatrixOperatorAssig) {
  S21Matrix one(3, 3);
  S21Matrix two;

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;
  one(2, 0) = 7;
  one(2, 1) = 8;
  one(2, 2) = 9;

  two = one;

  EXPECT_EQ(one == two, true);
}

TEST(MatrixTest, MatrixOperatorSum) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 3);
  S21Matrix result(3, 3);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;
  one(2, 0) = 7;
  one(2, 1) = 8;
  one(2, 2) = 9;

  two(0, 0) = 9;
  two(0, 1) = 8;
  two(0, 2) = 7;
  two(1, 0) = 6;
  two(1, 1) = 5;
  two(1, 2) = 4;
  two(2, 0) = 3;
  two(2, 1) = 2;
  two(2, 2) = 1;

  two += one;

  result(0, 0) = 10;
  result(0, 1) = 10;
  result(0, 2) = 10;
  result(1, 0) = 10;
  result(1, 1) = 10;
  result(1, 2) = 10;
  result(2, 0) = 10;
  result(2, 1) = 10;
  result(2, 2) = 10;

  EXPECT_EQ(two == result, true);
}

TEST(MatrixTest, MatrixOperatorSumIncorrect) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 4);
  EXPECT_THROW(one += two, std::invalid_argument);
}

TEST(MatrixTest, MatrixOperatorSub) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 3);
  S21Matrix result(3, 3);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;
  one(2, 0) = 7;
  one(2, 1) = 8;
  one(2, 2) = 9;

  two(0, 0) = 9;
  two(0, 1) = 8;
  two(0, 2) = 7;
  two(1, 0) = 6;
  two(1, 1) = 5;
  two(1, 2) = 4;
  two(2, 0) = 3;
  two(2, 1) = 2;
  two(2, 2) = 1;

  two -= one;

  result(0, 0) = 8;
  result(0, 1) = 6;
  result(0, 2) = 4;
  result(1, 0) = 2;
  result(1, 1) = 0;
  result(1, 2) = -2;
  result(2, 0) = -4;
  result(2, 1) = -6;
  result(2, 2) = -8;

  EXPECT_EQ(two == result, true);
}

TEST(MatrixTest, MatrixOperatorSubIncorrect) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 4);
  EXPECT_THROW(one -= two, std::invalid_argument);
}

TEST(MatrixTest, MatrixOperatorEqMulNum) {
  S21Matrix one(2, 2);
  S21Matrix result(2, 2);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(1, 0) = 3;
  one(1, 1) = 4;

  result(0, 0) = 3;
  result(0, 1) = 6;
  result(1, 0) = 9;
  result(1, 1) = 12;

  one *= 3;
  EXPECT_EQ(one == result, true);
}

TEST(MatrixTest, MatrixOperatorEqMulMatrix) {
  S21Matrix one(2, 3);
  S21Matrix two(3, 2);
  S21Matrix three(2, 2);
  S21Matrix result(2, 2);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;

  two(0, 0) = 1;
  two(0, 1) = 2;
  two(1, 0) = 3;
  two(1, 1) = 4;
  two(2, 0) = 5;
  two(2, 1) = 6;

  result(0, 0) = 22;
  result(0, 1) = 28;
  result(1, 0) = 49;
  result(1, 1) = 64;

  one *= two;
  EXPECT_EQ(one == result, true);
}

TEST(MatrixTest, MatrixOperatorEqMulMatrixIncorrect) {
  S21Matrix one(3, 3);
  S21Matrix two(4, 3);
  EXPECT_THROW(one *= two, std::length_error);
}

TEST(MatrixTest, MatrixIndex) {
  S21Matrix one(2, 2);

  one(0, 0) = 1;
  double result = one(0, 0);
  EXPECT_EQ(result, 1);
}

TEST(MatrixTest, MatrixIndexIncorrect) {
  S21Matrix one(2, 2);
  EXPECT_THROW(one(4, 4), std::invalid_argument);
}

TEST(MatrixTest, MatrixGetRow) {
  S21Matrix one(2, 3);
  EXPECT_EQ(one.GetRows(), 2);
}

TEST(MatrixTest, MatrixGetColumns) {
  S21Matrix one(2, 3);
  EXPECT_EQ(one.GetColumns(), 3);
}

TEST(MatrixTest, MatrixSetRowUp) {
  S21Matrix one(2, 3);
  S21Matrix res(3, 3);

  one(0, 0) = 1;
  one(1, 0) = 2;

  res(0, 0) = 1;
  res(1, 0) = 2;

  one.SetRows(3);

  EXPECT_EQ(res == one, true);
}

TEST(MatrixTest, MatrixSetRowDown) {
  S21Matrix one(3, 3);
  S21Matrix res(2, 3);

  one(0, 0) = 1;
  one(1, 0) = 2;
  one(2, 0) = 3;

  res(0, 0) = 1;
  res(1, 0) = 2;

  one.SetRows(2);

  EXPECT_EQ(res == one, true);
}

TEST(MatrixTest, MatrixSetColumnsUp) {
  S21Matrix one(3, 3);
  S21Matrix res(3, 4);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;

  res(0, 0) = 1;
  res(0, 1) = 2;
  res(0, 2) = 3;

  one.SetColumns(4);

  EXPECT_EQ(res == one, true);
}

TEST(MatrixTest, MatrixSetColumnsDown) {
  S21Matrix one(3, 3);
  S21Matrix res(3, 2);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;

  res(0, 0) = 1;
  res(0, 1) = 2;

  one.SetColumns(2);
  EXPECT_EQ(res == one, true);
}

TEST(MatrixTest, MatrixSetRowsIncorrect) {
  S21Matrix one(3, 3);
  EXPECT_THROW(one.SetRows(-1), std::invalid_argument);
}

TEST(MatrixTest, MatrixSetColumnsIncorrect) {
  S21Matrix one(3, 3);
  EXPECT_THROW(one.SetColumns(-2), std::invalid_argument);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}