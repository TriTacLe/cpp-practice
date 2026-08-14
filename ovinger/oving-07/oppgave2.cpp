// Øving 7, oppgave 2: testprogram for Set.

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

  // Eksempelet fra oppgaveteksten: {1, 4, 3} union {4, 7} er {1, 4, 3, 7}.
  Set union_set = set1 + set2;
  cout << "union: " << union_set << endl;

  // Tallet finnes fra før, så ingenting skjer.
  set1 += 4;
  cout << "set1 etter å legge inn 4 en gang til: " << set1 << endl;

  Set set3;
  set3 = union_set;
  cout << "set3 satt lik union: " << set3 << endl;

  cout << "inneholder set3 7? " << (set3.contains(7) ? "ja" : "nei") << endl;
  cout << "inneholder set3 9? " << (set3.contains(9) ? "ja" : "nei") << endl;
}
