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
#include <time.h>

#include "fileio.h"

//this function is used for repeating the game onto file printout
int replayGame(FILE *file, moveList *m, char gameOpponent)
{
    //set up current time
    char* current_time;
    time_t t = time(NULL);
    //get current time
    current_time = ctime(&t);

    //create temp holder for ascii move notation
    char asciimove[4];

    //printed to console so that player knows game has been recorded
    printf("Writing game to file...");

    //write header to file
    fprintf(file, "=== Chess Program, EECS22L Team 03 Spring 2021 ===\n");
    fprintf(file, "Chess Game played: %s \n", current_time);

    //gameOpponent is used as a stand in for the player opponent. If PvP, should be 0. 
    //if PvAI (player white), =1. If PvAI (player black), =2. 
    fprintf(file, "Game played: Player vs ");
    //AI, player is white
    if (gameOpponent == 1) 
    {
        fprintf(file, "AI\n");
        fprintf(file, "Player: White (w)\n");
        fprintf(file, "AI: Black (b)\n");
    }
    //AI, player is black
    else if (gameOpponent == 2) 
    {
        fprintf(file, "AI\n");
        fprintf(file, "Player: Black (b)\n");
        fprintf(file, "AI: White (w)\n");
    }
    //PvP should be 0, but this will catch anythign weird
    else
    {
        fprintf(file, "Player\n");    //assume player by default
        fprintf(file, "Player 1: White (w)\n");
        fprintf(file, "Player 2: Black (b)\n");
    }

    //set "current" entry to the first in the list; iterate through until there are no more in there
    entry* current=m->first;
    //index for below do while
    int a = 0;

    //walk through each board and add them into the file
    do
    {
        //change notation back to ascii from ints
        revertPrintNotation(asciimove, current->latestMove);
        
        //ouchie, this hurts to look at. 
        if (!current->latestMove)
            continue;

        if (a % 2 == 1)
            fprintf(file, "w: ");
        else if (a == 0)
            fprintf(file, "   ");
        else
            fprintf(file, "b: ");

        for (int i=0; i<4; i++)
        {
            fprintf(file, "%c", asciimove[i]);
        }
        fprintf(file, "\n");

        //set current to next board in list
        current=current->next;
        a++;
    } while(current->next!=NULL);
    fprintBoard((m->last)->gameBoard, file);

    //end of file
    fprintf(file, "\n#EOF\n");
    printf(" done\n");

    return 0;
}

int revertPrintNotation(char asciiMove[4], int lastMove[4])
{

    asciiMove[1] = 56 - lastMove[0]; 
    asciiMove[0] = lastMove[1] + 65;
    asciiMove[3] = 56 - lastMove[2]; 
    asciiMove[2] = lastMove[3] + 65;

    return 0;
}


// print board out to file
void fprintBoard(char gameBoard[8][8][2], FILE *file) {

	for (int i = 0; i< 8; i++) 
        {
		if (i == 0) 
        	{
			fprintf(file, "\n    +----+----+----+----+----+----+----+----+\n");
		}
		fprintf(file, "%d   |", 8 - i);
		for (int j = 0; j < 8; j++)
        	{
			fprintf(file, " %c%c |", gameBoard[i][j][0], gameBoard[i][j][1]);
		}
		fprintf(file, "\n    +----+----+----+----+----+----+----+----+\n");
		if (i == 7) 
        	{
				fprintf(file, "      A    B    C    D    E    F    G    H");
		}
	}
	fprintf(file, "\n");
}

/* EOF */
