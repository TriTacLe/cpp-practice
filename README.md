# INFT2503 C++ for programmerere

Referansekode til de ti øvingene i INFT2503, høst 2026.

## Hva dette er

Dette er **ikke** innleveringer. Det er arbeidseksempler jeg leser ved siden av oppgaveteksten
for å se hvordan et mønster ser ut i praksis. Hver øving har:

- `README.md` med hva oppgaven spør om, hvilken fil som svarer på hva, og hva som er verdt å merke seg
- kildekode med forklaringene i kommentarene, kompilert rent med `-Wall -Wextra`
- `TEORI.md` der oppgaven har reine teorispørsmål (øving 2 og 7)

Egne innleveringer skrives fra bunn i et separat prosjekt.

Tre steder er koden skrevet uten kursets eget utgangspunkt, fordi de eksemplene ligger i
gitlab-repoer som ikke er med her. Det står i hver enkelt fil:

- øving 4 oppgave 2 er skrevet rett mot gtkmm-3.0, ikke mot `gtkmm-example`
- øving 6 oppgave 2 er skrevet rett mot POSIX-sockets, ikke mot `example6`
- øving 10 har ingen kode. Oppgaven bygger på `ntnu-iini4003/game`, og oppgaveteksten sier selv at
  det ikke finnes noe løsningsforslag. Mappa inneholder bare en plan.

## Bygg

```sh
cmake -B build
cmake --build build
```

Kjørbare filer havner i `build/ovinger/oving-NN/`.

Øving 4 oppgave 2 krever gtkmm-3.0. Den bygges bare hvis `pkg-config` finner biblioteket.

## Frister

| Øving | Tema | Frist |
|-------|------|-------|
| 1 | Grunnleggende C++ | 2026-09-04 |
| 2 | Pekere og referanser | 2026-09-11 |
| 3 | Objektorientert programmering | 2026-09-18 |
| 4 | Konteinere, auto og lambda | 2026-09-25 |
| 5 | Liv og død, smarte pekere, polymorfi | 2026-10-02 |
| 6 | Funksjonsobjekter og trådprogrammering | 2026-10-09 |
| 7 | Operator overloading | 2026-10-16 |
| 8 | Templates | 2026-10-23 |
| 9 | STL-algoritmer | 2026-10-30 |
| 10 | Tredjeparts biblioteker | 2026-11-06 |

Alle frister kl 23:59 norsk tid. 8 av 10 må være godkjent for eksamensrett.
Eksamen er hjemmeeksamen 15.12.2026, uttak 09:00, innlevering 13:00, i Inspera.

## Kilder

- Oppgavetekst og leksjoner: <https://folk.ntnu.no/eidheim/c++/>
- Emnebeskrivelse: <https://www.ntnu.no/studier/emner/INFT2503>
