// Øving 3, oppgave 3: klassen Commodity.
//
// Prisen som lagres er alltid uten moms. Alt annet regnes ut fra den, slik at
// det bare finnes én sannhet i objektet. Momsen ligger som global konstant,
// på samme måte som pi i oppgave 1.

#ifndef COMMODITY_HPP
#define COMMODITY_HPP

#include <string>

const double sales_tax = 0.25; // 25 prosent merverdiavgift

class Commodity {
public:
  Commodity(const std::string &name, int id, double price);

  std::string get_name() const;
  int get_id() const;

  // Uten argument: prisen for én enhet, uten moms.
  double get_price() const;
  // Med argument: prisen for så mange enheter, uten moms.
  double get_price(double quantity) const;
  // Samme, men med moms lagt på.
  double get_price_with_sales_tax(double quantity) const;

  void set_price(double price);

private:
  std::string name;
  int id;
  double price; // alltid uten moms
};

inline Commodity::Commodity(const std::string &name, int id, double price)
    : name(name), id(id), price(price) {}

inline std::string Commodity::get_name() const {
  return name;
}

inline int Commodity::get_id() const {
  return id;
}

inline double Commodity::get_price() const {
  return price;
}

inline double Commodity::get_price(double quantity) const {
  return price * quantity;
}

inline double Commodity::get_price_with_sales_tax(double quantity) const {
  // Gjenbruker overlastingen over i stedet for å gjenta ganginga.
  return get_price(quantity) * (1.0 + sales_tax);
}

inline void Commodity::set_price(double price) {
  this->price = price; // this-> skiller medlemmet fra parameteren
}

#endif
