#include <stdio.h>
#include <stdlib.h>

#define N 50

typedef enum {EMPTY, USER, COMPUTER} Cell;

typedef struct {
    int row, col;
} Coordinate;

void generateBoard(Cell **board, int n);
void printBoard(Cell **board, int n);
int isMoveValid(Cell **board, int n, int direction_x[], int direction_y[], int row, int col, Cell move_turn);
int getValidMoves(Cell **board, int n, int validMoves_x[], int validMoves_y[], int direction_x[], int direction_y[], Cell move_turn);
void getUserInput(Coordinate *move, int validMoves_x[], int validMoves_y[], int valid_move_counts);
void applyMoveandFlip(Cell **board, Coordinate move, int n, int direction_x[], int direction_y[], Cell move_turn);
void findBestMoveAI(Cell **board, Coordinate *move, int n, int direction_x[], int direction_y[], Cell move_turn, int validMoves_x_AI[], int validMoves_y_AI[], int valid_move_counts_AI);
int findFlapCount(Cell** board, int row, int col, int n, int direction_x[], int direction_y[], Cell move_turn);
void isGameOver(Cell **board, int n, int *game_is_on);
void calculateScore(Cell **board, int n, int *user_score, int *computer_score);


int main() {
    int n, flag = 0, i, game_is_on = 1, move_turn_num = 2;
    int user_score = 0, computer_score = 0;
    Cell move_turn;
    Cell **board;
    Coordinate move;
    int direction_x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int direction_y[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    char ch, user_move_y;
    int valid_move_counts, valid_move_counts_AI;
    int validMoves_x[N], validMoves_y[N], validMoves_x_AI[N], validMoves_y_AI[N];
    while (!flag) {
        printf("Please enter size of board: ");
        if((!scanf("%d", &n)) || n % 2 != 0 || n < 4 || n > 20) {
            printf("Invalid input! Please try it again.\n");
            while ((ch = getchar() != '\n' && ch != EOF));
            continue;
        }
        flag = 1;
    }
    board = (Cell**)malloc(sizeof(Cell*)* n);
    for (i = 0; i < n; i++) {
        board[i] = (Cell*)malloc(sizeof(Cell)* n);
    }

    generateBoard(board, n);
    printBoard(board, n);

    while (game_is_on) {
        if (move_turn_num % 2 == 0) {
            move_turn = USER;
        }
        else move_turn = COMPUTER;
        valid_move_counts = getValidMoves(board, n, validMoves_x, validMoves_y, direction_x, direction_y, USER);
        valid_move_counts_AI = getValidMoves(board, n, validMoves_x_AI, validMoves_y_AI, direction_x, direction_y, COMPUTER);

        if (move_turn == USER) {
            printf("USER'S TURN\n");
            if (valid_move_counts != 0) {
                getUserInput(&move, validMoves_x, validMoves_y, valid_move_counts);
                applyMoveandFlip(board, move, n, direction_x, direction_y, USER);
            }
        }
        else if (move_turn == COMPUTER) {
            printf("COMPUTER'S TURN\n");
            if (valid_move_counts_AI != 0) {
                
                findBestMoveAI(board, &move, n, direction_x, direction_y, COMPUTER, validMoves_x_AI, validMoves_y_AI, valid_move_counts_AI);

                applyMoveandFlip(board, move, n, direction_x, direction_y, COMPUTER);
            }
        }
        calculateScore(board, n, &user_score, &computer_score);
        printf("User Score: %d || Computer Score: %d\n", user_score, computer_score);

        move_turn_num++;
        printBoard(board, n);
        isGameOver(board, n, &game_is_on);
        if (valid_move_counts == 0 && valid_move_counts_AI == 0) {
            game_is_on = 0;
        }
    }

    printf("Game is over!\n");
    printf("User Score: %d || Computer Score: %d\n", user_score, computer_score);
    if (user_score > computer_score) {
        printf("You won! Congratulations.\n");
    } else if (computer_score > user_score) {
        printf("Computer Won!\n");
    }
    else{
        printf("Draw!\n");
    }

    for (i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
}

void generateBoard(Cell **board, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            board[i][j] = EMPTY;
        }
    }
    board[n/2-1][n/2-1] = COMPUTER;
    board[n/2-1][n/2] = USER;
    board[n/2][n/2-1] = USER;
    board[n/2][n/2] = COMPUTER;
}

void printBoard(Cell **board, int n) {
    int i, j;
    char character = 'a';
    
    printf("  ");
    for(i = 0; i < n; i++) {
        printf(" %c ", (character)+i);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("%d ", i+1);
        for (j = 0; j < n; j++) {
            if (board[i][j] == EMPTY)printf(" . ");
            else if (board[i][j] == USER)printf(" O ");
            else if (board[i][j] == COMPUTER)printf(" X ");
        }
        printf("\n");
    }
}

int isMoveValid(Cell **board, int n, int direction_x[], int direction_y[], int row, int col, Cell move_turn) {
    if (board[row][col] != EMPTY)
        return 0;
    int i, x, y;
    for (i = 0; i < 8; i++) {
        x = row + direction_x[i];
        y = col + direction_y[i];

        if (x < 0 || x >= n || y < 0 || y >= n) continue;

        if (move_turn == USER && board[x][y] == COMPUTER) {
            while (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == COMPUTER) {
                x += direction_x[i];
                y += direction_y[i];
            }
            if (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == USER)
                return 1;
        }

        if (move_turn == COMPUTER && board[x][y] == USER) {
            while (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == USER) {
                x += direction_x[i];
                y += direction_y[i];
            }
            if (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == COMPUTER)
                return 1;
        }
    }

    return 0;
}

