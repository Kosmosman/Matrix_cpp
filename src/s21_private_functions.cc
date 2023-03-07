#include "s21_matrix_oop.h"

void S21Matrix::s21_create_matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0)
    throw std::length_error(
        "Count of rows and columns can't be equal or less than 0");
  matrix_ = new double* [rows] { 0 };
  if (!matrix_) throw std::bad_alloc();
  matrix_[0] = new double[rows * cols]{0};
  if (!matrix_[0]) {
    delete matrix_;
    throw std::bad_alloc();
  }
  for (int i = 1; i < rows; ++i) {
    matrix_[i] = matrix_[0] + i * cols;
  }
}

void S21Matrix::s21_copy_matrix(const S21Matrix& other) {
  this->s21_create_matrix(other.rows_, other.cols_);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

/// @brief Очистка матрицы и зануление всех элементов объекта
void S21Matrix::s21_remove_matrix() {
  if (matrix_) {
    delete[] matrix_[0];
    matrix_[0] = nullptr;
  }
  delete[] matrix_;
  matrix_ = nullptr;
  rows_ = cols_ = 0;
}

void S21Matrix::show() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}