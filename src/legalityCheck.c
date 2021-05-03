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

/*This function checks for valid pawn's move*/
bool checkPawn(char from[2], char to[2], char board[8][8][2])
{
     #ifndef DEBUG
     printf("checkingpawn\n");
     #endif

         /*convert to number*/
         int columnFrom = (int)from[1];
         int rowFrom = (int)from[0];
         int columnTo = (int)to[1];
         int rowTo = (int)to[0];
  	
         /*Check for white pawn*/
         if(board[rowFrom][columnFrom][0] == 'w')
         {
		/*The first pawn's move has the option of advancing 2 squares*/
		if (rowFrom == 6)
		{
                	if ((columnTo == columnFrom) &&  \
			   ((rowTo == rowFrom - 1) || (rowTo == rowFrom - 2)))
			{
				 /*check if there is any blocking piece*/
				if(board[rowTo][columnTo][0] != ' ')
                			return false;
		  		return true;
			}
		}
		
		/*Pawn can only move 1 square after the first move*/
		else
		{
			
                	if ((columnTo == columnFrom) && (rowTo == rowFrom - 1))
			{
				 /*check if there is any blocking piece*/
				if(board[rowTo][columnTo][0] != ' ')
                			return false;
		  		return true;
			}
		}

          }

          /*Check for black pawn*/	
          else 
          {                   
		/*The first pawn's move has the option of advancing 2 squares*/
		if (rowFrom == 1)
		{
                	if ((columnTo == columnFrom) && \
			   ((rowTo == rowFrom + 1) || (rowTo == rowFrom + 2)))
			{
				 /*check if there is any blocking piece*/
				if(board[rowTo][columnTo][0] != ' ')
                			return false;
		  		return true;
			}
		}
		
		/*Pawn can only move 1 square after the first move*/
		else
		{
			
                	if ((columnTo == columnFrom) && (rowTo == rowFrom + 1))
			{
				 /*check if there is any blocking piece*/
				if(board[rowTo][columnTo][0] != ' ')
                			return false;
		  		return true;
			}
		}

          }
	  /*default case*/
	  return false;
}
 
