/*
 * ============================================================================
 * PROJEKT: Alpské lyžování - Kombinace Ženy
 * TYPU: Maturitní praktická prověrka z programování (2. ročník)
 * ============================================================================
 * 
 * POPIS:
 * Program zpracovává data z alpských závodů lyžování v kombinaci (sjezd+slalom)
 * Načítá data ze souboru, převádí příjmení na velká písmena, třídí podle výkonu
 * a exportuje výsledky do výstupního souboru.
 * 
 * HLAVNÍ FUNKCE:
 * 1. Načítání dat ze textového souboru
 * 2. Dynamická alokace paměti
 * 3. Parsování a strukturování dat
 * 4. Vyhledávání v datech
 * 5. Třídění pomocí qsort()
 * 6. Export výsledků do souboru
 * 
 * KOMPILACE: gcc -o kombinace main.c
 * SPUŠTĚNÍ: ./kombinace
 * 
 * ============================================================================
 */

#include <stdio.h>      // Standardní vstup/výstup (printf, scanf, FILE...)
#include <stdlib.h>     // Dynamická paměť, qsort, atoi...
#include <string.h>     // Operace se řetězci (strcmp, strcpy, strlen, strtok)

// ============================================================================
// DEFINICE KONSTANT
// ============================================================================

#define VSTUP "startovni_listina_kombinace_zeny.txt"  // Vstupní soubor
#define VYSTUP "vysledkova_listina_kombinace_zeny.txt" // Výstupní soubor
#define MAX 100         // Maximální délka řádku v souboru
#define ODDELOVACE " :," // Znaky, kterými se dělí data v souboru

// ============================================================================
// DEFINICE STRUKTUR
// ============================================================================

/*
 * Struktura CAS - reprezentuje čas v různých jednotkách
 * 
 * Příklad: 1:35,68 znamená:
 *  - minuty = 1
 *  - vteriny = 35
 *  - setiny = 68 (setiny vteřiny, tj. 0.68 sekundy)
 */
typedef struct {
    int minuty;        // Minuty (0-2)
    int vteriny;       // Vteřiny (0-59)
    int setiny;        // Setiny vteřiny (0-99)
} CAS;

/*
 * Struktura ZAVODNIK - všechny údaje o jedné závodnici
 * 
 * Příklad: 
 * startovniCislo = 2
 * jmeno = "Ester"
 * prijmeni = "Ledecka"
 * stat = "CZE"
 * sjezd = {1, 32, 43}  (1:32,43)
 * slalom = {0, 55, 89} (55,89)
 */
typedef struct {
    int startovniCislo;      // Pořadí startu v závodě (1-N)
    char jmeno[30];          // Křestní jméno (max 30 znaků)
    char prijmeni[30];       // Příjmení (max 30 znaků)
    char stat[4];            // Státní kód ISO (3 znaky + \0)
    CAS sjezd;               // Čas sjezdu (super-G)
    CAS slalom;              // Čas slalomu
} ZAVODNIK;

// ============================================================================
// DEKLARACE FUNKCÍ (FORWARD DECLARATIONS)
// ============================================================================

ZAVODNIK *otevriTo(int *pocet);
void vypis(ZAVODNIK *zavodnik, int pocet);
int naSetiny(CAS cas);
int soucetCasu(CAS sjezd, CAS slalom);
void naVelkaP(char *retezec);
int vyhledej(ZAVODNIK *zavodnik, int pocet, char *hledane);
int porovnej(const void *a, const void *b);
void vypis_soubor(ZAVODNIK *zavodnik, int pocet, const char *jmenoSouboru);

// ============================================================================
// FUNKCE: OTEVŘENÍ A NAČTENÍ SOUBORU
// ============================================================================

/*
 * FUNKCE: otevriTo()
 * 
 * ÚČEL: Načíst všechny závodnice ze souboru do paměti
 * 
 * PARAMETRY:
 *  - pocet: ukazatel na proměnnou, kam se uloží počet načtených řádků
 * 
 * VRACÍ:
 *  - Ukazatel na alokované pole struktury ZAVODNIK, nebo NULL při chybě
 * 
 * ALGORITMUS:
 *  1. Otevřeme soubor k čtení
 *  2. Pro každý řádek:
 *     a. Alokujeme (realokujeme) paměť pro nový prvek
 *     b. Parsujeme řádek podle oddělovačů
 *     c. Uložíme data do struktury
 *  3. Vrátíme alokované pole a počet prvků
 * 
 * TECHNICKÉ DETAILY:
 *  - Používáme realloc(), která v sobě obsahuje malloc()
 *  - strtok() dělí řetězec podle více oddělovačů najednou
 *  - Slalom ve vstupním souboru nemá minuty (jen sekundy,setiny)
 */
