#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VSTUP "startovni_listina_kombinace_zeny.txt"
#define VYSTUP "vysledkova_listina_kombinace_zeny.txt"
#define MAX 100
#define ODDELOVACE " :,"

typedef struct {
    int minuty;
    int vteriny;
    int setiny;
} CAS;

typedef struct {
    int startovniCislo;
    char jmeno[30];
    char prijmeni[30];
    char stat[4];
    CAS sjezd;
    CAS slalom;
} ZAVODNIK;

ZAVODNIK *otevriTo(int *pocet) {
    FILE *pFile;
    char mystring[MAX];
    int radky = 0;
    ZAVODNIK *zavodnik = NULL;
    ZAVODNIK *tmpZavodnik = NULL;
    pFile = fopen(VSTUP, "r");
    if (pFile == NULL) {
        printf("Soubor %s nebyl otevren\n", VSTUP);
        return NULL;
    }
    while (fgets(mystring, MAX, pFile) != NULL) {
        puts(mystring);
        tmpZavodnik = (ZAVODNIK *) realloc(zavodnik, (radky + 1) * sizeof(ZAVODNIK));
        if (tmpZavodnik != NULL) {
            zavodnik = tmpZavodnik;
            //parsovani
            char *pch;
            int sloupce = 0;
            //nastaveni minut u slalomu na 0
            zavodnik[radky].slalom.minuty = 0;
            pch = strtok(mystring, ODDELOVACE);
            while (pch != NULL) {
                sloupce++;
                switch (sloupce) {
                    case 1:
                        zavodnik[radky].startovniCislo = atoi(pch);
                        break;
                    case 2:
                        strcpy(zavodnik[radky].jmeno, pch);
                        break;
                    case 3:
                        strcpy(zavodnik[radky].prijmeni, pch);
                        break;
                    case 4:
                        strcpy(zavodnik[radky].stat, pch);
                        break;
                    case 5:
                        zavodnik[radky].sjezd.minuty = atoi(pch);
                        break;
                    case 6:
                        zavodnik[radky].sjezd.vteriny = atoi(pch);
                        break;
                    case 7:
                        zavodnik[radky].sjezd.setiny = atoi(pch);
                        break;
                    case 8:
                        zavodnik[radky].slalom.vteriny = atoi(pch);
                        break;
                    case 9:
                        zavodnik[radky].slalom.setiny = atoi(pch);
                        break;
                }
                //printf("%s\n", pch);
                pch = strtok(NULL, ODDELOVACE);

            }
        } else {
            free(zavodnik);
            puts("Error (re)allocating memory");
            break;
        }
        radky++;
    }
    if (fclose(pFile) == EOF) {
        printf("soubor %s se nepodarilo zavrit.\n", VSTUP);
    }

    *pocet = radky;
    return zavodnik;
}

void vypis(ZAVODNIK *zavodnik, int pocet) {
    printf("Alpske lyzovani startovni listina K O M B I N A C E     Z E N Y\n");
    printf("--------------------------------------------------------------------\n");
    printf("startovni cislo      jmeno        prijmeni   stat      sjezd  slalom\n");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < pocet; i++) {
        printf("%15d %10s %15s %6s    %d:%02d,%02d   %02d,%02d\n",
               zavodnik[i].startovniCislo, zavodnik[i].jmeno, zavodnik[i].prijmeni, zavodnik[i].stat,
               zavodnik[i].sjezd.minuty, zavodnik[i].sjezd.vteriny, zavodnik[i].sjezd.setiny,
               zavodnik[i].slalom.vteriny, zavodnik[i].slalom.setiny);
    }
}

int naSetiny(CAS cas) {
    return cas.minuty * 6000 + cas.vteriny * 100 + cas.setiny;
}

int soucetCasu(CAS sjezd, CAS slalom) {
    return naSetiny(sjezd) + naSetiny(slalom);
}

// Převede řetězec na VELKÁ PÍSMENA
void naVelkaP(char *retezec) {
    for (int i = 0; retezec[i] != '\0'; i++) {
        if (retezec[i] >= 'a' && retezec[i] <= 'z') {
            retezec[i] = retezec[i] - 32; // ASCII: 'a' je 97, 'A' je 65
        }
    }
}

// Vyhledávání podle příjmení
int vyhledej(ZAVODNIK *zavodnik, int pocet, char *hledane) {
    for (int i = 0; i < pocet; i++) {
        if (strcmp(zavodnik[i].prijmeni, hledane) == 0) {
            return i;
        }
    }
    return -1; // Nenalezeno
}

// Porovnávací funkce pro qsort - řadí dle součtu časů (vzestupně)
int porovnej(const void *a, const void *b) {
    ZAVODNIK *z1 = (ZAVODNIK *)a;
    ZAVODNIK *z2 = (ZAVODNIK *)b;
    
    int cas1 = soucetCasu(z1->sjezd, z1->slalom);
    int cas2 = soucetCasu(z2->sjezd, z2->slalom);
    
    return cas1 - cas2;
}

