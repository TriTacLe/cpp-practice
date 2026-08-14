// Exercise 2 task 1. Addresses, contents, and what happens when a pointer is
// reassigned instead of written through.

#include <iostream>

using namespace std;

int main() {
  int i = 3;
  int j = 5;
  int *p = &i;
  int *q = &j;

  // a) p and q are variables of their own, so they have their own addresses.
  cout << "a)" << endl;
  cout << "&i = " << &i << ", i  = " << i << endl;
  cout << "&j = " << &j << ", j  = " << j << endl;
  cout << "&p = " << &p << ", p  = " << p << ", *p = " << *p << endl;
  cout << "&q = " << &q << ", q  = " << q << ", *q = " << *q << endl;

  cout << endl
       << "b)" << endl;

  *p = 7; // writes through p, so i becomes 7
  cout << "after *p = 7:      i = " << i << ", j = " << j << endl;

  *q += 4; // writes through q, so j becomes 9
  cout << "after *q += 4:     i = " << i << ", j = " << j << endl;

  *q = *p + 1; // j = i + 1 = 8
  cout << "after *q = *p + 1: i = " << i << ", j = " << j << endl;

  p = q; // changes the pointer itself, not what it points at
  cout << "after p = q:       both point at j" << endl;

  // Same value twice, and i is untouched since the line before.
  cout << *p << " " << *q << endl;
}
