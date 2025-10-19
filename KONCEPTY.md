# 🎓 Klíčové koncepty a shrnutí - Kombinace Ženy

## 📚 Obsahuje

1. Základní koncepty
2. Algoritmy
3. Datové struktury
4. Práce s pamětí
5. Příklady kódu
6. Časté chyby

---

## 1️⃣ ZÁKLADNÍ KONCEPTY

### A) Dynamická alokace paměti

Proč ji potřebujeme?
- **Statické pole:** `ZAVODNIK arr[100];` - zabereme VŽDY 100 prvků
- **Dynamické pole:** Zabereme pouze kolik potřebujeme!

```c
// Alokace pro 10 prvků
ZAVODNIK *arr = malloc(10 * sizeof(ZAVODNIK));

// Realokace pro 15 prvků (bez ztráty dat!)
arr = realloc(arr, 15 * sizeof(ZAVODNIK));

// Uvolnění když už nepotřebujeme
free(arr);
arr = NULL;  // Bezpečná praxe
```

**Příklad v naší aplikaci:**
```c
// Na začátku: 0 prvků
zavodnik = NULL;

// Po 1. řádku: 1 prvek
zavodnik = realloc(zavodnik, 1 * sizeof(ZAVODNIK));

// Po 2. řádku: 2 prvky
zavodnik = realloc(zavodnik, 2 * sizeof(ZAVODNIK));
// ... atd ...
```

---

### B) Struktury (struct)

Seskupuje více proměnných pod jedním jménem.

```c
// BEZ struktury:
int cas1_minuty, cas1_vteriny, cas1_setiny;
int cas2_minuty, cas2_vteriny, cas2_setiny;
// Chaos!

// SE strukturou:
struct CAS {
    int minuty;
    int vteriny;
    int setiny;
};

CAS cas1, cas2;  // Přehledné!
```

**Přístup k prvkům:**
```c
CAS cas;
cas.minuty = 1;
cas.vteriny = 35;
cas.setiny = 68;

// Nebo přes ukazatel:
CAS *pCas = &cas;
pCas->minuty = 1;  // Ekvivalentní s cas.minuty
```

---

### C) Parsování řetězců

Rozdělení řetězce na jednotlivé části (tokeny).

```c
// Vstup: "2 Ester Ledecka CZE 1:32,43 55,89"
// Oddělovače: " :,"

char *pch = strtok(mystring, " :,");
while (pch != NULL) {
    printf("Token: %s\n", pch);
    pch = strtok(NULL, " :,");
}

// Výstup:
// Token: 2
// Token: Ester
// Token: Ledecka
// Token: CZE
// Token: 1
// Token: 32
// Token: 43
// Token: 55
// Token: 89
```

**Pozor:** `strtok()` modifikuje původní řetězec (vkládá `\0`)!

---

## 2️⃣ ALGORITMY

### A) Lineární vyhledávání

```c
int vyhledej(ZAVODNIK *zavodnik, int pocet, char *hledane) {
    for (int i = 0; i < pocet; i++) {
        if (strcmp(zavodnik[i].prijmeni, hledane) == 0) {
            return i;  // Nalezeno
        }
    }
    return -1;  // Nenalezeno
}
```

**Složitost:** O(n) - v nejhorším případě projdeme N prvků
**Výhoda:** Jednoduchý, funguje na neseřazeném poli
**Nevýhoda:** Pomalý pro velké datové sady

---

### B) Třídění - Quicksort (qsort)

C standardní knihovna obsahuje optimalizovanou implementaci Quicksortu.

```c
// Porovnávací funkce
int porovnej(const void *a, const void *b) {
    ZAVODNIK *z1 = (ZAVODNIK *)a;
    ZAVODNIK *z2 = (ZAVODNIK *)b;
    int cas1 = soucetCasu(z1->sjezd, z1->slalom);
    int cas2 = soucetCasu(z2->sjezd, z2->slalom);
    return cas1 - cas2;  // Vzestupně
}

// Třídění
qsort(zavodnik, pocet, sizeof(ZAVODNIK), porovnej);
```

**Mechanika `qsort()`:**
1. Vybere "pivot" prvek
2. Rozdělí pole na menší a větší prvky
3. Rekurzivně třídí obě části
4. Spojí je dohromady

**Složitost:** O(n log n) v průměru
**Výhoda:** Rychlý, in-place třídění
**Pozor:** Modifikuje pole na místě!

**Porovnávací funkce - pravidla:**
```c
// Vzestupně (od nejmenšího):
return a - b;  // a < b → negativní, a bude dřív ✓

// Sestupně (od největšího):
return b - a;  // a > b → negativní, a bude dřív ✓

// Podle řetězce:
return strcmp(a->name, b->name);  // Abecedně
```

---

### C) Konverze jednotek

Převod času na jednotnou jednotku (setiny) pro srovnávání.

