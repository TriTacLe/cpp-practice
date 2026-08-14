// Øving 7, oppgave 2: klassen Set, en mengde heltall.
//
// Oppgaven krever at operasjonene er konstruktører eller operatorer, så:
//
//   Set()                      tom mengde
//   operator+=(int)            legg inn ett tall, gjør ingenting hvis det finnes
//   operator+(const Set &)     union
//   operator=(const Set &)     sett en mengde lik en annen
//   operator<<                 utskrift, ikke-medlem fordi venstre operand er ostream
//
// Rekkefølgen på elementene er ikke definert i en mengde. Vi tar vare på
// innsettingsrekkefølgen fordi det er enklest, ikke fordi den betyr noe.

#ifndef SET_HPP
#define SET_HPP

#include <algorithm>
#include <iostream>
#include <vector>

class Set {
public:
  /// Ny, tom mengde.
  Set() {}

  /// Kopikonstruktør. Den måtte skrives fordi vi selv skriver operator=
  /// lenger nede. Skriver du én av kopikonstruktør, operator= og destruktor,
  /// bør du tenke gjennom alle tre. Gjør du det ikke, advarer kompilatoren
  /// med -Wdeprecated-copy.
  Set(const Set &other) : numbers(other.numbers) {}

  /// Legger inn et tall. Finnes det fra før, skjer ingenting. Det er nettopp
  /// dette som skiller en mengde fra en vanlig liste.
  Set &operator+=(int number) {
    if (!contains(number))
      numbers.push_back(number);
    return *this;
  }

  /// Union. Lager en ny mengde, og lar operator+= ta seg av duplikatene.
  Set operator+(const Set &other) const {
    Set result = *this;
    for (int number : other.numbers)
      result += number;
    return result;
  }

  /// Tilordning. Kompilatoren ville laget en identisk en selv, men oppgaven
  /// ber om den. Selvtilordningssjekken er vanen som redder deg den dagen
  /// klassen får en peker som datamedlem.
  Set &operator=(const Set &other) {
    if (this != &other)
      numbers = other.numbers;
    return *this;
  }

  bool contains(int number) const {
    return std::find(numbers.begin(), numbers.end(), number) != numbers.end();
  }

  friend std::ostream &operator<<(std::ostream &out, const Set &set) {
    out << "{";
    for (size_t i = 0; i < set.numbers.size(); i++) {
      if (i > 0)
        out << ", ";
      out << set.numbers[i];
    }
    out << "}";
    return out;
  }

private:
  std::vector<int> numbers;
};

#endif
