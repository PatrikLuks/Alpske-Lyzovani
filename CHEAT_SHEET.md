# 📋 Cheat Sheet - Rychlý přehled

Tento dokument obsahuje nejdůležitější informace na jedné stránce.

---

## 🎯 Hlavní funkce v jednom pohledu

| Funkce | Účel | Klíčový kód |
|--------|------|-------------|
| `otevriTo()` | Načte soubor | `realloc()` + `strtok()` |
| `naVelkaP()` | Velká písmena | `char - 32` |
| `naSetiny()` | Konverze času | `m*6000 + s*100 + cs` |
| `vyhledej()` | Hledání | `strcmp() == 0` |
| `porovnej()` | Třídění | `return cas1 - cas2` |
| `vypis_soubor()` | Export | `fprintf()` |

---

## 📐 Matematika

### ASCII
```
'a' = 97, 'A' = 65, Rozdíl = 32
```

### Čas
```
1 min = 6000 setin
1 sec = 100 setin
```

### Příklad
```
1:35,68 = 1*6000 + 35*100 + 68 = 9568 setin
```

---

## 🔑 Klíčové znalosti

### Dynamická paměť
```c
ZAVODNIK *arr = malloc(n * sizeof(ZAVODNIK));
arr = realloc(arr, new_n * sizeof(ZAVODNIK));
free(arr);
```

### Struktura
```c
typedef struct { ... } CAS;
CAS cas;
cas.minuty = 1;
```

### Parsing
```c
char *token = strtok(string, " :,");
while (token != NULL) {
    // Zpracuj token
    token = strtok(NULL, " :,");
}
```

### Třídění
```c
qsort(array, count, sizeof(Type), compare_func);

int compare(const void *a, const void *b) {
    Type *x = (Type *)a;
    Type *y = (Type *)b;
    return x->value - y->value;  // Vzestupně
}
```

---

## ⚠️ Časté chyby

| Chyba | Příčina | Řešení |
|-------|---------|--------|
| Segmentation fault | Neallokovaná paměť | Zavolat `malloc()` |
| Buffer overflow | Řetězec moc dlouhý | Použít `strncpy()` |
| Memory leak | Zapomenutý `free()` | Vždy zavolat `free()` |
| Špatné třídění | Opačné znaménko | `return a - b` (vzestupně) |
| NULL pointer | Neinicializovaný ukazatel | `= NULL` na začátku |

---

## 📁 Struktura projektu

```
kombinace/
├── main.c                              ← Originální kód
├── main_KOMENTOVANY.c                  ← S detailními komentáři
├── README.md                           ← Hlavní dokumentace
├── POZNAMKY.md                         ← Detailní poznámky
├── KONCEPTY.md                         ← Učební koncepty
├── NAVOD.md                            ← Krok-za-krokem návod
├── CHEAT_SHEET.md                      ← Tento soubor
├── cmake-build-debug/
│   ├── kombinace                       ← Zkompilovaný program
│   ├── startovni_listina_kombinace_zeny.txt
│   └── vysledkova_listina_kombinace_zeny.txt
└── CMakeLists.txt
```

---

## 🚀 Rychlý start

### 1. Kompilace
```bash
cd cmake-build-debug
gcc -Wall -Wextra -std=c11 -o kombinace ../main.c
```

### 2. Spuštění
```bash
./kombinace
```

### 3. Výsledky
```bash
cat vysledkova_listina_kombinace_zeny.txt
```

---

## 🧠 Mentální model

```
VSTUP (soubor)
    ↓
otevriTo() - Načtení + Parsing + Alokace
    ↓
naVelkaP() - Transformace (10x)
    ↓
vypis() - Výstup startovní listiny
    ↓
vyhledej() - Demo: hledání LEDECKA
    ↓
qsort() - Třídění podle výkonu
    ↓
Výstup výsledkové listiny
    ↓
vypis_soubor() - Zápis do souboru
    ↓
free() - Uvolnění paměti
    ↓
VÝSTUP (soubor + terminál)
```

