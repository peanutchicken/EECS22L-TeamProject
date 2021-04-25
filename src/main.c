//Main file, used for running program, menu options, quitting

/*********************************************************************/
/* UCI EECS22L Software engineering project, Chess Game              */
/* Team 03, EECS22L Spring 2021                                      */
/*                                                                   */
/* Authors: Jacob Bokor, Rayi Lam, Lichen Wang,                      */
/* Nghi Nguyen, Ryan Shum                                            */
/*                                                                   */
/* Modifications are all tracked in git at:                          */
/* https://github.uci.edu/EECS-22L-S-21-Team-Projects/Team03/        */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "board.h"
#include "movelist.h"
#include "ai.h"
#include "legalityCheck.h"

/*
int printBoard() {



    return 0;
}
*/

int main()
{
	char gameBoard[8][8][2] = {
				{"bR", "bN", "bB", "bQ", "bK", "bB", "bN", "bR"},
				{"bP", "bP", "bP", "bP", "bP", "bP", "bP", "bP"},
				{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
				{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
				{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
				{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
				{"wP", "wP", "wP", "wP", "wP", "wP", "wP", "wP"},
				{"wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"}};

	playerVsAI(gameBoard);

	return 0;
}

/* EOF */