// Výpis do souboru
void vypis_soubor(ZAVODNIK *zavodnik, int pocet, const char *jmenoSouboru) {
    FILE *pFile = fopen(jmenoSouboru, "w");
    if (pFile == NULL) {
        printf("Soubor %s se nepodařilo otevřít pro zápis\n", jmenoSouboru);
        return;
    }
    
    fprintf(pFile, "A L P S K E     L Y Z O V A N I  -  K O M B I N A C E   Z E N Y\n");
    fprintf(pFile, "--------------------------------------------------------------------\n");
    fprintf(pFile, "poradi   jmeno        prijmeni   stat  sjezd    slalom    celkem    ztrata\n");
    fprintf(pFile, "--------------------------------------------------------------------\n");
    
    int nejLepsiCas = soucetCasu(zavodnik[0].sjezd, zavodnik[0].slalom);
    
    for (int i = 0; i < pocet; i++) {
        int celkovyCas = soucetCasu(zavodnik[i].sjezd, zavodnik[i].slalom);
        int ztrata = celkovyCas - nejLepsiCas;
        
        fprintf(pFile, "%3d. %10s %15s %6s    %d:%02d,%02d   %02d,%02d    %d:%02d,%02d  %02d,%02d\n",
                i + 1, zavodnik[i].jmeno, zavodnik[i].prijmeni, zavodnik[i].stat,
                zavodnik[i].sjezd.minuty, zavodnik[i].sjezd.vteriny, zavodnik[i].sjezd.setiny,
                zavodnik[i].slalom.vteriny, zavodnik[i].slalom.setiny,
                (int)(ztrata / 6000), (int)((ztrata % 6000) / 100), (ztrata % 100),
                (int)(ztrata / 100), (ztrata % 100));
    }
    
    fclose(pFile);
    printf("\nVýsledky byly zapsány do souboru: %s\n", jmenoSouboru);
}


int main(void) {
    ZAVODNIK *zavodnik;
    int pocet;
    
    // 1. Načtení dat ze souboru
    zavodnik = otevriTo(&pocet);
    if (zavodnik == NULL) return 1;
    
    // 2. Převedení všech příjmení na VELKÁ PÍSMENA
    for (int i = 0; i < pocet; i++) {
        naVelkaP(zavodnik[i].prijmeni);
    }
    
    // 3. Výpis startovní listiny
    printf("\n=== STARTOVNÍ LISTINA ===\n\n");
    vypis(zavodnik, pocet);
    
    // 4. Vyhledávání - příklad
    printf("\n=== VYHLEDÁVÁNÍ ===\n");
    char *hledane = "LEDECKA";
    int index = vyhledej(zavodnik, pocet, hledane);
    if (index != -1) {
        printf("Nalezena: %s %s - startovní číslo %d\n", 
               zavodnik[index].jmeno, zavodnik[index].prijmeni, zavodnik[index].startovniCislo);
    } else {
        printf("Závodnice %s nebyla nalezena\n", hledane);
    }
    
    // 5. Řazení podle součtu časů
    printf("\n=== ŘAZENÍ PODLE VÝKONU ===\n");
    qsort(zavodnik, pocet, sizeof(ZAVODNIK), porovnej);
    
    // 6. Výpis seřazených výsledků
    printf("\n=== VÝSLEDKOVÁ LISTINA (seřazená) ===\n\n");
    printf("Alpske lyzovani - KOMBINACE ZENY\n");
    printf("--------------------------------------------------------------------\n");
    printf("poradi   jmeno        prijmeni   stat      sjezd    slalom    celkem\n");
    printf("--------------------------------------------------------------------\n");
    
    for (int i = 0; i < pocet; i++) {
        int celkovyCas = soucetCasu(zavodnik[i].sjezd, zavodnik[i].slalom);
        printf("%3d. %10s %15s %6s    %d:%02d,%02d   %02d,%02d    %d:%02d,%02d\n",
               i + 1, zavodnik[i].jmeno, zavodnik[i].prijmeni, zavodnik[i].stat,
               zavodnik[i].sjezd.minuty, zavodnik[i].sjezd.vteriny, zavodnik[i].sjezd.setiny,
               zavodnik[i].slalom.vteriny, zavodnik[i].slalom.setiny,
               (int)(celkovyCas / 6000), (int)((celkovyCas % 6000) / 100), (celkovyCas % 100));
    }
    
    // 7. Zápis do výstupního souboru
    vypis_soubor(zavodnik, pocet, VYSTUP);
    
    // 8. Uvolnění paměti
    free(zavodnik);

    return 0;
}
