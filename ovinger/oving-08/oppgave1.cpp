// Øving 8, oppgave 1: funksjonstemplate for likhet, med egen utgave for double.
//
// Hvorfor double trenger sin egen: 0.1 + 0.2 er ikke 0.3 i flyttall. Verdiene
// lagres binært, og 0.1 kan ikke skrives eksakt i binær, like lite som 1/3 kan
// skrives eksakt med desimaler. Et == på beregnede desimaltall svarer derfor
// nesten alltid usant. Løsningen er å spørre om forskjellen er liten nok.
//
// Overlastingen med konkret type vinner alltid over templaten når typene
// passer eksakt. Templaten brukes bare når ingen vanlig funksjon matcher.

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

template <typename Type>
bool equal(Type a, Type b) {
  cout << "  [template-utgaven]" << endl;
  return a == b;
}

// Spesialutgave for double. Dette er en helt vanlig overlasting, ikke en
// template-spesialisering, og det er nok her.
bool equal(double a, double b) {
  cout << "  [double-utgaven]" << endl;
  const double epsilon = 0.00001;
  return fabs(a - b) < epsilon;
}

int main() {
  cout << "int 3 og 3:" << endl;
  cout << "  " << (equal(3, 3) ? "like" : "ulike") << endl;

  cout << "string hei og hei:" << endl;
  cout << "  " << (equal(string("hei"), string("hei")) ? "like" : "ulike") << endl;

  cout << "string hei og hoo:" << endl;
  cout << "  " << (equal(string("hei"), string("hoo")) ? "like" : "ulike") << endl;

  // Klassisk flyttallsfelle. 0.1 + 0.2 blir ikke helt 0.3.
  const double sum = 0.1 + 0.2;
  cout << setprecision(20) << fixed;
  cout << "0.1 + 0.2 = " << sum << endl;
  cout << "0.3       = " << 0.3 << endl;
  cout << defaultfloat << setprecision(6);

  cout << "double 0.1 + 0.2 og 0.3:" << endl;
  cout << "  " << (equal(sum, 0.3) ? "like" : "ulike") << endl;

  cout << "double 1.0 og 1.001:" << endl;
  cout << "  " << (equal(1.0, 1.001) ? "like" : "ulike") << endl;

  // Uten epsilon-utgaven ville dette svart usant:
  cout << "rå sammenligning sum == 0.3: " << ((sum == 0.3) ? "sant" : "usant") << endl;
}
