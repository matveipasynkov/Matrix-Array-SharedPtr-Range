#include "big_integer.h"

#include <iostream>
#include "range.h"
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <sstream>
#include <vector>

void REQUIRE(bool a) {
  if (!a) {
    throw "CRINGE";
  }
}

void REQUIRE_FALSE(bool a) {
  if (a) {
    throw "CRINGE";
  }
}

// template <class T, class U, size_t N>
// void Equals(const Array<T, N>& actual, const std::array<U, N>& required) {
//   for (size_t i = 0; i < N; ++i) {
//     REQUIRE(actual[i] == required[i]);
//   }
// }

template <class T >
void f(T& x , T&& y);

int main() {
  size_t n = 0;
  std::vector<std::string> passwords = {};
  std::cin >> n;
  size_t result = 0;
  for (size_t i = 0; i < n; ++i) {
    std::string word;
    std::cin >> word;
    for (size_t j = 0; j < passwords.size(); ++j) {
      if (passwords[j].find(word) != std::string::npos) {
        ++result;
      } else if (word.find(passwords[j]) != std::string::npos) {
        ++result;
      }
    }
    passwords.push_back(word);
  }
  std::cout << result;
}