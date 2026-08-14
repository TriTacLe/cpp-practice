// Exercise 7 task 2. Test program for Set.

#include "set.hpp"
#include <iostream>

using namespace std;

int main() {
  Set set1;
  set1 += 1;
  set1 += 4;
  set1 += 3;

  Set set2;
  set2 += 4;
  set2 += 7;

  cout << "set1: " << set1 << endl;
  cout << "set2: " << set2 << endl;

  // From the task text: {1, 4, 3} union {4, 7} is {1, 4, 3, 7}.
  Set union_set = set1 + set2;
  cout << "union: " << union_set << endl;

  // 4 is already there, so nothing happens.
  set1 += 4;
  cout << "set1 after adding 4 again: " << set1 << endl;

  Set set3;
  set3 = union_set;
  cout << "set3 assigned from union: " << set3 << endl;

  cout << "does set3 contain 7? " << (set3.contains(7) ? "yes" : "no") << endl;
  cout << "does set3 contain 9? " << (set3.contains(9) ? "yes" : "no") << endl;
}
