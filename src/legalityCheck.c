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

#include "legalityCheck.h"

/*validates whether a passed move is legal or not*/
bool legalMove(char from[2], char to[2],char board[8][8][2])
 {
     /*check for valid piece unit*/
     if ((from[0] < 65 || from[0] > 72) || (from[1] < 49 || from[1] > 56))
     {
        return false;
     }
     /*check for valid move*/
     else if ((to[0] < 65 || to[0] > 72) || (to[1] < 49 || to[1] > 56))
     {
         return false;
     }
     else 
     {
         /*convert to number*/
         int columnFrom = (int)from[0]-65;
         int rowFrom = (int)56-from[1];
         int columnTo = (int)to[0]-65;
         int rowTo = (int)56-to[1];
  
         /*Check for pawn*/
         if (board[rowFrom][columnFrom][1] == 'P')
         {
            /*Check for white pawn*/
            if(board[rowFrom][columnFrom][0] == 'w')
            {
		if ((columnTo == columnFrom) && ((rowTo == rowFrom - 1) || (rowTo == rowFrom - 2)))
		{
			return true;
		}
                else
                {
                       return false;
                }
            }

	    /*Check for black pawn*/	
            else 
            {
                if (((rowTo == rowFrom + 1) && (columnTo == columnFrom)) || ((rowTo == rowFrom+2) && (columnTo == columnFrom)))
                {
                    return true;
                }
                else
                {
		    printf("Invalid Pawn's move.");
                    return false;
                }
            }
            
        }
	
	/*Check for king*/
	else if (board[rowFrom][columnFrom][1] == 'K')
	{
		if(((rowTo == rowFrom + 1) && (columnTo == columnFrom - 1))||((rowTo == rowFrom + 1) && (columnTo == columnFrom))||((rowTo == rowFrom + 1) && (columnTo == columnFrom + 1))||((rowTo == rowFrom) && (columnTo == columnFrom - 1))|| ((rowTo == rowFrom) && (columnTo == columnFrom + 1)) || ((rowTo == rowFrom - 1) && (columnTo == columnFrom - 1)) || ((rowTo == rowFrom - 1) && (columnTo == columnFrom)) || ((rowTo == rowFrom - 1) && (columnTo == columnFrom + 1)))
		{
		   return true;
		}
		else
		{
		   return false;
		}
	}
         
         
     }
     
 }

/* EOF */
