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

    //write header to file
    fprintf(file, "=== Chess Program, EECS22L Team 03 Spring 2021 ===\n");
    fprintf(file, "Chess Game played: %s \n", current_time);

    fprintf(file, "Game played: Player vs ");
    if (gameOpponent == 1) 
        fprintf(file, "AI\n");
    //written this way to provide extendibility for other AI options
    else
        fprintf(file, "Player\n");    //assume player by default
        


    //end of file
    fprintf(file, "\n#EOF");
    return 0;
}

/* EOF */
