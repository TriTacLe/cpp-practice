## Øving 1: enkel C++

Frist 04.09.2026.

Les inn fem temperaturer og tell hvor mange som er under 10, mellom 10 og 20 medregnet begge, og over 20.

| Fil | Hva den svarer på |
|-----|-------------------|
| `a_uten_tabell.cpp` | a) uten tabell og uten egne funksjoner, alt skjer i løkka i `main` |
| `b_med_tabell.cpp` | b) leser fra `temperaturer.txt` inn i en tabell, med `read_temperatures` deklarert før `main` og definert etter |
| `temperaturer.txt` | testdata, ett tall per linje |

Kjør:

```
./build/ovinger/oving-01/oving01a
./build/ovinger/oving-01/oving01b
```

Det som er verdt å merke seg:

- I a) er poenget at du ikke får lov til å lagre tallene. Du må klassifisere hver temperatur med en gang du har lest den, ellers er den borte.
- I b) er prototypen før `main` det som gjør at `main` kan kalle funksjonen selv om definisjonen står lenger nede. Kompilatoren leser fila ovenfra og ned og må vite signaturen på forhånd.
- Sjekk alltid at fila faktisk ble åpnet. `ifstream` sier ikke fra av seg selv, den bare gir deg null verdier.
