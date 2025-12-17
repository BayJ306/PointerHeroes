#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stddef.h>

#define MAX_HEROES 100
#define MAX_NAME 50
#define MAX_CLASS 20

typedef struct {
    char name[MAX_NAME];
    char className[MAX_CLASS];
    int level;
    int hp;
    int attack;
    int defense;
    int luck;
    float power;
} Hero;

void computeHeroPower(Hero *h);
void computeAllPowers(Hero squad[], int n);
void printAllHeroes(const Hero squad[], int n);
int findHeroByName(const Hero squad[], int n, const char *name);
void sortByPowerDesc(Hero squad[], int n);
void showHeroesByClass(const Hero squad[], int n, const char *className);
void simulateBattle(Hero squad[], int n);
void addNewHero(Hero squad[], int *n);
void removeHero(Hero squad[], int *n);
int loadHeroesFromFile(const char *filename, Hero squad[], int maxN);
void saveHeroesToFile(const char *filename, Hero squad[], int n);
void printMenu(void);
void clearInputBuffer(void);
int strcasecmp_custom(const char *s1, const char *s2);

void getAutoFilePath(char *dest, const char *filename)
{
    const char *fullpath = __FILE__;
    const char *lastSlash = strrchr(fullpath, '/');
    const char *lastBackslash = strrchr(fullpath, '\\');
    
    const char *p = NULL;
    if (lastSlash && lastBackslash) {
        p = (lastSlash > lastBackslash) ? lastSlash : lastBackslash;
    } else if (lastSlash) {
        p = lastSlash;
    } else if (lastBackslash) {
        p = lastBackslash;
    }
    if (p != NULL) {
        ptrdiff_t diff = p - fullpath;
        size_t path_len = (diff > 0) ? (size_t)diff : 0;
        
        strncpy(dest, fullpath, path_len);
        dest[path_len] = '\0';
        
        strncat(dest, "/", 1);
        strncat(dest, filename, strlen(filename));
    } else {
        
        strncpy(dest, filename, 1023);
        dest[1023] = '\0';
    }
}

