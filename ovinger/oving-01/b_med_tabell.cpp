// Øving 1 b): les temperaturene fra fil inn i en tabell, og tell opp etterpå.
//
// Oppgaven er spesifikk på strukturen: prototypen skal stå foran main(), og
// definisjonen etter main(). Det er det eneste stedet rekkefølgen betyr noe,
// og grunnen er at kompilatoren bare trenger deklarasjonen for å sjekke
// kallet, mens lenkeren finner definisjonen senere.

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

// Deklarasjon (prototype). Tabellparameteren er egentlig en peker til
// første element, derfor må lengden sendes med som eget argument.
void read_temperatures(double temperatures[], int length);

int main() {
  const int length = 5;
  double temperatures[length];

  read_temperatures(temperatures, length);

  int below_10 = 0;
  int between_10_and_20 = 0;
  int above_20 = 0;

  for (int i = 0; i < length; i++) {
    if (temperatures[i] < 10.0)
      below_10++;
    else if (temperatures[i] <= 20.0)
      between_10_and_20++;
    else
      above_20++;
  }

  cout << "Antall under 10 er " << below_10 << endl;
  cout << "Antall mellom 10 og 20 er " << between_10_and_20 << endl;
  cout << "Antall over 20 er " << above_20 << endl;
}

// Definisjon. Åpner filen, leser inn i tabellen, lukker filen.
void read_temperatures(double temperatures[], int length) {
  ifstream file("temperaturer.txt");

  if (!file) {
    cerr << "Fant ikke temperaturer.txt i katalogen programmet kjorer fra." << endl;
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < length; i++) {
    if (!(file >> temperatures[i])) {
      cerr << "Filen inneholder faerre enn " << length << " temperaturer." << endl;
      exit(EXIT_FAILURE);
    }
  }

  file.close();
}
