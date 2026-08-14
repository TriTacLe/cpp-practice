// Exercise 8 task 2. Template class for a pair.
//
// What the class assumes about the types put into it:
//   1. operator+ exists for First + First and Second + Second, and the result
//      fits in the same type.
//   2. first and second can be added to each other. That sum is what
//      operator> compares.
//   3. operator> exists for the type of that sum.
//   4. both types can be copied.
//
// Pair<double, int> satisfies all of it, since double + int gives double.

#ifndef PAIR_HPP
#define PAIR_HPP

template <typename First, typename Second>
class Pair {
public:
  First first;
  Second second;

  Pair(First first, Second second) : first(first), second(second) {}

  /// Element wise sum.
  Pair operator+(const Pair &other) const {
    return Pair(first + other.first, second + other.second);
  }

  /// Compares the sum of the elements in each pair.
  bool operator>(const Pair &other) const {
    return (first + second) > (other.first + other.second);
  }
};

#endif
