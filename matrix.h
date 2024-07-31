#pragma once
#define MATRIX_SQUARE_MATRIX_IMPLEMENTED
#include <stdexcept>
#include <iostream>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <typename T, size_t Rows, size_t Columns>
class Matrix {
 public:
  T elements[Rows][Columns] = {};
  static T RowsNumber() {
    return Rows;
  }

  static T ColumnsNumber() {
    return Columns;
  }

  T operator()(size_t row, size_t column) const {
    return elements[row][column];
  }

  T& operator()(size_t row, size_t column) {
    return elements[row][column];
  }

  T& At(size_t row, size_t column) {
    if (row >= Rows || column >= Columns) {
      throw MatrixOutOfRange{};
    }
    return elements[row][column];
  }

  T At(size_t row, size_t column) const {
    if (row >= Rows || column >= Columns) {
      throw MatrixOutOfRange{};
    }
    return elements[row][column];
  }

  Matrix operator+(const Matrix& other) const {
    Matrix result = {};
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        result.elements[i][j] = elements[i][j] + other.elements[i][j];
      }
    }
    return result;
  }

  Matrix operator-(const Matrix& other) const {
    Matrix result = {};
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        result.elements[i][j] = elements[i][j] - other.elements[i][j];
      }
    }
    return result;
  }

  Matrix& operator+=(const Matrix& other) {
    Matrix result = *this + other;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        elements[i][j] = result.elements[i][j];
      }
    }
    return *this;
  }

  Matrix& operator-=(const Matrix& other) {
    Matrix result = *this - other;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        elements[i][j] = result.elements[i][j];
      }
    }
    return *this;
  }

  Matrix operator*(const T& other) const {
    Matrix result = {};
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        result.elements[i][j] = elements[i][j] * other;
      }
    }
    return result;
  }

  Matrix& operator*=(const T& other) {
    Matrix result = *this * other;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        elements[i][j] = result.elements[i][j];
      }
    }
    return *this;
  }

  Matrix operator/(const T& other) const {
    Matrix result = {};
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        result.elements[i][j] = elements[i][j] / other;
      }
    }
    return result;
  }

  Matrix& operator/=(const T& other) {
    Matrix result = *this / other;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        elements[i][j] = result.elements[i][j];
      }
    }
    return *this;
  }

  bool operator==(const Matrix& other) const {
    bool result = true;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        if (!(other.elements[i][j] == elements[i][j])) {
          result = false;
        }
      }
    }
    return result;
  }

  bool operator!=(const Matrix& other) const {
    return !(*this == other);
  }

  friend std::istream& operator>>(std::istream& is, Matrix& matrix) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        is >> matrix.At(i, j);
      }
    }
    return is;
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns - 1; ++j) {
        os << matrix.elements[i][j] << ' ';
      }
      os << matrix.elements[i][Columns - 1] << '\n';
    }
    return os;
  }
};

template <typename T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> operator*(const int64_t& other, const Matrix<T, Rows, Columns>& matrix) {
  Matrix<T, Rows, Columns> result = {};
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      result.elements[i][j] = matrix.elements[i][j] * other;
    }
  }
  return result;
}

template <typename T, size_t Rows, size_t Columns>
Matrix<T, Columns, Rows> GetTransposed(const Matrix<T, Rows, Columns>& matrix) {
  auto new_matrix = Matrix<T, Columns, Rows>{};
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      new_matrix.elements[j][i] = matrix.elements[i][j];
    }
  }
  return new_matrix;
}

template <typename T, size_t M, size_t N, size_t K>
Matrix<T, M, K> operator*(const Matrix<T, M, N>& self, const Matrix<T, N, K>& other) {
  Matrix<T, M, K> result = {};
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < K; ++j) {
      T summary = 0;
      for (size_t k = 0; k < N; ++k) {
        summary += self.elements[i][k] * other.elements[k][j];
      }
      result.elements[i][j] = summary;
    }
  }
  return result;
}

