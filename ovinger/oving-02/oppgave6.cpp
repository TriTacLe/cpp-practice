// Øving 2, oppgave 6: summer deler av en tabell gjennom en peker.
//
// Poenget med signaturen int find_sum(const int *table, int length) er at
// funksjonen ikke vet noe om hvor tabellen begynner eller slutter. Den ser
// bare "start her, ta så mange". Derfor kan samme funksjon summere de ti
// første, de fem neste og de fem siste, bare ved å flytte startpekeren.

#include <iostream>

using namespace std;

int find_sum(const int *table, int length) {
  int sum = 0;
  for (int i = 0; i < length; i++)
    sum += table[i]; // table[i] er det samme som *(table + i)
  return sum;
}

int main() {
  const int size = 20;
  int table[size];

  for (int i = 0; i < size; i++)
    table[i] = i + 1; // 1, 2, 3, ... 20

  cout << "De 10 første:  " << find_sum(table, 10) << endl;      // 1..10
  cout << "De 5 neste:    " << find_sum(table + 10, 5) << endl;  // 11..15
  cout << "De 5 siste:    " << find_sum(table + 15, 5) << endl;  // 16..20
}
