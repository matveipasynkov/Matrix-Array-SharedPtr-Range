// #include <iostream>
// #include "array.h"
// #include <array>
// #include <sstream>
//
// void REQUIRE(bool a) {
//   if (!a) {
//     throw "CRINGE";
//   }
// }
//
// template <class T, class U, size_t N>
// void Equals(const Array<T, N>& actual, const std::array<U, N>& required) {
//    for (size_t i = 0; i < N; ++i) {
//      REQUIRE(actual[i] == required[i]);
//    }
// }
//
// int main() {
//   Array<int, 3> a{1, 2, 3};
//   Array<int, 3> b{-1, -2, -3};
//
//   a.Swap(b);
//   Equals(a, std::array{-1, -2, -3});
//   Equals(b, std::array{1, 2, 3});
// }
