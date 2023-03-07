#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = cols_ = 0;
  matrix_ = nullptr;
};

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  s21_create_matrix(rows, cols);
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  std::cout << "Bro\n";
  this->s21_copy_matrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  this->s21_copy_matrix(other);
  other.s21_remove_matrix();
}

S21Matrix::~S21Matrix() { s21_remove_matrix(); }