# 📝 Poznámky k projektu - Alpské lyžování - Kombinace Ženy

## 📋 Přehled projektu

**Typ úkolu:** Maturitní praktická prověrka z programování - 2. ročník  
**Jazyk:** C (C11 standard)  
**Téma:** Zpracování textového souboru - načítání, třídění a výstup dat  
**Obtížnost:** ⭐⭐⭐ (střední)

---

## 🎯 Požadavky zadání

1. ✅ **Načtení vstupního souboru** do vhodné datové struktury
2. ✅ **Převedení příjmení** na velká písmena
3. ✅ **Výpis startovní listiny** na obrazovku (dle vzoru)
4. ✅ **Implementace vyhledávání** - funkce pro hledání podle příjmení
5. ✅ **Implementace řazení** - seřazení dat podle součtu časů (vzestupně)
6. ✅ **Zápis výsledků** do výstupního souboru

---

## 🏗️ Datové struktury

### Struct CAS - čas v jednotlivých formátech

```c
typedef struct {
    int minuty;      // Minuty (0-2)
    int vteriny;     // Vteřiny (0-59)
    int setiny;      // Setiny vteřiny (0-99)
} CAS;
```

**Proč tato struktura?**
- Umožňuje přehledně pracovat s časy
- Každá komponenta času má svůj formát
- Lze snadno převádět na sekundy/setiny pro porovnávání

### Struct ZAVODNIK - údaje o závodnici

```c
typedef struct {
    int startovniCislo;      // Pořadové číslo v závodě
    char jmeno[30];          // Křestní jméno
    char prijmeni[30];       // Příjmení
    char stat[4];            // Kód státu (CHE, AUT, CZE...)
    CAS sjezd;               // Čas sjezdu (super-G)
    CAS slalom;              // Čas slalomu
} ZAVODNIK;
```

**Proč tato struktura?**
- Centralizuje všechny údaje o jedné závodnici
- Usnadňuje práci s poli `ZAVODNIK zavodnici[MAX]`
- Přehledná organizace dat

---

## 🔑 Klíčové funkce

### 1. `ZAVODNIK *otevriTo(int *pocet)` - Načítání ze souboru

**Co dělá?**
- Otevře vstupní soubor `startovni_listina_kombinace_zeny.txt`
- Dynamicky alokuje paměť pro pole struktury `ZAVODNIK`
- Parsuje každý řádek pomocí `strtok()` s oddělovači `" :,"`
- Vrací pole závodnic a počet v parametru `*pocet`

**Klíčové techniky:**
```c
realloc(zavodnik, (radky + 1) * sizeof(ZAVODNIK))
```
- Dynamicky rozšiřuje pole o jeden prvek na každý řádek
- Ušetří paměť - alokujeme jen co potřebujeme

```c
strtok(mystring, ODDELOVACE)
```
- Dělí řetězec na tokeny podle oddělovačů
- Užitečné pro parsování strukturovaných dat

**Rizika a řešení:**
- ⚠️ Pokud soubor neexistuje → vrátí `NULL`
- ⚠️ Nedostatek paměti → uvolníme a skončíme
- ⚠️ Řetězec příliš dlouhý (`MAX=100`) → ignoruje se

---

### 2. `void naVelkaP(char *retezec)` - Konverze na velká písmena

**Co dělá?**
- Projde každý znak v řetězci
- Malé písmeno (a-z) převede na velké (A-Z)

**Jak funguje ASCII:**
```
'a' = 97, 'A' = 65
'z' = 122, 'Z' = 90
Rozdíl = 32
```

**Kód:**
```c
if (retezec[i] >= 'a' && retezec[i] <= 'z') {
    retezec[i] = retezec[i] - 32;
}
```

**Alternativa (moderněji):**
```c
retezec[i] = toupper(retezec[i]);  // Vyžaduje ctype.h
```

---

### 3. `int naSetiny(CAS cas)` - Převod na jednotné jednotky

