## Øving 7: operatoroverlasting

Frist 16.10.2026.

| Fil | Hva den svarer på |
|-----|-------------------|
| `fraction.hpp` | oppgave 1a, `Fraction` med `f - 5` og `5 - f` |
| `oppgave1.cpp` | oppgave 1a, testprogram |
| `TEORI.md` | oppgave 1b, hvordan `5 - 3 - fraction1 - 7 - fraction2` tolkes |
| `set.hpp` | oppgave 2, klassen `Set` |
| `oppgave2.cpp` | oppgave 2, testprogram |

`fraction.hpp` er en trimmet `Fraction` med bare det oppgaven trenger. Den fullstendige klassen fra leksjonen ligger i kursets eget eksempelrepo. Jobber du videre fra leksjonskoden, bytter du bare ut fila.

Det som er verdt å merke seg:

- `5 - fraction1` kan ikke være en medlemsfunksjon. En medlemsfunksjon kalles på venstre operand, og venstre operand er en `int`. Innebygde typer kan ikke få nye medlemmer.
- `Set` bruker `operator+=` til innsetting og `operator+` til union, fordi oppgaven krever at operasjonene er konstruktører eller operatorer.
- `operator<<` for utskrift må ligge utenfor klassen av samme grunn som over: venstre operand er en `ostream`.
- Selvtilordningssjekken i `operator=` betyr ingenting her, siden `vector` klarer seg selv. Ta den likevel med som vane, den redder deg den dagen klassen får en peker.
