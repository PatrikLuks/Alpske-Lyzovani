/*
 * ============================================================================
 * PROJEKT: Alpské lyžování - Kombinace Ženy
 * TYP: Maturitní praktická prověrka z programování (2. ročník)
 * ============================================================================
 * 
 * POPIS:
 * Program zpracovává data alpských lyžařů v kombinaci (sjezd + slalom).
 * Načítá data ze souboru, třídí podle výkonu a exportuje výsledky.
 * 
 * HLAVNÍ FUNKCE:
 * - Dynamická alokace paměti (malloc/realloc)
 * - Parsování CSV-like formátu (strtok)
 * - Vyhledávání (strcmp)
 * - Třídění (qsort)
 * - Formátované výstupy
 * 
 * KOMPILACE: gcc -Wall -Wextra -std=c11 -o kombinace main.c
 * SPUŠTĚNÍ: ./kombinace
 * ============================================================================
 */

#include <stdio.h>      // Standardní I/O (printf, fopen, fprintf)
#include <stdlib.h>     // Dynamická paměť (malloc, realloc, free), qsort, atoi
#include <string.h>     // Operace se řetězci (strcmp, strcpy, strtok, strlen)

// ============================================================================
// DEFINICE KONSTANT
// ============================================================================

#define VSTUP "startovni_listina_kombinace_zeny.txt"  // Vstupní soubor
#define VYSTUP "vysledkova_listina_kombinace_zeny.txt" // Výstupní soubor
#define MAX 100          // Maximální délka řádku (buffer)
#define ODDELOVACE " :," // Znaky, kterými se dělí data v souboru

// ============================================================================
// DEFINICE STRUKTUR
// ============================================================================

/**
 * Struktura CAS - reprezentace času v různých jednotkách
 * 
 * Příklad: čas 1:35,68 znamená:
 *   - minuty = 1
 *   - vteriny = 35
 *   - setiny = 68 (setiny vteřiny, tj. 0.68 sekund)
 * 
 * Pro srovnávání se převádí na jednotnou jednotku (setiny):
 *   1*6000 + 35*100 + 68 = 9568 setin
 */
typedef struct {
    int minuty;   // Minuty (0-2)
    int vteriny;  // Vteřiny (0-59)
    int setiny;   // Setiny vteřiny (0-99)
} CAS;

/**
 * Struktura ZAVODNIK - všechny údaje o jedné závodnici
 * 
 * Příklad:
 *   startovniCislo = 2
 *   jmeno = "Ester"
 *   prijmeni = "LEDECKA" (po normalizaci)
 *   stat = "CZE"
 *   sjezd = {1, 32, 43}   // 1:32,43
 *   slalom = {0, 55, 89}  // 0:55,89 (0 minut, protože chybí)
 */
typedef struct {
    int startovniCislo;  // Pořadí startu (1-N)
    char jmeno[30];      // Křestní jméno (max 30 znaků)
    char prijmeni[30];   // Příjmení (max 30 znaků, v VELKÝCH PÍSMENECH)
    char stat[4];        // Státní kód ISO (3 znaky + \0)
    CAS sjezd;           // Čas sjezdu (super-G)
    CAS slalom;          // Čas slalomu
} ZAVODNIK;

/**
 * FUNKCE: otevriTo()
 * 
 * ÚČEL: Načte všechny závodnice ze vstupního souboru do dynamického pole
 * 
 * PARAMETRY:
 *   - pocet: ukazatel na proměnnou, kam se uloží počet načtených řádků
 * 
 * VRACÍ:
 *   - Ukazatel na alokované pole struktur ZAVODNIK, nebo NULL při chybě
 * 
 * ALGORITMUS:
 *   1. Otevře soubor k čtení
 *   2. Pro každý řádek:
 *      - Realokuje paměť pro nový prvek (radky+1)
 *      - Parsuje řádek podle oddělovačů (" :,")
 *      - Uloží data do struktury
 *   3. Vrátí alokované pole a počet řádků přes ukazatel
 * 
 * POZNÁMKY:
 *   - Slalom ve vstupním souboru nemá minuty (jen sekundy,setiny)
 *   - strtok() modifikuje původní řetězec (vkládá \0)
 *   - realloc() automaticky zahrnuje malloc() pro první alokaci
 */
