// Exercise 1 a. No arrays and no own functions allowed, so each temperature
// has to be counted in the same round it is read.

#include <iostream>

using namespace std;

int main() {
  const int length = 5;

  int below_10 = 0;
  int between_10_and_20 = 0;
  int above_20 = 0;

  cout << "Du skal skrive inn " << length << " temperaturer." << endl;

  for (int i = 0; i < length; i++) {
    cout << "Temperatur nr " << i + 1 << ": ";

    double temperature = 0.0;
    cin >> temperature;

    if (temperature < 10.0)
      below_10++;
    else if (temperature <= 20.0)
      between_10_and_20++;
    else
      above_20++;
  }

  cout << "Antall under 10 er " << below_10 << endl;
  cout << "Antall mellom 10 og 20 er " << between_10_and_20 << endl;
  cout << "Antall over 20 er " << above_20 << endl;
}
