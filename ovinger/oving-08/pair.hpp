// Øving 8, oppgave 2: template-klasse for par.
//
// Forutsetninger klassen gjør på typene som settes inn:
//
//   1. operator+ finnes for First + First og for Second + Second, og
//      resultatet kan lagres i samme type. Ellers virker ikke operator+.
//   2. first og second kan legges sammen med hverandre, altså at det finnes
//      en operator+ for First + Second. Det er den summen operator>
//      sammenligner.
//   3. operator> finnes for typen den summen får.
//   4. begge typene kan kopieres.
//
// For Pair<double, int> holder alt dette av seg selv: double + int gir double
// gjennom vanlig type-forfremmelse.

#ifndef PAIR_HPP
#define PAIR_HPP

template <typename First, typename Second>
class Pair {
public:
  First first;
  Second second;

  Pair(First first, Second second) : first(first), second(second) {}

  /// Elementvis summering.
  Pair operator+(const Pair &other) const {
    return Pair(first + other.first, second + other.second);
  }

  /// Sammenligner summen av elementene i hvert par.
  bool operator>(const Pair &other) const {
    return (first + second) > (other.first + other.second);
  }
};

#endif
