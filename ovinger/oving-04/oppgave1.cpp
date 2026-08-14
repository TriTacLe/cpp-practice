// Øving 4, oppgave 1: vector, front, back, emplace og find.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<double> numbers{1.5, 2.5, 3.5, 4.5, 5.5};

  // front() og back() returnerer referanser til første og siste element.
  // De tar ingen argumenter, og de sjekker ikke om vektoren er tom.
  cout << "front(): " << numbers.front() << endl;
  cout << "back():  " << numbers.back() << endl;

  // emplace() setter inn foran iteratoren den får. begin() + 1 peker på
  // element nummer to, så det nye tallet havner etter det første.
  numbers.emplace(numbers.begin() + 1, 99.9);

  cout << "etter emplace, front(): " << numbers.front() << endl; // fortsatt 1.5
  cout << "hele vektoren:";
  for (auto number : numbers)
    cout << " " << number;
  cout << endl;

  // find() tar start, slutt og søkeverdi. Slutt-iteratoren peker forbi siste
  // element, så intervallet er halvåpent. Returverdien er end() når verdien
  // ikke finnes, og det er den eneste måten å oppdage bom på.
  auto it = find(numbers.begin(), numbers.end(), 3.5);
  if (it != numbers.end())
    cout << "fant " << *it << " på posisjon " << (it - numbers.begin()) << endl;
  else
    cout << "fant ikke 3.5" << endl;

  auto missing = find(numbers.begin(), numbers.end(), 42.0);
  if (missing != numbers.end())
    cout << "fant " << *missing << endl;
  else
    cout << "fant ikke 42" << endl;
}
