//header file for board

#ifndef BOARD_H
#define BOARD_H

#endif

#include <stdbool.h>

// game runner that loops through human vs human chess game
void playerVsPlayer(char gameBoard[8][8][2]);

// game runner that loops through human vs AI chess game
void playerVsAI(char gameBoard[8][8][2]);

// print current state of the chess board and its pieces
void printBoard(char gameBoard[8][8][2]);

// update the chess board accordingly from player user input and returns if the user has exited the game or not
bool playerInput(char gameBoard[8][8][2], char player);

/* EOF */ 
