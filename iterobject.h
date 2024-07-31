#pragma once
#include "iterator.h"
#include "reverse_iterator.h"

class IterObject {
private:
  int start_ = 0;
  int end_ = 0;
  int step_ = 1;

public:
  explicit IterObject(int finish) {
    if (finish < start_) {
      end_ = 0;
    } else {
      end_ = finish;
    }
  }

  IterObject(int start, int finish) {
    if (finish < start) {
      start_ = 0;
      end_ = 0;
    } else {
      start_ = start;
      end_ = finish;
    }
  }

  IterObject(int start, int finish, int step) {
    if (finish > start) {
      if (step > 0) {
        start_ = start;
        end_ = finish;
        step_ = step;
      } else {
        start_ = 0;
        end_ = 0;
        step_ = 1;
      }
    } else {
      if (step < 0) {
        start_ = start;
        end_ = finish;
        step_ = step;
      } else {
        start_ = 0;
        end_ = 0;
        step_ = 1;
      }
    }
  }

  Iterator begin() const {  // NOLINT
    return Iterator(start_, end_, step_);
  }

  Iterator end() const {  // NOLINT
    return Iterator(end_, end_, step_);
  }

  ReverseIterator rbegin() const {  // NOLINT
    return ReverseIterator(end_, start_, step_);
  }

  ReverseIterator rend() const {  // NOLINT
    return ReverseIterator(start_, start_, step_);
  }
};