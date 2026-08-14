// Øving 2, oppgave 1: adresser, innhold og hva som skjer når pekere flyttes.
//
// a) skriver ut adresse og innhold for i, j, p og q.
// b) kjører sekvensen fra oppgaven og viser at *p og *q ender likt.

#include <iostream>

using namespace std;

int main() {
  int i = 3;
  int j = 5;
  int *p = &i;
  int *q = &j;

  // a)
  // Adressene skrives ut i heksadesimal. p og q er egne variabler med egne
  // adresser, og innholdet deres er adressene til henholdsvis i og j.
  cout << "a)" << endl;
  cout << "&i = " << &i << ", i  = " << i << endl;
  cout << "&j = " << &j << ", j  = " << j << endl;
  cout << "&p = " << &p << ", p  = " << p << ", *p = " << *p << endl;
  cout << "&q = " << &q << ", q  = " << q << ", *q = " << *q << endl;

  // b)
  // Vi følger sekvensen steg for steg:
  cout << endl << "b)" << endl;

  *p = 7; // skriver gjennom p, altså i = 7
  cout << "etter *p = 7:      i = " << i << ", j = " << j << endl;

  *q += 4; // skriver gjennom q, altså j = 5 + 4 = 9
  cout << "etter *q += 4:     i = " << i << ", j = " << j << endl;

  *q = *p + 1; // j = i + 1 = 8
  cout << "etter *q = *p + 1: i = " << i << ", j = " << j << endl;

  p = q; // her endres pekeren selv, ikke det den peker på. Nå peker begge på j.
  cout << "etter p = q:       p og q peker begge på j" << endl;

  // Derfor blir begge utskriftene like, og i er urørt siden forrige linje.
  cout << *p << " " << *q << endl;
}
