// Øving 9: STL-algoritmer med lambdauttrykk.
//
// v1 og v2 er de samme vektorene som i leksjonen.
//
// Lambdaen er bare en funksjon uten navn, skrevet der den brukes. [] er
// fangstlisten, altså hva fra omgivelsene lambdaen får se. Her fanger vi
// ingenting i a) og c), men i b) fanger vi toleransen med [tolerance].

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

ostream &operator<<(ostream &out, const vector<int> &table) {
  for (auto &e : table)
    out << e << " ";
  return out;
}

int main() {
  vector<int> v1 = {3, 3, 12, 14, 17, 25, 30};
  vector<int> v2 = {2, 3, 12, 14, 24};

  cout << "v1: " << v1 << endl;
  cout << "v2: " << v2 << endl
       << endl;

  // a) første element i v1 som er større enn 15.
  // find_if tar et predikat, altså en funksjon som svarer true eller false på
  // ett element. Som find returnerer den end() hvis ingen passer.
  auto pos = find_if(v1.begin(), v1.end(), [](int value) { return value > 15; });
  if (pos != v1.end())
    cout << "a) første element større enn 15: " << *pos
         << " på indeks " << (pos - v1.begin()) << endl;
  else
    cout << "a) ingen elementer større enn 15" << endl;

  // b) "omtrent lik" med toleranse 2.
  // equal går gjennom første intervall og sammenligner element for element mot
  // andre sekvens. Predikatet tar ett element fra hver.
  const int tolerance = 2;
  auto about_equal = [tolerance](int a, int b) { return abs(a - b) <= tolerance; };

  // Intervallet [v1.begin(), v1.begin() + 5) er {3, 3, 12, 14, 17} mot
  // v2 {2, 3, 12, 14, 24}. Siste par er 17 mot 24, forskjell 7, altså ulike.
  const bool equal5 = equal(v1.begin(), v1.begin() + 5, v2.begin(), about_equal);
  cout << "b) [begin, begin+5) omtrent lik v2: " << (equal5 ? "ja" : "nei") << endl;

  // Intervallet [v1.begin(), v1.begin() + 4) er {3, 3, 12, 14} mot de fire
  // første i v2 {2, 3, 12, 14}. Største forskjell er 1, altså like.
  const bool equal4 = equal(v1.begin(), v1.begin() + 4, v2.begin(), about_equal);
  cout << "b) [begin, begin+4) omtrent lik v2: " << (equal4 ? "ja" : "nei") << endl;

  // c) erstatt alle oddetall med 100.
  // replace_copy_if skriver til en ny sekvens i stedet for å endre den gamle,
  // så målet må ha plass fra før. Derfor resize til samme størrelse som v1.
  vector<int> v3(v1.size());
  replace_copy_if(v1.begin(), v1.end(), v3.begin(),
                  [](int value) { return value % 2 != 0; }, 100);

  cout << endl;
  cout << "c) v1 uendret: " << v1 << endl;
  cout << "c) v3 kopi:    " << v3 << endl;
}
