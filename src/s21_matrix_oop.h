#ifndef CPP1_S21_MATRIXPLUS_3_SRC_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_3_SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <exception>
#include <iostream>

constexpr double EPS = 1e-7;

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix() noexcept;

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
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num);
  double& operator()(int i, int j);
  double operator()(int i, int j) const;

  friend S21Matrix operator*(double num, const S21Matrix& other);
  friend S21Matrix operator*(const S21Matrix& other, double num);

  int GetRows() const;
  int GetColumns() const;
  double** GetMatrix() const;
  void SetRows(int rows);
  void SetColumns(int columns);

 private:
  int rows_, cols_;
  double** matrix_;
  void CreateMatrix();
  void Allocator();
  void CopyMatrix(const S21Matrix& other);
  void RemoveMatrix();
  int SwitchRows(int row_1);
  double TriangleDeterminant(double mul);
  S21Matrix DecreaseMatrix(int row, int column);
  void ReplaceMatrix(S21Matrix&& other);
};

S21Matrix operator*(double num, const S21Matrix& other);
S21Matrix operator*(const S21Matrix& other, double num);

#endif  // CPP1_S21_MATRIXPLUS_3_SRC_S21_MATRIX_OOP_H_