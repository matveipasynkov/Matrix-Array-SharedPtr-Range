#pragma once

class ReverseIterator {
private:
  int value_ = 0;
  int step_ = 1;
  int finish_ = 0;

public:
  explicit ReverseIterator(int value, int finish, int step) {
    step_ = step;
    if (value != finish) {
      int mod = 0;
      if (std::abs(finish - value) % std::abs(step_) == 0) {
        mod = std::abs(step_);
      } else {
        mod = std::abs(finish - value) % std::abs(step_);
      }
      if (step_ > 0) {
        finish_ = finish - 1;
        value_ = value - mod;
      } else {
        finish_ = finish + 1;
        value_ = value + mod;
      }
    } else {
      finish_ = finish - step_;
      value_ = value - step_;
    }
  }

  int operator*() const {
    return value_;
  }

  ReverseIterator& operator++() {
    value_ -= step_;
    return *this;
  }

  ReverseIterator operator++(int) {
    const ReverseIterator tmp = *this;
    ++*this;
    return tmp;
  }

  friend bool operator==(const ReverseIterator& first_iterator, const ReverseIterator& second_iterator) {
    return first_iterator.value_ == second_iterator.value_;
  }

  friend bool operator!=(const ReverseIterator& first_iterator, const ReverseIterator& second_iterator) {
    return first_iterator.value_ != second_iterator.value_;
  }
};