template <typename T, size_t M, size_t N>
Matrix<T, M, N>& operator*=(Matrix<T, M, N>& self, const Matrix<T, N, N>& other) {
  Matrix<T, M, N> result = self * other;
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      self.elements[i][j] = result.elements[i][j];
    }
  }
  return self;
}

template <typename T, size_t M>
Matrix<T, M, M>& Transpose(Matrix<T, M, M>& matrix) {
  matrix = GetTransposed(matrix);
  return matrix;
}

template <typename T, size_t N>
T Trace(const Matrix<T, N, N>& matrix) {
  T result = 0;
  for (size_t i = 0; i < N; ++i) {
    result += matrix.At(i, i);
  }
  return result;
}

template <typename T, size_t N>
Matrix<T, N - 1, N - 1> GetMinor(const Matrix<T, N, N>& matrix, size_t row, size_t column) {
  Matrix<T, N - 1, N - 1> result = {};
  for (size_t i = 0; i < N; ++i) {
    if (i != row) {
      for (size_t j = 0; j < N; ++j) {
        if (j < column && i < row) {
          result.At(i, j) = matrix.At(i, j);
        } else if (j < column && i > row) {
          result.At(i - 1, j) = matrix.At(i, j);
        } else if (j > column && i < row) {
          result.At(i, j - 1) = matrix.At(i, j);
        } else if (j > column && i > row) {
          result.At(i - 1, j - 1) = matrix.At(i, j);
        }
      }
    }
  }
  return result;
}

template <typename T, size_t N>
T Determinant(const Matrix<T, N, N>& matrix) {
  T result = 0;
  if (N <= 1) {
    result = matrix(0, 0);
    return result;
  }
  for (size_t i = 0; i < N; ++i) {
    if (i % 2 == 1) {
      Matrix<T, N - 1, N - 1> minor = GetMinor(matrix, 0, i);
      result += -1 * matrix(0, i) * Determinant(minor);
    } else {
      Matrix<T, N - 1, N - 1> minor = GetMinor(matrix, 0, i);
      result += matrix(0, i) * Determinant(minor);
    }
  }
  return result;
}

template <typename T>
T Determinant(const Matrix<T, 1, 1>& matrix) {
  T result = 0;
  result = matrix(0, 0);
  return result;
}

template <typename T>
T Determinant(const Matrix<T, 0, 0>&) {
  return 0;
}

template <typename T, size_t N>
Matrix<T, N, N> UnionMatrix(const Matrix<T, N, N>& matrix) {
  Matrix<T, N, N> result = {};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      if ((i + j) % 2 == 0) {
        result.At(i, j) = Determinant(GetMinor(matrix, i, j));
      } else {
        result.At(i, j) = -Determinant(GetMinor(matrix, i, j));
      }
    }
  }
  Transpose(result);
  return result;
}

template <typename T>
Matrix<T, 1, 1> UnionMatrix(const Matrix<T, 1, 1>& matrix) {
  Matrix<T, 1, 1> result = matrix;
  return result;
}

template <typename T>
Matrix<T, 0, 0> UnionMatrix(const Matrix<T, 0, 0>&) {
  return Matrix<T, 0, 0>{};
}

template <typename T, size_t N>
Matrix<T, N, N> GetInversed(const Matrix<T, N, N>& matrix) {
  T det = Determinant(matrix);
  if (det == 0) {
    throw MatrixIsDegenerateError{};
  }
  return UnionMatrix(matrix) / det;
}
template <typename T>
Matrix<T, 1, 1> GetInversed(const Matrix<T, 1, 1>& matrix) {
  T det = Determinant(matrix);
  if (det == 0) {
    throw MatrixIsDegenerateError{};
  }
  return Matrix<T, 1, 1> {1 / det};
}

template <typename T, size_t N>
Matrix<T, N, N>& Inverse(Matrix<T, N, N>& matrix) {
  T det = Determinant(matrix);
  if (det == 0) {
    throw MatrixIsDegenerateError{};
  }
  matrix = GetInversed(matrix);
  return matrix;
}