ZAVODNIK *otevriTo(int *pocet) {
    FILE *pFile;                // Ukazatel na otevřený soubor
    char mystring[MAX];         // Buffer pro jeden řádek (max 100 znaků)
    int radky = 0;              // Počitadlo řádků
    ZAVODNIK *zavodnik = NULL;  // Pole struktur (zatím prázdné)
    ZAVODNIK *tmpZavodnik = NULL; // Dočasný ukazatel pro realloc
    
    // Pokus o otevření souboru k čtení
    pFile = fopen(VSTUP, "r");
    if (pFile == NULL) {
        printf("Soubor %s nebyl otevren\n", VSTUP);
        return NULL;  // Návrat s chybou
    }
    
    // Čtení řádku po řádku z otevřeného souboru
    while (fgets(mystring, MAX, pFile) != NULL) {
        // Výpis řádku ze souboru (debug)
        puts(mystring);
        
        // REALOKACE PAMĚTI: Rozšíříme pole o jeden prvek
        // Vypočítáme nový požadovaný objem: (počet řádků + 1) * velikost jedné struktury
        tmpZavodnik = (ZAVODNIK *) realloc(zavodnik, (radky + 1) * sizeof(ZAVODNIK));
        
        if (tmpZavodnik != NULL) {
            // Realokace byla úspěšná
            zavodnik = tmpZavodnik;  // Aktualizujeme ukazatel
            
            // PARSOVÁNÍ ŘÁDKU
            // Připravíme pomocné proměnné
            char *pch;               // Ukazatel na aktuální token (slovo)
            int sloupce = 0;         // Čitadlo sloupců (1-9)
            
            // U slalomu jsou jen sekundy a setiny, minuty jsou 0
            zavodnik[radky].slalom.minuty = 0;
            
            // TOKENIZACE: Rozdělíme řádek podle oddělovačů
            // Příklad: "2 Ester Ledecka CZE 1:32,43 55,89"
            //          strtok vrátí: "2", "Ester", "Ledecka", ...
            pch = strtok(mystring, ODDELOVACE);
            
            while (pch != NULL) {
                sloupce++;  // Zvýšíme čitadlo
                
                // SWITCH: Podle sloupce vložíme data na správné místo
                switch (sloupce) {
                    case 1:
                        // Startovní číslo: "2" -> 2
                        zavodnik[radky].startovniCislo = atoi(pch);
                        break;
                    case 2:
                        // Jméno: "Ester" -> zavodnik[radky].jmeno
                        strcpy(zavodnik[radky].jmeno, pch);
                        break;
                    case 3:
                        // Příjmení: "Ledecka" -> zavodnik[radky].prijmeni
                        strcpy(zavodnik[radky].prijmeni, pch);
                        break;
                    case 4:
                        // Státní kód: "CZE" -> zavodnik[radky].stat
                        strcpy(zavodnik[radky].stat, pch);
                        break;
                    case 5:
                        // Sjezd - minuty: "1" -> zavodnik[radky].sjezd.minuty
                        zavodnik[radky].sjezd.minuty = atoi(pch);
                        break;
                    case 6:
                        // Sjezd - vteřiny: "32" -> zavodnik[radky].sjezd.vteriny
                        zavodnik[radky].sjezd.vteriny = atoi(pch);
                        break;
                    case 7:
                        // Sjezd - setiny: "43" -> zavodnik[radky].sjezd.setiny
                        zavodnik[radky].sjezd.setiny = atoi(pch);
                        break;
                    case 8:
                        // Slalom - vteřiny: "55" -> zavodnik[radky].slalom.vteriny
                        zavodnik[radky].slalom.vteriny = atoi(pch);
                        break;
                    case 9:
                        // Slalom - setiny: "89" -> zavodnik[radky].slalom.setiny
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
        
        // Zvýšíme počitadlo řádků
        radky++;
    }
    
    // Zavřeme soubor
    if (fclose(pFile) == EOF) {
        printf("soubor %s se nepodarilo zavrit.\n", VSTUP);
    }
    
    // Vrátíme počet načtených řádků přes ukazatel
    *pocet = radky;
    
    return zavodnik;  // Vrátíme alokované pole
}

// ============================================================================
// FUNKCE: VÝPIS STARTOVNÍ LISTINY
// ============================================================================

/*
 * FUNKCE: vypis()
 * 
 * ÚČEL: Vypsat závodnice v jejich aktuálním pořadí (startovní listina)
 * 
 * PARAMETRY:
 *  - zavodnik: pole struktur s daty závodnic
 *  - pocet: počet závodnic v poli
 * 
 * VRACÍ: nic (void)
 * 
 * FORMÁTOVÁNÍ:
 *  - %15d = číslo, zarovnáno doprava, šířka 15 znaků
 *  - %10s = řetězec, šířka 10 znaků
 *  - %02d = dvouciferné číslo s úvodní nulou (05, 09, 10)
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

// ============================================================================
// FUNKCE: KONVERZE ČASU NA JEDNOTNÉ JEDNOTKY
// ============================================================================

/*
 * FUNKCE: naSetiny()
 * 
 * ÚČEL: Převést čas z formátu MM:SS,CS na jednotný čas v setinách vteřiny
 * 
 * PARAMETRY:
 *  - cas: struktura CAS s minutami, vteřinami a setinami
 * 
 * VRACÍ: čas v setinách vteřiny (int)
 * 
 * MATEMATIK A:
 *  1 minuta = 60 sekund = 6000 setin
 *  1 sekunda = 100 setin
 *  
 *  Příklad: 1:35,68
 *    = 1*6000 + 35*100 + 68
 *    = 6000 + 3500 + 68
 *    = 9568 setin
 * 
 * VÝHODA: Lze porovnávat jako normální čísla (<, >, ==)
 */
int naSetiny(CAS cas) {
    return cas.minuty * 6000 + cas.vteriny * 100 + cas.setiny;
}

/*
 * FUNKCE: soucetCasu()
 * 
 * ÚČEL: Sečíst čas sjezdu a slalomu (kombinovaný čas)
 * 
 * PARAMETRY:
 *  - sjezd: struktura CAS se sjezdovým časem
 *  - slalom: struktura CAS se slalomovým časem
 * 
 * VRACÍ: součet obou časů v setinách vteřiny (int)
 * 
 * PŘÍKLAD:
 *  sjezd = 1:33,42 = 9342 setin
 *  slalom = 0:52,25 = 5225 setin
 *  součet = 14567 setin = 2:25,67
 */
int soucetCasu(CAS sjezd, CAS slalom) {
    return naSetiny(sjezd) + naSetiny(slalom);
}

// ============================================================================
// FUNKCE: KONVERZE NA VELKÁ PÍSMENA
// ============================================================================

/*
 * FUNKCE: naVelkaP()
 * 
 * ÚČEL: Převést všechna malá písmena na VELKÁ v daném řetězci
 * 
 * PARAMETRY:
 *  - retezec: ukazatel na řetězec (bude změněn in-situ!)
 * 
 * VRACÍ: nic (void)
 * 
 * MECHANIKA:
 *  - ASCII tabulka: 'a' = 97, 'z' = 122
 *                   'A' = 65, 'Z' = 90
 *  - Rozdíl: 97 - 65 = 32
 *  - Řešení: malé písmeno - 32 = velké písmeno
 * 
 * PŘÍKLAD:
 *  Input: "ledecka"
 *  Output: "LEDECKA"
 * 
 * POZNÁMKA: Funkce modifikuje řetězec na místě (in-place modification)
 */
void naVelkaP(char *retezec) {
    // Iterujeme přes všechny znaky v řetězci
    for (int i = 0; retezec[i] != '\0'; i++) {
        // Kontrola, zda je znak malé písmeno
        if (retezec[i] >= 'a' && retezec[i] <= 'z') {
            // Převod na velké písmeno: odečteme 32
            retezec[i] = retezec[i] - 32;
            // Alternativa: retezec[i] = toupper(retezec[i]); (z ctype.h)
        }
    }
}

// ============================================================================
// FUNKCE: VYHLEDÁVÁNÍ V DATECH
// ============================================================================

/*
 * FUNKCE: vyhledej()
 * 
 * ÚČEL: Najít závodnici podle jejího příjmení (LINEÁRNÍ VYHLEDÁVÁNÍ)
 * 
 * PARAMETRY:
 *  - zavodnik: pole struktur se závodnicemi
 *  - pocet: počet prvků v poli
 *  - hledane: hledané příjmení (musí být v VELKÝCH písmenech!)
 * 
 * VRACÍ: index prvku v poli, nebo -1 pokud není nalezeno
 * 
 * SLOŽITOST: O(n) - v nejhorším případě projdeme všechny prvky
 * 
 * PŘÍKLAD:
 *  int index = vyhledej(zavodnik, 10, "LEDECKA");
 *  if (index != -1) {
 *      printf("Nalezena: %s %s\n", zavodnik[index].jmeno, zavodnik[index].prijmeni);
 *  }
 */
int vyhledej(ZAVODNIK *zavodnik, int pocet, char *hledane) {
    // Procházíme všechny závodnice
    for (int i = 0; i < pocet; i++) {
        // Porovnáme příjmení s hledaným řetězcem
        // strcmp vrací 0, pokud jsou řetězce stejné
        if (strcmp(zavodnik[i].prijmeni, hledane) == 0) {
            return i;  // Vrátíme index
        }
    }
    return -1;  // Nenalezeno - speciální hodnota
}

// ============================================================================
// FUNKCE: POROVNÁVACÍ FUNKCE PRO QSORT
// ============================================================================

/*
 * FUNKCE: porovnej()
 * 
 * ÚČEL: Porovnat dvě závodnice pro účely třídění (qsort callback)
 * 
 * PARAMETRY:
 *  - a, b: generické ukazatele na prvky k porovnání
 *         (qsort je generic, tak musíme castovat na ZAVODNIK*)
 * 
 * VRACÍ:
 *  - < 0 (negativní): první prvek bude dřív (a < b)
 *  - = 0 (nula): prvky jsou si rovny
 *  - > 0 (kladné): druhý prvek bude dřív (a > b)
 * 
 * PRINCIP TŘÍDĚNÍ:
 *  - Chceme seřadit od NEJRYCHLEJŠÍHO (nejmenší čas)
 *  - Porovnáváme součet časů (sjezd + slalom)
 *  - Vrátíme: cas1 - cas2
 *    * Pokud cas1 < cas2 → vrátíme záporné číslo → a bude dřív (správně!)
 *    * Pokud cas1 > cas2 → vrátíme kladné číslo → b bude dřív (správně!)
 * 
 * PŘÍKLAD BĚHU:
 *  zavodnik[0]: Michelle Gisinova = 14567 setin
 *  zavodnik[1]: Wendy Holdenerova = 14672 setin
 *  
 *  Porovnání: 14567 - 14672 = -105 (negativní)
 *  Výsledek: Michelle bude dřív (správně!)
 */
int porovnej(const void *a, const void *b) {
    // Castujeme generické ukazatele na ZAVODNIK*
    ZAVODNIK *z1 = (ZAVODNIK *)a;
    ZAVODNIK *z2 = (ZAVODNIK *)b;
    
    // Vypočítáme součet časů (sjezd + slalom) pro obě závodnice
    int cas1 = soucetCasu(z1->sjezd, z1->slalom);
    int cas2 = soucetCasu(z2->sjezd, z2->slalom);
    
    // Vrátíme rozdíl (vzestupné pořadí - nejmenší časy první)
    return cas1 - cas2;
}

// ============================================================================
// FUNKCE: ZÁPIS VÝSLEDKŮ DO SOUBORU
// ============================================================================

/*
 * FUNKCE: vypis_soubor()
 * 
 * ÚČEL: Zapsat seřazené výsledky do výstupního souboru
 * 
 * PARAMETRY:
 *  - zavodnik: pole struktur se seřazenými závodnicemi
 *  - pocet: počet prvků v poli
 *  - jmenoSouboru: cesta/jméno výstupního souboru
 * 
 * VRACÍ: nic (void)
 * 
 * PROCES:
 *  1. Otevřeme soubor pro zápis (mode "w")
 *  2. Zapíšeme hlavičku
 *  3. Pro každou závodnici:
 *     - Vypočítáme celkový čas
 *     - Vypočítáme ztrátu vůči vítězce
 *     - Zapíšeme řádek
 *  4. Zavřeme soubor
 * 
 * VÝSTUP: Příklad řádku:
 *  1.   Michelle        GISINOVA    CHE    1:33,42   52,25    2:25,67  00,00
 * 
 * POZNÁMKA: Musíme POVINNĚ zavřít soubor (fclose)!
 */
void vypis_soubor(ZAVODNIK *zavodnik, int pocet, const char *jmenoSouboru) {
    // Otevření souboru pro zápis
    FILE *pFile = fopen(jmenoSouboru, "w");
    if (pFile == NULL) {
        printf("Soubor %s se nepodařilo otevřít pro zápis\n", jmenoSouboru);
        return;  // Brzký výstup - chyba
    }
    
    // Zápis hlavičky
    fprintf(pFile, "A L P S K E     L Y Z O V A N I  -  K O M B I N A C E   Z E N Y\n");
    fprintf(pFile, "--------------------------------------------------------------------\n");
    fprintf(pFile, "poradi   jmeno        prijmeni   stat  sjezd    slalom    celkem    ztrata\n");
    fprintf(pFile, "--------------------------------------------------------------------\n");
    
    // Zjistíme nejrychlejší čas (první v seřazeném poli)
    int nejLepsiCas = soucetCasu(zavodnik[0].sjezd, zavodnik[0].slalom);
    
    // Iterujeme přes všechny závodnice
    for (int i = 0; i < pocet; i++) {
        // Vypočítáme součet časů pro aktuální závodnici
        int celkovyCas = soucetCasu(zavodnik[i].sjezd, zavodnik[i].slalom);
        
        // Vypočítáme ztrátu (rozdíl od nejrychlejší)
        int ztrata = celkovyCas - nejLepsiCas;
        
        // Formatovaný zápis řádku
        fprintf(pFile, "%3d. %10s %15s %6s    %d:%02d,%02d   %02d,%02d    %d:%02d,%02d  %02d,%02d\n",
                i + 1,                           // Pořadí (1-N)
                zavodnik[i].jmeno,               // Jméno
                zavodnik[i].prijmeni,            // Příjmení
                zavodnik[i].stat,                // Státní kód
                zavodnik[i].sjezd.minuty,        // Sjezd: minuty
                zavodnik[i].sjezd.vteriny,       // Sjezd: vteřiny
                zavodnik[i].sjezd.setiny,        // Sjezd: setiny
                zavodnik[i].slalom.vteriny,      // Slalom: vteřiny
                zavodnik[i].slalom.setiny,       // Slalom: setiny
                (int)(celkovyCas / 6000),        // Celk. čas: minuty
                (int)((celkovyCas % 6000) / 100), // Celk. čas: vteřiny
                (celkovyCas % 100),              // Celk. čas: setiny
                (int)(ztrata / 100),             // Ztráta: vteřiny
                (ztrata % 100));                 // Ztráta: setiny
    }
    
    // Zavření souboru - NUTNÉ!
    fclose(pFile);
    printf("\nVýsledky byly zapsány do souboru: %s\n", jmenoSouboru);
}

// ============================================================================
// HLAVNÍ PROGRAM
// ============================================================================

/*
 * FUNKCE: main()
 * 
 * ÚČEL: Hlavní řídící program - orchestruje všechny kroku
 * 
 * VRACÍ: 0 = úspěch, 1 = chyba
 * 
 * LOGIKA:
 * 1. Načtení dat ze souboru do paměti
 * 2. Převedení příjmení na velká písmena
 * 3. Výpis startovní listiny
 * 4. Vyhledávání příkladu (demonstrace)
 * 5. Třídění podle výkonu
 * 6. Výpis seřazených výsledků
 * 7. Zápis do souboru
 * 8. Uvolnění paměti
 */
int main(void) {
    ZAVODNIK *zavodnik;  // Ukazatel na pole závodnic
    int pocet;           // Počet načtených závodnic
    
    // ========== KROK 1: NAČTENÍ DAT ZE SOUBORU ==========
    printf("Nacteni dat...\n");
    zavodnik = otevriTo(&pocet);
    if (zavodnik == NULL) {
        printf("Chyba pri nacitani souboru!\n");
        return 1;  // Chyba - ukončení programu
    }
    printf("Nacitano %d zavodnic.\n\n", pocet);
    
    // ========== KROK 2: PŘEVEDENÍ PŘÍJMENÍ NA VELKÁ PÍSMENA ==========
    printf("Prevod prijmeni na velka pismena...\n");
    for (int i = 0; i < pocet; i++) {
        naVelkaP(zavodnik[i].prijmeni);
    }
    printf("Hotovo.\n\n");
    
    // ========== KROK 3: VÝPIS STARTOVNÍ LISTINY ==========
    printf("=== STARTOVNÍ LISTINA ===\n\n");
    vypis(zavodnik, pocet);
    
    // ========== KROK 4: VYHLEDÁVÁNÍ - PŘÍKLAD ==========
    printf("\n=== VYHLEDÁVÁNÍ ===\n");
    char *hledane = "LEDECKA";  // Hledáme Ester Ledecka
    int index = vyhledej(zavodnik, pocet, hledane);
    if (index != -1) {
        printf("Nalezena: %s %s - startovní číslo %d\n", 
               zavodnik[index].jmeno, 
               zavodnik[index].prijmeni, 
               zavodnik[index].startovniCislo);
    } else {
        printf("Závodnice %s nebyla nalezena\n", hledane);
    }
    
    // ========== KROK 5: TŘÍDĚNÍ PODLE VÝKONU ==========
    printf("\n=== ŘAZENÍ PODLE VÝKONU ===\n");
    printf("Serazuji data podle souctu casu...\n");
    // qsort sortuje pole in-place pomocí Quicksort algoritmu
    qsort(zavodnik, pocet, sizeof(ZAVODNIK), porovnej);
    printf("Hotovo.\n");
    
    // ========== KROK 6: VÝPIS SEŘAZENÝCH VÝSLEDKŮ ==========
    printf("\n=== VÝSLEDKOVÁ LISTINA (seřazená) ===\n\n");
    printf("Alpske lyzovani - KOMBINACE ZENY\n");
    printf("--------------------------------------------------------------------\n");
    printf("poradi   jmeno        prijmeni   stat      sjezd    slalom    celkem\n");
    printf("--------------------------------------------------------------------\n");
    
    for (int i = 0; i < pocet; i++) {
        // Vypočítáme celkový čas
        int celkovyCas = soucetCasu(zavodnik[i].sjezd, zavodnik[i].slalom);
        
        // Vypíšeme řádek s výsledkem
        printf("%3d. %10s %15s %6s    %d:%02d,%02d   %02d,%02d    %d:%02d,%02d\n",
               i + 1,                              // Pořadí (1-N)
               zavodnik[i].jmeno,                  // Jméno
               zavodnik[i].prijmeni,               // Příjmení
               zavodnik[i].stat,                   // Státní kód
               zavodnik[i].sjezd.minuty,           // Sjezd: minuty
               zavodnik[i].sjezd.vteriny,          // Sjezd: vteřiny
               zavodnik[i].sjezd.setiny,           // Sjezd: setiny
               zavodnik[i].slalom.vteriny,         // Slalom: vteřiny
               zavodnik[i].slalom.setiny,          // Slalom: setiny
               (int)(celkovyCas / 6000),           // Celk. čas: minuty
               (int)((celkovyCas % 6000) / 100),   // Celk. čas: vteřiny
               (celkovyCas % 100));                // Celk. čas: setiny
    }
    
    // ========== KROK 7: ZÁPIS DO VÝSTUPNÍHO SOUBORU ==========
    printf("\n");
    vypis_soubor(zavodnik, pocet, VYSTUP);
    
    // ========== KROK 8: UVOLNĚNÍ PAMĚTI ==========
    printf("\nOsvobozovani pameti...\n");
    free(zavodnik);  // DŮLEŽITÉ! Vrátíme alokovanou paměť
    printf("Hotovo.\n");
    
    // ========== KONEC PROGRAMU ==========
    printf("\nProgram skoncil uspesne.\n");
    return 0;  // Úspěch
}