**Proč?**
- Časy jsou ve formátu MM:SS,CS
- Pro porovnávání potřebujeme jednu jednotku
- Setiny vteřiny jsou nejmenší jednotka

**Matematika:**
```
1 minuta = 60 sekund = 6000 setin
1 sekunda = 100 setin

Příklad: 1:35,68 = 1*6000 + 35*100 + 68 = 9568 setin
```

**Výhoda:**
- Lze porovnávat pomocí `<`, `>` jako normální čísla
- Snadné počítání rozdílů (ztráty)

---

### 4. `int soucetCasu(CAS sjezd, CAS slalom)` - Kombinovaný čas

**Co dělá?**
- Sečte čas sjezdu a slalomu
- Převedením obou na setiny a sečtením

**Použití:**
```c
int celkovyCas = soucetCasu(zavodnik[i].sjezd, zavodnik[i].slalom);
```

---

### 5. `int vyhledej(...)` - Vyhledávání podle příjmení

**Co dělá?**
- Procházíme pole všech závodnic
- Porovnáme `strcmp(zavodnik[i].prijmeni, hledane)`
- Vrátíme index nebo -1 (nenalezeno)

**Složitost:** O(n) - lineární vyhledávání

**Výstup:**
```
Nalezena: Ester LEDECKA - startovní číslo 2
```

---

### 6. `int porovnej(const void *a, const void *b)` - Pro qsort()

**Co dělá?**
- Porovnává dvě závodnice podle součtu jejich časů
- Vrácené hodnoty:
  - **Negativní** → první má lepší čas (bude dřív)
  - **0** → stejný čas
  - **Kladná** → druhá má lepší čas (bude dřív)

**Podrobně:**
```c
return cas1 - cas2;  // Vzestupné pořadí (nejrychlejší první)
```

**Funkce qsort():**
```c
qsort(zavodnik, pocet, sizeof(ZAVODNIK), porovnej);
```
- Třídí pole `zavodnik`
- `pocet` prvků
- Každý prvek je `sizeof(ZAVODNIK)` bajtů
- Porovnává pomocí funkce `porovnej`

---

### 7. `void vypis_soubor(...)` - Zápis výsledků

**Co dělá?**
- Otevře soubor pro zápis: `fopen(jmenoSouboru, "w")`
- Zapíše hlavičku a řádky s výsledky
- **DŮLEŽITÉ:** Zavře soubor `fclose(pFile)`

**Speciální výpočet - ztráta času:**
```c
int ztrata = celkovyCas - nejLepsiCas;
```
- Vypočítá rozdíl od nejrychlejší závodnice
- Umožňuje vidět, o kolik setin máte handicap

**Formátování:**
```c
fprintf(pFile, "%3d. %10s %15s ...");
```
- `%3d` = číslo zarovnáno doprava na 3 pozice
- `%10s` = řetězec na 10 pozic
- `%02d` = dvouciferné číslo s nulou vepředu (05 místo 5)

---

## ⚡ Tok programu

```
1. Spuštění main()
   ↓
2. otevriTo() - Načte soubor do paměti
   ↓
3. naVelkaP() - Převede příjmení na VELKÁ PÍSMENA (10x)
   ↓
4. vypis() - Vypíše startovní listinu
   ↓
5. vyhledej() - Vyhledá příklad (LEDECKA)
   ↓
6. qsort() + porovnej() - Seřadí podle výkonu
   ↓
7. Výpis seřazených výsledků
   ↓
8. vypis_soubor() - Zapíše do souboru
   ↓
9. free() - Uvolní paměť
   ↓
10. return 0 - Program skončí
```

---

## 🐛 Možné problémy a řešení

| Problém | Příčina | Řešení |
|---------|---------|--------|
| "Soubor nebyl otevřen" | Soubor není v aktuálním adresáři | Zkopírovat `startovni_listina_kombinace_zeny.txt` do adresáře s programem |
| Zvláštní znaky v názvu | UTF-8 vs. Windows-1250 | Otevřít soubor s kódováním UTF-8 |
| Paměť neuvolněna | Zapomenuté `free()` | Vždy volat `free()` při konci programu |
| Chybné řazení | Funkce `porovnej()` má opačný logiku | Zkontrolovat znaménko (`return cas1 - cas2`) |
| Buffer overflow | Pole `char prijmeni[30]` příliš malé | Zvětšit rozměr pole |

