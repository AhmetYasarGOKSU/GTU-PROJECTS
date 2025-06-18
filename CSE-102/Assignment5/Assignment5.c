#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generateNewBoard(char board[10][10], char printing_board[10][10]);
void printBoard(char printing_board[10][10]);
void generateShips(int size, FILE * file, char board[10][10]);
int isValidShipPlace(char direction, int row, int col, int size, char board[10][10]);
void shipsPlaces(FILE * file, char board[10][10]);
void isShipSank(FILE * file, char printing_board[10][10], int sank_status[4]);
int isGameOver(int sank_status[4]);

int main() {
    srand(time(NULL));
    char play_again = 'N';
    char board[10][10];
    char printing_board[10][10];
    char ch;
    int total_shots;
    int row, col;
    FILE * ship_file;
    FILE * log_file;
    int check_input;

    while (play_again == 'N') {
        generateNewBoard(board, printing_board);
        printBoard(printing_board);
        ship_file = fopen("ships.txt", "w");
        fclose(ship_file);
        shipsPlaces(ship_file, board);
        int sank_status[4] = {0, 0, 0, 0}; 
        log_file = fopen("battleship_log.txt", "w");
        fclose(log_file);
        printf("Enter coordinates (X to quit): ");
        total_shots = 0;
        check_input = scanf("%d %d", &row, &col);
        while (check_input == 2) {
            if (row > 9 || row < 0 || col > 9 || col < 0) {
                printf("Invalid coordinates! Please enter values between 0 and 9\n\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                printBoard(printing_board);
                printf("Enter coordinates (X to quit): ");
                check_input = scanf("%d %d", &row, &col);
                continue;
            }
            log_file = fopen("battleship_log.txt", "a");
            if (board[row][col] == 'S') {
                printf("HIT!\n");
                printing_board[row][col] = 'X';
                board[row][col] = 'X';
                fprintf(log_file,"Shot: %d %d - HIT\n", row, col);
            } else if (board[row][col] == '-') {
                printf("MISS!\n");
                printing_board[row][col] = 'O';
                board[row][col] = 'O';
                fprintf(log_file,"Shot: %d %d - MISS\n", row, col);
            } else if (printing_board[row][col] == 'X') {
                printf("There is a location that you've already hit\n");
                printf("Enter coordinates (X to quit): ");
                while ((ch = getchar()) != '\n' && ch != EOF);
                
                check_input = scanf("%d %d", &row, &col);
                continue;
            } else if (printing_board[row][col] == 'O') {
                printf("There is a location that you've already hit\n");
                printf("Enter coordinates (X to quit): ");
                while ((ch = getchar()) != '\n' && ch != EOF);
            
                check_input = scanf("%d %d", &row, &col);
                continue;
            }
            fclose(log_file);

            total_shots++;
            isShipSank(ship_file, printing_board, sank_status);
            printBoard(printing_board);
            if (isGameOver(sank_status) == 1) {
                printf("All ships are sunk! Total shots: %d\n", total_shots);
                printBoard(printing_board);
                printf("Press 'N' to play again or 'X' to exit:");
                scanf(" %c", &play_again);
                if (play_again == 'X' || play_again == 'x')return 0;
                else if (play_again == 'N' || play_again == 'n') {
                    break;
                }
            }
            printf("Enter coordinates (X to quit): "); 
            check_input = scanf("%d %d", &row, &col);
        }
        if (check_input != 2) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);

            printf("Did you try to quit? Press 'X' to quit. If you press something else the game will start again.\n");

            char temp;
            scanf(" %c", &temp);
            if (temp == 'X' || temp == 'x') {
                return 0;
            } else {

                while ((ch = getchar()) != '\n' && ch != EOF);
                continue;
            }
        }
    }
}

void generateNewBoard(char board[10][10], char printing_board[10][10]) {
    int i, j;
    printf("\n\n   Welcome to Battleship Game!\n\n");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            board[i][j] = '-';
            printing_board[i][j] = '-';
        }
    }
}
void printBoard(char printing_board[10][10]) {
    int i, j;
    printf("   ");
    for (i = 0; i < 10; i++) {
        printf("%d  ", i);
    
    }
    printf("\n");
    for (i = 0; i < 10; i++) {
        printf("%d  ", i);
        for (j = 0; j < 10; j++) {
            printf("%c  ", printing_board[i][j]);
        }
        printf("\n");
    }
}

int isValidShipPlace(char direction, int row, int col, int size, char board[10][10]) {
    int i;
    if (direction == 'H') {
        if (col + size > 10)return 0;
        for (i = 0; i < size; i++) {
            if (board[row][col+i] != '-')return 0;
        
        }
    } else {
        if (row + size > 10)return 0;
        for (i = 0; i < size; i++) {
            if (board[row+i][col] != '-')return 0;
        }
    }
    return 1;
}

void generateShips(int size, FILE * file, char board[10][10]) {
    int row, col, i;
    char direction;
    do {
        row = rand() % 10;
        col = rand() % 10;
        if (rand() % 2) {
            direction = 'H';
        } else {
            direction = 'V';
        }
    }while (!isValidShipPlace(direction, row, col, size, board));
    
    file = fopen("ships.txt", "a");
    for (i = 0; i < size; i++) {

        if (direction == 'H') {
            board[row][col+i] = 'S';
            fprintf(file, "%d %d %d\n", row, col+i, size);
        } else {
            board[row+i][col] = 'S';
            fprintf(file, "%d %d %d\n", row+i, col, size);
        }
    }
    fclose(file);
    
}

void shipsPlaces(FILE * file, char board[10][10]) {
    file = fopen("ships.txt", "w"); 
    if (file == NULL) {
        printf("Error: Could not open ships.txt!\n");
        return;
    }
    generateShips(4, file, board);
    generateShips(3, file, board);
    generateShips(3, file, board);
    generateShips(2, file, board);
    fclose(file); 
}

void isShipSank(FILE * file, char printing_board[10][10], int sank_status[4]) {
    file = fopen("ships.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open ships.txt!\n");
        return;
    }

    int ship_sizes[4] = {4, 3, 3, 2};  

    int ships[4][4][2]; 
    int i, j, row, col, size, hit_count;


    for (i = 0; i < 4; i++) {
        for (j = 0; j < ship_sizes[i]; j++) {
            fscanf(file, "%d %d %d", &ships[i][j][0], &ships[i][j][1], &size);
        }
    }
    fclose(file);


    for (i = 0; i < 4; i++) {
        if (sank_status[i] == 1) continue; 

        hit_count = 0;
        for (j = 0; j < ship_sizes[i]; j++) {
            row = ships[i][j][0];
            col = ships[i][j][1];

            if (printing_board[row][col] == 'X') {
                hit_count++;
            }
        }

        if (hit_count == ship_sizes[i]) {
            sank_status[i] = 1; 
            printf("Congratulations! You sank a %d-Cell Ship\n\n\n\n", ship_sizes[i]);
        }
    }
}



int isGameOver(int sank_status[4]) {
    int i;
    for (i = 0; i < 4; i++) {
        if (sank_status[i] == 0) {
            return 0;
        }
    }
    return 1;
}




