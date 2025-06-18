#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define MIN_SIZE 2
#define MAX_MOVES 100

void boardGeneration(char board[MAX_SIZE][MAX_SIZE], char mined_board[MAX_SIZE][MAX_SIZE], int N);
void printBoard(char board[MAX_SIZE][MAX_SIZE], int N);
void mineGeneration(char mined_board[MAX_SIZE][MAX_SIZE], int N);
void saveBoard(char board[MAX_SIZE][MAX_SIZE], int N, FILE * map_file);
void push(int row, int col, int move_rows[MAX_MOVES], int move_cols[MAX_MOVES], int* move_top);
void pop(int* move_top);
void pop_flood_fill(int* flood_fill_top);
int isEmpty(int* move_top);
int checkMineCount(char mined_board[][MAX_SIZE], int row, int col, int N);
void floodFill(int row, int col, char mined_board[][MAX_SIZE], char board[][MAX_SIZE], int N, int flood_fill_rows[MAX_MOVES], int flood_fill_cols[MAX_MOVES], int* flood_fill_top, int* flood_fill_count);
void saveMoves(int move_rows[], int move_cols[], int* move_top, FILE * moves_file);
int checkGameOver(char board[][MAX_SIZE], char mined_board[][MAX_SIZE], int N);
void push_flood_fill(int row, int col, int flood_fill_rows[MAX_MOVES], int flood_fill_cols[MAX_MOVES], int* flood_fill_top, int* flood_fill_count);

int main(void) {
    int N, i;
    char board[MAX_SIZE][MAX_SIZE];
    char printing_board[MAX_SIZE][MAX_SIZE];
    char mined_board[MAX_SIZE][MAX_SIZE];
    
    FILE * map_file;
    FILE * moves_file;
    int move_top;
    move_top = -1;
    int move_rows[MAX_MOVES];
    int move_cols[MAX_MOVES];
    int mine_count;
    char user_move[10], ch;
    int row, col;
    srand(time(NULL));

    int flood_fill_rows[MAX_MOVES];
    int flood_fill_cols[MAX_MOVES];
    int flood_fill_top = -1;
    int flood_fill_count;
    int flood_fill_counts[MAX_MOVES];
    int index = 0;

    N = rand() % ((MAX_SIZE - MIN_SIZE) + 1) + MIN_SIZE;

    boardGeneration(board, mined_board, N);
    mineGeneration(mined_board, N);   
    saveBoard(mined_board, N, map_file);

    /* GAMEPLAY PART*/

    while (1) {
        printBoard(board, N);
        printf("Enter move (row col) or 'undo': ");
        fgets(user_move, sizeof(user_move), stdin);
        flood_fill_count = 0;
        if (sscanf(user_move, "%d %d", &row, &col) == 2) {
            if (row < 0 || col < 0 || row >= N || col >= N) {
                printf("Row or Col can not be bigger than board length. Also can not be lower than 0.\n");
                    continue;
                }
    
                if (board[row][col] != '#') {
                    printf("This cell is already opened. Please try another cell.\n");
                    continue;
                }
    
    
                if (mined_board[row][col] == '*') {
                    board[row][col] = 'X';
                    printBoard(board, N);
                    push(row, col, move_rows, move_cols, &move_top);
                    printf("BOOM! You hit a mine. Game Over.\n");
                    break;
                }
                else if (mined_board[row][col] == '.') {
                    floodFill(row, col, mined_board, board, N, flood_fill_rows, flood_fill_cols, &flood_fill_top, &flood_fill_count);
                }
                push(row, col, move_rows, move_cols, &move_top);
                flood_fill_counts[index] = flood_fill_count;
                index++;
    
            }
        else {
            if (user_move[0] == 'u' && user_move[1] == 'n' && user_move[2] == 'd' && user_move[3] == 'o' && user_move[4] == '\n') {
                if (!isEmpty(&move_top)) {
                    index--;
                    printf("Last move undone\n");
                    for (i = 0; i < flood_fill_counts[index]; i++) {
                        row = flood_fill_rows[flood_fill_top];
                        col = flood_fill_cols[flood_fill_top];
                        board[row][col] = '#';
                        pop_flood_fill(&flood_fill_top);
                    }
                    pop(&move_top);
                } else {
                    printf("You have not done any move already. You can not use 'undo'\n");
                }
            }
            else {
                printf("Invalid input. Please try it again.\n");
                continue;
            }
        }
        if (checkGameOver(board, mined_board, N)) {
            printf("The game has finished. You did it. Congratulations.");
            break;
        }
    }
    saveMoves(move_rows, move_cols, &move_top, moves_file);
}