---

## 📚 Použité funkce ze stdlib.h a string.h

| Funkce | Knihovna | Účel |
|--------|----------|------|
| `fopen()` | `stdio.h` | Otevřít soubor |
| `fgets()` | `stdio.h` | Přečíst řádek ze souboru |
| `fprintf()` | `stdio.h` | Zapsat do souboru |
| `fclose()` | `stdio.h` | Zavřít soubor |
| `strtok()` | `string.h` | Rozdělit řetězec |
| `strcmp()` | `string.h` | Porovnat řetězce |
| `strcpy()` | `string.h` | Zkopírovat řetězec |
| `strlen()` | `string.h` | Délka řetězce |
| `malloc()` | `stdlib.h` | Alokovat paměť |
| `realloc()` | `stdlib.h` | Realokovat paměť |
| `free()` | `stdlib.h` | Uvolnit paměť |
| `qsort()` | `stdlib.h` | Třídění quicksort |
| `atoi()` | `stdlib.h` | Převést na číslo |

---

## 🎓 Co se na tomto příkladu naučíš

1. **Čtení textových souborů** - `fopen()`, `fgets()`
2. **Parsování dat** - `strtok()`, `atoi()`
3. **Dynamická alokace paměti** - `malloc()`, `realloc()`, `free()`
4. **Struktury v C** - `typedef struct`
5. **Práce s poli struktur** - iterace, vyhledávání
6. **Třídění** - `qsort()` a vlastní porovnávací funkce
7. **Zápis do souborů** - `fprintf()`, `fclose()`
8. **Řetězcové operace** - `strcmp()`, `strcpy()`, `strlen()`
9. **Formátování výstupu** - specifikátory formátu

---

## 💡 Tipy pro vylepšení (domácí úkol)

1. **Vyhledávání bez ohledu na velikost písmen**
   ```c
   char *searchUpper = strdup(hledane);
   naVelkaP(searchUpper);
   ```

2. **Výstup v obou pořadích** (startovní i výsledkové)
   - Uložit původní pořadí do pole indexů

3. **Filtrace** - vybrat jen určitý stát
   ```c
   if (strcmp(zavodnik[i].stat, "AUT") == 0) { ... }
   ```

4. **Statistika** - průměrný čas, nejrychlejší čas
   ```c
   int soucet = 0;
   for (...) soucet += soucetCasu(...);
   int prumer = soucet / pocet;
   ```

5. **Kontrola vstupu** - ověřit formát souborů
   ```c
   if (pocet == 0) { printf("Soubor je prázdný\n"); }
   ```

---

## 📊 Výsledky běhu

**Vstupní data:** 10 závodnic
**Výstupní data:** Seřazeno podle kombinovaného času

**Top 3:**
1. 🥇 Michelle Gisinova (CHE) - 2:25,67
2. 🥈 Wendy Holdenerova (CHE) - 2:26,72
3. 🥉 Frederica Brignoneova (FRA) - 2:27,52

---

## ✅ Kontrolní seznam

- [x] Program se kompiluje bez chyb
- [x] Program se spouští bez chyb runtime
- [x] Načítá se správně ze vstupního souboru
- [x] Příjmení jsou v VELKÝCH písmenech
- [x] Výpis startovní listiny je správný
- [x] Vyhledávání funguje (LEDECKA)
- [x] Řazení je správné (od nejrychlejšího)
- [x] Výstupní soubor se vytvoří
- [x] Paměť je správně uvolněna
- [x] Formátování výstupu odpovídá vzoru

---

**Poslední aktualizace:** 19. října 2025  
**Status:** ✅ Hotovo a testováno
