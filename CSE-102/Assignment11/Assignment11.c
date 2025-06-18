#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SPELL_COUNT 6
#define SPELL_FILE "spellbook.txt"
#define MIN_RECOVER_MANA 10
#define MAX_RECOVER_MANA 20
#define STAT_COUNT 3

typedef struct {
    int total_damage_dealt;
    int total_mana_spent;
    int number_of_recoveries;
} BattleStat;

typedef struct {
    char name[50];
    char magic_class[30];
    int min_damage, max_damage;
    int min_mana_cost, max_mana_cost;
} Spell;

typedef struct {
    char name[50];
    char magic_class[30];
    int HP;
    int Mana;
    int Alive;
    Spell spells[3];
    BattleStat battle_stats;
} Wizard;


void readSpells(Spell* spells);
void selectSpells(Wizard *wizard, Spell *spells);
void duel(Wizard *attacker, Wizard *defender);
void recover(Wizard *wizard);
int calculateScore(int stats[], int n);

int main () {
    srand(time(NULL));
    Wizard wizard_1 = {"Merlin", "fire", 100, 100, 1, .battle_stats = {0, 0, 0}}, wizard_2 = {"Frostina", "ice", 100, 100, 1, .battle_stats = {0, 0, 0}};
    Spell *spells;
    spells = (Spell*)malloc(sizeof(Spell) * SPELL_COUNT);
    int score_wizard_1, score_wizard_2;
    readSpells(spells);
    
    selectSpells(&wizard_1, spells);
    selectSpells(&wizard_2, spells);


    printf("Wizard Duel Begins: %s vs %s!\n\n\n", wizard_1.name, wizard_2.name);
    printf("-------------------------------------------------\n\n");
    duel(&wizard_1, &wizard_2);
    int stats_wizard_1[STAT_COUNT] = {wizard_1.battle_stats.total_damage_dealt,
                                    wizard_1.battle_stats.total_mana_spent,
                                    wizard_1.battle_stats.number_of_recoveries};
    int stats_wizard_2[STAT_COUNT] = {wizard_2.battle_stats.total_damage_dealt,
                                    wizard_2.battle_stats.total_mana_spent, 
                                    wizard_2.battle_stats.number_of_recoveries};

    score_wizard_1 = calculateScore(stats_wizard_1, STAT_COUNT);
    score_wizard_2 = calculateScore(stats_wizard_2, STAT_COUNT);

    printf("Battle Summary:\n\n");
    printf("%s -- Damage: %d | Mana Spent: %d | Recoveries: %d | Score: %d\n\n", wizard_1.name, wizard_1.battle_stats.total_damage_dealt, wizard_1.battle_stats.total_mana_spent, wizard_1.battle_stats.number_of_recoveries, score_wizard_1);
    printf("%s -- Damage: %d | Mana Spent: %d | Recoveries: %d | Score: %d\n\n", wizard_2.name, wizard_2.battle_stats.total_damage_dealt, wizard_2.battle_stats.total_mana_spent, wizard_2.battle_stats.number_of_recoveries, score_wizard_2);
    
    free(spells);
    return 0;
}

void readSpells(Spell* spells) {
    int i;
    char temp[50];
    char* token;
    FILE * spell_file;
    spell_file = fopen(SPELL_FILE, "r");

    if (spell_file == NULL) {
        printf("ERROR! Spell file could not be opened!\n");
        exit(-1);
    }
    for (i = 0; i < SPELL_COUNT; i++) {
        fgets(temp, sizeof(temp), spell_file);
        token = strtok(temp, ",");
        strcpy(spells[i].name, token);            
        token = strtok(NULL, ",");
        strcpy(spells[i].magic_class, token);
        token = strtok(NULL, ",");
        spells[i].min_damage = atoi(token);
        token = strtok(NULL, ",");
        spells[i].max_damage = atoi(token);
        token = strtok(NULL, ",");
        spells[i].min_mana_cost = atoi(token);
        token = strtok(NULL, ",");
        spells[i].max_mana_cost = atoi(token);
                    
    }
    fclose(spell_file);
}

void selectSpells(Wizard *wizard, Spell *spells) {
    int i = 0, j, num, flag;
    int chosen_nums[3];
    while (i < 3) {
        num = rand() % 6;
        flag = 0;
        for (j = 0; j < i; j++) {
            if (chosen_nums[j] == num) {
                flag = 1;
                break;
            }
            
        }
        if (!flag) {
            wizard->spells[i] = spells[num];
            chosen_nums[i] = num;
            i++;
        }
    }
}

void duel(Wizard *attacker, Wizard *defender) {
    int attacker_spell, random_mana_cost, random_damage;
    attacker_spell = rand() % 3;
    random_mana_cost = (rand() % ((attacker->spells[attacker_spell].max_mana_cost) - (attacker->spells[attacker_spell].min_mana_cost) + 1)) + attacker->spells[attacker_spell].min_mana_cost;
    if (random_mana_cost > attacker->Mana) {
        printf("%s is low on mana and meditates...\n\n", attacker->name);
        recover(attacker);
        duel(defender, attacker);
        
    }
    else {
        random_damage = (rand() % ((attacker->spells[attacker_spell].max_damage) - (attacker->spells[attacker_spell].min_damage) + 1)) + attacker->spells[attacker_spell].min_damage;
        
        if (strcmp(attacker->magic_class, attacker->spells[attacker_spell].magic_class) == 0) {
            random_damage += 5;
        }
        printf("%s casts %s on %s!\n\n", attacker->name, attacker->spells[attacker_spell].name, defender->name);
        defender->HP -= random_damage;
        attacker->Mana -= random_mana_cost;
        attacker->battle_stats.total_damage_dealt += random_damage;
        attacker->battle_stats.total_mana_spent += random_mana_cost;
        printf("Damage: %d | %s's HP: %d | %s's Mana: %d\n\n", random_damage, defender->name, defender->HP, attacker->name, attacker->Mana);
        printf("-------------------------------------------------\n\n");

        if (defender->HP > 0) {
            duel(defender, attacker);
        }
        else {
            if (strcmp(attacker->name, "Frostina") == 0) {
                printf("Winner: Frostina the Ice Wizard!\n\n\n\n");
            }
            else {
                printf("Winner: Merlin the Fire Wizard!\n\n\n\n");
            }


            defender->Alive = 0;
        }

    }

}

void recover(Wizard *wizard) {
    int random_recover_mana;
    random_recover_mana = rand() % (MAX_RECOVER_MANA - MIN_RECOVER_MANA + 1) + MIN_RECOVER_MANA;
    wizard->Mana += random_recover_mana;
    printf("%s recovers %d mana. Current mana: %d\n\n", wizard->name, random_recover_mana, wizard->Mana);
    wizard->battle_stats.number_of_recoveries++;
}

int calculateScore(int stats[], int n) {
    if (n == 0) return 0;
    if (n == 3) {
        return -(stats[n-1]*3) + calculateScore(stats, n-1);
    }
    if (n == 2) {
        return stats[n-1] + calculateScore(stats, n-1);
    }
    if (n == 1) {
        return stats[n-1]*2 + calculateScore(stats, n-1); 
    }
}
