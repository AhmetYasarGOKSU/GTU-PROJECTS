#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void AdminMode();
void playerMode();
int* generateCode(int code_length, int min_digit, int max_digit, int allow_duplicates);
int* getGuess(int code_length, int min_digit, int max_digit);
int duplicateControl(int* array, int checked_number, int size);
void numToDigits(int* array, int num, int size);
int* compareCodes(int* generated_code, int* guessed_code, int code_length);
void gameOn(int* generated_code, int max_attempt, int code_length, int min_digit, int max_digit, int allow_duplicates,
            int points_for_correct, int points_for_wrong, int penalty_for_wrong);




int main() {
    char start;
    int check_input;
    

    /* Game start input*/
    do {
        printf("Please choose the mode: (A = Admin Mode, P = Player Mode): ");
        check_input = scanf(" %c", &start);
    } while (check_input != 1 || (start != 'a' && start != 'A' && start != 'p' && start != 'P'));
    
    if (start == 'a' || start == 'A') {
        AdminMode();
    }
    else if (start == 'p' || start == 'P') {
        playerMode();
    }

    return 0;
}

void AdminMode() {
    int code_length, min_digit, max_digit;   /* Declaration Variables */
    int allow_duplicates, max_attempt_nums;
    int points_for_correct, points_for_wrong, penalty_for_wrong;
    char ch;
    FILE * vault_config_file;


    /* Open file and check*/
    vault_config_file = fopen("vault_config.txt", "wt");

    if (vault_config_file == NULL) {
        printf("ERROR! Vault config file could not be opened.\n");
        return;
    }
    else {
        /* Some Inputs and checking are its correct */
        while (1) {
            printf("Enter the code length: ");
            if (!scanf("%d", &code_length) || code_length < 1) {
                printf("Invalid input for code length. Please set config again.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                continue;
            }

            printf("Enter minimum and maximum digits (range from 0 to 9): ");
            if (!scanf("%d %d", &min_digit, &max_digit) || min_digit < 0 || max_digit <= min_digit || max_digit > 9) {
                printf("Invalid input for min and max digits. Min digit can not be lower than max digit. Min digit can not be lower than zero and max digit can not be higher than 9. Please set config again.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                continue;
            }

            printf("Enter the maximum number of attempts allowed: ");
            if (!scanf("%d", &max_attempt_nums) || max_attempt_nums < 1) {
                printf("Invalid input for max attempt. Please set config again.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                continue;
            }

            printf("Allow duplicate digits? (1 = Yes, 0 = No): ");
            if (!scanf("%d", &allow_duplicates) || (allow_duplicates != 1 && allow_duplicates != 0)) {
                printf("Invalid input for allow duplicates. Please set config again.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                continue;
            }

            if (!allow_duplicates) {
                if ((max_digit - min_digit) < code_length) {
                    printf("We can not generate this %d length code without duplicate between %d-%d\n", code_length, min_digit, max_digit);
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    continue;    
                }
            }

            printf("Enter points for correct digit in correct place (C): ");
            if (!scanf("%d", &points_for_correct)) {
                printf("Invalid input for points of correct answers. Please set config again.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                continue;
            }

            printf("Enter points for correct digit in wrong place (M): ");
            if (!scanf("%d", &points_for_wrong)) {
                printf("Invalid input for points of wrong answers. Please set config again.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                continue;
            }

            printf("Enter penalty points for incorrect digit (W): ");
            if (!scanf("%d", &penalty_for_wrong)) {
                printf("Invalid input for points of penalty answers. Please set config again.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                continue;
            }

            break;
        }

    /* Print file datas from input */
    fprintf(vault_config_file, "CODE_LENGTH=%d\n", code_length);
    fprintf(vault_config_file, "DIGIT_MIN=%d\n", min_digit);
    fprintf(vault_config_file, "DIGIT_MAX=%d\n", max_digit);
    fprintf(vault_config_file, "MAX_ATTEMPTS=%d\n", max_attempt_nums);
    fprintf(vault_config_file, "ALLOW_DUPLICATES=%d\n", allow_duplicates);
    fprintf(vault_config_file, "POINTS_CORRECT=%d\n", points_for_correct);
    fprintf(vault_config_file, "POINTS_MISPLACED=%d\n", points_for_wrong);
    fprintf(vault_config_file, "PENALTY_WRONG=%d", penalty_for_wrong);

    }
    fclose(vault_config_file);
}

void playerMode() {
    int code_length, min_digit, max_digit;
    int allow_duplicates, max_attempt_nums;
    int points_for_correct, points_for_wrong, penalty_for_wrong;
    char ch;
    int* generated_code;
    FILE * vault_config_file;

    vault_config_file = fopen("vault_config.txt", "rt");
    if (!vault_config_file) {
        printf("ERROR! Vault config file could not opened.\n");
        return;
    }

    /* Takes datas from file */
    while (fscanf(vault_config_file, " %c", &ch) && ch != '='); 
    fscanf(vault_config_file, "%d\n", &code_length);
    
    while (fscanf(vault_config_file, " %c", &ch) && ch != '='); 
    fscanf(vault_config_file, "%d\n", &min_digit);

    while (fscanf(vault_config_file, " %c", &ch) && ch != '='); 
    fscanf(vault_config_file, "%d\n", &max_digit);

    while (fscanf(vault_config_file, " %c", &ch) && ch != '='); 
    fscanf(vault_config_file, "%d\n", &max_attempt_nums);

    while (fscanf(vault_config_file, " %c", &ch) && ch != '='); 
    fscanf(vault_config_file, "%d\n", &allow_duplicates);

    while (fscanf(vault_config_file, " %c", &ch) && ch != '='); 
    fscanf(vault_config_file, "%d\n", &points_for_correct);

    while (fscanf(vault_config_file, " %c", &ch) && ch != '='); 
    fscanf(vault_config_file, "%d\n", &points_for_wrong);
   
    while (fscanf(vault_config_file, " %c", &ch) && ch != '='); 
    fscanf(vault_config_file, "%d\n", &penalty_for_wrong);

    generated_code= generateCode(code_length, min_digit, max_digit, allow_duplicates);
    

    gameOn(generated_code, max_attempt_nums, code_length, min_digit, max_digit, allow_duplicates, points_for_correct, points_for_wrong, penalty_for_wrong);
   
   
    free(generated_code);
    fclose(vault_config_file);
}

int* generateCode(int code_length, int min_digit, int max_digit, int allow_duplicates) {
    int* secret_code;
    int i, random_value, value_is_okey;

    FILE * vault_code_file;

    vault_code_file = fopen("vault_code.txt", "wt");

    if (vault_code_file == NULL) {
        printf("ERROR: Could not open vault_code.txt for writing.\n");
        exit(1);
    }
    
    secret_code = (int*)malloc(code_length * sizeof(int));
    srand(time(NULL));

    for (i = 0; i < code_length; i++) {
        value_is_okey = 0;
        while (!value_is_okey){
            random_value = rand() % 10;
            /* Check conditions*/
            if (random_value < min_digit || random_value > max_digit) {
                continue;
            }
            else if (!allow_duplicates) {
                if (duplicateControl(secret_code, random_value, i)) {
                    continue;
                }
                else {
                    secret_code[i] = random_value;
                    value_is_okey = 1;
                }
            }
            else {
                secret_code[i] = random_value;
                value_is_okey = 1;
            }
        }
        
    }

    for (i = 0; i < code_length; i++) {
        fprintf(vault_code_file, "%d", secret_code[i]);

    }
    fclose(vault_code_file);

    return secret_code;
}

int* getGuess(int code_length, int min_digit, int max_digit) {
    int* guess_arr;
    int i;
    char ch;
    guess_arr = (int*)malloc(code_length * sizeof(int));


    while (1) {
        printf("Enter your guess (%d-digit number): ", code_length);
        for (i = 0; i < code_length; i++) {
            if(!scanf(" %1d", &guess_arr[i])) {
                printf("Invalid input. Please enter digits only.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                continue;

            }
        }
        break;
    }

    return guess_arr;
}

void gameOn(int* generated_code, int max_attempt, int code_length, int min_digit, int max_digit, int allow_duplicates,
     int points_for_correct, int points_for_wrong, int penalty_for_wrong) 
{
    int current_attempt = 1, i, score = 0, count_c;
    int* guessed_code;
    int* compared_code;

    time_t current_time;
    struct tm * time_info;
    char time_str[100];

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);

    FILE * gamelog_file;

    gamelog_file = fopen("game_log.txt", "wt");

    if (gamelog_file == NULL) {
        printf("ERROR: Could not open game_log.txt for writing.\n");
        free(generated_code);
        exit(1);
    }
    fprintf(gamelog_file, "--- Vault Codebreaker Game Log ---\n");
    fprintf(gamelog_file, "Game Date: %s\n", time_str);
    fprintf(gamelog_file, "Secret Code: ");

    for(i = 0; i < code_length; i++) {
        fprintf(gamelog_file, "%d", generated_code[i]);
    }
    fprintf(gamelog_file, "\nCode Length: %d\n", code_length);
    fprintf(gamelog_file, "Digit Range: %d-%d\n", min_digit, max_digit);
    fprintf(gamelog_file, "Duplicates Allowed: %d\n", allow_duplicates);
    fprintf(gamelog_file, "Max Attempts: %d\n\n", max_attempt);



    while (current_attempt <= max_attempt) {
        guessed_code = getGuess(code_length, min_digit, max_digit);  
        compared_code = compareCodes(generated_code, guessed_code, code_length);
    
        count_c = 0;
        fprintf(gamelog_file, "Attempt %d :", current_attempt);
        for (i = 0; i < code_length; i++) {
            fprintf(gamelog_file, "%d", guessed_code[i]);
        }

        fprintf(gamelog_file, " =>  Feedback: ");
        printf("Feedback: ");

        for (i = 0; i < code_length; i++) {

            if (compared_code[i] == 1) {
                printf("C");
                fprintf(gamelog_file, "C ");
                score += points_for_correct;
                count_c++;
            }
            else if (compared_code[i] == 0) {
                printf("M");
                fprintf(gamelog_file, "M ");
                score += points_for_wrong;
            }
            else if (compared_code[i] == -1) {
                printf("W");
                fprintf(gamelog_file, "W ");
                score -= penalty_for_wrong;
            }  
        }
        printf("\n");
        fprintf(gamelog_file, "| Score: %d\n", score);

        if (count_c == code_length) {
            printf("\nCongratulations! You've guessed the secret code!\n");
            break;
        }
        current_attempt++;
        free(guessed_code);
        free(compared_code);
    
    }

    if (count_c < code_length) {
        printf("Game Over. You've used all your attempts.\n");
    }
    printf("The secret code was: ");
    for (i = 0; i < code_length; i++) {
        printf("%d", generated_code[i]);
    }
    
    printf("\nYour final score is: %d\n", score);
    fprintf(gamelog_file, "\nFinal Score: %d\n", score);
    
    if (score >= 90) {
        fprintf(gamelog_file, "Rank: Code Master \n");
        printf("Rank: Code Master \n");
    } else if (score < 90 && score >= 70) {
        fprintf(gamelog_file, "Rank: Cipher Hunter \n");
        printf("Rank: Cipher Hunter \n");
    } else if (score < 70 && score >= 50) {
        fprintf(gamelog_file, "Rank: Number Sleuth \n");
        printf("Rank: Number Sleuth \n");

    } else if (score < 50 && score >= 30) {
        fprintf(gamelog_file, "Rank: Safe Kicker \n");
        printf("Rank: Safe Kicker \n");

    } else if (score < 30 && score >= 10) {
        fprintf(gamelog_file, "Rank: Lucky Breaker \n");
        printf("Rank: Lucky Breaker \n");

    } else if (score < 10) {
        fprintf(gamelog_file, "Rank: Code Potato \n");
        printf("Rank: Code Potato \n");

    }



    fprintf(gamelog_file, "-----------------------\n");

    fclose(gamelog_file);
}

int* compareCodes(int* generated_code, int* guessed_code, int code_length) {
    int* compared_code;
    
    compared_code = (int*)malloc(code_length * sizeof(int));

    int i;
    for (i = 0; i < code_length; i++) {
        if (generated_code[i] == guessed_code[i]) {
            compared_code[i] = 1;
        }
        else if (duplicateControl(generated_code, guessed_code[i], code_length)) {
            compared_code[i] = 0;
        }
        else {
            compared_code[i] = -1;
        }
    }
    
    return compared_code;
}

int duplicateControl(int *array, int checked_number, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (array[i] == checked_number)return 1;
    }
    return 0;
}

void numToDigits(int* array, int num, int size) {
    int i;

    for (i = size - 1; i >= 0; i--) {
        array[i] = num % 10;
        num = (num - (num % 10)) / 10;
    }
    return;
}
