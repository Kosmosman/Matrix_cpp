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
void S21Matrix::operator=(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::invalid_argument("Both matrix must be a same size!");
  this->s21_copy_matrix(other);
}

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