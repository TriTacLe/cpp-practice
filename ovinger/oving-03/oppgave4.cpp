// Øving 3, oppgave 4: øvelse i std::string, punkt a til h.

#include <iostream>
#include <string>

using namespace std;

int main() {
  // a) les inn tre ord
  string word1, word2, word3;
  cout << "Skriv tre ord: ";
  cin >> word1 >> word2 >> word3;

  // b) skjøt sammen med mellomrom og punktum til slutt.
  // operator+ på string lager en ny streng.
  string sentence = word1 + " " + word2 + " " + word3 + ".";
  cout << "Setning: " << sentence << endl;

  // c) lengder. size() og length() er det samme.
  cout << "Lengder: " << word1.size() << " " << word2.size() << " " << word3.size()
       << ", hele setningen: " << sentence.size() << endl;

  // d) kopi. string kopieres med vanlig tilordning, ingen peker involvert.
  string sentence2 = sentence;

  // e) bytt tegn 10 til 12 med x. Sjekk at posisjonene finnes først, ellers
  // kaster replace out_of_range.
  if (sentence2.size() > 12)
    sentence2.replace(10, 3, "xxx");
  else
    cout << "Setningen er for kort til å bytte tegn 10-12" << endl;
  cout << "sentence:  " << sentence << endl;
  cout << "sentence2: " << sentence2 << endl;

  // f) de fem første tegnene
  if (sentence.size() >= 5) {
    string sentence_start = sentence.substr(0, 5);
    cout << "sentence:       " << sentence << endl;
    cout << "sentence_start: " << sentence_start << endl;
  }
  else
    cout << "Setningen er kortere enn 5 tegn" << endl;

  // g) inneholder setningen "hallo"? find returnerer string::npos hvis ikke.
  if (sentence.find("hallo") != string::npos)
    cout << "Setningen inneholder hallo" << endl;
  else
    cout << "Setningen inneholder ikke hallo" << endl;

  // h) alle forekomster av "er". Vi søker videre fra posisjonen etter forrige
  // treff, ellers finner vi det samme treffet om og om igjen.
  int count = 0;
  for (size_t pos = sentence.find("er"); pos != string::npos; pos = sentence.find("er", pos + 1)) {
    cout << "Fant er på posisjon " << pos << endl;
    count++;
  }
  cout << "Antall forekomster av er: " << count << endl;
}
