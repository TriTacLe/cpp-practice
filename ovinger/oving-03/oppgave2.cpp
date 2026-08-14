// Øving 3, oppgave 2: klientprogrammet fra oppgaven, med hullene fylt ut.
//
// Original med hull:
//
//   /*---*/ circle(5);
//   /*---*/ area = circle.get_area();
//   cout << "Arealet er lik " /*---*/ endl;
//   double circumference = /*---*/.get_circumference();
//
// Hull 1: typen mangler. Circle circle(5); kaller konstruktøren med 5.
// Hull 2: typen på area. get_area() returnerer double.
// Hull 3: to utskriftsoperatorer mangler, en for area og en for endl.
// Hull 4: objektet det kalles på, altså circle.

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
