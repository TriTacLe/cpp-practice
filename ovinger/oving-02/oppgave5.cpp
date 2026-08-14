// Øving 2, oppgave 5: peker og referanse til samme variabel, og tre måter å
// tilordne verdi til den på.

#include <iostream>

using namespace std;

int main() {
  double number = 0.0;

  double *pointer = &number;    // peker til number
  double &reference = number;   // referanse til number

  // Måte 1: rett på variabelen.
  number = 1.5;
  cout << "etter number = 1.5:      " << number << endl;

  // Måte 2: gjennom pekeren. Pekeren må dereferereses.
  *pointer = 2.5;
  cout << "etter *pointer = 2.5:    " << number << endl;

  // Måte 3: gjennom referansen. Referansen er bare et annet navn, ingen
  // dereferering.
  reference = 3.5;
  cout << "etter reference = 3.5:   " << number << endl;
}
