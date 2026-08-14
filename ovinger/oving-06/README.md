## Øving 6: funksjonsobjekter og en enkel web-server

Frist 09.10.2026.

| Fil | Hva den svarer på |
|-----|-------------------|
| `oppgave1.cpp` | oppgave 1, `ChessBoardPrint` med lambdaer og `after_piece_move` |
| `oppgave2.cpp` | oppgave 2, web-server på port 8080 |

Oppgave 2 sier "ta utgangspunkt i `example6`". Fila her bruker ikke det eksempelet, den er skrevet rett mot POSIX-sockets slik at den bygger uten eksterne bibliotek. Struktur og API-kall avviker derfor fra kursets eksempel. Bygges bare på UNIX.

Test av serveren:

```
./build/ovinger/oving-06/oving06_oppgave2
curl -i http://localhost:8080/
curl -i http://localhost:8080/en_side
curl -i http://localhost:8080/finnes_ikke
```

Det som er verdt å merke seg:

- `ChessBoard` eier noen `std::function`-medlemmer og kaller dem når noe skjer. Den vet ikke hva som ligger i dem. Det er det som gjør at all `cout` kan flyttes ut.
- En tom `std::function` kaster hvis du kaller den, så alle kall står bak `if (callback)`.
- Lambdaen for `after_piece_move` fanger `this`, fordi den må nå `print_board()`. De andre fanger ingenting, siden de får alt de trenger som argument. Fang minst mulig.
- I HTTP må `Content-Length` stemme med kroppen, ellers blir nettleseren stående og vente på data som aldri kommer.
