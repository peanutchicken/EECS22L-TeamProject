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

/* print a menu */
void PrintMenu();

int main()
{       
	int n;
	
	char gameBoard[8][8][2] = {
				{"bR", "bN", "bB", "bQ", "bK", "bB", "bN", "bR"},
				{"bP", "bP", "bP", "bP", "bP", "bP", "bP", "bP"},
				{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
				{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
				{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
				{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
				{"wP", "wP", "wP", "wP", "wP", "wP", "wP", "wP"},
				{"wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"}};

	PrintMenu();
	scanf("%d", &n);
	while(n != 3) {
		switch (n) {
	                    case 1:
	                        printf("player Vs Player is loading...\n");
	                        playerVsPlayer(gameBoard);
	                        break;
	                    case 2:
	                        printf("player Vs AI is loading...\n");
	                        playerVsAI(gameBoard);
				break;
			    default :
	                        printf("Invalid option!\n" );
		            }
		PrintMenu();
		scanf("%d", &n);
	}	
	
	return 0;
}
/* Menu */
void PrintMenu()
{

    printf("\n-------------------------\n");
    printf(" 1: Player vs player\n");
    printf(" 2: Player vs AI\n");
    printf(" 3: Exit Program\n");
    printf("\n-------------------------\n");
    printf("Please make your choice: ");
}
/* EOF */
