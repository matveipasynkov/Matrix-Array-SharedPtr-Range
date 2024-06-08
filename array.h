#pragma once
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <class T, size_t N>
class Array {
 public:
  T elements[N] = {};
  T& operator[](size_t index) {
    return elements[index];
  }
  const T& operator[](size_t index) const {
    return elements[index];
  }
  T& At(size_t index) {
    if (index >= N) {
      throw ArrayOutOfRange{};
    }
    return elements[index];
  }
  const T& At(size_t index) const {
    if (index >= N) {
      throw ArrayOutOfRange{};
    }
    return elements[index];
  }
  T& Front() {
    return elements[0];
  }
  const T& Front() const {
    return elements[0];
  }
  T& Back() {
    return elements[N - 1];
  }
  const T& Back() const {
    return elements[N - 1];
  }
  T* Data() {
    T* ptr = elements;
    return ptr;
  }
  const T* Data() const {
    const T* ptr = elements;
    return ptr;
  }
  static size_t Size() {
    return N;
  }
  static bool Empty() {
    return N == 0;
  }
  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      elements[i] = value;
    }
  }
  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
      T tmp = elements[i];
      elements[i] = other[i];
      other[i] = tmp;
    }
  }
};
