#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <cmath>
#include <exception>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void s21_create_matrix(int rows, int cols);
  void s21_copy_matrix(const S21Matrix& other);
  void s21_remove_matrix();
  int s21_switch_rows(int row_1);
  double s21_triangle_determinant(double mul);
  void s21_decrease_matrix(int row, int column);

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();
  void show();
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  void operator=(const S21Matrix& other);
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  friend S21Matrix operator*(double num, const S21Matrix& other);
  friend S21Matrix operator*(const S21Matrix& other, double num);
};

S21Matrix operator*(double num, const S21Matrix& other);
S21Matrix operator*(const S21Matrix& other, double num);

#endif  // S21_MATRIX_OOP_H_