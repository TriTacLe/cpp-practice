// Øving 2, oppgave 4: finn syntaksfeilene og forklar hver enkelt.
//
// Original programbit:
//
//   int a = 5;
//   int &b;
//   int *c;
//   c = &b;
//   *a = *b + *c;
//   &b = 2;
//
// Feilene, linje for linje:
//
//   int &b;
//     En referanse må bindes til noe når den defineres. Det finnes ingen
//     "tom" referanse slik det finnes en uinitialisert peker. Feilmelding:
//     "declaration of reference variable 'b' requires an initializer".
//
//   c = &b;
//     Var ugyldig så lenge b ikke fantes. Når b er bundet til a, gir &b
//     adressen til a, ikke adressen til en egen referansevariabel. En
//     referanse har ingen egen identitet å ta adressen til.
//
//   *a = *b + *c;
//     a er int, ikke peker, så *a er ulovlig. Det samme gjelder *b, siden b
//     er en referanse til int. Bare c kan dereferereres.
//
//   &b = 2;
//     &b er en adresseverdi, en rverdi. Man kan ikke tilordne til den.
//     Skal man endre verdien, skriver man b = 2, som endrer a.
//
// Under er den rettede versjonen.

#include <iostream>

using namespace std;

int main() {
  int a = 5;
  int &b = a; // referansen må bindes med en gang, her til a
  int *c;
  c = &b; // lovlig nå, og gir adressen til a fordi b er et annet navn på a

  a = b + *c; // a er int, b er int, bare c må dereferereses
  b = 2;      // endrer a gjennom referansen

  cout << "a = " << a << ", b = " << b << ", *c = " << *c << endl;
}