void boardGeneration(char board[][MAX_SIZE], char mined_board[][MAX_SIZE], int N) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            board[i][j] = '#';
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            mined_board[i][j] = '.';
        }
    }
}

void mineGeneration(char mined_board[][MAX_SIZE], int N) {
    int i, mine_count;
    
    mine_count = N*N / 3;  /* 25% will be mined of board*/
    int random_row, random_col;
    for (i = 0; i < mine_count; i++) {
        random_row = rand() % N;
        random_col = rand() % N;

        if (mined_board[random_row][random_col] == '*') {
            i--;
        }
        else if (mined_board[random_row][random_col] == '.') {
            mined_board[random_row][random_col] = '*';
        }
    }
}

void printBoard(char board[][MAX_SIZE], int N) {
    int i, j;
    printf(" ");
    for (i = 0; i < N; i++) {
        printf("  %d", i);
    }
    printf("\n");
    for (i = 0; i < N; i++) {
        printf("%d", i);
        for (j = 0; j < N; j++) {
            printf("  %c", board[i][j]);
        }
        printf("\n");
    }
}

void saveBoard(char mined_board[][MAX_SIZE], int N, FILE * map_file) {
    int i, j;

    map_file = fopen("map.txt", "wt");


    if (map_file != NULL){
        fprintf(map_file, " ");
        for (i = 0; i < N; i++) {
            fprintf(map_file, "  %d", i);
        }
        fprintf(map_file, "\n");
        for (i = 0; i < N; i++) {
            fprintf(map_file, "%d", i);
            for (j = 0; j < N; j++) {
                fprintf(map_file, "  %c", mined_board[i][j]);
            }
            fprintf(map_file, "\n");
        }
        fclose(map_file);

    } else {
        printf("ERROR. Map.txt file could not be opened.");
        exit(1);
    }

}

void push(int row, int col, int move_rows[MAX_MOVES], int move_cols[MAX_MOVES], int* move_top) {
    if (*move_top < MAX_MOVES) {
        (*move_top)++; 
        move_rows[*move_top] = row;
        move_cols[*move_top] = col;
    }
}

void push_flood_fill(int row, int col, int flood_fill_rows[MAX_MOVES], int flood_fill_cols[MAX_MOVES], int* flood_fill_top, int* flood_fill_count) {
    if (*flood_fill_top < MAX_MOVES) {
        (*flood_fill_top)++;
        (*flood_fill_count)++;
        flood_fill_rows[*flood_fill_top] = row;
        flood_fill_cols[*flood_fill_top] = col;
    }
}


void pop(int* move_top) {
    if (*move_top >= 0) {
        (*move_top)--;
    }
}

void pop_flood_fill(int* flood_fill_top) {
    if (*flood_fill_top >= 0) {
        (*flood_fill_top)--;
    }
}

int isEmpty(int* move_top) {
    return *move_top == -1;
}

