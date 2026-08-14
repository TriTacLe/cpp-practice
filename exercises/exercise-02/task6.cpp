// Exercise 2 task 6. Sum parts of an array through a pointer.
// The function only knows where to start and how many to take, so moving the
// start pointer is enough to sum a different part.

#include <iostream>

using namespace std;

int find_sum(const int *table, int length) {
  int sum = 0;
  for (int i = 0; i < length; i++)
    sum += table[i]; // same as *(table + i)
  return sum;
}

int main() {
  const int size = 20;
  int table[size];

  for (int i = 0; i < size; i++)
    table[i] = i + 1;

  cout << "first 10: " << find_sum(table, 10) << endl;
  cout << "next 5:   " << find_sum(table + 10, 5) << endl;
  cout << "last 5:   " << find_sum(table + 15, 5) << endl;
}
