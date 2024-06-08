#include <iostream>
#include "matrix.h"
#include <iosfwd>
#include <sstream>

int main() {
  Matrix<int, 2, 3> matrix{};
  std::cin >> matrix;
  std::cout << GetTransposed(matrix);
  return 0;
}
