#pragma once
#include <iterator>
#include <stdexcept>
#include <type_traits>

template <typename T>
class Vector {
 private:
  size_t capacity_ = 0;
  size_t size_ = 0;
  T* array_ = nullptr;

 public:
  Vector() {
    try {
      capacity_ = 0;
      size_ = 0;
      array_ = new T[0];
    } catch (...) {
    }
  }
  explicit Vector(const size_t n) {
    try {
      size_ = n;
      while (capacity_ < n) {
        capacity_ *= 2;
      }
      array_ = new T[capacity_];
    } catch (...) {
    }
  }
  Vector(const size_t size, const T value) {
    try {
      while (capacity_ < size) {
        capacity_ *= 2;
      }
      size_ = size;
      array_ = new T[capacity_];
      for (size_t i = 0; i < size; ++i) {
        array_[i] = value;
      }
    } catch (...) {
    }
  }
  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first, Iterator last) {
    try {
      while (capacity_ < last - first) {
        capacity_ *= 2;
      }
      size_ = last - first;
      array_ = new T[capacity_];
      size_t i = 0;
      for (auto iter = first; iter != last; ++iter) {
        array_[i] = *iter;
        ++i;
      }
    } catch (...) {
    }
  }
  Vector(std::initializer_list<T> initializer_list) {
    try {
      while (capacity_ < initializer_list.size()) {
        capacity_ *= 2;
      }
      size_ = initializer_list.size();
      array_ = new T[capacity_];
      for (size_t i = 0; i < initializer_list.size(); ++i) {
        array_[i] = initializer_list[i];
      }
    } catch (...) {
    }
  }
  Vector(const Vector& vector) {
    try {
      delete[] array_;
      array_ = new T[vector.capacity_];
      capacity_ = vector.capacity_;
      size_ = vector.size_;
      for (size_t i = 0; i < size_; ++i) {
        array_[i] = vector[i];
      }
    } catch (...) {
    }
  }
  Vector& operator=(const Vector& vector) {
    try {
      delete[] array_;
      array_ = new T[vector.capacity_];
      capacity_ = vector.capacity_;
      size_ = vector.size_;
      for (size_t i = 0; i < size_; ++i) {
        array_[i] = vector[i];
      }
    } catch (...) {
    }
    return *this;
  }
  Vector(Vector&& vector) noexcept {
    delete[] array_;
    array_ = new T[vector.capacity_];
    capacity_ = vector.capacity_;
    size_ = vector.size_;
    for (size_t i = 0; i < size_; ++i) {
      array_[i] = vector[i];
    }
    delete[] vector.array_;
    vector.array_ = nullptr;
    vector.capacity_ = 0;
    vector.size_ = 0;
  }
  Vector& operator=(Vector&& vector) noexcept {
    delete[] array_;
    array_ = new T[vector.capacity_];
    capacity_ = vector.capacity_;
    size_ = vector.size_;
    for (size_t i = 0; i < size_; ++i) {
      array_[i] = vector[i];
    }
    delete[] vector.array_;
    vector.array_ = nullptr;
    vector.capacity_ = 0;
    vector.size_ = 0;
    return *this;
  }
  size_t Size() const {
    return size_;
  }
  size_t Capacity() const {
    return capacity_;
  }
  bool Empty() const {
    return size_ == 0;
  }
  T& operator[](size_t index) {
    return array_[index];
  }
  const T& operator[](size_t index) const {
    return array_[index];
  }
  T& At(size_t index) {
    if (index >= size_) {
      throw std::out_of_range<>{};
    }
    return array_[index];
  }
  const T& At(size_t index) const {
    if (index >= size_) {
      throw std::out_of_range<>{};
    }
    return array_[index];
  }
  T& Front() {
    return array_[0];
  }
  const T& Front() const {
    return array_[0];
  }
  T& Back() {
    return array_[size_ - 1];
  }
  const T& Back() const {
    return array_[size_ - 1];
  }
  T* Data() {
    T* ptr = array_;
    return ptr;
  }
  const T* Data() const {
    const T* ptr = array_;
    return ptr;
  }
  void Swap(Vector& other) {
    std::swap(*this, other);
  }

  ~Vector() {
    delete[] array_;
  }
};