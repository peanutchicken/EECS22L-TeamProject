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
     //format of from[row][col], to[row][col]
     bool result;

     //get the piece char (P, R, N, B) from board using the index provided by from
     //int casting is done to prevent complaints about passing char types as array indicies
     char piece = board[(int)from[0]][(int)from[1]][1];
     switch(piece)
     {
         //pawn
         case 'P':
             result = checkPawn(from, to, board);
             break;

         //rook
         case 'R': 
             result = checkRook(from, to, board);
             break;

         //kNight
         case 'N': 
             result = checkKnight(from, to, board);
             break;

         //bishop
         case 'B': 
             result = checkBishop(from, to, board);
             break;

        //Queen
         case 'Q': 
             result = checkQueen(from, to, board);
             break;

        //King
         case 'K': 
             result = checkKing(from, to, board);
             break;

         default:
             printf("ERR: INVALID PIECE PASSED TO LEGALMOVE\n");
             break;

    }
    return result;
}


bool checkPawn(char from[2], char to[2], char board[8][8][2])
{
     #ifndef DEBUG
     printf("checkingpawn\n");
     #endif

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
                if (((rowTo == rowFrom + 1) && (columnTo == columnFrom)) || \
                    ((rowTo == rowFrom+2) && (columnTo == columnFrom)))
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
		if(((rowTo == rowFrom + 1) && (columnTo == columnFrom - 1)) || \
           ((rowTo == rowFrom + 1) && (columnTo == columnFrom)) || \
           ((rowTo == rowFrom + 1) && (columnTo == columnFrom + 1)) || \
           ((rowTo == rowFrom) && (columnTo == columnFrom - 1)) || \
           ((rowTo == rowFrom) && (columnTo == columnFrom + 1)) || \
           ((rowTo == rowFrom - 1) && (columnTo == columnFrom - 1)) || \
           ((rowTo == rowFrom - 1) && (columnTo == columnFrom)) || \
           ((rowTo == rowFrom - 1) && (columnTo == columnFrom + 1)))
        {
		   return true;
		}

		else
		{
		   return false;
		}
	}
         
         
     }
     //default case
     return false;
}
 
bool checkRook(char from[2], char to[2], char board[8][8][2])
{
   return true;   
}

bool checkKnight(char from[2], char to[2], char board[8][8][2])
{
     #ifndef DEBUG
     printf("checking Knight\n");
     #endif
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
  
         /*Check for Knight*/
         if (board[rowFrom][columnFrom][1] == 'N')
         {
            if (((columnTo == columnFrom + 1) && (rowTo == rowFrom - 2)) || \
                ((columnTo == columnFrom + 1) && (rowTo == rowFrom + 2)) || \
                ((columnTo == columnFrom - 1) && (rowTo == rowFrom + 2)) || \
                ((columnTo == columnFrom - 1) && (rowTo == rowFrom - 2)) || \
                ((columnTo == columnFrom + 2) && (rowTo == rowFrom - 1)) || \
                ((columnTo == columnFrom + 2) && (rowTo == rowFrom + 1)) || \
                ((columnTo == columnFrom - 2) && (rowTo == rowFrom + 1)) || \
                ((columnTo == columnFrom - 2) && (rowTo == rowFrom - 1)))
                {
                   return true;
		}
		else
		{
		   return false;
		}    
	   
	      //default case
              return false;
	    }
     }

     //end default condition, in case none of the above conditions worked
     return false;
}

bool checkBishop(char from[2], char to[2], char board[8][8][2])
{
    return true;
}

bool checkQueen(char from[2], char to[2], char board[8][8][2])
{
    return true;
}

bool checkKing(char from[2], char to[2], char board[8][8][2])
{
    return true;
}

/* EOF */
