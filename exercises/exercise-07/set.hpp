// Exercise 7 task 2. Set, a set of integers.
// The task wants every operation to be a constructor or an operator.
// Element order is undefined in a set. We keep insertion order because it is
// the simplest thing, not because it means anything.

#ifndef SET_HPP
#define SET_HPP

#include <algorithm>
#include <iostream>
#include <vector>

class Set {
public:
  Set() {}

  // Needed because we write operator= ourselves. Without it the compiler
  // warns with -Wdeprecated-copy.
  Set(const Set &other) : numbers(other.numbers) {}

  /// Adds a number. Does nothing if it is already there.
  Set &operator+=(int number) {
    if (!contains(number))
      numbers.push_back(number);
    return *this;
  }

  /// Union. Lets operator+= handle the duplicates.
  Set operator+(const Set &other) const {
    Set result = *this;
    for (int number : other.numbers)
      result += number;
    return result;
  }

  /// The compiler would generate an identical one, but the task asks for it.
  /// The self assignment check is the habit that saves you once the class
  /// holds a pointer.
  Set &operator=(const Set &other) {
    if (this != &other)
      numbers = other.numbers;
    return *this;
  }

  bool contains(int number) const {
    return std::find(numbers.begin(), numbers.end(), number) != numbers.end();
  }

  friend std::ostream &operator<<(std::ostream &out, const Set &set) {
    out << "{";
    for (size_t i = 0; i < set.numbers.size(); i++) {
      if (i > 0)
        out << ", ";
      out << set.numbers[i];
    }
    out << "}";
    return out;
  }

private:
  std::vector<int> numbers;
};

#endif
