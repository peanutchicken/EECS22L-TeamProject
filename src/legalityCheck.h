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

// check if there is a check from one color side
bool check(int kPosRow, int kPosCol, char board[8][8][2], char color);

//special moves 
void pawnPromotion(int rowFrom, int columnFrom, char board[8][8][2]);
#endif
