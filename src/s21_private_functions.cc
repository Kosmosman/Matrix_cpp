#include "s21_matrix_oop.h"

/// @brief Создание матрицы
void S21Matrix::CreateMatrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0)
    throw std::length_error(
        "Count of rows and columns can't be equal or less than 0");
  this->rows_ = rows;
  this->cols_ = cols;
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

/// @brief Копирование матрицы
void S21Matrix::CopyMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    this->RemoveMatrix();
    this->CreateMatrix(other.rows_, other.cols_);
  }
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

/// @brief Очистка матрицы и зануление всех элементов объекта
void S21Matrix::RemoveMatrix() {
  if (matrix_) {
    delete[] matrix_[0];
    matrix_[0] = nullptr;
  }
  delete[] matrix_;
  matrix_ = nullptr;
  rows_ = cols_ = 0;
}

/// @brief Проверяет строку на наличие в ней 0 в i-м столбце.
/// В положительном случае, находит первую строку с ненулевым элементом. При
/// ненахождении таковой, возвращает 0.
int S21Matrix::SwithRows(int row_1) {
  int tmp = 0, res = 0, row_2 = 0;
  if (this->matrix_[row_1][row_1] == 0) {
    for (int count = row_1 + 1; !res && count < this->rows_; count++) {
      if (this->matrix_[count][row_1] != 0) {
        row_2 = count;
        res = 2;
      }
    }
    if (res) {
      for (int i = 0; i < this->cols_; i++) {
        tmp = this->matrix_[row_1][i];
        this->matrix_[row_1][i] = this->matrix_[row_2][i];
        this->matrix_[row_2][i] = tmp;
      }
    }
  } else {
    res = 1;
  }
  return res;
}

/// @brief Нахождение детерминанта путем перемножения членов треугольной
/// матрицы, находящихся на главной диагонали.
double S21Matrix::TriangleDeterminant(double mul) {
  double res = 1;
  for (int i = 0; i < this->rows_; i++) {
    res *= this->matrix_[i][i];
  }
  return res / mul;
}

/// @brief Заполнение матрицы с вычеркнутыми строкой и столбцом.
S21Matrix S21Matrix::DecreaseMatrix(int row, int column) {
  int i_result = 0, j_result = 0;
  S21Matrix tmp(this->rows_ - 1, this->cols_ - 1);
  for (int i = 0; i < this->rows_; i++)
    if (i != row) {
      for (int j = 0; j < this->cols_; j++) {
        if (j != column) {
          tmp.matrix_[i_result][j_result++] = this->matrix_[i][j];
        }
      }
      j_result = 0;
      i_result++;
    }
  return tmp;
}