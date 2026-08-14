## Øving 3: objektorientert programmering

Frist 18.09.2026.

| Fil | Hva den svarer på |
|-----|-------------------|
| `circle.hpp` | oppgave 1, rettet `Circle` med alle feilene forklart øverst |
| `oppgave2.cpp` | oppgave 2, klientprogrammet med hullene fylt ut |
| `commodity.hpp` | oppgave 3, klassen `Commodity` |
| `oppgave3.cpp` | oppgave 3, testklienten fra oppgaveteksten |
| `oppgave4.cpp` | oppgave 4, `std::string` punkt a til h |

Det som er verdt å merke seg:

- Definisjonen utenfor klassen må matche erklæringen nøyaktig, `const` inkludert. Gjør den ikke det, er det en ny funksjon, ikke en implementasjon av den gamle.
- Initialiseringslista skriver medlemsvariabelen, ikke parameteren: `radius(radius_)`, ikke omvendt.
- `Commodity` lagrer bare prisen uten moms. Alt annet regnes ut. Én sannhet i objektet betyr at `set_price` ikke kan etterlate noe inkonsistent.
- `find` på `std::string` returnerer `string::npos` når den ikke finner noe, ikke -1. Sammenlign alltid mot `string::npos`.
- `replace` og `substr` kaster `out_of_range` på ugyldige posisjoner, så sjekk lengden først.
