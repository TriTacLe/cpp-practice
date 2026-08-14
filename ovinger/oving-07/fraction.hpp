// Øving 7, oppgave 1: Fraction med subtraksjon mot int begge veier.
//
// Merk: den fullstendige Fraction fra leksjonen ligger i kursets eget
// eksempelrepo. Denne fila er en trimmet utgave med akkurat det oppgaven
// trenger, skrevet med samme grensesnitt som leksjonen bruker. Bytt den ut
// med din egen Fraction hvis du jobber videre fra leksjonskoden.
//
// Det som er nytt for oppgave a):
//
//   Fraction operator-(int value) const;                 medlem, gir f - 5
//   Fraction operator-(int value, const Fraction &f);    ikke-medlem, gir 5 - f
//
// Den andre kan ikke være medlemsfunksjon. En medlemsfunksjon kalles alltid
// på venstre operand, og venstre operand her er en int. int er ikke en klasse
// og kan ikke få nye medlemmer. Derfor må den ligge utenfor klassen.

#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <cstdlib>
#include <iostream>

class Fraction {
public:
  int numerator;
  int denominator;

  Fraction() : numerator(0), denominator(1) {}
  Fraction(int numerator, int denominator) { set(numerator, denominator); }

  void set(int numerator_, int denominator_ = 1) {
    if (denominator_ == 0) {
      std::cerr << "nevner kan ikke være null" << std::endl;
      std::exit(EXIT_FAILURE);
    }
    numerator = numerator_;
    denominator = denominator_;
    reduce();
  }

  Fraction operator-(const Fraction &other) const {
    return Fraction(numerator * other.denominator - other.numerator * denominator,
                    denominator * other.denominator);
  }

  // a) Fraction minus heltall. Kan godt være medlem, siden venstre operand
  // er en Fraction.
  Fraction operator-(int value) const {
    return *this - Fraction(value, 1);
  }

  Fraction operator-() const {
    return Fraction(-numerator, denominator);
  }

  friend std::ostream &operator<<(std::ostream &out, const Fraction &fraction) {
    out << fraction.numerator << " / " << fraction.denominator;
    return out;
  }

private:
  void reduce() {
    // Negativt fortegn holdes i telleren, slik at 1/-2 og -1/2 skrives likt.
    if (denominator < 0) {
      numerator = -numerator;
      denominator = -denominator;
    }
    int a = std::abs(numerator);
    int b = denominator;
    while (b != 0) { // Euklids algoritme
      const int rest = a % b;
      a = b;
      b = rest;
    }
    if (a > 1) {
      numerator /= a;
      denominator /= a;
    }
  }
};

// a) Heltall minus Fraction. Må ligge utenfor klassen, se kommentaren øverst.
inline Fraction operator-(int value, const Fraction &fraction) {
  return Fraction(value, 1) - fraction;
}

#endif