int getValidMoves(Cell **board, int n, int validMoves_x[], int validMoves_y[], int direction_x[], int direction_y[], Cell move_turn) {
    int i, j;
    int valid_moves_count = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (isMoveValid(board, n, direction_x, direction_y, i, j, move_turn)) {
                validMoves_x[valid_moves_count] = i;
                validMoves_y[valid_moves_count] = j;
                valid_moves_count++;
            }

        }
    }
    return valid_moves_count;
}

void getUserInput(Coordinate *move, int validMoves_x[], int validMoves_y[], int valid_move_counts) {
    int i, row_int, col_int, is_input_correct;
    char col_char, ch;
    while (1) {
        printf("Moves that you can do: \n");
        printf("Row - Col\n");
        for (i = 0; i < valid_move_counts; i++) {
            char move_y = 'a' + validMoves_y[i];
            printf(" %d  -  %c  \n", validMoves_x[i]+1, move_y);
        }
        printf("\nPlease enter your move (row col): ");
        if(scanf("%d %c", &row_int, &col_char) != 2) {
            printf("Invalid Input! Please try it again.\n");
            while((ch = getchar()) != '\n' && ch != EOF);
            continue;
        }
        row_int -= 1;
        col_int = col_char - 'a';
        is_input_correct = 0;
        for (i = 0; i < valid_move_counts; i++) {
            if (row_int == validMoves_x[i] && col_int == validMoves_y[i]) {
                is_input_correct = 1;
                break;
            }
        }

        if (is_input_correct) {
            move->row = row_int;
            move->col = col_int;
            break;
        }
        else {
            printf("Wrong input! You can not do that move!\n");
        }
    }
}

void applyMoveandFlip(Cell **board, Coordinate move, int n, int direction_x[], int direction_y[], Cell move_turn) {
    int x, y, i, flip;
    for (i = 0; i < 8; i++) {
        x = move.row; y = move.col;
        flip = 0;
        x += direction_x[i];
        y += direction_y[i];
        if (x < 0 || x >= n || y < 0 || y >= n)
            continue;

        if (move_turn == USER && board[x][y] == COMPUTER) {
            while (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == COMPUTER) {
                x += direction_x[i];
                y += direction_y[i];
            }
            if (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == USER)
                flip = 1;

            if (flip) {
                x = move.row;
                y = move.col;

                board[x][y] = USER;
                x += direction_x[i];
                y += direction_y[i];
                while (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == COMPUTER) {
                    board[x][y] = USER;
                    x += direction_x[i];
                    y += direction_y[i];
                }
            }
        }


        /* Flap for computer */
        if (move_turn == COMPUTER && board[x][y] == USER) {
            while (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == USER) {
                x += direction_x[i];
                y += direction_y[i];
            }
            if (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == COMPUTER)
                flip = 1;
                
            if (flip) {
                x = move.row;
                y = move.col;

                board[x][y] = COMPUTER;
                x += direction_x[i];
                y += direction_y[i];
                while (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == USER) {
                    board[x][y] = COMPUTER;
                    x += direction_x[i];
                    y += direction_y[i];
                }
            }

        }

    }

}  

int findFlapCount(Cell** board, int row, int col, int n, int direction_x[], int direction_y[], Cell move_turn) {
    int x, y, i, flipable;
    int counter = 0;
    for (i = 0; i < 8; i++) {
        x = row; y = col;
        flipable = 0;
        x += direction_x[i];
        y += direction_y[i];
        if (x < 0 || x >= n || y < 0 || y >= n)
            continue;

        if (move_turn == COMPUTER && board[x][y] == USER) {
            while (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == USER) {
                x += direction_x[i];
                y += direction_y[i];
            }
            if (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == COMPUTER)
                flipable = 1;
                
            if (flipable) {
                x = row + direction_x[i];
                y = col + direction_y[i];
                counter++;
                while (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == USER) {
                    counter++;
                    x += direction_x[i];
                    y += direction_y[i];
                }
            }

        }

    }
    return counter;

}

void findBestMoveAI(Cell **board, Coordinate *move, int n, int direction_x[], int direction_y[], Cell move_turn, int validMoves_x_AI[], int validMoves_y_AI[], int valid_move_counts_AI) {
    int i, x, y, flap_count, temp_flap_count;
    x = validMoves_x_AI[0];
    y = validMoves_y_AI[0];
    flap_count = findFlapCount(board, x, y, n, direction_x, direction_y, COMPUTER);

    for (i = 1; i < valid_move_counts_AI; i++) {
        temp_flap_count = findFlapCount(board, validMoves_x_AI[i], validMoves_y_AI[i], n, direction_x, direction_y, COMPUTER);
        if (temp_flap_count > flap_count) {
            flap_count = temp_flap_count;
            x = validMoves_x_AI[i];
            y = validMoves_y_AI[i];
        }
    }
    move->row = x;
    move->col = y;
}

void isGameOver(Cell **board, int n, int *game_is_on) {
    int i, j, flag = 1;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (board[i][j] == EMPTY) {
                flag = 0;
                break;
            }
        }
    }
    if (!flag) {
        *game_is_on = 1;
    }
    else if (flag) {
        *game_is_on = 0;
    }
}

void calculateScore(Cell **board, int n, int *user_score, int *computer_score) {
    int i, j;
    int user_s = 0, computer_s = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (board[i][j] == USER) user_s++;
            else if (board[i][j] == COMPUTER) computer_s++;
        }
    }
    *user_score = user_s;
    *computer_score = computer_s;

}
