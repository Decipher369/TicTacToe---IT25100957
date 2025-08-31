/*
 * Tic-Tac-Toe Game
 * Started working on this today
 * Not sure how to implement everything yet
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Welcome to Tic-Tac-Toe!\n");
    
    // trying to make a 3x3 board
    char board[3][3];
    
    // initialize board with spaces
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
    
    // game loop - this is probably wrong
    int gameOver = 0;
    int player = 1; // 1 for X, 2 for O
    
    while(!gameOver) {
        displayBoard(board);
        
        int row, col;
        printf("Player %d, enter row and column: ", player);
        scanf("%d %d", &row, &col);
        
        // trying to place the move
        if(board[row][col] == ' ') {
            board[row][col] = (player == 1) ? 'X' : 'O';
            player = (player == 1) ? 2 : 1; // switch player
        } else {
            printf("That spot is taken!\n");
        }
        
        // check if game is over - not working yet
        if(checkWin(board)) {
            printf("Someone won!\n");
            gameOver = 1;
        }
    }
    
    return 0;
}

// trying to make a function to check if someone won
// this is my first attempt - probably has bugs
int checkWin(char board[3][3]) {
    // check rows
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return 1;
        }
    }
    
    // check columns - not sure if this is right
    for(int j = 0; j < 3; j++) {
        if(board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ') {
            return 1;
        }
    }
    
    // check diagonals - this might be wrong
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return 1;
    }
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return 1;
    }
    
    return 0;
}

// function to display board
// this is my first attempt - might have bugs
void displayBoard(char board[3][3]) {
    printf("  0 1 2\n");
    for(int i = 0; i < 3; i++) {
        printf("%d ", i);
        for(int j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}