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
    
    displayBoard(board);
    
    return 0;
}

// trying to make a function to check if someone won
// not sure if this is right
int checkWin() {
    // this function is empty for now
    // need to figure out how to check rows, columns, diagonals
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