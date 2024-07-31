#pragma once
#include <stdexcept>
#include <vector>

class BigIntegerOverflow : public std::runtime_error {
 public:
  BigIntegerOverflow() : std::runtime_error("BigIntegerOverflow") {
  }
};

class BigIntegerDivisionByZero : public std::runtime_error {
 public:
  BigIntegerDivisionByZero() : std::runtime_error("BigIntegerDivisionByZero") {
  }
};

class BigInteger {
 private:
  std::vector<int64_t> number_ = {};
  int64_t foundation_ = 1000000000;
  int64_t length_ = 9;
  bool sign_ = false;

 public:
  explicit BigInteger(int64_t);
  explicit BigInteger(int32_t);
  explicit BigInteger(const char*);
  bool IsNegative() const;
  BigInteger operator+() const;
  BigInteger operator-() const;

  BigInteger operator+(const BigInteger&) const;
  BigInteger operator-(const BigInteger&) const;
  BigInteger operator*(const BigInteger&) const;
  BigInteger& operator+=(const BigInteger&);
  BigInteger& operator-=(const BigInteger&);
  BigInteger operator*=(const BigInteger&) const;

  BigInteger operator+(int64_t) const;
  BigInteger operator-(int64_t) const;
  BigInteger& operator+=(int64_t);
  BigInteger& operator-=(int64_t);

  BigInteger& operator++();
  BigInteger operator++(int);
  BigInteger& operator--();
  BigInteger operator--(int);

  bool operator>(const BigInteger&) const;
  bool operator<(const BigInteger&) const;
  bool operator>=(const BigInteger&) const;
  bool operator<=(const BigInteger&) const;
  bool operator==(const BigInteger&) const;
  bool operator!=(const BigInteger&) const;

  friend std::istream& operator>>(std::istream&, BigInteger&);
  friend std::ostream& operator<<(std::ostream&, const BigInteger&);
};