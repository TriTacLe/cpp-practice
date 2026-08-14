// Øving 7, oppgave 1a: prøver ut begge subtraksjonene.
// Svaret på oppgave 1b ligger i TEORI.md.

#include "fraction.hpp"
#include <iostream>

using namespace std;

int main() {
  Fraction fraction1(1, 2);
  Fraction fraction2(2, 3);

  cout << "fraction1     = " << fraction1 << endl;
  cout << "fraction2     = " << fraction2 << endl;

  cout << "fraction1 - 5 = " << (fraction1 - 5) << endl; // medlemsfunksjon
  cout << "5 - fraction1 = " << (5 - fraction1) << endl; // ikke-medlem

  // Uttrykket fra oppgave 1b, se TEORI.md for hvilke operatorer som brukes.
  cout << "5 - 3 - fraction1 - 7 - fraction2 = "
       << (5 - 3 - fraction1 - 7 - fraction2) << endl;
}
