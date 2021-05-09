//header file for legalityCheck.c

#ifndef LEGALITYCHECK_H 
#define LEGALITYCHECK_H

#include <stdbool.h>

// validates whether a passed move is legal or not
bool legalMove(char from[2], char to[2], char board[8][8][2]);

bool checkPawn(char from[2], char to[2], char board[8][8][2]);

bool checkRook(char from[2], char to[2], char board[8][8][2]);

bool checkKnight(char from[2], char to[2], char board[8][8][2]);

bool checkBishop(char from[2], char to[2], char board[8][8][2]);

bool checkQueen(char from[2], char to[2], char board[8][8][2]);

bool checkKing(char from[2], char to[2], char board[8][8][2]);

// check the game board whether a player has won or not
bool winCheck(char board[8][8][2]);

// check if there is a check and a possible block from one color side and check for blockage
bool checkAndBlock(int kPosRow, int kPosCol, char board[8][8][2], char color);

// check if there is a block that could be made from a check
bool checkBlock(char board[8][8][2], char color, int array[8][2]);

// check if there is a check around the king
bool check(int kPosRow, int kPosCol, char board[8][8][2], char color);

#endif
