#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <cmath>
#include <exception>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void CreateMatrix(int rows, int cols);
  void CopyMatrix(const S21Matrix& other);
  void RemoveMatrix();
  int SwithRows(int row_1);
  double TriangleDeterminant(double mul);
  S21Matrix DecreaseMatrix(int row, int column);

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
  void operator*=(double num);
  double& operator()(int i, int j);

  friend S21Matrix operator*(double num, const S21Matrix& other);
  friend S21Matrix operator*(const S21Matrix& other, double num);

  double GetRows();
  double GetColumns();
  double** GetMatrix();
  void SetRows(int rows);
  void SetColumns(int columns);
};

S21Matrix operator*(double num, const S21Matrix& other);
S21Matrix operator*(const S21Matrix& other, double num);

#endif  // S21_MATRIX_OOP_H_