ZAVODNIK *otevriTo(int *pocet) {
    FILE *pFile;                    // Ukazatel na otevřený soubor
    char mystring[MAX];             // Buffer pro jeden řádek (max 100 znaků)
    int radky = 0;                  // Počitadlo řádků
    ZAVODNIK *zavodnik = NULL;      // Pole struktur (zatím prázdné)
    ZAVODNIK *tmpZavodnik = NULL;   // Dočasný ukazatel pro bezpečný realloc
    
    // Pokus o otevření souboru k čtení
    pFile = fopen(VSTUP, "r");
    if (pFile == NULL) {
        printf("Soubor %s nebyl otevren\n", VSTUP);
        return NULL;
    }
    
    // Čtení řádku po řádku z otevřeného souboru
    while (fgets(mystring, MAX, pFile) != NULL) {
        // Výpis řádku (debug - vidí se, co se načítá)
        puts(mystring);
        
        // REALOKACE PAMĚTI: Rozšíříme pole o jeden prvek
        // Vypočítáme nový požadovaný objem: (počet řádků + 1) * velikost jedné struktury
        tmpZavodnik = (ZAVODNIK *) realloc(zavodnik, (radky + 1) * sizeof(ZAVODNIK));
        
        if (tmpZavodnik != NULL) {
            // Realokace byla úspěšná
            zavodnik = tmpZavodnik;  // Aktualizujeme ukazatel na nové místo
            
            // PARSOVÁNÍ ŘÁDKU
            char *pch;               // Ukazatel na aktuální token (slovo/číslo)
            int sloupce = 0;         // Čitadlo sloupců (1-9)
            
            // Slalom ve vstupním souboru má jen sekundy a setiny (bez minut)
            // Proto si inicializujeme minuty na 0
            zavodnik[radky].slalom.minuty = 0;
            
            // TOKENIZACE: Rozdělíme řádek podle oddělovačů
            // Příklad: "2 Ester Ledecka CZE 1:32,43 55,89"
            // strtok vrátí postupně: "2", "Ester", "Ledecka", "CZE", "1", "32", "43", "55", "89"
            pch = strtok(mystring, ODDELOVACE);
            
            // Smyčka pokračuje, dokud jsou tokeny k dispozici
            while (pch != NULL) {
                sloupce++;  // Zvýšíme počitadlo sloupců
                
                // SWITCH: Podle sloupce vložíme data na správné místo ve struktuře
                switch (sloupce) {
                    case 1:  // Startovní číslo: "2" → 2
                        zavodnik[radky].startovniCislo = atoi(pch);
                        break;
                    case 2:  // Jméno: "Ester" → zavodnik[radky].jmeno
                        strcpy(zavodnik[radky].jmeno, pch);
                        break;
                    case 3:  // Příjmení: "Ledecka" → zavodnik[radky].prijmeni
                        strcpy(zavodnik[radky].prijmeni, pch);
                        break;
                    case 4:  // Státní kód: "CZE" → zavodnik[radky].stat
                        strcpy(zavodnik[radky].stat, pch);
                        break;
                    case 5:  // Sjezd - minuty: "1" → zavodnik[radky].sjezd.minuty
                        zavodnik[radky].sjezd.minuty = atoi(pch);
                        break;
                    case 6:  // Sjezd - vteřiny: "32" → zavodnik[radky].sjezd.vteriny
                        zavodnik[radky].sjezd.vteriny = atoi(pch);
                        break;
                    case 7:  // Sjezd - setiny: "43" → zavodnik[radky].sjezd.setiny
                        zavodnik[radky].sjezd.setiny = atoi(pch);
                        break;
                    case 8:  // Slalom - vteřiny: "55" → zavodnik[radky].slalom.vteriny
                        zavodnik[radky].slalom.vteriny = atoi(pch);
                        break;
                    case 9:  // Slalom - setiny: "89" → zavodnik[radky].slalom.setiny
                        zavodnik[radky].slalom.setiny = atoi(pch);
                        break;
                }
                
                // Pokračujeme s dalším tokenem
                pch = strtok(NULL, ODDELOVACE);
            }
        } else {
            // Chyba při realokaci - uvolníme paměť a skončíme
            free(zavodnik);
            puts("Error (re)allocating memory");
            break;
        }
        
        // Zvýšíme počitadlo řádků pro příští iteraci
        radky++;
    }
    
    // Uzavřeme soubor
    if (fclose(pFile) == EOF) {
        printf("soubor %s se nepodarilo zavrit.\n", VSTUP);
    }

    // Vrátíme počet načtených řádků přes ukazatel
    *pocet = radky;
    
    return zavodnik;  // Vrátíme alokované pole
}

