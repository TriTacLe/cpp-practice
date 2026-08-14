// Exercise 2 task 4. Corrected version of the broken snippet.
// The errors are explained in THEORY.md.

#include <iostream>

using namespace std;

int main() {
  int a = 5;
  int &b = a; // a reference must be bound where it is defined
  int *c;
  c = &b; // gives the address of a, since b is just another name for a

  a = b + *c; // a and b are ints, only c has to be dereferenced
  b = 2;      // writes to a through the reference

  cout << "a = " << a << ", b = " << b << ", *c = " << *c << endl;
}
