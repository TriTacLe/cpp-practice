## Oppgave 2

```cpp
char *text;
strcpy(text, "Hallo");
```

`text` er en peker som aldri har fått noen verdi. Den peker på en tilfeldig adresse, eller på null. `strcpy` skriver seks tegn dit uten å spørre om noe.

Hva som skjer er ikke definert. Typisk enten segmentation fault med en gang, eller at programmet overskriver noe helt annet og krasjer et sted som ser helt urelatert ut. Det siste er verst, fordi feilen dukker opp langt fra der den ble laget.

`strcpy` kan ikke vite noe om plassen. Den får bare en adresse og kopierer til den treffer nulltegnet i kilden. Det er alltid den som skriver koden som må sørge for at det finnes plass.

Riktig er enten en tabell med kjent størrelse:

```cpp
char text[6]; // "Hallo" er 5 tegn pluss nulltegn
strcpy(text, "Hallo");
```

eller, i C++, bare `std::string text = "Hallo";` som ordner plassen selv.

## Oppgave 3

```cpp
char text[5];
strcpy(text, "Hallo");
```

Her finnes det plass, men for lite. "Hallo" er fem tegn, og i tillegg kommer nulltegnet som avslutter strengen. Det trengs altså seks bytes, og det er bare fem.

Nulltegnet havner rett etter tabellen, altså på minne som tilhører noe annet. Det er en bufferoverflyt på én byte. Konsekvensen avhenger helt av hva som tilfeldigvis ligger der: kanskje ingenting synlig, kanskje en variabel som får rar verdi, kanskje krasj. Kompilatoren sier ikke fra, og programmet kan godt kjøre riktig i mange runder før det slutter å gjøre det.

Dette er grunnen til at `strcpy` regnes som farlig og at C++ heller bruker `std::string`.
