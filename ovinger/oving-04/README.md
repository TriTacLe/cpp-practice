## Øving 4: konteinere, auto og lambda

Frist 25.09.2026.

| Fil | Hva den svarer på |
|-----|-------------------|
| `oppgave1.cpp` | oppgave 1, `front`, `back`, `emplace` og `find` på en `vector<double>` |
| `oppgave2.cpp` | oppgave 2, gtkmm-vindu som slår sammen fornavn og etternavn |

Oppgave 2 sier "ta utgangspunkt i `gitlab.com/ntnu-iini4003/gtkmm-example`. Fila her bruker ikke det repoet, den er skrevet rett mot gtkmm-3.0, så oppsett og navn kan avvike fra kursets eksempel. API-kallene er de samme.

Bygging av oppgave 2 krever gtkmm-3.0 via pkg-config. CMake hopper over den hvis biblioteket ikke finnes, slik at resten av repoet fortsatt bygger.

Det som er verdt å merke seg:

- `emplace` setter inn foran iteratoren den får, så `begin() + 1` gir innsetting etter første element. Derfor er `front()` uendret etterpå.
- `find` returnerer `end()` når verdien ikke finnes. Det er den eneste måten å oppdage bom på, så `if`-testen er ikke valgfri.
- I gtkmm er sensitiviteten på knappen noe du regner ut på nytt hver gang et felt endres. Derfor kobles `signal_changed()` på begge feltene til samme funksjon.