/**
 * FUNKCE: vypis()
 * 
 * ÚČEL: Vypsat závodnice v jejich aktuálním pořadí (startovní nebo výsledková listina)
 * 
 * PARAMETRY:
 *   - zavodnik: pole struktur s daty všech závodnic
 *   - pocet: počet závodnic v poli
 * 
 * VRACÍ: nic (void) - funkce jen vypíše na terminál
 * 
 * FORMÁTOVÁNÍ:
 *   - %15d = číslo zarovnáno doprava, šířka 15 znaků
 *   - %10s = řetězec, šířka 10 znaků
 *   - %02d = dvouciferné číslo s úvodní nulou (05, 09, 10)
 */
void vypis(ZAVODNIK *zavodnik, int pocet) {
    printf("Alpske lyzovani startovni listina K O M B I N A C E     Z E N Y\n");
    printf("--------------------------------------------------------------------\n");
    printf("startovni cislo      jmeno        prijmeni   stat      sjezd  slalom\n");
    printf("--------------------------------------------------------------------\n");
    
    // Smyčka přes všechny závodnice
    for (int i = 0; i < pocet; i++) {
        printf("%15d %10s %15s %6s    %d:%02d,%02d   %02d,%02d\n",
               zavodnik[i].startovniCislo,      // Startovní číslo
               zavodnik[i].jmeno,               // Křestní jméno
               zavodnik[i].prijmeni,            // Příjmení
               zavodnik[i].stat,                // Státní kód
               zavodnik[i].sjezd.minuty,        // Sjezd: minuty
               zavodnik[i].sjezd.vteriny,       // Sjezd: vteřiny
               zavodnik[i].sjezd.setiny,        // Sjezd: setiny
               zavodnik[i].slalom.vteriny,      // Slalom: vteřiny
               zavodnik[i].slalom.setiny);      // Slalom: setiny
    }
}

/**
 * FUNKCE: naSetiny()
 * 
 * ÚČEL: Převést čas z formátu MM:SS,CS na jednotný čas v setinách vteřiny
 * 
 * PARAMETRY:
 *   - cas: struktura CAS s minutami, vteřinami a setinami
 * 
 * VRACÍ: čas v setinách vteřiny (int)
 * 
 * MATEMATIKA:
 *   1 minuta = 60 sekund = 6000 setin
 *   1 sekunda = 100 setin
 *   
 *   Příklad: 1:35,68
 *     = 1*6000 + 35*100 + 68
 *     = 6000 + 3500 + 68
 *     = 9568 setin
 * 
 * VÝHODA: Lze porovnávat jako normální čísla (<, >, ==)
 */
int naSetiny(CAS cas) {
    return cas.minuty * 6000 + cas.vteriny * 100 + cas.setiny;
}

/**
 * FUNKCE: soucetCasu()
 * 
 * ÚČEL: Sečíst čas sjezdu a slalomu (kombinovaný čas)
 * 
 * PARAMETRY:
 *   - sjezd: struktura CAS s časem sjezdu
 *   - slalom: struktura CAS s časem slalomu
 * 
 * VRACÍ: součet obou časů v setinách (int)
 * 
 * PŘÍKLAD:
 *   sjezd = 1:35,68 = 9568 setin
 *   slalom = 0:53,11 = 5311 setin
 *   součet = 14879 setin = 2:28,79
 */
int soucetCasu(CAS sjezd, CAS slalom) {
    return naSetiny(sjezd) + naSetiny(slalom);
}

/**
 * FUNKCE: naVelkaP()
 * 
 * ÚČEL: Převést všechny malé písmeny v řetězci na VELKÁ PÍSMENA
 * 
 * PARAMETRY:
 *   - retezec: ukazatel na řetězec, který se má modifikovat
 * 
 * VRACÍ: nic (void) - modifikuje řetězec na místě
 * 
 * MECHANIKA:
 *   ASCII hodnoty: 'a'=97, 'b'=98, ..., 'z'=122
 *                  'A'=65, 'B'=66, ..., 'Z'=90
 *   Rozdíl: 97 - 65 = 32
 *   
 *   Příklad: 'a' - 32 = 97 - 32 = 65 = 'A'
 * 
 * POZNÁMKA: Modifikuje původní řetězec (ne kopii)
 */
