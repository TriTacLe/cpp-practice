// Exercise 8 task 1. Function template for equality, with an own version for
// double.
//
// double needs its own because 0.1 + 0.2 is not 0.3 in floating point. 0.1
// cannot be written exactly in binary, so == on computed decimals almost
// always answers false. Ask whether the difference is small enough instead.
//
// An overload with a concrete type always wins over the template when the
// types match exactly.

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

template <typename Type>
bool equal(Type a, Type b) {
  cout << "  [template version]" << endl;
  return a == b;
}

// A plain overload, not a template specialisation, and that is enough here.
bool equal(double a, double b) {
  cout << "  [double version]" << endl;
  const double epsilon = 0.00001;
  return fabs(a - b) < epsilon;
}

int main() {
  cout << "int 3 and 3:" << endl;
  cout << "  " << (equal(3, 3) ? "equal" : "not equal") << endl;

  cout << "string hei and hei:" << endl;
  cout << "  " << (equal(string("hei"), string("hei")) ? "equal" : "not equal") << endl;

  cout << "string hei and hoo:" << endl;
  cout << "  " << (equal(string("hei"), string("hoo")) ? "equal" : "not equal") << endl;

  const double sum = 0.1 + 0.2;
  cout << setprecision(20) << fixed;
  cout << "0.1 + 0.2 = " << sum << endl;
  cout << "0.3       = " << 0.3 << endl;
  cout << defaultfloat << setprecision(6);

  cout << "double 0.1 + 0.2 and 0.3:" << endl;
  cout << "  " << (equal(sum, 0.3) ? "equal" : "not equal") << endl;

  cout << "double 1.0 and 1.001:" << endl;
  cout << "  " << (equal(1.0, 1.001) ? "equal" : "not equal") << endl;

  // Without the epsilon version this would answer false.
  cout << "raw comparison sum == 0.3: " << ((sum == 0.3) ? "true" : "false") << endl;
}