```
Vstup: MM:SS,CS (1:35,68)
          ↓ (konverze)
Výstup: setiny (9568)

Matematika:
1 minuta = 60 sekund = 6000 setin
1 sekunda = 100 setin

naSetiny(CAS cas) {
    return cas.minuty * 6000 + cas.vteriny * 100 + cas.setiny;
}

Příklad:
1:35,68 = 1*6000 + 35*100 + 68 = 9568
0:52,25 = 0*6000 + 52*100 + 25 = 5225
Součet: 14793 setin = 2:47,93
```

**Výhoda:** Snadné porovnávání a počítání rozdílů

---

## 3️⃣ DATOVÉ STRUKTURY

### Struktura CAS

```c
typedef struct {
    int minuty;   // 0-2 (max cca 2:59,99)
    int vteriny;  // 0-59
    int setiny;   // 0-99
} CAS;
```

**Proč tímto způsobem?**
- Odpovídá lidskému vnímání času
- Čitelnost pro uživatele
- Snadnější zacházení se vstupem/výstupem

**Alternativa:**
```c
typedef struct {
    int setiny_celkem;  // Všechno v sedinách
} CAS_ALT;
```
- Jednodušší pro výpočty
- Obtížnější pro vstup/výstup

---

### Struktura ZAVODNIK

```c
typedef struct {
    int startovniCislo;      // Klíč (unikátní identifikátor)
    char jmeno[30];          // Omezení: max 29 + '\0'
    char prijmeni[30];
    char stat[4];            // 3 znaky + '\0' (ISO 3166-1)
    CAS sjezd;               // Vnořená struktura
    CAS slalom;              // Vnořená struktura
} ZAVODNIK;
```

**Velikost v paměti:**
```
int = 4 B
char[30] = 30 B
CAS (3 × int) = 12 B

Celkem: 4 + 30 + 30 + 4 + 12 + 12 = 92 B

Pole 10 prvků: 10 × 92 = 920 B
```

---

## 4️⃣ PRÁCE S PAMĚTÍ

### Diagram paměti

```
Stack (automatická paměť):
┌─────────────────────┐
│ int pocet = 10      │ (alokován automaticky)
│ char *pch           │ (ukazatel - 8 B na 64-bit)
│ ...                 │
└─────────────────────┘

Heap (dynamická paměť):
┌─────────────────────┐
│ ZAVODNIK arr[10]    │ (musíme alokovat sami!)
│ arr[0].startovniCislo = 1
│ arr[0].jmeno = "Katharina"
│ ...                 │
│ arr[9].prijmeni = "PLESKOVOVA"
└─────────────────────┘
```

### Správná práce s pamětí

```c
// ✅ SPRÁVNĚ
ZAVODNIK *zavodnik = NULL;
zavodnik = realloc(zavodnik, 10 * sizeof(ZAVODNIK));
if (zavodnik == NULL) {
    printf("Chyba: nedostatek paměti\n");
    return 1;
}
// ... používáme zavodnik ...
free(zavodnik);
zavodnik = NULL;  // Bezpečná praxe

// ❌ ŠPATNĚ
ZAVODNIK *zavodnik = malloc(10 * sizeof(ZAVODNIK));
// ... někde se chyba ...
// free se nikdy nezavolá - memory leak!

// ❌ ŠPATNĚ
ZAVODNIK *zavodnik = malloc(10 * sizeof(ZAVODNIK));
free(zavodnik);
printf("%s\n", zavodnik[0].jmeno);  // Use-after-free!

// ❌ ŠPATNĚ
ZAVODNIK zavodnik[1000000];  // Stack overflow!
```

---

## 5️⃣ PŘÍKLADY KÓDU

### Příklad 1: Manipulace se strukturami

```c
// Vytvoření
ZAVODNIK z;
z.startovniCislo = 1;
strcpy(z.jmeno, "Michelle");
strcpy(z.prijmeni, "Gisinova");
strcpy(z.stat, "CHE");

// Nastavení času
z.sjezd.minuty = 1;
z.sjezd.vteriny = 33;
z.sjezd.setiny = 42;

// Výpočet
int cas = soucetCasu(z.sjezd, z.slalom);
printf("Celkový čas: %d setin\n", cas);
```

---

### Příklad 2: Práce s polem struktur

```c
// Alokace
ZAVODNIK *zavodnici = malloc(10 * sizeof(ZAVODNIK));

// Přístup
zavodnici[0].startovniCislo = 1;
zavodnici[0].sjezd.minuty = 1;

// Přes ukazatel
ZAVODNIK *z = &zavodnici[0];
z->startovniCislo = 1;  // Ekvivalentní s zavodnici[0].startovniCislo

// Iterace
for (int i = 0; i < 10; i++) {
    printf("%s\n", zavodnici[i].jmeno);
}

// Dealokace
free(zavodnici);
```

---

### Příklad 3: Parsování a alokace

```c
char *radek = "2 Ester Ledecka CZE 1:32,43 55,89";
ZAVODNIK z;

char *copy = strdup(radek);  // Kopie (musíme free!)
char *pch = strtok(copy, " :,");

z.startovniCislo = atoi(pch); pch = strtok(NULL, " :,");
strcpy(z.jmeno, pch); pch = strtok(NULL, " :,");
strcpy(z.prijmeni, pch); pch = strtok(NULL, " :,");
// ... atd ...

free(copy);
```

