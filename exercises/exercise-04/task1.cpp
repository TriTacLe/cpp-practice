// Exercise 4 task 1. vector with front, back, emplace and find.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<double> numbers{1.5, 2.5, 3.5, 4.5, 5.5};

  // front() and back() return references. They take no arguments and do not
  // check whether the vector is empty.
  cout << "front(): " << numbers.front() << endl;
  cout << "back():  " << numbers.back() << endl;

  // emplace() inserts in front of the iterator it gets.
  numbers.emplace(numbers.begin() + 1, 99.9);

  cout << "front() after emplace: " << numbers.front() << endl;
  cout << "whole vector:";
  for (auto number : numbers)
    cout << " " << number;
  cout << endl;

  // find() takes start, end and the value. The end iterator points past the
  // last element, and a returned end() is the only way to spot a miss.
  auto it = find(numbers.begin(), numbers.end(), 3.5);
  if (it != numbers.end())
    cout << "found " << *it << " at position " << (it - numbers.begin()) << endl;
  else
    cout << "did not find 3.5" << endl;

  auto missing = find(numbers.begin(), numbers.end(), 42.0);
  if (missing != numbers.end())
    cout << "found " << *missing << endl;
  else
    cout << "did not find 42" << endl;
}
