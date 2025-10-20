# 🏂 Alpské lyžování - Kombinace Ženy# 🏂 Alpské lyžování - Kombinace Ženy# 🏂 Alpské lyžování - Kombinace Ženy# 🏂 Alpské lyžování - Kombinace Ženy

**Maturitní projekt z programování v C** | Zpracování sportovních dat

**Maturitní projekt z programování v C** | Zpracování sportovních dat

---



## 🎯 Co dělá program

---

Načítá data závodnic v kombinovaném alpském lyžování (sjezd + slalom), třídí je podle výkonu a exportuje výsledky.

> **👉 Veškerá dokumentace je v [`README_FINALNI.md`](README_FINALNI.md)**Projekt zpracování dat alpského lyžování pro maturitní praktickou prověrku z programování.

**Učební cíle:**

- ✅ Dynamická alokace paměti (`malloc`, `realloc`, `free`)## 🎯 Co dělá program

- ✅ Parsování textových souborů (`strtok`)

- ✅ Struktury a pole struktur>

- ✅ Třídění (`qsort`)

- ✅ Vyhledávání (lineární)Načítá data závodnic v kombinovaném alpském lyžování (sjezd + slalom), třídí je podle výkonu a exportuje výsledky.

- ✅ Manipulace se řetězci a formátování

> Toto je redukovaný projekt zaměřený na **kvalitu a koncentraci**.---

---

**Učební cíle:**

## 🚀 Spuštění (2 minuty)

- ✅ Dynamická alokace paměti (`malloc`, `realloc`, `free`)

```bash

# 1. Jdi do build adresáře- ✅ Parsování textových souborů (`strtok`)

cd cmake-build-debug

- ✅ Struktury a pole struktur---## 📖 Obsah

# 2. Kompiluj

gcc -Wall -Wextra -std=c11 -o kombinace ../main.c- ✅ Třídění (`qsort`)



# 3. Spusť- ✅ Vyhledávání (lineární)

./kombinace

```- ✅ Manipulace se řetězci a formátování



---## 🚀 Rychlý start- [O projektu](#-o-projektu)



## 📊 Datové struktury---



```c- [Požadavky](#-požadavky)

// Čas: minuty, vteřiny, setiny

typedef struct {## 🚀 Spuštění (2 minuty)

    int minuty;      // 0-2

    int vteriny;     // 0-59```bash- [Instalace](#-instalace)

    int setiny;      // 0-99

} CAS;```bash



// Závodnice: identifikace + dva časy# 1. Jdi do build adresáře# Kompilace- [Spuštění](#-spuštění)

typedef struct {

    int startovniCislo;     // 1-Ncd cmake-build-debug

    char jmeno[30];         // Křestní jméno

    char prijmeni[30];      // Příjmení (VELKÁ)cd cmake-build-debug- [Struktura souboru](#-struktura-souboru)

    char stat[4];           // Státní kód (3 znaky)

    CAS sjezd;              // Čas 1: super-G# 2. Kompiluj

    CAS slalom;             // Čas 2: slalom

} ZAVODNIK;gcc -Wall -Wextra -std=c11 -o kombinace ../main.cgcc -Wall -Wextra -std=c11 -o kombinace ../main.c- [Jak program funguje](#-jak-program-funguje)

```



---

# 3. Spusť- [Vstupy a výstupy](#-vstupy-a-výstupy)

## 🔑 Klíčové koncepty v `main.c`

./kombinace

### Parsování (řádka ~43-83)

```c```# Spuštění- [Učební cíle](#-učební-cíle)

// Rozdělení řádku "2 Ester Ledecka CZE 1:32,43 55,89" pomocí strtok()

pch = strtok(mystring, " :,");  // Oddělovače: mezera, :, ,

