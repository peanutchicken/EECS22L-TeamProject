//header file for fileio

#ifndef FILEIO_H
#define FILEIO_H

#include "movelist.h"

int replayGame(FILE *file, moveList *m, char gameOpponent);

void fprintBoard(char gameBoard[8][8][2], FILE *file);

int revertPrintNotation(char asciiMove[4], int lastMove[4]);

#endif
