## Oppgave 1b: hvordan tolkes `5 - 3 - fraction1 - 7 - fraction2`

Minus er venstreassosiativ, så uttrykket grupperes fra venstre:

```
((((5 - 3) - fraction1) - 7) - fraction2)
```

Kompilatoren velger operator for ett og ett steg, ut fra typene på de to operandene i det steget:

| Steg | Uttrykk | Typer | Hvilken operator |
|------|---------|-------|------------------|
| 1 | `5 - 3` | `int - int` | innebygd heltallssubtraksjon, ingen av våre funksjoner |
| 2 | `2 - fraction1` | `int - Fraction` | ikke-medlemsfunksjonen `operator-(int, const Fraction &)` |
| 3 | `(...) - 7` | `Fraction - int` | medlemsfunksjonen `Fraction::operator-(int)` |
| 4 | `(...) - fraction2` | `Fraction - Fraction` | medlemsfunksjonen `Fraction::operator-(const Fraction &)` |

Poenget: steg 2 er det eneste som ikke kan være en medlemsfunksjon. En medlemsfunksjon kalles alltid på venstre operand, og der er venstre operand en `int`. Man kan ikke legge medlemmer til en innebygd type, så funksjonen må ligge utenfor klassen.

Steg 1 er verdt å merke seg: `5 - 3` regnes ut som vanlig heltallsaritmetikk før noen `Fraction` er involvert. Klassen ser bare tallet 2.

Regnestykket med `fraction1 = 1/2` og `fraction2 = 2/3`:

```
5 - 3        = 2
2 - 1/2      = 3/2
3/2 - 7      = -11/2
-11/2 - 2/3  = -37/6
```
