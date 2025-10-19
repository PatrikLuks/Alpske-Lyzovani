# 🚀 Návod na řešení - Krok za krokem

Tento dokument vás provede řešením maturitního příkladu od začátku do konce.

---

## 📖 Fáze 1: Pochopení zadání

### Co máme dělat?

Zpracovat data z alpských závodů:
1. Načíst data ze souboru
2. Převést příjmení na VELKÁ PÍSMENA
3. Zobrazit startovní listinu
4. Vyhledat konkrétní závodnici
5. Seřadit podle výkonu
6. Uložit výsledky do souboru

### Formát vstupního souboru

```
1 Katharina Huberova AUT 1:35,68 53,11
^ startovní ^jméno    ^pří ^státní ^sjezd    ^slalom
  číslo                jmení     kód
```

**Oddělovače:** mezera, dvojtečka, čárka

---

## 🏗️ Fáze 2: Návrh datových struktur

### Kroku 1: Čas (CAS)

```c
// Reprezentace: minuty, vteřiny, setiny
typedef struct {
    int minuty;   // 0-2
    int vteriny;  // 0-59
    int setiny;   // 0-99
} CAS;

// Příklad: 1:35,68
// cas.minuty = 1
// cas.vteriny = 35
// cas.setiny = 68
```

**Proč?** Odpovídá lidskému vnímání času, snadný vstup/výstup

---

### Krok 2: Závodnice (ZAVODNIK)

```c
typedef struct {
    int startovniCislo;      // Klíč, unikátní
    char jmeno[30];          // Dynamické by bylo lepší, ale statické je OK
    char prijmeni[30];
    char stat[4];            // "CHE", "AUT", "CZE", ...
    CAS sjezd;               // Super-G
    CAS slalom;              // Slalom
} ZAVODNIK;
```

**Výhoda:** Všechny informace o jedné osobě na jednom místě

---

## 💾 Fáze 3: Implementace funkcí

### Funkce 1: Načítání ze souboru

```c
ZAVODNIK *otevriTo(int *pocet)
```

**Logika:**
```
1. Otevři soubor
   - if (soubor == NULL) → chyba
2. Inicializuj prázdné pole (NULL)
3. Smyčka - pro každý řádek:
   a. Realokuj paměť (pro 1 prvek více)
   b. Přečti řádek
   c. Parsuj pomocí strtok()
   d. Ulož do struktury
4. Zavři soubor
5. Vrať počet a ukazatel
```

**Praktické kroky:**

```c
// Krok 1: Deklarace
FILE *pFile = fopen("soubor.txt", "r");
char radek[100];
ZAVODNIK *zavodnik = NULL;
int pocet = 0;

// Krok 2: Čtení
while (fgets(radek, 100, pFile) != NULL) {
    // Realokace
    zavodnik = realloc(zavodnik, (pocet+1) * sizeof(ZAVODNIK));
    
    // Parsování
    char *token = strtok(radek, " :,");
    zavodnik[pocet].startovniCislo = atoi(token);
    
    // ... atd ...
    
    pocet++;
}

// Krok 3: Cleanup
fclose(pFile);
```

---

### Funkce 2: Konverze na velká písmena

```c
void naVelkaP(char *retezec)
```

**Logika:**
```
1. Projdi každý znak
2. Pokud je to malé písmeno (a-z):
   - Odečti 32 (ASCII rozdíl)
3. Konec
```

**ASCII tabulka:**
- 'a' = 97
- 'A' = 65
- Rozdíl = 32

```c
void naVelkaP(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = s[i] - 32;
        }
    }
}
```

---

### Funkce 3: Vyhledávání

```c
int vyhledej(ZAVODNIK *zavodnik, int pocet, char *hledane)
```

**Logika:**
```
1. Smyčka přes všechny závodnice
2. Porovnaj příjmení s hledaným
3. Pokud se shoduje: vrať index
4. Pokud se nepřechází nic: vrať -1
```

```c
int vyhledej(ZAVODNIK *z, int n, char *hledane) {
    for (int i = 0; i < n; i++) {
        if (strcmp(z[i].prijmeni, hledane) == 0) {
            return i;  // Nalezeno
        }
    }
    return -1;  // Nenalezeno
}
```

---

### Funkce 4: Konverze času na setiny

```c
int naSetiny(CAS cas)
```

**Logika:**
```
1 minuta = 60 sekund = 6000 setin
1 sekunda = 100 setin

naSetiny = minuty*6000 + vteriny*100 + setiny
```

```c
// Příklad: 1:35,68
int cas = 1*6000 + 35*100 + 68;
// cas = 6000 + 3500 + 68 = 9568
```

---

### Funkce 5: Součet časů

```c
int soucetCasu(CAS sjezd, CAS slalom)
```

**Logika:**
```
Volej naSetiny() pro oba časy
Sečti výsledky
```

```c
int soucetCasu(CAS s, CAS sl) {
    return naSetiny(s) + naSetiny(sl);
}
```

---

### Funkce 6: Porovnávací funkce pro qsort

```c
int porovnej(const void *a, const void *b)
```

**Logika:**
```
1. Castuj oba parametry na ZAVODNIK*
2. Vypočítej součet časů pro oba
3. Vrať: cas1 - cas2
   - Negativní → a bude dřív (lepší čas)
   - Kladné → b bude dřív
```

