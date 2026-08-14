## Øving 2: pekere og referanser

Frist 11.09.2026.

| Fil | Hva den svarer på |
|-----|-------------------|
| `oppgave1.cpp` | a) skriv ut adresser og innhold, b) følg sekvensen `*p = 7` til `p = q` |
| `TEORI.md` | oppgave 2 og 3, som er reine teorispørsmål |
| `oppgave4.cpp` | oppgave 4, syntaksfeilene forklart i kommentar øverst, rettet kode under |
| `oppgave5.cpp` | oppgave 5, peker og referanse til samme variabel, tre måter å tilordne på |
| `oppgave6.cpp` | oppgave 6, `find_sum` over deler av en tabell |

Det som er verdt å merke seg:

- `*p = 7` endrer det p peker på. `p = q` endrer p selv. Det er hele forskjellen, og det er den folk roter med.
- En referanse må bindes når den lages og kan aldri bindes om. En peker kan flyttes så mye du vil.
- `table + 10` gir en peker ti elementer lenger ut. Det er derfor `find_sum` kan brukes på hvilken som helst del av tabellen uten at funksjonen vet noe om det.
