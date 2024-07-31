#pragma once
#include <algorithm>
#include <cstdint>
#define WEAK_PTR_IMPLEMENTED

class BadWeakPtr : public std::bad_weak_ptr {
 public:
  BadWeakPtr() : std::bad_weak_ptr() {
  }
};

class Counter {
 public:
  int64_t strong_count = 0;
  int64_t weak_count = 0;
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
 public:
  T* ptr = nullptr;
  Counter* counter = nullptr;

  SharedPtr() : ptr(nullptr) {
  }

  explicit SharedPtr(T* other_ptr) : ptr(other_ptr) {
    if (ptr) {
      counter = new Counter();
      ++counter->strong_count;
    }
  }

  explicit SharedPtr(const WeakPtr<T>& weak_ptr) : ptr(weak_ptr.ptr), counter(weak_ptr.counter) {
    if (weak_ptr.Expired()) {
      throw BadWeakPtr{};
    }
    ++counter->strong_count;
  }

  SharedPtr(const SharedPtr& other) : ptr(other.ptr), counter(other.counter) {
    if (ptr) {
      ++counter->strong_count;
    }
  }

  SharedPtr& operator=(const SharedPtr& other) {
    if (this != &other) {
      Reset();
      ptr = other.ptr;
      counter = other.counter;
      if (ptr) {
        ++counter->strong_count;
      }
    }
    return *this;
  }

  SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), counter(other.counter) {
    other.ptr = nullptr;
    other.counter = nullptr;
  }

  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
      Reset();
      ptr = other.ptr;
      counter = other.counter;
      other.ptr = nullptr;
      other.counter = nullptr;
    }
    return *this;
  }

  void Reset(T* other_ptr = nullptr) {
    if (ptr) {
      --counter->strong_count;
      if (counter->strong_count == 0) {
        delete ptr;
        if (counter->weak_count == 0) {
          delete counter;
        }
      }
      ptr = nullptr;
      counter = nullptr;
    }
    if (other_ptr) {
      ptr = other_ptr;
      counter = new Counter();
      ++counter->strong_count;
    }
  }

  void Swap(SharedPtr& other) {
    SharedPtr tmp = SharedPtr();
    tmp = std::move(*this);
    *this = std::move(other);
    other = std::move(tmp);
  }

  T* Get() const {
    return ptr;
  }

  T& operator*() const {
    return *ptr;
  }

  T* operator->() const {
    return ptr;
  }

  size_t UseCount() const {
    if (ptr) {
      return counter->strong_count;
    }
    return 0;
  }

  operator bool() const {  // NOLINT
    return ptr;
  }

  ~SharedPtr() {
    Reset();
  }
};

template <class T>
class WeakPtr {
 public:
  T* ptr = nullptr;
  Counter* counter = nullptr;

  WeakPtr() : ptr(nullptr) {
  }

  WeakPtr(const WeakPtr& other) : ptr(other.ptr), counter(other.counter) {
    if (ptr) {
      ++counter->weak_count;
    }
  }

  WeakPtr& operator=(const WeakPtr& other) {
    if (this != &other) {
      Reset();
      ptr = other.ptr;
      counter = other.counter;
      if (ptr) {
        ++counter->weak_count;
      }
    }
    return *this;
  }

  WeakPtr(WeakPtr&& other) noexcept : ptr(other.ptr), counter(other.counter) {
    if (ptr) {
      ++counter->weak_count;
    }
  }

  WeakPtr(const SharedPtr<T>& other) : ptr(other.ptr), counter(other.counter) {  // NOLINT
    if (ptr) {
      ++counter->weak_count;
    }
  }

  WeakPtr& operator=(WeakPtr&& other) noexcept {
    if (this != &other) {
      Reset();
      ptr = other.ptr;
      counter = other.counter;
      other.ptr = nullptr;
      other.counter = nullptr;
    }
    return *this;
  }

  void Reset() {
    if (ptr) {
      --counter->weak_count;
      if (counter->strong_count == 0) {
        delete counter;
      }
      ptr = nullptr;
      counter = nullptr;
    }
  }

  void Swap(WeakPtr& other) {
    WeakPtr tmp = WeakPtr();
    tmp = std::move(*this);
    *this = std::move(other);
    other = std::move(tmp);
  }

  T* Get() const {
    return ptr;
  }

  T& operator*() const {
    return *ptr;
  }

  T* operator->() const {
    return ptr;
  }

  size_t UseCount() const {
    if (ptr) {
      return counter->strong_count;
    }
    return 0;
  }

  bool Expired() const {
    if (ptr) {
      return counter->strong_count == 0;
    }
    return true;
  }

  SharedPtr<T> Lock() const {
    if (ptr) {
      if (counter->strong_count == 0) {
        return SharedPtr<T>(nullptr);
      }
      return SharedPtr<T>(*this);
    }
    return SharedPtr<T>(nullptr);
  }

  operator bool() const {  // NOLINT
    return ptr;
  }

  ~WeakPtr() {
    Reset();
  }
};

template <class T, class... Args>
SharedPtr<T> MakeShared(Args&&... args) {
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}