---

## 6️⃣ ČASTÉ CHYBY

### Chyba 1: Zapomenutá realokace

```c
// ❌ ŠPATNĚ: Přepsání prvního prvku
ZAVODNIK *zavodnik = NULL;
zavodnik[0].startovniCislo = 1;  // Segmentation fault!

// ✅ SPRÁVNĚ
ZAVODNIK *zavodnik = malloc(sizeof(ZAVODNIK));
zavodnik[0].startovniCislo = 1;
free(zavodnik);
```

---

### Chyba 2: Buffer overflow

```c
// ❌ ŠPATNĚ: Příliš dlouhý řetězec
char prijmeni[30];
strcpy(prijmeni, "VerlyDlouhéPříjmeníKteréNemáVtomToPoliMísto");  // Overflow!

// ✅ SPRÁVNĚ: Použití strncpy
strncpy(prijmeni, "VerlyDlouhéPříjmeníKteréNemáVtomToPoliMísto", 29);
prijmeni[29] = '\0';  // Ručně zakončíme
```

---

### Chyba 3: Špatná porovnávací funkce

```c
// ❌ ŠPATNĚ: Opačné pořadí
int porovnej(const void *a, const void *b) {
    return b - a;  // Sestupně - vítězka bude poslední!
}

// ✅ SPRÁVNĚ
int porovnej(const void *a, const void *b) {
    return a - b;  // Vzestupně - vítězka bude první!
}
```

---

### Chyba 4: Uninitiálizované proměnné

```c
// ❌ ŠPATNĚ
int cas;
if (cas > 100) { ... }  // cas obsahuje náhodné číslo!

// ✅ SPRÁVNĚ
int cas = 0;
if (cas > 100) { ... }
```

---

### Chyba 5: Nesprávné znaménko u atoi

```c
// ❌ ŠPATNĚ: atoi vrací int, ne char
char c = atoi("5");  // Chyba!

// ✅ SPRÁVNĚ
int x = atoi("5");
char c = (char)x;
```

---

## 7️⃣ TABULKA FUNKCÍ

| Funkce | Knihovna | Účel |
|--------|----------|------|
| `malloc(n)` | stdlib.h | Alokace n bajtů |
| `realloc(p, n)` | stdlib.h | Změna velikosti alokace |
| `free(p)` | stdlib.h | Uvolnění paměti |
| `fopen(n, m)` | stdio.h | Otevření souboru |
| `fgets(s, n, f)` | stdio.h | Čtení řádku |
| `fprintf(f, ...)` | stdio.h | Zápis do souboru |
| `fclose(f)` | stdio.h | Zavření souboru |
| `strtok(s, d)` | string.h | Dělení řetězce |
| `strcmp(a, b)` | string.h | Porovnání řetězců |
| `strcpy(d, s)` | string.h | Kopírování řetězce |
| `strncpy(d, s, n)` | string.h | Bezpečné kopírování |
| `strlen(s)` | string.h | Délka řetězce |
| `atoi(s)` | stdlib.h | Řetězec → int |
| `atof(s)` | stdlib.h | Řetězec → double |
| `qsort(a, n, s, c)` | stdlib.h | Třídění |
| `toupper(c)` | ctype.h | Malé → Velké |
| `tolower(c)` | ctype.h | Velké → Malé |

---

## 8️⃣ TESTOVACÍ SCÉNÁŘE

### Test 1: Správné načtení

```
Očekávaný výstup: 10 řádků
Skutečný výstup: 10 řádků
Status: ✅ PASS
```

### Test 2: Konverze na velká písmena

```
Vstup:  "ledecka"
Výstup: "LEDECKA"
Status: ✅ PASS
```

### Test 3: Vyhledávání

```
Hledáme: "LEDECKA"
Vráceno: index 3 (po seřazení bude index 3)
Status: ✅ PASS
```

### Test 4: Řazení

```
Před: [2:28,79, 2:25,67, 2:30,70, ...]
Po:   [2:25,67, 2:26,72, 2:27,52, ...]
Status: ✅ PASS
```

### Test 5: Výstupní soubor

```
Soubor existuje: ANO
Počet řádků: 13 (2 hlavička + 10 dat + 1 separator)
Formátování OK: ANO
Status: ✅ PASS
```

---

## 9️⃣ Quick Reference

### ASCII tabulka (důležité znaky)

```
'0' = 48    '9' = 57
'A' = 65    'Z' = 90
'a' = 97    'z' = 122
' ' = 32    '\0' = 0
'\n' = 10
```

### Specifikátory formátu

```c
%d      - int
%f      - float/double
%s      - řetězec (char*)
%c      - jeden znak
%p      - ukazatel
%x      - hexadecimální
%02d    - int se 2 místy a nulou vepředu (05, 09)
%10s    - řetězec na 10 znaků
%-10s   - řetězec zarovnán vlevo
```

---

**Poslední aktualizace:** 19. října 2025
