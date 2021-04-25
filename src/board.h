//header file for board

#ifndef BOARD_H
#define BOARD_H

#endif

// game runner that loops through human vs human chess game
void playerVsPlayer(char gameBoard[8][8][2]);

// game runner that loops through human vs AI chess game
void playerVsAI(char gameBoard[8][8][2]);

// print current state of the chess board and its pieces
void printBoard(char gameBoard[8][8][2]);

// update the chess board accordingly from player user input
void playerInput(char gameBoard[8][8][2], char player);

/* EOF */ 