```c
int porovnej(const void *a, const void *b) {
    ZAVODNIK *z1 = (ZAVODNIK *)a;
    ZAVODNIK *z2 = (ZAVODNIK *)b;
    
    int c1 = soucetCasu(z1->sjezd, z1->slalom);
    int c2 = soucetCasu(z2->sjezd, z2->slalom);
    
    return c1 - c2;  // Vzestupně!
}
```

---

### Funkce 7: Zápis do souboru

```c
void vypis_soubor(ZAVODNIK *zavodnik, int pocet, const char *jmenoSouboru)
```

**Logika:**
```
1. Otevři soubor pro zápis
2. Napiš hlavičku
3. Smyčka přes závodnice:
   - Vypočítej časy
   - Vypočítej ztrátu (rozdíl od vítězky)
   - Napiš řádek
4. Zavři soubor
```

```c
void vypis_soubor(ZAVODNIK *z, int n, const char *soubor) {
    FILE *f = fopen(soubor, "w");
    if (f == NULL) {
        printf("Chyba: Nelze otevřít soubor\n");
        return;
    }
    
    fprintf(f, "Výsledky:\n");
    
    int nejLepsi = soucetCasu(z[0].sjezd, z[0].slalom);
    
    for (int i = 0; i < n; i++) {
        int cas = soucetCasu(z[i].sjezd, z[i].slalom);
        int ztrata = cas - nejLepsi;
        
        fprintf(f, "%d. %s %s - %02d,%02d zaostalosti\n",
                i+1, z[i].jmeno, z[i].prijmeni,
                ztrata/100, ztrata%100);
    }
    
    fclose(f);
}
```

---

## ⚙️ Fáze 4: Hlavní program (main)

```c
int main(void) {
    // 1. Deklarace
    ZAVODNIK *zavodnik;
    int pocet;
    
    // 2. Načtení dat
    zavodnik = otevriTo(&pocet);
    if (zavodnik == NULL) return 1;
    
    // 3. Převedení příjmení
    for (int i = 0; i < pocet; i++) {
        naVelkaP(zavodnik[i].prijmeni);
    }
    
    // 4. Výpis startovní listiny
    printf("=== STARTOVNÍ LISTINA ===\n");
    vypis(zavodnik, pocet);
    
    // 5. Vyhledávání
    printf("\n=== VYHLEDÁVÁNÍ ===\n");
    int idx = vyhledej(zavodnik, pocet, "LEDECKA");
    if (idx != -1) {
        printf("Nalezena: %s %s\n",
               zavodnik[idx].jmeno, zavodnik[idx].prijmeni);
    }
    
    // 6. Třídění
    printf("\n=== ŘAZENÍ ===\n");
    qsort(zavodnik, pocet, sizeof(ZAVODNIK), porovnej);
    
    // 7. Výpis výsledků
    printf("\n=== VÝSLEDKOVÁ LISTINA ===\n");
    for (int i = 0; i < pocet; i++) {
        int cas = soucetCasu(zavodnik[i].sjezd, zavodnik[i].slalom);
        printf("%d. %s %s - %d:%02d,%02d\n",
               i+1, zavodnik[i].jmeno, zavodnik[i].prijmeni,
               cas/6000, (cas%6000)/100, cas%100);
    }
    
    // 8. Zápis do souboru
    vypis_soubor(zavodnik, pocet, "vysledky.txt");
    
    // 9. Cleanup
    free(zavodnik);
    
    return 0;
}
```

---

## 🧪 Fáze 5: Testování

### Test 1: Kompilace
```bash
gcc -Wall -Wextra -std=c11 -o kombinace main.c
```
**Očekávání:** Bez chyb, bez varování

---

### Test 2: Spuštění
```bash
./kombinace
```
**Očekávání:** Program se spustí a provede všechny kroky

---

### Test 3: Výstupní data
```bash
cat vysledkova_listina_kombinace_zeny.txt
```
**Očekávání:** 
- 10 závodnic (řádků s daty)
- Seřazeno od nejrychlejší
- Michelle Gisinova na 1. místě
- Správné formátování

---

### Test 4: Kontrola paměti (Linux)
```bash
valgrind ./kombinace
```
**Očekávání:** Bez memory leaků

---

## ✅ Kontrolní seznam

Před odevzdáním zkontroluj:

- [ ] Program se kompiluje bez chyb
- [ ] Program se spouští bez segmentation faultu
- [ ] Načte se 10 řádků
- [ ] Všechna příjmení jsou v VELKÝCH písmenech
- [ ] Startovní listina se zobrazí správně
- [ ] Vyhledávání najde "LEDECKA" na pozici 2 (v původním pořadí)
- [ ] Výsledková listina je seřazena správně (Michelle první)
- [ ] Michelle Gisinova má nejmenší čas (2:25,67)
- [ ] Výstupní soubor se vytvoří
- [ ] Výstupní soubor má správný formát
- [ ] Program skončí bez chyb a uvolní paměť
- [ ] Kód je přehledný a komentovaný

---

## 🎓 Co jste se naučili

Po vyřešení tohoto příkladu zvládáte:

✅ Načítání a parsování textových souborů  
✅ Dynamickou alokaci paměti (malloc, realloc, free)  
✅ Struktury a pole struktur  
✅ Vyhledávání v datech  
✅ Třídění pomocí standardní knihovny (qsort)  
✅ Zápis do výstupních souborů  
✅ Formátování výstupu  

**To jsou základní dovednosti, které budete potřebovat v praxi a na další úrovni studia!**

---

**Hodně štěstí! 💪 Pokud se zasekneš, podívej se na soubor `KONCEPTY.md` pro detaily.**
