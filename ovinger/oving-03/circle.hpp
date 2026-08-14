// Øving 3, oppgave 1: rettet versjon av klassen Circle.
//
// Feilene i originalen, i rekkefølge:
//
//   circle(double radius_);
//     Konstruktøren må hete nøyaktig det samme som klassen, altså Circle.
//
//   int get_area() const;
//     Arealet er ikke et heltall. Returtypen bør være double, ellers kuttes
//     desimalene bort uten at kompilatoren sier fra.
//
//   private double radius;
//     private er en aksessmodifikator og skal ha kolon: "private:".
//
//   }
//     Klassedefinisjonen må avsluttes med semikolon: "};".
//
//   public Circle::Circle(...)
//     public skrives ikke på definisjoner utenfor klassen.
//
//   : radius_(radius)
//     Initialiseringslisten er snudd. Det er medlemsvariabelen som skal
//     initialiseres fra parameteren: radius(radius_).
//
//   int Circle::get_area() { ... }
//     Mangler const. Definisjonen må matche erklæringen nøyaktig, ellers er
//     det en helt ny funksjon som ikke overstyrer noe.
//
//   Circle::get_circumference() const { ... }
//     Mangler returtype.
//
//   circumference = 2.0 * pi * radius;
//     circumference er aldri deklarert.

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

const double pi = 3.141592;

class Circle {
public:
  Circle(double radius_);
  double get_area() const;
  double get_circumference() const;

private:
  double radius;
};

// Implementasjon av klassen Circle

// Medlemsvariabelen radius initialiseres fra parameteren radius_.
inline Circle::Circle(double radius_) : radius(radius_) {}

inline double Circle::get_area() const {
  return pi * radius * radius;
}

inline double Circle::get_circumference() const {
  double circumference = 2.0 * pi * radius;
  return circumference;
}

#endif