while (pch != NULL) {

    switch (sloupce) {---./kombinace- [Souborová struktura](#-souborová-struktura)

        case 1: zavodnik[radky].startovniCislo = atoi(pch); break;

        case 2: strcpy(zavodnik[radky].jmeno, pch); break;

        case 3: strcpy(zavodnik[radky].prijmeni, pch); break;

        // ... atd pro sloupce 4-9## 📊 Datové struktury```

    }

    pch = strtok(NULL, " :,");

}

``````c---



### Dynamická alokace (řádka ~39)// Čas: minuty, vteřiny, setiny

```c

// Realokace: rozšíření pole o jeden prvektypedef struct {---

tmpZavodnik = realloc(zavodnik, (radky + 1) * sizeof(ZAVODNIK));

if (tmpZavodnik != NULL) {    int minuty;      // 0-2

    zavodnik = tmpZavodnik;  // Aktualizace ukazatele

    // ... zpracování    int vteriny;     // 0-59## 📋 O projektu

}

```    int setiny;      // 0-99



### Konverze času na setiny (řádka ~155)} CAS;## 📁 Soubory v projektu

```c

// Převod MM:SS,CS na jednotnou jednotku pro porovnávání

// 1 minuta = 6000 setin, 1 sekunda = 100 setin

// Příklad: 1:35,68 = 1*6000 + 35*100 + 68 = 9568 setin// Závodnice: identifikace + dva časyTento projekt je **maturitní prověrkou z programování** (2. ročník), jejímž cílem je zvládnout:



int naSetiny(CAS cas) {typedef struct {

    return cas.minuty * 6000 + cas.vteriny * 100 + cas.setiny;

}    int startovniCislo;     // 1-N| Soubor | Obsah |

```

    char jmeno[30];         // Křestní jméno

### Třídění (řádka ~193-200)

```c    char prijmeni[30];      // Příjmení (VELKÁ)|--------|-------|✅ Načítání a parsování textových souborů  

// Porovnávací funkce pro qsort()

int porovnej(const void *a, const void *b) {    char stat[4];           // Státní kód (3 znaky)

    ZAVODNIK *z1 = (ZAVODNIK *)a;

    ZAVODNIK *z2 = (ZAVODNIK *)b;    CAS sjezd;              // Čas 1: super-G| **README_FINALNI.md** | ⭐ VŠECHNO V JEDNOM - čtěte toto |✅ Práci s dynamickou alokací paměti  

    int cas1 = soucetCasu(z1->sjezd, z1->slalom);

    int cas2 = soucetCasu(z2->sjezd, z2->slalom);    CAS slalom;             // Čas 2: slalom

    return cas1 - cas2;  // Vzestupně: nejrychlejší první

}} ZAVODNIK;| **main.c** | Finální řešení |✅ Práci se strukturami a poli struktur  



// Třídění```

qsort(zavodnik, pocet, sizeof(ZAVODNIK), porovnej);

```| **main_KOMENTOVANY.c** | S detailními vysvětleními |✅ Vyhledávání v datech  



------



## 📥 Formáty souborů| **CMakeLists.txt** | Build konfigurace |✅ Třídění dat pomocí `qsort()`  



### Vstup: `startovni_listina_kombinace_zeny.txt`## 🔑 Klíčové koncepty v `main.c`

```

1 Katharina Huberova AUT 1:35,68 53,11✅ Zápis dat do výstupního souboru  

2 Ester Ledecka CZE 1:32,43 55,89

3 Michelle Gisinova CHE 1:33,42 52,25### Parsování (řádka ~43-83)

...

``````c---

**Formát:** `<číslo> <jméno> <příjmení> <kód> <sjezd MM:SS,CS> <slalom SS,CS>`

// Rozdělení řádku "2 Ester Ledecka CZE 1:32,43 55,89" pomocí strtok()

### Výstup: `vysledkova_listina_kombinace_zeny.txt`

```pch = strtok(mystring, " :,");  // Oddělovače: mezera, :, ,**Téma:** Kombinované závodění v alpském lyžování (sjezd + slalom)

A L P S K E     L Y Z O V A N I  -  K O M B I N A C E   Z E N Y

--------------------------------------------------------------------while (pch != NULL) {

poradi   jmeno        prijmeni   stat  sjezd    slalom    celkem    ztrata

--------------------------------------------------------------------    switch (sloupce) {## 🎓 Jak se učit

  1.   Michelle        GISINOVA    CHE    1:33,42   52,25    2:25,67  00,00

  2.      Wendy     HOLDENEROVA    CHE    1:33,41   53,31    2:26,72  01,05        case 1: zavodnik[radky].startovniCislo = atoi(pch); break;

```

        case 2: strcpy(zavodnik[radky].jmeno, pch); break;---

---

        case 3: strcpy(zavodnik[radky].prijmeni, pch); break;

## 🔄 Tok programu v `main()`

        // ... atd pro sloupce 4-91. Otevřete [`README_FINALNI.md`](README_FINALNI.md)

```

1. otevriTo()           → Načte soubor, alokuje paměť, parsuje data    }

                          Výstup: pole ZAVODNIK

2. naVelkaP()           → Převede příjmení na VELKÁ PÍSMENA    pch = strtok(NULL, " :,");2. Čtěte `main_KOMENTOVANY.c` - s vysvětleními## ⚙️ Požadavky

3. vypis()              → Vypíše startovní listinu

4. vyhledej()           → Vyhledá a vypíše jednu závodnici}

5. qsort() + porovnej() → Seřadí podle součtu časů

6. vypis()              → Vypíše seřazenou listinu```3. Spusťte program - vidět, jak to funguje

7. vypis_soubor()       → Uloží do výstupního souboru

8. free()               → Uvolní paměť

```

### Dynamická alokace (řádka ~39)4. Experimentujte s vlastním kódem### Hardware

---

```c

## 🔧 Funkce v programu

// Realokace: rozšíření pole o jeden prvek- Počítač s 64 MB volné paměti (minimum)

| Funkce | Řádka | Popis |

|--------|-------|-------|tmpZavodnik = realloc(zavodnik, (radky + 1) * sizeof(ZAVODNIK));

| `otevriTo()` | 100+ | Načte soubor, realloc + parsování |

| `vypis()` | 170+ | Vypíše startovní/výsledkovou listinu |if (tmpZavodnik != NULL) {---- Libovolný operační systém (Windows, macOS, Linux)

| `naSetiny()` | 210+ | Převede čas na setiny |

| `soucetCasu()` | 235+ | Sečte sjezd + slalom |    zavodnik = tmpZavodnik;  // Aktualizace ukazatele

| `naVelkaP()` | 255+ | Převede string na VELKÁ |

| `vyhledej()` | 280+ | Lineární vyhledávání (strcmp) |    // ... zpracování

| `porovnej()` | 310+ | Komparátor pro qsort() |

| `vypis_soubor()` | 350+ | Zápis do souboru (fprintf) |}

| `main()` | 400+ | Orchestrace |

```**Veškerá podrobná dokumentace → [`README_FINALNI.md`](README_FINALNI.md)**### Software

---



## ⚠️ Běžné chyby & řešení

### Konverze času na setiny (řádka ~155)- **Kompilátor C:** GCC, Clang nebo MSVC

| Chyba | Příčina | Řešení |

|-------|---------|--------|```c- **Build systém:** CMake (doporučeno) nebo přímá kompilace

| Segmentation fault | Alokace se nezdařila | Zkontroluj `malloc` vrátí ukazatel, ne NULL |

| Memory leak | Zapomenutý `free()` | Vždy `free(zavodnik)` na konci |// Převod MM:SS,CS na jednotnou jednotku pro porovnávání- **Textový editor:** VS Code, CLion, Sublime Text apod.

| "Soubor nebyl otevřen" | Špatná cesta | Spusť z `cmake-build-debug/` |

| Zvláštní znaky | Kódování | Soubor musí být UTF-8 |// 1 minuta = 6000 setin, 1 sekunda = 100 setin

| Špatné třídění | Opačné znaménko v qsort | `return a - b` = vzestupně |

// Příklad: 1:35,68 = 1*6000 + 35*100 + 68 = 9568 setin### Knihovny

---

Projekt používá pouze **standardní C knihovny** - žádné externí závislosti!

## 🎓 Klíčové vzorce & vztahy

int naSetiny(CAS cas) {

### ASCII transformace (malá → velká)

```c    return cas.minuty * 6000 + cas.vteriny * 100 + cas.setiny;```c

'a' = 97, 'A' = 65, rozdíl = 32

char velke = male - 32;  // 'a' - 32 = 'A'}#include <stdio.h>    // I/O operace

```

```#include <stdlib.h>   // Paměť, qsort

### Konverze času

```#include <string.h>   // Manipulace se řetězci

1 minuta = 6000 setin

1 sekunda = 100 setin### Třídění (řádka ~193-200)```



Příklad: 1:35,68```c

= 1*6000 + 35*100 + 68 = 9568 setin

```// Porovnávací funkce pro qsort()---



### Porovnání řetězcůint porovnej(const void *a, const void *b) {

```c

strcmp(s1, s2)    ZAVODNIK *z1 = (ZAVODNIK *)a;## 📥 Instalace

// Vrací: 0 (stejné), <0 (s1<s2), >0 (s1>s2)

```    ZAVODNIK *z2 = (ZAVODNIK *)b;



### Standardní knihovny    int cas1 = soucetCasu(z1->sjezd, z1->slalom);### Varianta 1: Přes CMake (doporučeno)

```c

#include <stdio.h>    // printf, fopen, fprintf    int cas2 = soucetCasu(z2->sjezd, z2->slalom);

#include <stdlib.h>   // malloc, realloc, free, qsort, atoi

#include <string.h>   // strcpy, strcmp, strlen, strtok    return cas1 - cas2;  // Vzestupně: nejrychlejší první```bash

```

}# Klonování/stažení projektu

---

git clone <url-projektu>

## ✅ Verifikace správnosti

// Tříděnícd kombinace

Zkontroluj, zda program:

- [ ] Načte všechny řádky ze vstupního souboruqsort(zavodnik, pocet, sizeof(ZAVODNIK), porovnej);

- [ ] Převede příjmení na VELKÁ PÍSMENA

- [ ] Najde LEDECKA = Ester (číslo 2)```# Vytvoření build adresáře

- [ ] Seřadí správně podle součtu časů

- [ ] Nejrychlejší je Michelle Gisinova (2:25,67)mkdir build

- [ ] Vytvoří výstupní soubor bez chyb

- [ ] Vypíše ztrátu správně (nejrychlejší = 0, ostatní = rozdíl)---cd build



---



## 📚 Struktura projektu## 📥 Formáty souborů# Generování Makefile



```cmake ..

kombinace/

├── main.c              ← Zdrojový kód (500+ řádků s komentáři)### Vstup: `startovni_listina_kombinace_zeny.txt`

├── README.md           ← Toto (vše v jednom)

├── CMakeLists.txt      ← Build konfigurace```# Kompilace

│

└── cmake-build-debug/1 Katharina Huberova AUT 1:35,68 53,11make

    ├── kombinace       ← Spustitelný program

    ├── startovni_listina_kombinace_zeny.txt   ← Vstup2 Ester Ledecka CZE 1:32,43 55,89```

    └── vysledkova_listina_kombinace_zeny.txt  ← Výstup

```3 Michelle Gisinova CHE 1:33,42 52,25



---...### Varianta 2: Přímá kompilace s GCC



## 🔍 Jak studovat kód```



1. **Čtení struktury** (5 min)**Formát:** `<číslo> <jméno> <příjmení> <kód> <sjezd MM:SS,CS> <slalom SS,CS>````bash

   - Otevři `main.c`, soustřeď se na datové struktury (řádky 50-70)

   - Pochop rozdíl mezi `CAS` a `ZAVODNIK`cd kombinace



2. **Porozumění parsování** (15 min)### Výstup: `vysledkova_listina_kombinace_zeny.txt`gcc -o kombinace main.c

   - Čti funkci `otevriTo()` - jak pracuje `strtok()`

   - Jak se data ukládají do struktury``````



3. **Klíčové algoritmy** (15 min)A L P S K E     L Y Z O V A N I  -  K O M B I N A C E   Z E N Y

   - `naSetiny()` - konverze jednotek

   - `porovnej()` - jak funguje qsort()--------------------------------------------------------------------### Varianta 3: Přímá kompilace s Clang



4. **Komplexní pohled** (15 min)poradi   jmeno        prijmeni   stat  sjezd    slalom    celkem    ztrata

   - Čti `main()` - orchestrace všech funkcí

   - Pochop jak se data transformují--------------------------------------------------------------------```bash



5. **Experimenty** (20 min)  1.   Michelle        GISINOVA    CHE    1:33,42   52,25    2:25,67  00,00clang -o kombinace main.c

   - Změň kritérium třídění

   - Přidej vlastní vyhledávání  2.      Wendy     HOLDENEROVA    CHE    1:33,41   53,31    2:26,72  01,05```

   - Modifikuj výstupní formát

```

**Celkem: ~80 minut k úplnému porozumění**

---

---

---

## 💾 Kompilace na různých platformách

## 🚀 Spuštění

### Linux / macOS (GCC/Clang)

```bash## 🔄 Tok programu v `main()`

gcc -Wall -Wextra -std=c11 -o kombinace main.c

./kombinace### Linux / macOS

```

```

### Windows (MSVC)

```cmd1. otevriTo()           → Načte soubor, alokuje paměť, parsuje data```bash

cl /W4 /std:c11 main.c

kombinace.exe                          Výstup: pole ZAVODNIKcd cmake-build-debug

```

2. naVelkaP()           → Převede příjmení na VELKÁ PÍSMENA./kombinace

### S CMake (všechny platformy)

```bash3. vypis()              → Vypíše startovní listinu```

cmake -B build

cmake --build build4. vyhledej()           → Vyhledá a vypíše jednu závodnici

./build/kombinace

```5. qsort() + porovnej() → Seřadí podle součtu časů### Windows (CMD)



---6. vypis()              → Vypíše seřazenou listinu



## 🎯 Rozšíření projektu (pokud máš čas)7. vypis_soubor()       → Uloží do výstupního souboru```cmd



1. **Filtrování** - zobrazit jen určitý stát8. free()               → Uvolní paměťcd cmake-build-debug

2. **Statistika** - průměrný čas, medián, odchylka

3. **Vícekriteriální třídění** - nejdříve čeští, pak zahraniční```kombinace.exe

4. **CSV export** - výstup do CSV formátu

5. **Interaktivní menu** - vybírání operací```



------



## 📝 Technické detaily### Windows (PowerShell)



**Jazyk:** C (C11 standard)  ## 🔧 Funkce v programu

**Kompilace:** Bez externích knihoven (jen standardní C)  

**Paměťový model:** Dynamické pole s realokací  ```powershell

**Komplexita parsování:** O(n × m) kde n=řádky, m=znaky  

**Komplexita třídění:** O(n log n) - quicksort  | Funkce | Řádka | Popis |cd cmake-build-debug



---|--------|-------|-------|.\kombinace.exe



**Verze:** 2.0 (s kvalitními komentáři) | Datum: 20. října 2025  | `otevriTo()` | 26-123 | Načte soubor, realloc + parsování |```

**Určeno pro:** Maturitní praktickou prověrku z programování (2. ročník)

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
