// Exercise 3 task 2. The client program from the task, with the holes filled in.
// The holes are explained in THEORY.md.

#include "circle.hpp"
#include <iostream>

using namespace std;

int main() {
  Circle circle(5);

  double area = circle.get_area();
  cout << "Arealet er lik " << area << endl;

  double circumference = circle.get_circumference();
  cout << "Omkretsen er lik " << circumference << endl;
}