void naVelkaP(char *retezec) {
    for (int i = 0; retezec[i] != '\0'; i++) {
        // Kontrola, zda je znak malé písmeno (a-z)
        if (retezec[i] >= 'a' && retezec[i] <= 'z') {
            // Odečteme 32 (ASCII rozdíl mezi malým a velkým písmenem)
            retezec[i] = retezec[i] - 32;
        }
    }
}

/**
 * FUNKCE: vyhledej()
 * 
 * ÚČEL: Lineárně vyhledat závodnici v poli podle příjmení
 * 
 * PARAMETRY:
 *   - zavodnik: pole struktur všech závodnic
 *   - pocet: počet závodnic v poli
 *   - hledane: příjmení, které hledáme (musí být v VELKÝCH PÍSMENECH!)
 * 
 * VRACÍ: index v poli (0-pocet), nebo -1 pokud nenalezeno
 * 
 * ALGORITMUS: Lineární vyhledávání - procházíme pole od začátku do konce
 *   Složitost: O(n) - v nejhorším případě musíme projít všechny prvky
 * 
 * PŘÍKLAD:
 *   vyhledej(zavodnik, 10, "LEDECKA") → vrátí index (např. 1)
 *   zavodnik[1].prijmeni == "LEDECKA" ✓
 */
int vyhledej(ZAVODNIK *zavodnik, int pocet, char *hledane) {
    for (int i = 0; i < pocet; i++) {
        // strcmp vrací 0, pokud jsou řetězce stejné
        if (strcmp(zavodnik[i].prijmeni, hledane) == 0) {
            return i;  // Nalezeno - vrátíme index
        }
    }
    return -1;  // Nenalezeno - vrátíme -1
}

/**
 * FUNKCE: porovnej()
 * 
 * ÚČEL: Porovnávací funkce pro qsort() - třídí podle součtu časů vzestupně
 * 
 * PARAMETRY:
 *   - a: ukazatel na první prvek (ZAVODNIK*)
 *   - b: ukazatel na druhý prvek (ZAVODNIK*)
 * 
 * VRACÍ: 
 *   - negativní číslo, pokud a < b (a má být dřív)
 *   - 0, pokud a == b (jsou si rovny)
 *   - pozitivní číslo, pokud a > b (b má být dřív)
 * 
 * ALGORITMUS: Vypočítáme součet časů obou závodnic a porovnáme
 *   a - b vrátí negativní číslo, když a < b (vzestupně)
 *   b - a by vrátil negativní číslo, když b < a (sestupně)
 * 
 * POZNÁMKA: Tato funkce se volá tisíckrát během qsort()
 */
int porovnej(const void *a, const void *b) {
    // Přetypujeme void* na ZAVODNIK*
    ZAVODNIK *z1 = (ZAVODNIK *)a;
    ZAVODNIK *z2 = (ZAVODNIK *)b;
    
    // Vypočítáme součet časů obou závodnic
    int cas1 = soucetCasu(z1->sjezd, z1->slalom);
    int cas2 = soucetCasu(z2->sjezd, z2->slalom);
    
    // Vrátíme rozdíl (vzestupně - nejrychlejší první)
    return cas1 - cas2;
}

/**
 * FUNKCE: vypis_soubor()
 * 
 * ÚČEL: Zápis finálních výsledků do výstupního souboru (formátovaně)
 * 
 * PARAMETRY:
 *   - zavodnik: pole struktur všech závodnic (již seřazené!)
 *   - pocet: počet závodnic v poli
 *   - jmenoSouboru: cesta/název souboru pro zápis
 * 
 * VRACÍ: nic (void)
 * 
 * ČINNOST:
 *   1. Otevře soubor pro zápis (w = write, přepíše existující)
 *   2. Napíše hlavičku (formátování, názvy sloupců)
 *   3. Pro každou závodnici:
 *      - Vypočítá celkový čas (sjezd + slalom)
 *      - Vypočítá ztrátu (rozdíl od nejrychlejší)
 *      - Zformátuje a napíše řádek
 *   4. Zavře soubor
 * 
 * POZNÁMKA: Pole musí být již seřazené podle výkonu (qsort)
 *           Nejrychlejší je na pozici 0, proto se používá pro výpočet ztráty
 */
