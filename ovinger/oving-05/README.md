## Øving 5: liv og død, smarte pekere og polymorfi

Frist 02.10.2026.

| Fil | Hva den svarer på |
|-----|-------------------|
| `oppgave1.cpp` | oppgave 1, `King` og `Knight` fylt ut der det sto `// missing implementations` |
| `oppgave2.cpp` | oppgave 2, tekstutskrift av brettet etter hvert trekk |

`oppgave1` gir nøyaktig den utskriften oppgaveteksten oppgir, verifisert ved kjøring.

Det som er verdt å merke seg:

- `move_piece` vet ingenting om brikketypene. Den kaller `valid_move()` og `type()`, og hver klasse svarer for seg. Legger du til et tårn, rører du ikke `move_piece`.
- `Piece` har virtuell destruktor. Uten den ville `unique_ptr<Piece>` slettet objektet gjennom basetypen og hoppet over subklassens destruktor. `dynamic_cast` krever også at klassen er polymorf.
- `piece_to = move(piece_from)` flytter eierskapet. `unique_ptr` kan ikke kopieres, bare flyttes, og etterpå er `piece_from` tom. Det er nettopp derfor ruta blir ledig av seg selv.
- `valid_move` sjekker at målruta er på brettet. Uten den sjekken indekserer `squares[to_x][to_y]` utenfor vektoren.
