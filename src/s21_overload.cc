#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::invalid_argument("Both matrix must be a same size!");
  S21Matrix tmp(*this);
  tmp.SumMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::invalid_argument("Both matrix must be a same size!");
  S21Matrix tmp(*this);
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

// Если матрицы разного размера?
void S21Matrix::operator=(const S21Matrix& other) { this->CopyMatrix(other); }

void S21Matrix::operator+=(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::invalid_argument("Both matrix must be a same size!");
  this->SumMatrix(other);
}

void S21Matrix::operator-=(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::invalid_argument("Both matrix must be a same size!");
  this->SubMatrix(other);
}

void S21Matrix::operator*=(const S21Matrix& other) { this->MulMatrix(other); }

void S21Matrix::operator*=(double num) { this->MulNumber(num); }

S21Matrix operator*(double num, const S21Matrix& other) {
  S21Matrix tmp(other);
  tmp.MulNumber(num);
  return tmp;
}

S21Matrix operator*(const S21Matrix& other, double num) {
  S21Matrix tmp(other);
  tmp.MulNumber(num);
  return tmp;
}

double& S21Matrix::operator()(int i, int j) {
  if (rows_ < i || cols_ < j || i < 0 || j < 0)
    throw std::invalid_argument("Incorrect indexes!");
  if (rows_ < 1 || cols_ < 1)
    throw std::length_error("Incorrect number of columns or rows!");
  return matrix_[i][j];
}