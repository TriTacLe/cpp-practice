// Exercise 2 task 5. Three ways to assign to the same variable.

#include <iostream>

using namespace std;

int main() {
  double number = 0.0;

  double *pointer = &number;
  double &reference = number;

  number = 1.5;
  cout << "after number = 1.5:    " << number << endl;

  // Through the pointer, which has to be dereferenced.
  *pointer = 2.5;
  cout << "after *pointer = 2.5:  " << number << endl;

  // Through the reference, which is just another name for number.
  reference = 3.5;
  cout << "after reference = 3.5: " << number << endl;
}
