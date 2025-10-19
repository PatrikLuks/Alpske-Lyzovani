# 🏂 Alpské lyžování - Kombinace Ženy

Projekt zpracování dat alpského lyžování pro maturitní praktickou prověrku z programování.

---

## 📖 Obsah

- [O projektu](#-o-projektu)
- [Požadavky](#-požadavky)
- [Instalace](#-instalace)
- [Spuštění](#-spuštění)
- [Struktura souboru](#-struktura-souboru)
- [Jak program funguje](#-jak-program-funguje)
- [Vstupy a výstupy](#-vstupy-a-výstupy)
- [Učební cíle](#-učební-cíle)
- [Souborová struktura](#-souborová-struktura)

---

## 📋 O projektu

Tento projekt je **maturitní prověrkou z programování** (2. ročník), jejímž cílem je zvládnout:

✅ Načítání a parsování textových souborů  
✅ Práci s dynamickou alokací paměti  
✅ Práci se strukturami a poli struktur  
✅ Vyhledávání v datech  
✅ Třídění dat pomocí `qsort()`  
✅ Zápis dat do výstupního souboru  

**Téma:** Kombinované závodění v alpském lyžování (sjezd + slalom)

---

## ⚙️ Požadavky

### Hardware
- Počítač s 64 MB volné paměti (minimum)
- Libovolný operační systém (Windows, macOS, Linux)

### Software
- **Kompilátor C:** GCC, Clang nebo MSVC
- **Build systém:** CMake (doporučeno) nebo přímá kompilace
- **Textový editor:** VS Code, CLion, Sublime Text apod.

### Knihovny
Projekt používá pouze **standardní C knihovny** - žádné externí závislosti!

```c
#include <stdio.h>    // I/O operace
#include <stdlib.h>   // Paměť, qsort
#include <string.h>   // Manipulace se řetězci
```

---

## 📥 Instalace

### Varianta 1: Přes CMake (doporučeno)

```bash
# Klonování/stažení projektu
git clone <url-projektu>
cd kombinace

# Vytvoření build adresáře
mkdir build
cd build

# Generování Makefile
cmake ..

# Kompilace
make
```

### Varianta 2: Přímá kompilace s GCC

```bash
cd kombinace
gcc -o kombinace main.c
```

### Varianta 3: Přímá kompilace s Clang

```bash
clang -o kombinace main.c
```

---

## 🚀 Spuštění

### Linux / macOS

```bash
cd cmake-build-debug
./kombinace
```

### Windows (CMD)

```cmd
cd cmake-build-debug
kombinace.exe
```

### Windows (PowerShell)

```powershell
cd cmake-build-debug
.\kombinace.exe
```

---

## 📊 Struktura souboru

### Vstupní soubor: `startovni_listina_kombinace_zeny.txt`

```
1 Katharina Huberova AUT 1:35,68 53,11
2 Ester Ledecka CZE 1:32,43 55,89
3 Michelle Gisinova CHE 1:33,42 52,25
...
```

**Formát:**
```
<num> <jméno> <příjmení> <státní kód> <čas sjezdu> <čas slalomu>
```

- **num:** Startovní číslo (1-N)
- **jméno:** Křestní jméno
- **příjmení:** Příjmení
- **státní kód:** 3-písmenový kód (CHE, AUT, CZE...)
- **čas sjezdu:** Formát `MM:SS,CS` (minuty:sekundy,setiny)
- **čas slalomu:** Formát `SS,CS` (sekundy,setiny)

### Výstupní soubor: `vysledkova_listina_kombinace_zeny.txt`

```
A L P S K E     L Y Z O V A N I  -  K O M B I N A C E   Z E N Y
--------------------------------------------------------------------
poradi   jmeno        prijmeni   stat  sjezd    slalom    celkem    ztrata
--------------------------------------------------------------------
  1.   Michelle        GISINOVA    CHE    1:33,42   52,25    2:25,67  00,00
  2.      Wendy     HOLDENEROVA    CHE    1:33,41   53,31    2:26,72  01,05
...
```

---

## 🔄 Jak program funguje

### Krok 1: Načtení dat

```
┌─────────────────────────┐
│ Otevření vstupního      │
│ souboru (.txt)          │
└──────────┬──────────────┘
           │
           ▼
┌─────────────────────────┐
│ Dynamická alokace       │
│ paměti pro ZAVODNIK[]   │
└──────────┬──────────────┘
           │
           ▼
┌─────────────────────────┐
│ Parsování jednotlivých  │
│ řádků (strtok)          │
└──────────┬──────────────┘
           │
           ▼
┌─────────────────────────┐
│ Zanesení do struktury   │
│ v paměti                │
└─────────────────────────┘
```

### Krok 2: Transformace dat

```
┌─────────────────────────┐
│ Převod příjmení na      │
│ VELKÁ PÍSMENA           │
└─────────────────────────┘
```

### Krok 3: Zpracování a výstup

```
┌─────────────────────────┐         ┌──────────────────────┐
│ Výpis startovní        │ ──────→ │ Terminal (obrazovka) │
│ listiny                │         └──────────────────────┘
└─────────────────────────┘

┌─────────────────────────┐         ┌──────────────────────┐
│ Vyhledávání (příklad)   │ ──────→ │ Terminal (výsledek)  │
└─────────────────────────┘         └──────────────────────┘

┌─────────────────────────┐
│ Řazení podle součtu     │
│ časů (qsort)            │
└──────────┬──────────────┘
           │
           ▼
┌─────────────────────────┐         ┌──────────────────────┐
│ Výpis výsledků          │ ──────→ │ Terminal (seznam)    │
└─────────────────────────┘         └──────────────────────┘

┌─────────────────────────┐         ┌──────────────────────┐
│ Zápis do výstupního     │ ──────→ │ Soubor (.txt)        │
│ souboru                 │         └──────────────────────┘
└─────────────────────────┘

┌─────────────────────────┐
│ Uvolnění paměti (free)  │
└─────────────────────────┘
```

---

## 📥 Vstupy a výstupy

### Vstup
- **Textový soubor** s daty závodnic

### Výstupy
1. **Standardní výstup (terminál)**
   - Startovní listina
   - Výsledek vyhledávání
   - Výsledková listina (seřazená)

2. **Soubor** `vysledkova_listina_kombinace_zeny.txt`
   - Finální výsledková listina s pořadím a ztratou

---

## 🎓 Učební cíle

Po vyřešení tohoto příkladu byste měli umět:

- ✅ **Manipulace se soubory**
  - Otevření a čtení textových souborů
  - Zápis do textových souborů
  - Bezpečné zavření souborů

- ✅ **Parsování dat**
  - Rozdělování řetězců pomocí `strtok()`
  - Převádění řetězců na čísla (`atoi()`)
  - Zpracování strukturovaných dat

- ✅ **Dynamická paměť**
  - Alokace paměti pomocí `malloc()`
  - Realokace pomocí `realloc()`
  - Korektní uvolnění `free()`

- ✅ **Struktury a pole**
  - Definice struktur `typedef struct`
  - Pole struktur
  - Přístup k prvkům (`zavodnik[i].prijmeni`)

- ✅ **Vyhledávání a třídění**
  - Lineární vyhledávání
  - Použití `qsort()` se custom porovnávací funkcí
  - Manipulace s jednotkami (konverze na setiny)

- ✅ **Formátování výstupu**
  - Specifikátory formátu (`%d`, `%s`, `%02d`)
  - Zarovnávání textu v sloupci

---

## 📁 Souborová struktura

```
kombinace/
├── CMakeLists.txt                              # Build konfigurace
├── main.c                                      # Hlavní zdrojový kód
├── README.md                                   # Tento soubor
├── POZNAMKY.md                                 # Detailní poznámky
├── zadani.png                                  # Obrázek s původním zadáním
│
└── cmake-build-debug/                          # Build adresář
    ├── kombinace                               # Zkompilovaný binární soubor
    ├── kombinace.exe                           # Binární soubor (Windows)
    ├── startovni_listina_kombinace_zeny.txt   # Vstupní soubor
    ├── vysledkova_listina_kombinace_zeny.txt  # Výstupní soubor
    ├── CMakeCache.txt
    ├── build.ninja
    └── CMakeFiles/                             # CMake artifacts
```

---

## 🔍 Ověření správnosti

Zkontrolujte:

- [x] Počet výstupních řádků = počet vstupních řádků (10)
- [x] Všechna příjmení jsou v VELKÝCH písmenech
- [x] Vyhledávání LEDECKA vrací Ester s č. 2
- [x] Nejrychlejší je Michelle Gisinova (2:25,67)
- [x] Výstupní soubor je vytvořen bez chyb
- [x] Rozdíl (ztrata) se počítá správně

---

## 🐛 Řešení problémů

### Problém: "Soubor nebyl otevřen"

**Příčina:** Vstupní soubor není v aktuálním adresáři  
**Řešení:** 
```bash
# Ujistěte se, že jste v adresáři cmake-build-debug
cd cmake-build-debug
./kombinace
```

### Problém: Zvláštní znaky v terminálu

**Příčina:** Kódování souboru  
**Řešení:** Zkontrolujte, že editor používá UTF-8 kódování

### Problém: Program padá

**Příčina:** Paměť není správně alokována nebo uvolněna  
**Řešení:** 
- Zkontrolujte `malloc()` a `realloc()` vrátí `NULL` ✓
- Zkontrolujte `free()` na konci programu ✓

---

## 💾 Kompilace s různými kompilátory

### GCC (Linux/macOS)
```bash
gcc -Wall -Wextra -std=c11 -o kombinace main.c
```

### Clang (macOS)
```bash
clang -Wall -Wextra -std=c11 -o kombinace main.c
```

### MSVC (Windows - Visual Studio)
```cmd
cl /W4 /std:c11 main.c
```

### CMake (všechny platformy)
```bash
cmake -B build
cmake --build build
./build/kombinace
```

---

## 📖 Doporučená literatura

- **"The C Programming Language"** - Kernighan & Ritchie
- **"C Primer Plus"** - Stephen Prata
- [cppreference.com - C Reference](https://en.cppreference.com/w/c)
- [GCC Manual - C Standard Library](https://gcc.gnu.org/)

---

## 🎯 Rozšíření projektu

Pokud chcete projekt rozšířit, vyzkoušejte:

1. **Filtrování** - zobrazit jen určitý stát
2. **Statistika** - průměrný čas, medián, odchylka
3. **Vícekriteriální třídění** - nejdřív čeští, pak zahraniční
4. **GUI** - grafické rozhraní (SDL, GTK)
5. **Databáze** - uložení do SQLite
6. **Web** - export do HTML, CSV

---

## ✍️ Autor

**Vzdělávací projekt pro maturitu z programování**  
Vytvořeno: 19. října 2025

---

## 📄 Licence

Projekt je k dispozici pro vzdělávací účely.

---

**Hodně štěstí s učením! 💪 Máte-li otázky, podívejte se na soubor `POZNAMKY.md`.**
