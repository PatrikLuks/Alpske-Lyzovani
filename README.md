# 🏂 Alpské lyžování - Kombinace Ženy# 🏂 Alpské lyžování - Kombinace Ženy# 🏂 Alpské lyžování - Kombinace Ženy

**Maturitní projekt z programování v C** | Zpracování sportovních dat



---

> **👉 Veškerá dokumentace je v [`README_FINALNI.md`](README_FINALNI.md)**Projekt zpracování dat alpského lyžování pro maturitní praktickou prověrku z programování.

## 🎯 Co dělá program

>

Načítá data závodnic v kombinovaném alpském lyžování (sjezd + slalom), třídí je podle výkonu a exportuje výsledky.

> Toto je redukovaný projekt zaměřený na **kvalitu a koncentraci**.---

**Učební cíle:**

- ✅ Dynamická alokace paměti (`malloc`, `realloc`, `free`)

- ✅ Parsování textových souborů (`strtok`)

- ✅ Struktury a pole struktur---## 📖 Obsah

- ✅ Třídění (`qsort`)

- ✅ Vyhledávání (lineární)

- ✅ Manipulace se řetězci a formátování

## 🚀 Rychlý start- [O projektu](#-o-projektu)

---

- [Požadavky](#-požadavky)

## 🚀 Spuštění (2 minuty)

```bash- [Instalace](#-instalace)

```bash

# 1. Jdi do build adresáře# Kompilace- [Spuštění](#-spuštění)

cd cmake-build-debug

cd cmake-build-debug- [Struktura souboru](#-struktura-souboru)

# 2. Kompiluj

gcc -Wall -Wextra -std=c11 -o kombinace ../main.cgcc -Wall -Wextra -std=c11 -o kombinace ../main.c- [Jak program funguje](#-jak-program-funguje)



# 3. Spusť- [Vstupy a výstupy](#-vstupy-a-výstupy)

./kombinace

```# Spuštění- [Učební cíle](#-učební-cíle)



---./kombinace- [Souborová struktura](#-souborová-struktura)



## 📊 Datové struktury```



```c---

// Čas: minuty, vteřiny, setiny

typedef struct {---

    int minuty;      // 0-2

    int vteriny;     // 0-59## 📋 O projektu

    int setiny;      // 0-99

} CAS;## 📁 Soubory v projektu



// Závodnice: identifikace + dva časyTento projekt je **maturitní prověrkou z programování** (2. ročník), jejímž cílem je zvládnout:

typedef struct {

    int startovniCislo;     // 1-N| Soubor | Obsah |

    char jmeno[30];         // Křestní jméno

    char prijmeni[30];      // Příjmení (VELKÁ)|--------|-------|✅ Načítání a parsování textových souborů  

    char stat[4];           // Státní kód (3 znaky)

    CAS sjezd;              // Čas 1: super-G| **README_FINALNI.md** | ⭐ VŠECHNO V JEDNOM - čtěte toto |✅ Práci s dynamickou alokací paměti  

    CAS slalom;             // Čas 2: slalom

} ZAVODNIK;| **main.c** | Finální řešení |✅ Práci se strukturami a poli struktur  

```

| **main_KOMENTOVANY.c** | S detailními vysvětleními |✅ Vyhledávání v datech  

---

| **CMakeLists.txt** | Build konfigurace |✅ Třídění dat pomocí `qsort()`  

## 🔑 Klíčové koncepty v `main.c`

✅ Zápis dat do výstupního souboru  

### Parsování (řádka ~43-83)

```c---

// Rozdělení řádku "2 Ester Ledecka CZE 1:32,43 55,89" pomocí strtok()

pch = strtok(mystring, " :,");  // Oddělovače: mezera, :, ,**Téma:** Kombinované závodění v alpském lyžování (sjezd + slalom)

while (pch != NULL) {

    switch (sloupce) {## 🎓 Jak se učit

        case 1: zavodnik[radky].startovniCislo = atoi(pch); break;

        case 2: strcpy(zavodnik[radky].jmeno, pch); break;---

        case 3: strcpy(zavodnik[radky].prijmeni, pch); break;

        // ... atd pro sloupce 4-91. Otevřete [`README_FINALNI.md`](README_FINALNI.md)

    }

    pch = strtok(NULL, " :,");2. Čtěte `main_KOMENTOVANY.c` - s vysvětleními## ⚙️ Požadavky

}

```3. Spusťte program - vidět, jak to funguje



### Dynamická alokace (řádka ~39)4. Experimentujte s vlastním kódem### Hardware

```c

// Realokace: rozšíření pole o jeden prvek- Počítač s 64 MB volné paměti (minimum)

tmpZavodnik = realloc(zavodnik, (radky + 1) * sizeof(ZAVODNIK));

if (tmpZavodnik != NULL) {---- Libovolný operační systém (Windows, macOS, Linux)

    zavodnik = tmpZavodnik;  // Aktualizace ukazatele

    // ... zpracování

}

```**Veškerá podrobná dokumentace → [`README_FINALNI.md`](README_FINALNI.md)**### Software



### Konverze času na setiny (řádka ~155)- **Kompilátor C:** GCC, Clang nebo MSVC

```c- **Build systém:** CMake (doporučeno) nebo přímá kompilace

// Převod MM:SS,CS na jednotnou jednotku pro porovnávání- **Textový editor:** VS Code, CLion, Sublime Text apod.

// 1 minuta = 6000 setin, 1 sekunda = 100 setin

// Příklad: 1:35,68 = 1*6000 + 35*100 + 68 = 9568 setin### Knihovny

Projekt používá pouze **standardní C knihovny** - žádné externí závislosti!

int naSetiny(CAS cas) {

    return cas.minuty * 6000 + cas.vteriny * 100 + cas.setiny;```c

}#include <stdio.h>    // I/O operace

```#include <stdlib.h>   // Paměť, qsort

#include <string.h>   // Manipulace se řetězci

### Třídění (řádka ~193-200)```

```c

// Porovnávací funkce pro qsort()---

int porovnej(const void *a, const void *b) {

    ZAVODNIK *z1 = (ZAVODNIK *)a;## 📥 Instalace

    ZAVODNIK *z2 = (ZAVODNIK *)b;

    int cas1 = soucetCasu(z1->sjezd, z1->slalom);### Varianta 1: Přes CMake (doporučeno)

    int cas2 = soucetCasu(z2->sjezd, z2->slalom);

    return cas1 - cas2;  // Vzestupně: nejrychlejší první```bash

}# Klonování/stažení projektu

git clone <url-projektu>

// Tříděnícd kombinace

qsort(zavodnik, pocet, sizeof(ZAVODNIK), porovnej);

```# Vytvoření build adresáře

mkdir build

---cd build



## 📥 Formáty souborů# Generování Makefile

cmake ..

### Vstup: `startovni_listina_kombinace_zeny.txt`

```# Kompilace

1 Katharina Huberova AUT 1:35,68 53,11make

2 Ester Ledecka CZE 1:32,43 55,89```

3 Michelle Gisinova CHE 1:33,42 52,25

...### Varianta 2: Přímá kompilace s GCC

```

**Formát:** `<číslo> <jméno> <příjmení> <kód> <sjezd MM:SS,CS> <slalom SS,CS>````bash

cd kombinace

### Výstup: `vysledkova_listina_kombinace_zeny.txt`gcc -o kombinace main.c

``````

A L P S K E     L Y Z O V A N I  -  K O M B I N A C E   Z E N Y

--------------------------------------------------------------------### Varianta 3: Přímá kompilace s Clang

poradi   jmeno        prijmeni   stat  sjezd    slalom    celkem    ztrata

--------------------------------------------------------------------```bash

  1.   Michelle        GISINOVA    CHE    1:33,42   52,25    2:25,67  00,00clang -o kombinace main.c

  2.      Wendy     HOLDENEROVA    CHE    1:33,41   53,31    2:26,72  01,05```

```

---

---

## 🚀 Spuštění

## 🔄 Tok programu v `main()`

### Linux / macOS

```

1. otevriTo()           → Načte soubor, alokuje paměť, parsuje data```bash

                          Výstup: pole ZAVODNIKcd cmake-build-debug

2. naVelkaP()           → Převede příjmení na VELKÁ PÍSMENA./kombinace

3. vypis()              → Vypíše startovní listinu```

4. vyhledej()           → Vyhledá a vypíše jednu závodnici

5. qsort() + porovnej() → Seřadí podle součtu časů### Windows (CMD)

6. vypis()              → Vypíše seřazenou listinu

7. vypis_soubor()       → Uloží do výstupního souboru```cmd

8. free()               → Uvolní paměťcd cmake-build-debug

```kombinace.exe

```

---

### Windows (PowerShell)

## 🔧 Funkce v programu

```powershell

| Funkce | Řádka | Popis |cd cmake-build-debug

|--------|-------|-------|.\kombinace.exe

| `otevriTo()` | 26-123 | Načte soubor, realloc + parsování |```

| `vypis()` | 124-139 | Vypíše startovní/výsledkovou listinu |

| `naSetiny()` | 155-157 | Převede čas na setiny |---

| `soucetCasu()` | 159-161 | Sečte sjezd + slalom |

| `naVelkaP()` | 163-170 | Převede string na VELKÁ |## 📊 Struktura souboru

| `vyhledej()` | 172-181 | Lineární vyhledávání (strcmp) |

| `porovnej()` | 183-190 | Komparátor pro qsort() |### Vstupní soubor: `startovni_listina_kombinace_zeny.txt`

| `vypis_soubor()` | 192-236 | Zápis do souboru (fprintf) |

| `main()` | - | Orchestrace |```

1 Katharina Huberova AUT 1:35,68 53,11

---2 Ester Ledecka CZE 1:32,43 55,89

3 Michelle Gisinova CHE 1:33,42 52,25

## ⚠️ Běžné chyby & řešení...

```

| Chyba | Příčina | Řešení |

|-------|---------|--------|**Formát:**

| Segmentation fault | Alokace se nezdařila | Zkontroluj `malloc` vrátí ukazatel, ne NULL |```

| Memory leak | Zapomenutý `free()` | Vždy `free(zavodnik)` na konci |<num> <jméno> <příjmení> <státní kód> <čas sjezdu> <čas slalomu>

| "Soubor nebyl otevřen" | Špatná cesta | Spusť z `cmake-build-debug/` |```

| Zvláštní znaky | Kódování | Soubor musí být UTF-8 |

| Špatné třídění | Opačné znaménko v qsort | `return a - b` = vzestupně |- **num:** Startovní číslo (1-N)

- **jméno:** Křestní jméno

---- **příjmení:** Příjmení

- **státní kód:** 3-písmenový kód (CHE, AUT, CZE...)

## 🎓 Klíčové vzorce & vztahy- **čas sjezdu:** Formát `MM:SS,CS` (minuty:sekundy,setiny)

- **čas slalomu:** Formát `SS,CS` (sekundy,setiny)

### ASCII transformace (malá → velká)

```c### Výstupní soubor: `vysledkova_listina_kombinace_zeny.txt`

'a' = 97, 'A' = 65, rozdíl = 32

char velke = male - 32;  // 'a' - 32 = 'A'```

```A L P S K E     L Y Z O V A N I  -  K O M B I N A C E   Z E N Y

--------------------------------------------------------------------

### Konverze časuporadi   jmeno        prijmeni   stat  sjezd    slalom    celkem    ztrata

```--------------------------------------------------------------------

1 minuta = 6000 setin  1.   Michelle        GISINOVA    CHE    1:33,42   52,25    2:25,67  00,00

1 sekunda = 100 setin  2.      Wendy     HOLDENEROVA    CHE    1:33,41   53,31    2:26,72  01,05

...

Příklad: 1:35,68```

= 1*6000 + 35*100 + 68 = 9568 setin

```---



### Porovnání řetězců## 🔄 Jak program funguje

```c

strcmp(s1, s2)### Krok 1: Načtení dat

// Vrací: 0 (stejné), <0 (s1<s2), >0 (s1>s2)

``````

┌─────────────────────────┐

### Standardní knihovny│ Otevření vstupního      │

```c│ souboru (.txt)          │

#include <stdio.h>    // printf, fopen, fprintf└──────────┬──────────────┘

#include <stdlib.h>   // malloc, realloc, free, qsort, atoi           │

#include <string.h>   // strcpy, strcmp, strlen, strtok           ▼

```┌─────────────────────────┐

│ Dynamická alokace       │

---│ paměti pro ZAVODNIK[]   │

└──────────┬──────────────┘

## ✅ Verifikace správnosti           │

           ▼

Zkontroluj, zda program:┌─────────────────────────┐

- [ ] Načte všechny řádky ze vstupního souboru│ Parsování jednotlivých  │

- [ ] Převede příjmení na VELKÁ PÍSMENA│ řádků (strtok)          │

- [ ] Najde LEDECKA = Ester (číslo 2)└──────────┬──────────────┘

- [ ] Seřadí správně podle součtu časů           │

- [ ] Nejrychlejší je Michelle Gisinova (2:25,67)           ▼

- [ ] Vytvoří výstupní soubor bez chyb┌─────────────────────────┐

- [ ] Vypíše ztrátu správně (nejrychlejší = 0, ostatní = rozdíl)│ Zanesení do struktury   │

│ v paměti                │

---└─────────────────────────┘

```

## 📚 Struktura projektu

### Krok 2: Transformace dat

```

kombinace/```

├── main.c              ← Zdrojový kód (236 řádků)┌─────────────────────────┐

├── README.md           ← Toto (vše v jednom)│ Převod příjmení na      │

├── CMakeLists.txt      ← Build konfigurace│ VELKÁ PÍSMENA           │

│└─────────────────────────┘

└── cmake-build-debug/```

    ├── kombinace       ← Spustitelný program

    ├── startovni_listina_kombinace_zeny.txt   ← Vstup### Krok 3: Zpracování a výstup

    └── vysledkova_listina_kombinace_zeny.txt  ← Výstup

``````

┌─────────────────────────┐         ┌──────────────────────┐

---│ Výpis startovní        │ ──────→ │ Terminal (obrazovka) │

│ listiny                │         └──────────────────────┘

## 🔍 Jak studovat kód└─────────────────────────┘



1. **Čtení struktury** (5 min)┌─────────────────────────┐         ┌──────────────────────┐

   - Otevři `main.c`, soustřeď se na datové struktury (řádky 9-20)│ Vyhledávání (příklad)   │ ──────→ │ Terminal (výsledek)  │

   - Pochop rozdíl mezi `CAS` a `ZAVODNIK`└─────────────────────────┘         └──────────────────────┘



2. **Porozumění parsování** (15 min)┌─────────────────────────┐

   - Čti funkci `otevriTo()` - jak pracuje `strtok()`│ Řazení podle součtu     │

   - Jak se data ukládají do struktury│ časů (qsort)            │

└──────────┬──────────────┘

3. **Klíčové algoritmy** (15 min)           │

   - `naSetiny()` - konverze jednotek           ▼

   - `porovnej()` - jak funguje qsort()┌─────────────────────────┐         ┌──────────────────────┐

│ Výpis výsledků          │ ──────→ │ Terminal (seznam)    │

4. **Komplexní pohled** (15 min)└─────────────────────────┘         └──────────────────────┘

   - Čti `main()` - orchestrace všech funkcí

   - Pochop jak se data transformují┌─────────────────────────┐         ┌──────────────────────┐

│ Zápis do výstupního     │ ──────→ │ Soubor (.txt)        │

5. **Experimenty** (20 min)│ souboru                 │         └──────────────────────┘

   - Změň kritérium třídění└─────────────────────────┘

   - Přidej vlastní vyhledávání

   - Modifikuj výstupní formát┌─────────────────────────┐

│ Uvolnění paměti (free)  │

**Celkem: ~80 minut k úplnému porozumění**└─────────────────────────┘

```

---

---

## 💾 Kompilace na různých platformách

## 📥 Vstupy a výstupy

### Linux / macOS (GCC/Clang)

```bash### Vstup

gcc -Wall -Wextra -std=c11 -o kombinace main.c- **Textový soubor** s daty závodnic

./kombinace

```### Výstupy

1. **Standardní výstup (terminál)**

### Windows (MSVC)   - Startovní listina

```cmd   - Výsledek vyhledávání

cl /W4 /std:c11 main.c   - Výsledková listina (seřazená)

kombinace.exe

```2. **Soubor** `vysledkova_listina_kombinace_zeny.txt`

   - Finální výsledková listina s pořadím a ztratou

### S CMake (všechny platformy)

```bash---

cmake -B build

cmake --build build## 🎓 Učební cíle

./build/kombinace

```Po vyřešení tohoto příkladu byste měli umět:



---- ✅ **Manipulace se soubory**

  - Otevření a čtení textových souborů

## 🎯 Rozšíření projektu (pokud máš čas)  - Zápis do textových souborů

  - Bezpečné zavření souborů

1. **Filtrování** - zobrazit jen určitý stát

2. **Statistika** - průměrný čas, medián, odchylka- ✅ **Parsování dat**

3. **Vícekriteriální třídění** - nejdříve čeští, pak zahraniční  - Rozdělování řetězců pomocí `strtok()`

4. **CSV export** - výstup do CSV formátu  - Převádění řetězců na čísla (`atoi()`)

5. **Interaktivní menu** - vybírání operací  - Zpracování strukturovaných dat



---- ✅ **Dynamická paměť**

  - Alokace paměti pomocí `malloc()`

## 📝 Technické detaily  - Realokace pomocí `realloc()`

  - Korektní uvolnění `free()`

**Jazyk:** C (C11 standard)  

**Kompilace:** Bez externích knihoven (jen standardní C)  - ✅ **Struktury a pole**

**Paměťový model:** Dynamické pole s realokací    - Definice struktur `typedef struct`

**Komplexita parsování:** O(n × m) kde n=řádky, m=znaky    - Pole struktur

**Komplexita třídění:** O(n log n) - quicksort    - Přístup k prvkům (`zavodnik[i].prijmeni`)



---- ✅ **Vyhledávání a třídění**

  - Lineární vyhledávání

**Verze:** 1.0 | Datum: 20. října 2025    - Použití `qsort()` se custom porovnávací funkcí

**Určeno pro:** Maturitní praktickou prověrku z programování (2. ročník)  - Manipulace s jednotkami (konverze na setiny)


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
