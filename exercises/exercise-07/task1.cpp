// Exercise 7 task 1a. Tries both subtractions.
// The answer to task 1b is in THEORY.md.

#include "fraction.hpp"
#include <iostream>

using namespace std;

int main() {
  Fraction fraction1(1, 2);
  Fraction fraction2(2, 3);

  cout << "fraction1     = " << fraction1 << endl;
  cout << "fraction2     = " << fraction2 << endl;

  cout << "fraction1 - 5 = " << (fraction1 - 5) << endl; // member
  cout << "5 - fraction1 = " << (5 - fraction1) << endl; // non member

  cout << "5 - 3 - fraction1 - 7 - fraction2 = "
       << (5 - 3 - fraction1 - 7 - fraction2) << endl;
}
