#pragma once

class Iterator {
private:
  int value_ = 0;
  int step_ = 1;
  int finish_ = 0;

public:
  explicit Iterator(int value, int finish, int step) {
    step_ = step;
    value_ = value;
    finish_ = finish;
  }

  int operator*() const {
    return value_;
  }

  Iterator& operator++() {
    if (step_ > 0 && value_ + step_ <= finish_) {
      value_ += step_;
    } else if (step_ < 0 && value_ + step_ >= finish_) {
      value_ += step_;
    } else {
      value_ = finish_;
    }
    return *this;
  }

  Iterator operator++(int) {
    const Iterator tmp = *this;
    ++*this;
    return tmp;
  }

  friend bool operator==(const Iterator& first_iterator, const Iterator& second_iterator) {
    return first_iterator.value_ == second_iterator.value_;
  }

  friend bool operator!=(const Iterator& first_iterator, const Iterator& second_iterator) {
    return first_iterator.value_ != second_iterator.value_;
  }
};