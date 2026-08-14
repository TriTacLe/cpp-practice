// Exercise 1 b. Read temperatures from file into an array, then count.
// The task requires the prototype before main and the definition after it.

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

// An array parameter is really a pointer to the first element,
// so the length has to be passed separately.
void read_temperatures(double temperatures[], int length);

int main() {
  const int length = 5;
  double temperatures[length];

  read_temperatures(temperatures, length);

  int below_10 = 0;
  int between_10_and_20 = 0;
  int above_20 = 0;

  for (int i = 0; i < length; i++) {
    if (temperatures[i] < 10.0)
      below_10++;
    else if (temperatures[i] <= 20.0)
      between_10_and_20++;
    else
      above_20++;
  }

  cout << "Antall under 10 er " << below_10 << endl;
  cout << "Antall mellom 10 og 20 er " << between_10_and_20 << endl;
  cout << "Antall over 20 er " << above_20 << endl;
}

void read_temperatures(double temperatures[], int length) {
  ifstream file("temperatures.txt");

  if (!file) {
    cerr << "temperatures.txt not found in the working directory" << endl;
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < length; i++) {
    if (!(file >> temperatures[i])) {
      cerr << "file holds fewer than " << length << " temperatures" << endl;
      exit(EXIT_FAILURE);
    }
  }

  file.close();
}
