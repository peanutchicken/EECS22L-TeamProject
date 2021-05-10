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

int replayGame(FILE *file, moveList *m)
{

    char* current_time;
    time_t t = time(NULL);

    current_time = ctime(&t);

    fprintf(file, "Chess Program, EECS22L Team 03 Spring 2021");
    fprintf(file, "Chess Game played: %s", current_time);

    //end of file
    fprintf(file, "\n#EOF");
    return 0;
}

/* EOF */