---

## 📊 Vstupní/Výstupní formáty

### Vstup
```
1 Katharina Huberova AUT 1:35,68 53,11
```
Pole: `startovní# jméno příjmení kód sjezd slalom`

### Výstup
```
  1.   Michelle        GISINOVA    CHE    1:33,42   52,25    2:25,67  00,00
```
Pole: `pořadí jméno příjmení kód sjezd slalom celkový ztráta`

---

## 🎯 Kontrolní body

```
┌─ Načtení ─────────────┐
│ ✓ Soubor se otevřel   │
│ ✓ Paměť alokována     │
│ ✓ Data parsována      │
│ ✓ 10 řádků načteno    │
└───────────────────────┘

┌─ Transformace ────────┐
│ ✓ Příjmení → VELKÉ    │
└───────────────────────┘

┌─ Výstup ──────────────┐
│ ✓ Startovní listina   │
│ ✓ Vyhledávání works   │
│ ✓ Řazení OK           │
│ ✓ Výsledková listina  │
│ ✓ Soubor vytvořen     │
└───────────────────────┘

┌─ Cleanup ─────────────┐
│ ✓ Paměť uvolněna      │
│ ✓ Žádné chyby         │
└───────────────────────┘
```

---

## 💾 Klíčové prvky kódu

### Alokace na řádek
```c
while (fgets(line, MAX, file) != NULL) {
    tmp = realloc(zavodnik, (count+1) * sizeof(ZAVODNIK));
    zavodnik = tmp;
    // Parsování...
    count++;
}
```

### Vyhledávání
```c
for (int i = 0; i < n; i++) {
    if (strcmp(zavodnik[i].prijmeni, hledane) == 0) {
        return i;
    }
}
return -1;
```

### Třídění
```c
int porovnej(const void *a, const void *b) {
    ZAVODNIK *z1 = (ZAVODNIK *)a;
    ZAVODNIK *z2 = (ZAVODNIK *)b;
    return soucetCasu(z1->sjezd, z1->slalom) -
           soucetCasu(z2->sjezd, z2->slalom);
}
qsort(zavodnik, pocet, sizeof(ZAVODNIK), porovnej);
```

---

## 📚 Standardní knihovny

```c
#include <stdio.h>      // printf, scanf, file I/O
#include <stdlib.h>     // malloc, free, qsort, atoi
#include <string.h>     // strcmp, strcpy, strlen, strtok
```

---

## 🔗 Vztahy mezi funkcemi

```
main()
├── otevriTo()           (načtení)
│   ├── malloc()
│   ├── realloc()
│   ├── strtok()
│   ├── atoi()
│   ├── strcpy()
│   └── free() [na chybu]
│
├── naVelkaP() × 10      (transformace)
│
├── vypis()              (výstup 1)
│
├── vyhledej()           (hledání)
│   └── strcmp()
│
├── qsort()              (třídění)
│   └── porovnej()
│       ├── soucetCasu()
│       │   └── naSetiny()
│
├── [Výpis smyčka]       (výstup 2)
│   └── soucetCasu()
│
├── vypis_soubor()       (export)
│   ├── fopen()
│   ├── fprintf()
│   └── fclose()
│
└── free()               (cleanup)
```

---

## 🏆 Očekávané výsledky

### Top 3 závodnice
1. Michelle Gisinova (CHE) - 2:25,67 🥇
2. Wendy Holdenerova (CHE) - 2:26,72 🥈
3. Frederica Brignoneova (FRA) - 2:27,52 🥉

### Hledaná osoba
- Jméno: LEDECKA
- Křestní: Ester
- Startovní číslo: 2
- Čas: 2:28,32

---

## ✔️ Finální checklist

- [ ] Všechny funkce implementovány
- [ ] Kód se kompiluje bez varování
- [ ] Všechny testy projdou
- [ ] Paměť je správně spravována
- [ ] Výstup odpovídá specifikaci
- [ ] Kód je komentován

---

**Poslední aktualizace:** 19. října 2025