bool checkRook(char from[2], char to[2], char board[8][8][2])
{
        #ifndef DEBUG
     printf("checking Rock\n");
     #endif
  
         /*convert to number*/
         int columnFrom = (int)from[1];
         int rowFrom = (int)from[0];
         int columnTo = (int)to[1];
         int rowTo = (int)to[0];

         /*Check for Rock*/
         if (board[rowFrom][columnFrom][1] == 'N')
         {
            if ((rowTo == rowFrom) || (columnTo == columnFrom))
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
}

bool checkKnight(char from[2], char to[2], char board[8][8][2])
{
     #ifndef DEBUG
     printf("checking Knight\n");
     #endif
  
         /*convert to number*/
         int columnFrom = (int)from[1];
         int rowFrom = (int)from[0];
         int columnTo = (int)to[1];
         int rowTo = (int)to[0];

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
    
     #ifndef DEBUG
     printf("checkingbishop\n");
     #endif

     /*convert to number*/
     int columnFrom = (int)from[1];
     int rowFrom = (int)from[0];
     int columnTo = (int)to[1];
     int rowTo = (int)to[0];

     /*Check variables*/
     int checkRow = rowFrom;
     int checkColumn = columnFrom;
     int rowCheck = rowFrom;
     int columnCheck = columnFrom;

    /*check for the diagonal path to top-left*/
    if ((rowTo < rowFrom) && (columnTo < columnFrom))
    {
	while (checkRow >= 0 && checkColumn >= 0)
	{
		checkRow -= 1;
		checkColumn -= 1;    
		if ((rowTo == checkRow) && (columnTo == checkColumn))
		{
			/*check if there is any blocking piece on the path*/
			rowCheck -= 1;
			columnCheck -= 1;
			while(rowCheck > rowTo && columnCheck > columnTo)
			{
				if (board[rowCheck][columnCheck][0] != ' ')
					return false;
				rowCheck -= 1;
				columnCheck -= 1;
			}
			
			/*return false if the destination has the same unit piece color*/
			if (board[rowTo][columnTo][0] == board[rowFrom][columnFrom][0])
				return false;
			return true;
		}
	}
     }

    /*check for the diagonal path to top-right*/
    else if ((rowTo < rowFrom) && (columnTo > columnFrom))
    {
	while (checkRow >= 0 && checkColumn <= 7)
	{
		checkRow -= 1;
		checkColumn += 1;    
		if ((rowTo == checkRow) && (columnTo == checkColumn))
		{
			/*check if there is any blocking piece on the path*/
			rowCheck -= 1;
			columnCheck += 1;
			while(rowCheck > rowTo && columnCheck < columnTo)
			{	
				if (board[rowCheck][columnCheck][0] != ' ')
					return false;
				rowCheck -= 1;
				columnCheck += 1;
			}
			
			/*return false if the destination has the same unit piece color*/
			if (board[rowTo][columnTo][0] == board[rowFrom][columnFrom][0])
				return false;
			return true;
		}
	}
     }

     
    /*check for the diagonal path to bottom-left*/
    else if ((rowTo > rowFrom) && (columnTo < columnFrom))
    {
	while (checkRow <= 7 && checkColumn >= 0)
	{
		checkRow += 1;
		checkColumn -= 1;    
		if ((rowTo == checkRow) && (columnTo == checkColumn))
		{
		
			/*check if there is any blocking piece on the path*/
			rowCheck += 1;
			columnCheck -= 1;
			while(rowCheck < rowTo && columnCheck > columnTo)
			{
				if (board[rowCheck][columnCheck][0] != ' ')
					return false;
				rowCheck += 1;
				columnCheck -= 1;
			}
			
			/*return false if the destination has the same unit piece color*/
			if (board[rowTo][columnTo][0] == board[rowFrom][columnFrom][0])
				return false;
			return true;
		}
	}
     }

    /*check for the diagonal path to bottom-right*/
    else if ((rowTo > rowFrom) && (columnTo > columnFrom))
    {
	while (checkRow >= 0 && checkColumn <= 7)
	{
		checkRow += 1;
		checkColumn += 1;    
		if ((rowTo == checkRow) && (columnTo == checkColumn))
		{
		
			/*check if there is any blocking piece on the path*/
			rowCheck += 1;
			columnCheck += 1;
			while(rowCheck < rowTo && columnCheck < columnTo)
			{
				if (board[rowCheck][columnCheck][0] != ' ')
					return false;
				rowCheck += 1;
				columnCheck += 1;
			}
			
			/*return false if the destination has the same unit piece color*/
			if (board[rowTo][columnTo][0] == board[rowFrom][columnFrom][0])
				return false;
			return true;
		}
	}
     }

   /*return false for other cases*/
   else
   {
   	return false;
   }

   /*dafult case*/
   return false;
}

bool checkQueen(char from[2], char to[2], char board[8][8][2])
{
     #ifndef DEBUG
     printf("checking Queen\n");
     #endif
  
         /*convert to number*/
         int columnFrom = (int)from[1];
         int rowFrom = (int)from[0];
         int columnTo = (int)to[1];
         int rowTo = (int)to[0];
         /*Check for Knight*/
         if (board[rowFrom][columnFrom][1] == 'N')
         {
            if ((rowTo == columnnTo) && ( rowFrom == columnnFrom))
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

bool checkKing(char from[2], char to[2], char board[8][8][2])
{
	
     #ifndef DEBUG
     printf("checkingking\n");
     #endif

     /*convert to number*/
     int columnFrom = (int)from[1];
     int rowFrom = (int)from[0];
     int columnTo = (int)to[1];
     int rowTo = (int)to[0];

	if(((rowTo == rowFrom + 1) && (columnTo == columnFrom - 1)) || \
          ((rowTo == rowFrom + 1) && (columnTo == columnFrom)) || \
          ((rowTo == rowFrom + 1) && (columnTo == columnFrom + 1)) || \
          ((rowTo == rowFrom) && (columnTo == columnFrom - 1)) || \
          ((rowTo == rowFrom) && (columnTo == columnFrom + 1)) || \
          ((rowTo == rowFrom - 1) && (columnTo == columnFrom - 1)) || \
          ((rowTo == rowFrom - 1) && (columnTo == columnFrom)) || \
          ((rowTo == rowFrom - 1) && (columnTo == columnFrom + 1)))
	{
		if (board[rowTo][columnTo][0] == board[rowFrom][columnFrom][0])
			return false;
		return true;
	}
		     
     //default case
     return false;
}

/* EOF */
