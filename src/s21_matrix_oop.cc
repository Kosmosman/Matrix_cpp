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

S21Matrix::S21Matrix(const S21Matrix &other) {
  this->s21_create_matrix(other.rows_, other.cols_);
  this->s21_copy_matrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  this->s21_create_matrix(other.rows_, other.cols_);
  this->s21_copy_matrix(other);
  other.s21_remove_matrix();
}

S21Matrix::~S21Matrix() { s21_remove_matrix(); }

/// @brief Сравнение двух матриц
bool S21Matrix::EqMatrix(const S21Matrix &other) {
  int result = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    result = false;
  } else {
    for (int i = 0; i < this->rows_ && result; i++) {
      for (int j = 0; j < this->cols_ && result; j++) {
        if (round(this->matrix_[i][j] * pow(10, 7)) !=
            round(other.matrix_[i][j] * pow(10, 7)))
          result = false;
      }
    }
  }
  return result;
}

/// @brief Сумма двух матриц.
void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::invalid_argument("Both matrix must be a same size!");
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

/// @brief Разница двух матриц.
void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::invalid_argument("Both matrix must be a same size!");
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

/// @brief Произведение матрицы на число.
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
}

/// @brief Умножение матриц.
void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->cols_ != other.rows_)
    throw std::length_error(
        "Count of rows second matrix must be equal count of columns first "
        "matrix!");
  ;
  S21Matrix tmp(other.rows_, this->cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < this->cols_; k++) {
        tmp.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  this->s21_copy_matrix(tmp);
}

/// @brief Транспонирование матрицы.
S21Matrix S21Matrix::Transpose() {
  S21Matrix tmp(*this);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      tmp.matrix_[j][i] = this->matrix_[i][j];
    }
  }
  return tmp;
}

/// @brief Вычисление матрицы алгебраических дополнений
S21Matrix S21Matrix::CalcComplements() {
  double minor = 0;
  S21Matrix tmp(*this);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      tmp.s21_decrease_matrix(i, j);
      minor = tmp.Determinant();
      if ((i + j) % 2) minor = -minor;
      tmp.matrix_[i][j] = minor;
      minor = 0;
    }
  }
  return tmp;
}

/// @brief Вычисление детерминанта матрицы (метод Гауса)
double S21Matrix::Determinant() {
  int state = 0, flag = 0, num = 0, zero = 0;
  double num_const = 0, mul = 1, res = 0;
  S21Matrix tmp(*this);
  if (tmp.cols_ != tmp.rows_) throw std::length_error("Matrix must be square!");
  if (tmp.cols_ > 1) {
    for (int i = 0; i < tmp.rows_ && !zero; i++) {
      if ((num = tmp.s21_switch_rows(i))) {
        if (num == 2) mul *= -1;
        for (int j = i; j < tmp.rows_ - 1; j++) {
          if (!state && tmp.matrix_[j][i]) {
            state = j;
            flag = 1;
          }
          if (flag && tmp.matrix_[j + 1][i] != 0) {
            mul *= tmp.matrix_[state][i];
            num_const = tmp.matrix_[j + 1][i];
            for (int k = i; k < tmp.cols_; k++) {
              tmp.matrix_[j + 1][k] =
                  tmp.matrix_[j + 1][k] * tmp.matrix_[state][i] -
                  tmp.matrix_[state][k] * num_const;
            }
          }
        }
        flag = state = 0;
      } else {
        zero = 1;
      }
    }
  } else {
    res = tmp.matrix_[0][0];
  }
  if (!zero) res = tmp.s21_triangle_determinant(mul);
  return res;
}

/// @brief Инверсия матрицы, принимаются только квадратные
S21Matrix S21Matrix::InverseMatrix() {
  if (this->rows_ != this->cols_)
    throw std::length_error("Matrix must be square!");
  S21Matrix tmp(*this);
  double determinant = tmp.Determinant();
  if (fabs(determinant) > 1e-6) {
    if (tmp.rows_ == 1) {
      S21Matrix result(1, 1);
      result.matrix_[0][0] = 1.0 / tmp.matrix_[0][0];
    } else {
      tmp = tmp.CalcComplements();
      tmp = tmp.Transpose();
      tmp.MulNumber(1.0 / determinant);
    }
  } else {
    throw std::domain_error("Determinant is equal 0!");
  }
  return tmp;
}