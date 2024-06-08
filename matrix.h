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
  T elements[Rows][Columns];
  static T RowsNumber() {
    return Rows;
  }
  static T ColumnsNumber() {
    return Columns;
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
  Matrix<T, Rows, Rows> operator*(const Matrix<T, Columns, Rows>& other) const {
    Matrix<T, Rows, Rows> result = {};
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < other.ColumnsNumber(); ++j) {
        T summary = 0;
        for (size_t k = 0; k < Rows; ++k) {
          summary += elements[i][k] * other.elements[k][j];
        }
        result.elements[i][j] = summary;
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
  Matrix<T, Rows, Rows>& operator*=(const Matrix<T, Columns, Rows>& other) {
    Matrix<T, Rows, Rows> result = *this * other;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        elements[i][j] = result.elements[i][j];
      }
    }
    return *this;
  }
  Matrix operator*(const int64_t& other) const {
    Matrix result = {};
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        result.elements[i][j] = elements[i][j] * other;
      }
    }
    return result;
  }
  Matrix& operator*=(const int64_t& other) {
    Matrix result = *this * other;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        elements[i][j] = result.elements[i][j];
      }
    }
    return *this;
  }
  Matrix operator/(const int64_t& other) const {
    Matrix result = {};
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        result.elements[i][j] = elements[i][j] / other;
      }
    }
    return result;
  }
  Matrix& operator/=(const int64_t& other) const {
    Matrix result = *this / other;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        elements[i][j] = result.elements[i][j];
      }
    }
    return *this;
  }
  bool operator==(const Matrix& other) const {
    if (Rows == other.RowsNumber() && Columns == other.ColumnsNumber()) {
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
    return false;
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
      for (size_t j = 0; j < Columns; ++j) {
        os << matrix.elements[i][j] << ' ';
      }
      os << '\n';
    }
    return os;
  }
};

template <typename T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> operator*(const int64_t& other, const Matrix<T, Rows, Columns>& matrix) {
  Matrix<T, Rows, Columns>& result = {};
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      result.elements[i][j] = matrix.elements[i][j] * other;
    }
  }
  return result;
}

template <typename T, size_t Rows, size_t Columns>
Matrix<T, Columns, Rows> GetTransposed(const Matrix<T, Rows, Columns>& matrix) {
  Matrix new_matrix = Matrix<T, Columns, Rows>{};
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      new_matrix.elements[j][i] = matrix.elements[i][j];
    }
  }
  return new_matrix;
}
