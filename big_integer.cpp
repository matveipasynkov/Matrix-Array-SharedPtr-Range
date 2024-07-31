#include "big_integer.h"
#include <string>

BigInteger::BigInteger(int64_t integer) {
  if (integer < 0) {
    integer = -integer;
    sign_ = true;
  }
  while (integer != 0) {
    number_.push_back(integer / foundation_);
    integer %= foundation_;
  }
}

BigInteger::BigInteger(int32_t integer) {
  if (integer < 0) {
    integer = -integer;
    sign_ = true;
  }
  while (integer != 0) {
    number_.push_back(integer / foundation_);
    integer %= foundation_;
  }
}

BigInteger::BigInteger(const char* integer) {
  size_t size_of_string = std::strlen(integer);

  if (integer[0] == '-') {
    sign_ = true;
    ++integer;
  } else {
    if (integer[0] == '+') {
      ++integer;
    }
  }

  int64_t buffer = 0;
  int64_t len_of_buffer = 0;
  int64_t digit = 1;
  const char* pointer = integer + size_of_string - 1;
  while (integer <= pointer) {
    buffer += (*pointer - '0') * digit;
    digit *= 10;
    ++len_of_buffer;
    if (len_of_buffer == length_) {
      number_.push_back(buffer);
      buffer = 0;
      len_of_buffer = 0;
      digit = 1;
    }
    --pointer;
  }

  number_.push_back(buffer);
  if (number_.size() > 30000) {
    throw BigIntegerOverflow{};
  }
}

bool BigInteger::IsNegative() const {
  return sign_;
}

BigInteger BigInteger::operator+() const {
  return *this;
}

BigInteger BigInteger::operator-() const {
  BigInteger result = *this;
  result.sign_ = !result.sign_;
  return result;
}

BigInteger BigInteger::operator+(const BigInteger& other) const {
  BigInteger result = BigInteger(0);
  if (other.number_.size() > number_.size()) {
    result = other;
  } else {
    result = *this;
  }
  for (size_t i = 0; i < std::min(other.number_.size(), number_.size()); ++i) {
    result.number_[i + 1] += (number_[i] + other.number_[i]) / foundation_;
    result.number_[i] += other.number_[i];
    result.number_[i] %= foundation_;
  }

  result.sign_ = sign_ || other.sign_;
  return result;
}

BigInteger BigInteger::operator-(const BigInteger& other) const {
  return *this + (-other);
}

BigInteger BigInteger::operator*(const BigInteger&) const {

}