int main(void) {
    Hero squad[MAX_HEROES];
    int n = 0;
    int choice;
    char filename[1024];
    char searchName[MAX_NAME];
    char className[MAX_CLASS];
    
    srand((unsigned int)time(NULL));
    
    n = loadHeroesFromFile("heroes.txt", squad, MAX_HEROES);

    if (n == 0) {
        char autoPath[1024];
        getAutoFilePath(autoPath, "heroes.txt");
        n = loadHeroesFromFile(autoPath, squad, MAX_HEROES);

        if (n > 0) {
            printf("Debug: Loaded from %s\n", autoPath);
        }
    }

    if (n > 0) {
        computeAllPowers(squad, n);
        printf("\n");
        printf("HERO SQUAD MANAGER & BATTLE SIMULATOR\n");
        printf("[AUTO-LOAD] Loaded %d heroes!\n", n);
    } else {
        printf("\n");
        printf("HERO SQUAD MANAGER & BATTLE SIMULATOR\n");
        printf("Could not auto-load 'heroes.txt'\n");
    }
    
    printf("\n");
    printf("HERO SQUAD MANAGER & BATTLE SIMULATOR\n");
    printf("Welcome to the Kingdom of C-land!\n");
    
    while (1) {
        printMenu();
        printf("Your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("\nInvalid input! Please enter a number.\n");
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                printf("\nEnter filename (e.g., heroes.txt): ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';

                int loaded = loadHeroesFromFile(filename, squad, MAX_HEROES);

                if (loaded == 0) {
                    char autoPath[1024];
                    getAutoFilePath(autoPath, filename);
                    loaded = loadHeroesFromFile(autoPath, squad, MAX_HEROES);
                }

                n = loaded;
                            
                if (n > 0) {
                    computeAllPowers(squad, n);
                    printf("Loaded %d heroes successfully!\n", n);
                } else {
                    printf("Failed to load heroes from file.\n");
                }
                break;
                
            case 2:
                if (n >= MAX_HEROES) {
                    printf("\nSquad is full! Cannot add more heroes.\n");
                } else {
                    addNewHero(squad, &n);
                }
                break;
                
            case 3:
                if (n == 0) {
                    printf("\nNo heroes in squad to remove!\n");
                } else {
                    removeHero(squad, &n);
                }
                break;
                
            case 4:
                printAllHeroes(squad, n);
                break;
                
            case 5:
                if (n == 0) {
                    printf("\nNo heroes in squad!\n");
                    break;
                }
                printf("\nEnter hero name: ");
                scanf("%s", searchName);
                clearInputBuffer();
                int idx = findHeroByName(squad, n, searchName);
                if (idx >= 0) {
                    printf("\nHero Found!\n");
                    printf("%-15s: %s\n", "Name", squad[idx].name);
                    printf("%-15s: %s\n", "Class", squad[idx].className);
                    printf("%-15s: %d\n", "Level", squad[idx].level);
                    printf("%-15s: %d\n", "HP", squad[idx].hp);
                    printf("%-15s: %d\n", "Attack", squad[idx].attack);
                    printf("%-15s: %d\n", "Defense", squad[idx].defense);
                    printf("%-15s: %d\n", "Luck", squad[idx].luck);
                    printf("%-15s: %.2f\n", "Power Score", squad[idx].power);
                } else {
                    printf("\nHero '%s' not found!\n", searchName);
                }
                break;
                
            case 6:
                if (n == 0) {
                    printf("\nNo heroes in squad!\n");
                    break;
                }
                printf("\nEnter class name: ");
                scanf("%s", className);
                clearInputBuffer();
                showHeroesByClass(squad, n, className);
                break;
                
            case 7:
                if (n == 0) {
                    printf("\nNo heroes in squad!\n");
                    break;
                }
                sortByPowerDesc(squad, n);
                printf("\nHeroes sorted by power (descending)!\n");
                printAllHeroes(squad, n);
                break;
                
            case 8:
                if (n < 2) {
                    printf("\nNeed at least 2 heroes to battle!\n");
                    break;
                }
                simulateBattle(squad, n);
                break;
                
            case 9:
                if (n == 0) {
                    printf("\nNo heroes to save!\n");
                    break;
                }
                printf("\nEnter filename to save: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                saveHeroesToFile(filename, squad, n);
                break;
                
            case 0:
                printf("\nThank you for defending C-land! Goodbye!\n\n");
                return 0;
                
            default:
                printf("\nInvalid choice! Please select 0-9.\n");
        }
        printf("\nPress Enter to continue...");
        getchar();
    }
    return 0;
}

void computeHeroPower(Hero *h) {
    h->power = h->level * 0.5 + h->attack / 2.0 + h->defense / 3.0 + h->hp / 20.0;
}

void computeAllPowers(Hero squad[], int n) {
    for (int i = 0; i < n; i++) {
        computeHeroPower(&squad[i]);
    }
}

void printAllHeroes(const Hero squad[], int n) {
    if (n == 0) {
        printf("\nNo heroes in squad!\n");
        return;
    }
    printf("\nHERO SQUAD ROSTER\n");
    printf("%-12s %-10s %-5s %-5s %-6s %-7s %-5s %-7s\n",
           "Name", "Class", "Lvl", "HP", "Atk", "Def", "Luck", "Power");
    
    for (int i = 0; i < n; i++) {
        printf("%-12s %-10s %-5d %-5d %-6d %-7d %-5d %-7.2f\n",
               squad[i].name,
               squad[i].className,
               squad[i].level,
               squad[i].hp,
               squad[i].attack,
               squad[i].defense,
               squad[i].luck,
               squad[i].power);
    }
    printf("");
}

int findHeroByName(const Hero squad[], int n, const char *name) {
    for (int i = 0; i < n; i++) {
        if (strcasecmp_custom(squad[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void sortByPowerDesc(Hero squad[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (squad[j].power < squad[j + 1].power) {
                Hero temp = squad[j];
                squad[j] = squad[j + 1];
                squad[j + 1] = temp;
            }
        }
    }
}

void showHeroesByClass(const Hero squad[], int n, const char *className) {
    int found = 0;
    
    printf("\nHeroes of class '%s'\n\n", className);
    
    for (int i = 0; i < n; i++) {
        if (strcasecmp_custom(squad[i].className, className) == 0) {
            if (!found) {
                printf("%-12s %-5s %-5s %-6s %-7s %-5s %-7s\n",
                       "Name", "Lvl", "HP", "Atk", "Def", "Luck", "Power");
            }
            printf("%-12s %-5d %-5d %-6d %-7d %-5d %-7.2f\n",
                   squad[i].name,
                   squad[i].level,
                   squad[i].hp,
                   squad[i].attack,
                   squad[i].defense,
                   squad[i].luck,
                   squad[i].power);
            found++;
        }
    }
    
    if (!found) {
        printf("No heroes found with class '%s'.\n", className);
    } else {
        printf("\nTotal: %d hero(es)\n", found);
    }
}

void simulateBattle(Hero squad[], int n) {
    char name1[MAX_NAME], name2[MAX_NAME];
    int idx1, idx2;
    
    printf("\nBATTLE ARENA\n\n");
    printAllHeroes(squad, n);
    
    printf("\nEnter first hero name: ");
    scanf("%s", name1);
    clearInputBuffer();
    
    printf("Enter second hero name: ");
    scanf("%s", name2);
    clearInputBuffer();
    
    idx1 = findHeroByName(squad, n, name1);
    idx2 = findHeroByName(squad, n, name2);
    
    if (idx1 < 0) {
        printf("\nHero '%s' not found!\n", name1);
        return;
    }
    if (idx2 < 0) {
        printf("\nHero '%s' not found!\n", name2);
        return;
    }
    if (idx1 == idx2) {
        printf("\nCannot battle the same hero!\n");
        return;
    }
    
    Hero h1 = squad[idx1];
    Hero h2 = squad[idx2];
    int hp1 = h1.hp;
    int hp2 = h2.hp;
    
    printf("\n");
    printf("BATTLE COMMENCES!\n");
    printf("%s (%s) vs %s (%s)\n", h1.name, h1.className, h2.name, h2.className);
    printf("\n");
    
    int round = 1;
    
    while (hp1 > 0 && hp2 > 0) {
        printf("ROUND %d\n", round);
        
        int luckBonus1 = rand() % (h1.luck / 10 + 1);
        int damage1 = (h1.attack - h2.defense / 2) > 1 ? (h1.attack - h2.defense / 2) : 1;
        damage1 += luckBonus1;
        hp2 -= damage1;
        
        printf("%s attacks %s for %d damage", h1.name, h2.name, damage1);
        if (luckBonus1 > 0) printf(" (Luck +%d!)", luckBonus1);
        printf("\n");
        printf("%s HP: %d\n", h2.name, hp2 > 0 ? hp2 : 0);
        
        if (hp2 <= 0) {
            printf("\n");
            break;
        }
        
        printf("\n");
        
        int luckBonus2 = rand() % (h2.luck / 10 + 1);
        int damage2 = (h2.attack - h1.defense / 2) > 1 ? (h2.attack - h1.defense / 2) : 1;
        damage2 += luckBonus2;
        hp1 -= damage2;
        
        printf("%s attacks %s for %d damage", h2.name, h1.name, damage2);
        if (luckBonus2 > 0) printf(" (Luck +%d!)", luckBonus2);
        printf("\n");
        printf("%s HP: %d\n", h1.name, hp1 > 0 ? hp1 : 0);
        
        printf("\n\n");
        
        round++;
    }
    
    printf("BATTLE COMPLETE!\n");
    if (hp1 > 0) {
        printf("WINNER: %s (HP remaining: %d)\n", h1.name, hp1);
    } else {
        printf("WINNER: %s (HP remaining: %d)\n", h2.name, hp2);
    }
}

void addNewHero(Hero squad[], int *n) {
    Hero newHero;
    
    printf("\nADD NEW HERO\n\n");
    
    printf("Name (no spaces): ");
    fgets(newHero.name, MAX_NAME, stdin);
    newHero.name[strcspn(newHero.name, "\n")] = '\0';
    
    printf("Class (Warrior/Mage/Healer/Archer): ");
    fgets(newHero.className, MAX_CLASS, stdin);
    newHero.className[strcspn(newHero.className, "\n")] = '\0';
    
    printf("Level: ");
    scanf("%d", &newHero.level);
    
    printf("HP (1-500): ");
    scanf("%d", &newHero.hp);
    
    printf("Attack (1-100): ");
    scanf("%d", &newHero.attack);
    
    printf("Defense (0-100): ");
    scanf("%d", &newHero.defense);
    
    printf("Luck (0-100): ");
    scanf("%d", &newHero.luck);
    clearInputBuffer();
    
    computeHeroPower(&newHero);
    squad[*n] = newHero;
    (*n)++;
    
    printf("\nHero '%s' added successfully! Power: %.2f\n", newHero.name, newHero.power);
}

void removeHero(Hero squad[], int *n) {
    char heroName[MAX_NAME];
    int choice;
    
    printf("\nREMOVE HERO\n\n");
    
    printAllHeroes(squad, *n);
    
    printf("\nSelect removal method:\n");
    printf("1. Remove by name\n");
    printf("2. Remove by index\n");
    printf("0. Cancel\n");
    printf("Your choice: ");
    
    if (scanf("%d", &choice) != 1) {
        clearInputBuffer();
        printf("\nInvalid input!\n");
        return;
    }
    clearInputBuffer();
    
    if (choice == 0) {
        printf("\nRemoval cancelled.\n");
        return;
    }
    
    int idxToRemove = -1;
    
    if (choice == 1) {
        
        printf("\nEnter hero name to remove: ");
        fgets(heroName, sizeof(heroName), stdin);
        heroName[strcspn(heroName, "\n")] = '\0';

        
        idxToRemove = findHeroByName(squad, *n, heroName);
        
        if (idxToRemove < 0) {
            printf("\nHero '%s' not found!\n", heroName);
            return;
        }
    } else if (choice == 2) {
        
        printf("\nEnter hero index (0 to %d): ", *n - 1);
        if (scanf("%d", &idxToRemove) != 1) {
            clearInputBuffer();
            printf("\nInvalid input!\n");
            return;
        }
        clearInputBuffer();
        
        if (idxToRemove < 0 || idxToRemove >= *n) {
            printf("\nInvalid index! Must be between 0 and %d.\n", *n - 1);
            return;
        }
    } else {
        printf("\nInvalid choice!\n");
        return;
    }
    
    printf("\nAre you sure you want to remove '%s' (%s, Power: %.2f)?\n",
           squad[idxToRemove].name,
           squad[idxToRemove].className,
           squad[idxToRemove].power);
    printf("1. Yes, remove this hero\n");
    printf("2. No, cancel\n");
    printf("Your choice: ");
    
    int confirm;
    if (scanf("%d", &confirm) != 1 || confirm != 1) {
        clearInputBuffer();
        printf("\nRemoval cancelled.\n");
        return;
    }
    clearInputBuffer();
    
    char removedName[MAX_NAME];
    strncpy(removedName, squad[idxToRemove].name, sizeof(removedName)-1);
    removedName[sizeof(removedName)-1] = '\0';
    
    for (int i = idxToRemove; i < *n - 1; i++) {
        squad[i] = squad[i + 1];
    }
    
    (*n)--;
    computeAllPowers(squad, *n);
    
    printf("\nHero '%s' has been removed from the squad.\n", removedName);
    printf("Current squad size: %d hero(es)\n", *n);
}

int loadHeroesFromFile(const char *filename, Hero squad[], int maxN) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        
        return 0;
    }
    
    int n;
    fscanf(file, "%d", &n);
    
    if (n > maxN) {
        printf("File contains %d heroes, but max capacity is %d. Loading first %d.\n", n, maxN, maxN);
        n = maxN;
    }
    
    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %s %d %d %d %d %d",
               squad[i].name,
               squad[i].className,
               &squad[i].level,
               &squad[i].hp,
               &squad[i].attack,
               &squad[i].defense,
               &squad[i].luck);
    }
    
    fclose(file);
    return n;
}

void saveHeroesToFile(const char *filename, Hero squad[], int n) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Cannot create file '%s'\n", filename);
        return;
    }
    
    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s %s %d %d %d %d %d\n",
                squad[i].name,
                squad[i].className,
                squad[i].level,
                squad[i].hp,
                squad[i].attack,
                squad[i].defense,
                squad[i].luck);
    }
    
    fclose(file);
    printf("✓ Saved %d heroes to '%s'\n", n, filename);
}

void printMenu(void) {
    printf("\n");
    printf("HERO SQUAD MENU\n");
    printf("1. Load heroes from file\n");
    printf("2. Add a new hero\n");
    printf("3. Remove a hero\n");
    printf("4. Show all heroes\n");
    printf("5. Search hero by name\n");
    printf("6. Show heroes by class\n");
    printf("7. Sort heroes by power (descending)\n");
    printf("8. Simulate a battle (1 vs 1)\n");
    printf("9. Save heroes to file\n");
    printf("0. Exit\n");
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int strcasecmp_custom(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        int c1 = tolower((unsigned char)*s1);
        int c2 = tolower((unsigned char)*s2);
        if (c1 != c2) return c1 - c2;
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}
