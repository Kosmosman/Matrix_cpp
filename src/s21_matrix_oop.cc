#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_{}, cols_{}, matrix_{} {};

S21Matrix::S21Matrix(int rows, int cols) : rows_{rows}, cols_{cols}, matrix_{} {
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other) : S21Matrix() {
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept : S21Matrix() {
  ReplaceMatrix(std::move(other));
}

S21Matrix::~S21Matrix() noexcept { RemoveMatrix(); }

/// @brief Сравнение двух матриц
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) return false;
    }
  }
  return true;
}

/// @brief Сумма двух матриц.
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.GetRows() || cols_ != other.GetColumns())
    throw std::length_error("Both matrix must be a same size!");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other(i, j);
    }
  }
}

/// @brief Разница двух матриц.
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.GetRows() || cols_ != other.GetColumns())
    throw std::length_error("Both matrix must be a same size!");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other(i, j);
    }
  }
}

/// @brief Произведение матрицы на число.
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

/// @brief Умножение матриц.
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::length_error(
        "Count of rows second matrix must be equal count of columns first "
        "matrix!");
  S21Matrix tmp(rows_, other.GetColumns());
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.GetColumns(); j++) {
      for (int k = 0; k < cols_; k++) {
        tmp.matrix_[i][j] += matrix_[i][k] * other(k, j);
      }
    }
  }
  *this = std::move(tmp);
}

/// @brief Транспонирование матрицы.
S21Matrix S21Matrix::Transpose() {
  S21Matrix tmp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return tmp;
}

/// @brief Вычисление матрицы алгебраических дополнений
S21Matrix S21Matrix::CalcComplements() {
  double minor = 0;
  S21Matrix tmp(rows_ - 1, cols_ - 1);
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp = DecreaseMatrix(i, j);
      minor = tmp.Determinant();
      if ((i + j) % 2) minor = -minor;
      result.matrix_[i][j] = minor;
      minor = 0;
    }
  }
  return result;
}

/// @brief Вычисление детерминанта матрицы (метод Гауса)
double S21Matrix::Determinant() {
  int state = 0, flag = 0, num = 0, zero = 0;
  double num_const = 0, mul = 1, res = 0;
  S21Matrix tmp(*this);
  if (tmp.cols_ != tmp.rows_) throw std::length_error("Matrix must be square!");
  if (tmp.cols_ > 1) {
    for (int i = 0; i < tmp.rows_ && !zero; i++) {
      if ((num = tmp.SwitchRows(i))) {
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
  if (!zero) res = tmp.TriangleDeterminant(mul);
  return res;
}

/// @brief Инверсия матрицы, принимаются только квадратные
S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) throw std::length_error("Matrix must be square!");
  S21Matrix tmp(*this);
  double determinant = tmp.Determinant();
  if (fabs(determinant) > EPS) {
    if (tmp.rows_ == 1) {
      tmp.matrix_[0][0] = 1.0 / tmp.matrix_[0][0];
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

/* Accessor and mutator */

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetColumns() const { return cols_; }

double** S21Matrix::GetMatrix() const { return matrix_; }

void S21Matrix::SetRows(int rows) {
  if (rows <= 0)
    throw std::invalid_argument("Count of rows can't be less than 0!");
  if (rows_ != rows) {
    int tmpRow = rows < rows_ ? rows : rows_;
    int tmpCol = cols_ > 0 ? cols_ : rows_;
    S21Matrix tmpMatrix(rows, tmpCol);
    for (int i = 0; i < tmpRow; i++) {
      for (int j = 0; j < tmpCol; j++) {
        tmpMatrix.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = std::move(tmpMatrix);
  }
}

void S21Matrix::SetColumns(int columns) {
  if (columns <= 0)
    throw std::invalid_argument("Count of columns can't be less than 0!");
  if (cols_ != columns) {
    int tmpCol = columns < cols_ ? columns : cols_;
    int tmpRow = rows_ > 0 ? rows_ : cols_;
    S21Matrix tmpMatrix(tmpRow, columns);
    for (int i = 0; i < tmpRow; i++) {
      for (int j = 0; j < tmpCol; j++) {
        tmpMatrix.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = std::move(tmpMatrix);
  }
}

/* Overload operators */

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix tmp(*this);
  tmp.SumMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix tmp(*this);
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  CopyMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    RemoveMatrix();
    ReplaceMatrix(std::move(other));
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

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
  if (rows_ <= i || cols_ <= j || i < 0 || j < 0)
    throw std::invalid_argument("Incorrect indexes!");
  return matrix_[i][j];
}

double S21Matrix::operator()(int i, int j) const {
  if (rows_ <= i || cols_ <= j || i < 0 || j < 0)
    throw std::invalid_argument("Incorrect indexes!");
  return matrix_[i][j];
}

/* Private functions */

/// @brief Создание матрицы
void S21Matrix::CreateMatrix() {
  if (rows_ <= 0 || cols_ <= 0)
    throw std::length_error(
        "Count of rows and columns can't be equal or less than 0");
  Allocator();
}

/// @brief Копирование матрицы
void S21Matrix::CopyMatrix(const S21Matrix& other) {
  if (this != &other) {
    RemoveMatrix();
    rows_ = other.GetRows();
    cols_ = other.GetColumns();
    CreateMatrix();
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other(i, j);
      }
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
int S21Matrix::SwitchRows(int row_1) {
  int res = 0, row_2 = 0;
  double tmp = 0;
  if (matrix_[row_1][row_1] == 0) {
    for (int count = row_1 + 1; !res && count < rows_; count++) {
      if (matrix_[count][row_1] != 0) {
        row_2 = count;
        res = 2;
      }
    }
    if (res) {
      for (int i = 0; i < cols_; i++) {
        tmp = matrix_[row_1][i];
        matrix_[row_1][i] = matrix_[row_2][i];
        matrix_[row_2][i] = tmp;
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
  for (int i = 0; i < rows_; i++) {
    res *= matrix_[i][i];
  }
  return res / mul;
}

/// @brief Заполнение матрицы с вычеркнутыми строкой и столбцом.
S21Matrix S21Matrix::DecreaseMatrix(int row, int column) {
  int i_result = 0, j_result = 0;
  S21Matrix tmp(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++)
    if (i != row) {
      for (int j = 0; j < cols_; j++) {
        if (j != column) {
          tmp.matrix_[i_result][j_result++] = matrix_[i][j];
        }
      }
      j_result = 0;
      i_result++;
    }
  return tmp;
}

/// @brief Замещение матрицы
void S21Matrix::ReplaceMatrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = other.cols_ = 0;
}

/// @brief Метод для выделения памяти
void S21Matrix::Allocator() {
  matrix_ = new double*[rows_]();
  matrix_[0] = new double[rows_ * cols_]();
  for (int i = 1; i < rows_; ++i) {
    matrix_[i] = matrix_[0] + i * cols_;
  }
}