int checkMineCount(char mined_board[][MAX_SIZE], int row, int col, int N) {
    int mine_count = 0;    

    if (row == 0 && col == 0) {
        if (mined_board[row][col+1] == '*')mine_count++;
        if (mined_board[row+1][col+1] == '*')mine_count++;
        if (mined_board[row+1][col] == '*')mine_count++;
    } else if (row == N-1 && col == 0) {
        if (mined_board[row][col+1] == '*')mine_count++;
        if (mined_board[row-1][col+1] == '*')mine_count++;
        if (mined_board[row-1][col] == '*')mine_count++;
    } else if (row == N-1 && col == N-1) {
        if (mined_board[row][col-1] == '*')mine_count++;
        if (mined_board[row-1][col-1] == '*')mine_count++;
        if (mined_board[row-1][col] == '*')mine_count++;
    } else if (row == 0 && col == N-1) {
        if (mined_board[row][col-1] == '*')mine_count++;
        if (mined_board[row+1][col-1] == '*')mine_count++;
        if (mined_board[row+1][col] == '*')mine_count++;
    }
    else if (row == 0 && col != 0) {
        if (mined_board[row][col+1] == '*')mine_count++;
        if (mined_board[row][col-1] == '*')mine_count++;
        if (mined_board[row+1][col] == '*')mine_count++;
        if (mined_board[row+1][col+1] == '*')mine_count++;
        if (mined_board[row+1][col-1] == '*')mine_count++;
    } else if (row != 0 && col == 0) {
        if (mined_board[row-1][col] == '*')mine_count++;
        if (mined_board[row+1][col] == '*')mine_count++;
        if (mined_board[row-1][col+1] == '*')mine_count++;
        if (mined_board[row+1][col+1] == '*')mine_count++;
        if (mined_board[row][col+1] == '*')mine_count++;
    } else if (row == N-1 && col != N-1) {
        if (mined_board[row][col+1] == '*')mine_count++;
        if (mined_board[row][col-1] == '*')mine_count++;
        if (mined_board[row-1][col] == '*')mine_count++;
        if (mined_board[row-1][col+1] == '*')mine_count++;
        if (mined_board[row-1][col-1] == '*')mine_count++;
    } else if (row != N-1 && col == N-1) {
        if (mined_board[row-1][col] == '*')mine_count++;
        if (mined_board[row+1][col] == '*')mine_count++;
        if (mined_board[row-1][col-1] == '*')mine_count++;
        if (mined_board[row+1][col-1] == '*')mine_count++;
        if (mined_board[row][col-1] == '*')mine_count++;
    } else {
        if (mined_board[row][col+1] == '*')mine_count++;
        if (mined_board[row][col-1] == '*')mine_count++;
        if (mined_board[row+1][col] == '*')mine_count++;
        if (mined_board[row+1][col+1] == '*')mine_count++;
        if (mined_board[row+1][col-1] == '*')mine_count++;
        if (mined_board[row-1][col] == '*')mine_count++;
        if (mined_board[row-1][col+1] == '*')mine_count++;
        if (mined_board[row-1][col-1] == '*')mine_count++;
    }
    return mine_count;
}

void floodFill(int row, int col, char mined_board[][MAX_SIZE], char board[][MAX_SIZE], int N, int flood_fill_rows[MAX_MOVES], int flood_fill_cols[MAX_MOVES], int* flood_fill_top, int* flood_fill_count) {
    int mine_count;
    if (row < 0 || row >= N || col < 0 || col >= N)
        return;

    if (board[row][col] != '#')
        return;

    mine_count = checkMineCount(mined_board, row, col, N);
    if (mine_count != 0) {
        board[row][col] = (char)mine_count + '0';
        push_flood_fill(row, col, flood_fill_rows, flood_fill_cols, flood_fill_top, flood_fill_count);
        return;
    }
    else if (mine_count == 0 && board[row][col] == '#'){
        board[row][col] = '0';
        push_flood_fill(row, col, flood_fill_rows, flood_fill_cols, flood_fill_top, flood_fill_count);

        floodFill(row, col+1, mined_board, board, N, flood_fill_rows, flood_fill_cols, flood_fill_top, flood_fill_count);
        floodFill(row, col-1, mined_board, board, N, flood_fill_rows, flood_fill_cols, flood_fill_top, flood_fill_count);
        floodFill(row+1, col+1, mined_board, board, N, flood_fill_rows, flood_fill_cols, flood_fill_top, flood_fill_count);
        floodFill(row+1, col, mined_board, board, N, flood_fill_rows, flood_fill_cols, flood_fill_top, flood_fill_count);
        floodFill(row+1, col-1, mined_board, board, N, flood_fill_rows, flood_fill_cols, flood_fill_top, flood_fill_count);
        floodFill(row-1, col+1, mined_board, board, N, flood_fill_rows, flood_fill_cols, flood_fill_top, flood_fill_count);
        floodFill(row-1, col, mined_board, board, N, flood_fill_rows, flood_fill_cols, flood_fill_top, flood_fill_count);
        floodFill(row-1, col-1, mined_board, board, N, flood_fill_rows, flood_fill_cols, flood_fill_top, flood_fill_count);
    }
    
}

void saveMoves(int move_rows[], int move_cols[], int* move_top, FILE * moves_file) {
    int i = 1;
    moves_file = fopen("moves.txt", "wt");
    fprintf(moves_file, "--- Game Moves ---\n");
    while (i-1 <= *move_top) {
        fprintf(moves_file, "Move %d:  (Row %d, Col %d)\n", i, move_rows[i-1], move_cols[i-1]);
        i++;
    }
    fprintf(moves_file, "\n\n");

    fprintf(moves_file, "Total Moves: %d", (*move_top)+1);
    fclose(moves_file);
}

int checkGameOver(char board[][MAX_SIZE], char mined_board[][MAX_SIZE], int N) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (board[i][j] == '#' && mined_board[i][j] != '*')return 0;
        }
    }
    return 1;
}

