// Exercise 3 task 3. The class Commodity.
// The stored price is always without sales tax. Everything else is derived
// from it, so the object only holds one truth.

#ifndef COMMODITY_HPP
#define COMMODITY_HPP

#include <string>

const double sales_tax = 0.25;

class Commodity {
public:
  Commodity(const std::string &name, int id, double price);

  std::string get_name() const;
  int get_id() const;

  // Price for one unit, without sales tax.
  double get_price() const;
  // Price for the given quantity, without sales tax.
  double get_price(double quantity) const;
  // Same, with sales tax added.
  double get_price_with_sales_tax(double quantity) const;

  void set_price(double price);

private:
  std::string name;
  int id;
  double price;
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
  return get_price(quantity) * (1.0 + sales_tax);
}

inline void Commodity::set_price(double price) {
  this->price = price; // this-> separates the member from the parameter
}

#endif