void vypis_soubor(ZAVODNIK *zavodnik, int pocet, const char *jmenoSouboru) {
    // Otevřeme soubor pro zápis
    FILE *pFile = fopen(jmenoSouboru, "w");
    if (pFile == NULL) {
        printf("Soubor %s se nepodařilo otevřít pro zápis\n", jmenoSouboru);
        return;
    }
    
    // Zápis hlavičky
    fprintf(pFile, "A L P S K E     L Y Z O V A N I  -  K O M B I N A C E   Z E N Y\n");
    fprintf(pFile, "--------------------------------------------------------------------\n");
    fprintf(pFile, "poradi   jmeno        prijmeni   stat  sjezd    slalom    celkem    ztrata\n");
    fprintf(pFile, "--------------------------------------------------------------------\n");
    
    // Nejrychlejší čas je na první pozici (pole je seřazené)
    int nejLepsiCas = soucetCasu(zavodnik[0].sjezd, zavodnik[0].slalom);
    
    // Smyčka přes všechny závodnice
    for (int i = 0; i < pocet; i++) {
        // Vypočítáme celkový čas (sjezd + slalom)
        int celkovyCas = soucetCasu(zavodnik[i].sjezd, zavodnik[i].slalom);
        // Vypočítáme ztrátu (rozdíl od nejrychlejší)
        int ztrata = celkovyCas - nejLepsiCas;
        
        // Zápis řádku s formátováním
        fprintf(pFile, "%3d. %10s %15s %6s    %d:%02d,%02d   %02d,%02d    %d:%02d,%02d  %02d,%02d\n",
                i + 1,                                              // Pořadí (1-N)
                zavodnik[i].jmeno,                                  // Jméno
                zavodnik[i].prijmeni,                               // Příjmení
                zavodnik[i].stat,                                   // Státní kód
                zavodnik[i].sjezd.minuty,                           // Sjezd: minuty
                zavodnik[i].sjezd.vteriny,                          // Sjezd: vteřiny
                zavodnik[i].sjezd.setiny,                           // Sjezd: setiny
                zavodnik[i].slalom.vteriny,                         // Slalom: vteřiny
                zavodnik[i].slalom.setiny,                          // Slalom: setiny
                (int)(celkovyCas / 6000),                           // Celkem: minuty
                (int)((celkovyCas % 6000) / 100),                   // Celkem: vteřiny
                (celkovyCas % 100),                                 // Celkem: setiny
                (int)(ztrata / 100),                                // Ztrata: vteřiny
                (ztrata % 100));                                    // Ztrata: setiny
    }
    
    // Zavřeme soubor
    fclose(pFile);
    printf("\nVýsledky byly zapsány do souboru: %s\n", jmenoSouboru);
}


/**
 * FUNKCE: main()
 * 
 * ÚČEL: Hlavní program - orchestruje celý pracovní proces
 * 
 * ALGORITMUS (8 kroků):
 *   1. Načtení dat ze souboru do paměti (dynamicky alokované)
 *   2. Normalizace dat - příjmení na VELKÁ PÍSMENA
 *   3. Výpis startovní listiny (původní pořadí)
 *   4. Vyhledávání - příklad vyhledání jedné závodnice (LEDECKA)
 *   5. Řazení podle výkonu (součet sjezdu + slalomu)
 *   6. Výpis seřazené výsledkové listiny na terminál
 *   7. Zápis do výstupního souboru (s ztrátou)
 *   8. Uvolnění dynamicky alokované paměti
 * 
 * VRACÍ: 
 *   - 0 pokud vše OK
 *   - 1 při chybě (např. soubor nenalezen)
 */
