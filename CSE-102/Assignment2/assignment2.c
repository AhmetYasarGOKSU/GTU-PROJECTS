#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    int width, height; /* Input variables */
    int playerX, playerY, doorX, doorY; /* Coordinate variables */
    char ch; /* get char from file to check is file empty */
    char key_inst; /* Keyboard Instruction Input*/
    
    FILE * open_file;
    open_file = fopen("game_state.txt", "r");
    
    /* Check file is open */
    if (open_file == NULL) {
        open_file = fopen("game_state.txt", "w");
    }
    
    ch = fgetc(open_file);
    fclose(open_file);
    
    /* Check file is empty. If it is yes generate a new board. */
    if (ch == EOF) {
        printf("Generating a new board...\n");
        printf("Enter the width and height of board:\n");
        scanf("%d %d", &width, &height);
        
        /* Check Inputs are valid */
        if (width <= 0 || height <= 0) {
            printf("Invalid Input. Please try again!");
            return -1;
        }
        
        /* Generate coordinates of player and door */
        srand(time(NULL));    
        playerX = rand() % width + 1; 
        playerY = rand() % height + 1;
        doorX = rand() % width + 1;
        doorY = rand() % height + 1 ;
        if (playerX == doorX && playerY == doorY) {
                doorX = (doorX % width) + 1;
                doorY = (doorY % height) + 1;
        }
      

        /* Write datas to the file */
        open_file = fopen("game_state.txt", "w");
        if (open_file == NULL) {
            printf("Error opening file.\n");
            return -1;
        }
        /*fprintf(open_file, "Width:%d, Height:%d, Player:(%d,%d), Door:(%d,%d)", width, height, playerX, playerY, doorX, doorY); */
        fprintf(open_file, "%d %d %d %d %d %d", width, height, playerX, playerY, doorX, doorY); 
        fclose(open_file);
        
        printf("Width: %d, Height: %d, Player: (%d,%d), Door: (%d,%d)\n", width, height, playerX, playerY, doorX, doorY);
    }
    else {
        /* Take datas from txt file */
        open_file = fopen("game_state.txt", "r");
        if (open_file == NULL) {
            printf("Error opening file.\n");
            return -1;
        }
        fscanf(open_file, "%d %d %d %d %d %d", &width, &height, &playerX, &playerY, &doorX, &doorY);

        fclose(open_file);
        /* Take input for the next move */
        printf("Enter move (WASD): ");
        scanf(" %c", &key_inst);

        /* Check Is input valid */
        if (key_inst != 'W' && key_inst != 'A' && key_inst != 'S' && key_inst != 'D' && key_inst != 'w' && key_inst != 'a' && key_inst != 's' && key_inst != 'd') {
            printf("Invalid keyboard Input. Please try again!\n");
            return -1;
        
        }
        /* Check Keyboard Instruction*/
        else {
            if (key_inst == 'W' || key_inst == 'w') {
                if (playerY + 1 <= height) {
                    playerY += 1;
                    printf("Player moves up to (%d, %d)\n", playerX, playerY);
                }
                else {
                    printf("Out of bounds moves are rejected!\n");
                    return 0;
                }

            } 
            else if (key_inst == 'A' || key_inst == 'a') {
                if (playerX - 1 > 0) {
                    playerX -= 1;
                    printf("Player moves left to (%d, %d)\n", playerX, playerY);
                }
                else {
                    printf("Out of bounds moves are rejected!\n");
                    return 0;
                }
            }
            else if (key_inst == 'S' || key_inst == 's') {
                if (playerY -1 > 0) {
                    playerY -= 1;
                    printf("Player moves down to (%d, %d)\n", playerX, playerY);
                }
                else {
                    printf("Out of bounds moves are rejected!\n");
                    return 0;
                }                
            }
            else if (key_inst == 'D' || key_inst == 'd') {
                if (playerX + 1 <= width) {
                    playerX += 1;
                    printf("Player moves right to (%d, %d)\n", playerX, playerY);
                }
                else {
                    printf("Out of bounds moves are rejected!\n");
                    return 0;
                }
            }
        }
        
        open_file = fopen("game_state.txt", "w");
        if (open_file == NULL) {
            printf("Error opening file.\n");
            return -1;
        }
        fprintf(open_file, "%d %d %d %d %d %d", width, height, playerX, playerY, doorX, doorY); 
        fclose(open_file);
        /* Check hitting wall or win game */
        if (playerX == doorX && playerY == doorY){
            printf("Congratulations! You escaped!\n");
            printf("Generating a new board...\n");
            printf("Enter the width and height of board:\n");
            scanf("%d %d", &width, &height);
            /* If player win generate new board */
            open_file = fopen("game_state.txt", "w");

            playerX = rand() % width + 1; 
            playerY = rand() % height + 1;
            doorX = rand() % width + 1;
            doorY = rand() % height + 1 ;
            
            if (playerX == doorX && playerY == doorY) {
                    doorX = (doorX % width) + 1;
                    doorY = (doorY % height) + 1;
            }
            
            
            fprintf(open_file, "%d %d %d %d %d %d", width, height, playerX, playerY, doorX, doorY);
            printf("Width: %d, Height: %d, Player: (%d,%d), Door: (%d,%d)\n", width, height, playerX, playerY, doorX, doorY);
            fclose(open_file);
        }

        else {
            printf("Game continues\n");
        }
    


    }    
    
}
