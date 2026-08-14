// Øving 1 a): tell opp temperaturer i tre intervaller.
// Begrensning fra oppgaven: ingen tabeller, ingen egne funksjoner.
//
// Fordi vi ikke får lagre verdiene, må hver temperatur behandles ferdig i
// samme runde av løkka som den leses inn. Tellerne er det eneste vi tar med
// oss videre.

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

    // Intervallene i oppgaven: under 10, [10, 20] inklusive, over 20.
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