int main(void) {
    ZAVODNIK *zavodnik;  // Ukazatel na dynamické pole
    int pocet;           // Počet načtených závodnic
    
    // ========== KROK 1: NAČTENÍ DAT ==========
    // Funkce otevriTo() vrátí alokované pole a počet řádků přes ukazatel
    zavodnik = otevriTo(&pocet);
    if (zavodnik == NULL) return 1;  // Chyba - soubor nenalezen nebo alokace selhala
    
    // ========== KROK 2: NORMALIZACE - VELKÁ PÍSMENA ==========
    // Převedeme všechna příjmení na VELKÁ PÍSMENA (pro konzistenci a vyhledávání)
    for (int i = 0; i < pocet; i++) {
        naVelkaP(zavodnik[i].prijmeni);
    }
    
    // ========== KROK 3: VÝPIS STARTOVNÍ LISTINY ==========
    // Vypíšeme závodnice v původním pořadí (jak jsou v souboru)
    printf("\n=== STARTOVNÍ LISTINA ===\n\n");
    vypis(zavodnik, pocet);
    
    // ========== KROK 4: VYHLEDÁVÁNÍ - PŘÍKLAD ==========
    // Ukázka lineárního vyhledávání
    printf("\n=== VYHLEDÁVÁNÍ ===\n");
    char *hledane = "LEDECKA";  // Hledáme českou závodnici
    int index = vyhledej(zavodnik, pocet, hledane);
    if (index != -1) {
        // Nalezeno - vypíšeme informace o závodnici
        printf("Nalezena: %s %s - startovní číslo %d\n", 
               zavodnik[index].jmeno, zavodnik[index].prijmeni, zavodnik[index].startovniCislo);
    } else {
        // Nenalezeno - vypíšeme zprávu
        printf("Závodnice %s nebyla nalezena\n", hledane);
    }
    
    // ========== KROK 5: ŘAZENÍ PODLE VÝKONU ==========
    // Použijeme standardní funkci qsort() s naší porovnávací funkcí
    printf("\n=== ŘAZENÍ PODLE VÝKONU ===\n");
    qsort(zavodnik, pocet, sizeof(ZAVODNIK), porovnej);
    
    // ========== KROK 6: VÝPIS SEŘAZENÉ VÝSLEDKOVÉ LISTINY ==========
    // Vypíšeme závodnice seřazené podle výkonu (nejrychlejší první)
    printf("\n=== VÝSLEDKOVÁ LISTINA (seřazená) ===\n\n");
    printf("Alpske lyzovani - KOMBINACE ZENY\n");
    printf("--------------------------------------------------------------------\n");
    printf("poradi   jmeno        prijmeni   stat      sjezd    slalom    celkem\n");
    printf("--------------------------------------------------------------------\n");
    
    // Smyčka přes všechny (nyní seřazené) závodnice
    for (int i = 0; i < pocet; i++) {
        // Vypočítáme celkový čas (sjezd + slalom)
        int celkovyCas = soucetCasu(zavodnik[i].sjezd, zavodnik[i].slalom);
        
        // Zformátujeme a vypíšeme řádek
        printf("%3d. %10s %15s %6s    %d:%02d,%02d   %02d,%02d    %d:%02d,%02d\n",
               i + 1,                                              // Pořadí (1-N)
               zavodnik[i].jmeno,                                  // Jméno
               zavodnik[i].prijmeni,                               // Příjmení
               zavodnik[i].stat,                                   // Státní kód
               zavodnik[i].sjezd.minuty,                           // Sjezd: minuty
               zavodnik[i].sjezd.vteriny,                          // Sjezd: vteřiny
               zavodnik[i].sjezd.setiny,                           // Sjezd: setiny
               zavodnik[i].slalom.vteriny,                         // Slalom: vteřiny
               zavodnik[i].slalom.setiny,                          // Slalom: setiny
               (int)(celkovyCas / 6000),                           // Celkem: minuty
               (int)((celkovyCas % 6000) / 100),                   // Celkem: vteřiny
               (celkovyCas % 100));                                // Celkem: setiny
    }
    
    // ========== KROK 7: ZÁPIS DO SOUBORU ==========
    // Uložíme výsledky do formátovaného výstupního souboru
    vypis_soubor(zavodnik, pocet, VYSTUP);
    
    // ========== KROK 8: UVOLNĚNÍ PAMĚTI ==========
    // Velmi důležité! Všechna dynamicky alokovaná paměť se musí uvolnit
    free(zavodnik);
    zavodnik = NULL;  // Bezpečná praxe (nastavení na NULL)

    return 0;  // Program skončil bez chyb
}
