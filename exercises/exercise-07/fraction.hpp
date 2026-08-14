// Exercise 7 task 1. Fraction with subtraction against int both ways.
// Trimmed down to what the task needs, with the same interface the lesson
// uses. Swap it for your own Fraction if you continue from the lesson code.
//
// operator-(int, const Fraction &) cannot be a member. A member is always
// called on the left operand, and here the left operand is an int.

#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <cstdlib>
#include <iostream>

class Fraction {
public:
  int numerator;
  int denominator;

  Fraction() : numerator(0), denominator(1) {}
  Fraction(int numerator, int denominator) { set(numerator, denominator); }

  void set(int numerator_, int denominator_ = 1) {
    if (denominator_ == 0) {
      std::cerr << "denominator cannot be zero" << std::endl;
      std::exit(EXIT_FAILURE);
    }
    numerator = numerator_;
    denominator = denominator_;
    reduce();
  }

  Fraction operator-(const Fraction &other) const {
    return Fraction(numerator * other.denominator - other.numerator * denominator,
                    denominator * other.denominator);
  }

  // Fraction minus int. Fine as a member, the left operand is a Fraction.
  Fraction operator-(int value) const {
    return *this - Fraction(value, 1);
  }

  Fraction operator-() const {
    return Fraction(-numerator, denominator);
  }

  friend std::ostream &operator<<(std::ostream &out, const Fraction &fraction) {
    out << fraction.numerator << " / " << fraction.denominator;
    return out;
  }

private:
  void reduce() {
    // Keep the sign in the numerator, so 1/-2 and -1/2 print the same.
    if (denominator < 0) {
      numerator = -numerator;
      denominator = -denominator;
    }
    int a = std::abs(numerator);
    int b = denominator;
    while (b != 0) { // Euclid
      const int rest = a % b;
      a = b;
      b = rest;
    }
    if (a > 1) {
      numerator /= a;
      denominator /= a;
    }
  }
};

// int minus Fraction. Has to live outside the class.
inline Fraction operator-(int value, const Fraction &fraction) {
  return Fraction(value, 1) - fraction;
}

#endif
