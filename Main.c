/*
 * Tic-Tac-Toe Game
 * Final working version
 * Features: Dynamic board size, two-player mode, computer AI, file logging
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function declarations
void initializeBoard(char **board, int size);
void displayBoard(char **board, int size);
int getBoardSize();
int isValidMove(char **board, int size, int row, int col);
void makeMove(char **board, int size, int row, int col, char player);
int checkWin(char **board, int size, char player);
int checkDraw(char **board, int size);
void logMove(FILE *file, int move, int player, int row, int col, char **board, int size);
void playGame(char **board, int size, int gameMode);
int selectGameMode();
void computerMove(char **board, int size, int *row, int *col);

int main() {
    printf("========================================\n");
    printf("        WELCOME TO TIC-TAC-TOE!\n");
    printf("========================================\n");
    
    int size = getBoardSize();
    printf("Board Size: %dx%d\n", size, size);
    
    int gameMode = selectGameMode();
    
    // Allocate memory for board
    char **board = malloc(size * sizeof(char*));
    for(int i = 0; i < size; i++) {
        board[i] = malloc(size * sizeof(char));
    }
    
    initializeBoard(board, size);
    playGame(board, size, gameMode);
    
    // Free memory
    for(int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);
    
    printf("\nThanks for playing!\n");
    return 0;
}

void initializeBoard(char **board, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard(char **board, int size) {
    printf("\n  ");
    for(int j = 0; j < size; j++) {
        printf("%d ", j);
    }
    printf("\n");
    
    for(int i = 0; i < size; i++) {
        printf("%d ", i);
        for(int j = 0; j < size; j++) {
            printf("|%c", board[i][j]);
        }
        printf("|\n");
        
        if(i < size - 1) {
            for(int j = 0; j < size; j++) {
                printf("---");
            }
            printf("-\n");
        }
    }
}

int getBoardSize() {
    int size;
    printf("Enter board size (3-10): ");
    scanf("%d", &size);
    
    while(size < 3 || size > 10) {
        printf("Invalid size! Enter 3-10: ");
        scanf("%d", &size);
    }
    
    return size;
}

int selectGameMode() {
    int mode;
    printf("\nSelect Game Mode:\n");
    printf("1. Two Players\n");
    printf("2. Play against Computer\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &mode);
    
    while(mode != 1 && mode != 2) {
        printf("Invalid choice! Enter 1 or 2: ");
        scanf("%d", &mode);
    }
    
    if(mode == 1) {
        printf("Selected: Two Players\n");
    } else {
        printf("Selected: Play against Computer\n");
    }
    
    return mode;
}

int isValidMove(char **board, int size, int row, int col) {
    if(row < 0 || row >= size || col < 0 || col >= size) {
        return 0;
    }
    if(board[row][col] != ' ') {
        return 0;
    }
    return 1;
}

void makeMove(char **board, int size, int row, int col, char player) {
    board[row][col] = player;
}

int checkWin(char **board, int size, char player) {
    // Check rows
    for(int i = 0; i < size; i++) {
        int count = 0;
        for(int j = 0; j < size; j++) {
            if(board[i][j] == player) count++;
        }
        if(count == size) return 1;
    }
    
    // Check columns
    for(int j = 0; j < size; j++) {
        int count = 0;
        for(int i = 0; i < size; i++) {
            if(board[i][j] == player) count++;
        }
        if(count == size) return 1;
    }
    
    // Check main diagonal
    int count = 0;
    for(int i = 0; i < size; i++) {
        if(board[i][i] == player) count++;
    }
    if(count == size) return 1;
    
    // Check anti-diagonal
    count = 0;
    for(int i = 0; i < size; i++) {
        if(board[i][size-1-i] == player) count++;
    }
    if(count == size) return 1;
    
    return 0;
}

int checkDraw(char **board, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

void logMove(FILE *file, int move, int player, int row, int col, char **board, int size) {
    fprintf(file, "Move %d: Player %d (%c) at %d,%d\n", 
            move, player, (player == 1) ? 'X' : 'O', row, col);
    
    fprintf(file, "Board state:\n");
    fprintf(file, "  ");
    for(int j = 0; j < size; j++) {
        fprintf(file, "%d ", j);
    }
    fprintf(file, "\n");
    
    for(int i = 0; i < size; i++) {
        fprintf(file, "%d ", i);
        for(int j = 0; j < size; j++) {
            fprintf(file, "|%c", board[i][j]);
        }
        fprintf(file, "|\n");
    }
    fprintf(file, "\n");
}

void computerMove(char **board, int size, int *row, int *col) {
    int validMoves = 0;
    
    // Count valid moves
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(board[i][j] == ' ') validMoves++;
        }
    }
    
    if(validMoves == 0) {
        *row = -1;
        *col = -1;
        return;
    }
    
    // Generate random move
    int randomMove = (rand() % validMoves) + 1;
    int currentMove = 0;
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(board[i][j] == ' ') {
                currentMove++;
                if(currentMove == randomMove) {
                    *row = i;
                    *col = j;
                    return;
                }
            }
        }
    }
}

void playGame(char **board, int size, int gameMode) {
    FILE *logFile = fopen("game_log.txt", "w");
    if(logFile == NULL) {
        printf("Error opening log file\n");
        return;
    }
    
    fprintf(logFile, "Game Log\n");
    fprintf(logFile, "Size: %dx%d\n", size, size);
    if(gameMode == 1) {
        fprintf(logFile, "Mode: Two Players\n");
    } else {
        fprintf(logFile, "Mode: Player vs Computer\n");
    }
    fprintf(logFile, "\n");
    
    int player = 1;
    int move = 1;
    int gameOver = 0;
    int row, col;
    
    srand(time(NULL));
    
    while(!gameOver) {
        displayBoard(board, size);
        
        if(gameMode == 1 || player == 1) {
            // Human player
            printf("\nPlayer %d (%c), enter your move (row column): ", 
                   player, (player == 1) ? 'X' : 'O');
            scanf("%d %d", &row, &col);
        } else {
            // Computer player
            printf("\nComputer (%c) is thinking...\n", 'O');
            computerMove(board, size, &row, &col);
            printf("Computer chooses: %d %d\n", row, col);
        }
        
        if(isValidMove(board, size, row, col)) {
            makeMove(board, size, row, col, (player == 1) ? 'X' : 'O');
            logMove(logFile, move, player, row, col, board, size);
            
            if(checkWin(board, size, (player == 1) ? 'X' : 'O')) {
                printf("\nFinal Board:\n");
                displayBoard(board, size);
                
                if(gameMode == 1) {
                    printf("\nPlayer %d wins!\n", player);
                    fprintf(logFile, "Player %d wins!\n", player);
                } else {
                    if(player == 1) {
                        printf("\nYou win!\n");
                        fprintf(logFile, "Player wins!\n");
                    } else {
                        printf("\nComputer wins!\n");
                        fprintf(logFile, "Computer wins!\n");
                    }
                }
                gameOver = 1;
            } else if(checkDraw(board, size)) {
                printf("\nFinal Board:\n");
                displayBoard(board, size);
                printf("\nIt's a draw!\n");
                fprintf(logFile, "Draw!\n");
                gameOver = 1;
            } else {
                player = (player == 1) ? 2 : 1;
                move++;
            }
        } else {
            if(gameMode == 1 || player == 1) {
                if(row < 0 || row >= size || col < 0 || col >= size) {
                    printf("Error: Move out of bounds! Enter row and column between 0 and %d\n", size-1);
                } else {
                    printf("Error: Cell already occupied! Choose an empty cell\n");
                }
                printf("Try again!\n");
            }
        }
    }
    
    fclose(logFile);
    printf("\nGame saved to game_log.txt\n");
}