//header file for ai.c

#ifndef AI_H
#define AI_H 

#include "legalityCheck.h"
#include "movelist.h"
//lol dependencies
#include "board.h"

//makes a legal move for the specified player
void makeMove(moveList *m, char gameBoard[8][8][2], char player);


#endif
