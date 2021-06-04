//header file for board

#ifndef BOARD_H
#define BOARD_H

#include "movelist.h"
#include "legalityCheck.h"
#include "ai.h"
#include "fileio.h"

#include <stdbool.h>

// game runner that loops through human vs human chess game
void playerVsPlayer(char gameBoard[8][8][2], FILE *file);

// game runner that loops through human vs AI chess game
void playerVsAI(char gameBoard[8][8][2], FILE *file);

// print current state of the chess board and its pieces
void printBoard(char gameBoard[8][8][2]);

// print current state of the chess board and its pieces
void writeBoard(int sock, char gameBoard[8][8][2]);

// update the chess board accordingly from player user input and returns if the user has exited the game or not
bool playerInput(moveList *m, char gameBoard[8][8][2], char player);

// update the chess board accordingly from player user input and returns if the user has exited the game or not
// 0 for VALID. 1 for INVALID.
int clientInput(int sock, char move[4], char gameBoard[8][8][2], char player);

//ascii conversion from char input to int values
int lastMoveConvert(char move[4], char from[2], char to[2], int lastMove[4]);

//prints a suggested move for the respective player
void suggestedMove(char gameBoard[8][8][2], char player);

//restarts the turn
void takeBackMove(char gameBoard[8][8][2], moveList* list);

/* EOF */ 

#endif
