// Exercise 3 task 1. Corrected version of the class Circle.
// The errors in the original are listed in THEORY.md.

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

const double pi = 3.141592;

class Circle {
public:
  Circle(double radius_);
  double get_area() const;
  double get_circumference() const;

private:
  double radius;
};

inline Circle::Circle(double radius_) : radius(radius_) {}

inline double Circle::get_area() const {
  return pi * radius * radius;
}

inline double Circle::get_circumference() const {
  double circumference = 2.0 * pi * radius;
  return circumference;
}

#endif
