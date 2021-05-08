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
     bool result = false;

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
   return true;   
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
    return true;
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

// check the game board whether a player has won or not
bool winCheck(char board[8][8][2])
{
	bool result = false;
	bool whiteCheck = false;
	bool blackCheck = false;
	bool whiteMate = false; // check if there is a check surrounding king
	bool blackMate = false; // check if there is a check surrounding king
	int wKpos[2]; // position of white king ([0] - row, [1] - column)
	int bKpos[2]; // position of black king ([0] - row, [1] - column)

	// find positions of white and black king
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j][1] == 'K')
			{
				if (board[i][j][0] == 'w')
				{
					wKpos[0] = i;
					wKpos[1] = j;
				}
				else if (board[i][j][0] == 'b')
				{
					bKpos[0] = i;
					bKpos[1] = j;
				}
			}
		}
	}

	if (check(bKpos[0], bKpos[1], board, 'w'))
	{
		printf("White - check\n");
		whiteCheck = true;
	}
	if (check(wKpos[0], wKpos[1], board, 'b'))
	{
		printf("Black - check\n");
		blackCheck = true;
	}

	int whiteCounter = 0; // counting number of false checks around black king
	int blackCounter = 0; // counting number of false checks around white king

	// white checkmate or stalemate
	if (board[bKpos[0] - 1][bKpos[1] - 1][0]  == ' ' || board[bKpos[0] - 1][bKpos[1] - 1][0] == 'w')
	{
		if (!check(bKpos[0] - 1, bKpos[1] - 1, board, 'w'))
		{
			whiteCounter++;
		}
	}
	if (board[bKpos[0] - 1][bKpos[1]][0] == ' ' || board[bKpos[0] - 1][bKpos[1]][0] == 'w')
	{
		if (!check(bKpos[0] - 1, bKpos[1], board, 'w'))
		{
			whiteCounter++;
		}
	}
	if (board[bKpos[0] - 1][bKpos[1] + 1][0] == ' ' || board[bKpos[0] - 1][bKpos[1] + 1][0] == 'w')
	{
		if (!check(bKpos[0] - 1, bKpos[1] + 1, board, 'w'))
		{
			whiteCounter++;
		}
	}
	if (board[bKpos[0]][bKpos[1] + 1][0] == ' ' || board[bKpos[0]][bKpos[1] + 1][0] == 'w')
	{
		if (!check(bKpos[0], bKpos[1] + 1, board, 'w'))
		{
			whiteCounter++;
		}
	}
	if (board[bKpos[0] + 1][bKpos[1] + 1][0] == ' ' || board[bKpos[0] + 1][bKpos[1] + 1][0] == 'w')
	{
		if (!check(bKpos[0] + 1, bKpos[1] + 1, board, 'w'))
		{
			whiteCounter++;
		}
	}
	if (board[bKpos[0] + 1][bKpos[1]][0] == ' ' || board[bKpos[0] + 1][bKpos[1]][0] == 'w')
	{
		if (!check(bKpos[0] + 1, bKpos[1], board, 'w'))
		{
			whiteCounter++;
		}
	}
	if (board[bKpos[0] + 1][bKpos[1] - 1][0] == ' ' || board[bKpos[0] + 1][bKpos[1] - 1][0] == 'w')
	{
		if (!check(bKpos[0] + 1, bKpos[1] - 1, board, 'w'))
		{
			whiteCounter++;
		}
	}
	if (board[bKpos[0]][bKpos[1] - 1][0] == ' ' || board[bKpos[0]][bKpos[1] - 1][0] == 'w')
	{
		if (!check(bKpos[0], bKpos[1] - 1, board, 'w'))
		{
			whiteCounter++;
		}
	}

	// black checkmate or stalemate
	if (board[wKpos[0] - 1][wKpos[1] - 1][0]  == ' ' || board[wKpos[0] - 1][wKpos[1] - 1][0] == 'b')
	{
		if (!check(wKpos[0] - 1, wKpos[1] - 1, board, 'b'))
		{
			blackCounter++;
		}
	}
	if (board[wKpos[0] - 1][wKpos[1]][0] == ' ' || board[wKpos[0] - 1][wKpos[1]][0] == 'b')
	{
		if (!check(wKpos[0] - 1, wKpos[1], board, 'b'))
		{
			blackCounter++;
		}
	}
	if (board[wKpos[0] - 1][wKpos[1] + 1][0] == ' ' || board[wKpos[0] - 1][wKpos[1] + 1][0] == 'b')
	{
		if (!check(wKpos[0] - 1, wKpos[1] + 1, board, 'b'))
		{
			blackCounter++;
		}
	}
	if (board[wKpos[0]][wKpos[1] + 1][0] == ' ' || board[wKpos[0]][wKpos[1] + 1][0] == 'b')
	{
		if (!check(wKpos[0], wKpos[1] + 1, board, 'b'))
		{
			blackCounter++;
		}
	}
	if (board[wKpos[0] + 1][wKpos[1] + 1][0] == ' ' || board[wKpos[0] + 1][wKpos[1] + 1][0] == 'b')
	{
		if (!check(wKpos[0] + 1, wKpos[1] + 1, board, 'b'))
		{
			blackCounter++;
		}
	}
	if (board[wKpos[0] + 1][wKpos[1]][0] == ' ' || board[wKpos[0] + 1][wKpos[1]][0] == 'b')
	{
		if (!check(wKpos[0] + 1, wKpos[1], board, 'b'))
		{
			blackCounter++;
		}
	}
	if (board[wKpos[0] + 1][wKpos[1] - 1][0] == ' ' || board[wKpos[0] + 1][wKpos[1] - 1][0] == 'b')
	{
		if (!check(wKpos[0] + 1, wKpos[1] - 1, board, 'b'))
		{
			blackCounter++;
		}
	}
	if (board[wKpos[0]][wKpos[1] - 1][0] == ' ' || board[wKpos[0]][wKpos[1] - 1][0] == 'b')
	{
		if (!check(wKpos[0], wKpos[1] - 1, board, 'b'))
		{
			blackCounter++;
		}
	}

	if (whiteCounter == 0)
	{
		whiteMate = true;
	}
	else
	{
		whiteMate = false;
	}
	if (blackCounter == 0)
	{
		blackMate = true;
	}
	else
	{
		blackMate = false;
	}

	// checkmates or stalemates
	if (whiteCheck && whiteMate)
	{
		printf("White - Checkmate!\n");
		result = true;
	}
	else if (blackCheck && blackMate)
	{
		printf("Black - Checkmate!\n");
		result = true;
	}
	else if ((!whiteCheck && !blackCheck) && whiteMate)
	{
		// black's king stalemate
	}
	else if ((!whiteCheck && !blackCheck) && blackMate)
	{
		// white's king stalemate
	}
	else
	{
		result = false;
	}

	return result;
}

// check if there is a check from one color side
bool check(int kPosRow, int kPosCol, char board[8][8][2], char color)
{
	bool result = false;
	char pieceColor;
	char pieceType;

	// white pawn check
	if ((board[kPosRow + 1][kPosCol + 1][0] == color && board[kPosRow + 1][kPosCol + 1][1] == 'P') || \
		(board[kPosRow + 1][kPosCol - 1][0] == color && board[kPosRow + 1][kPosCol - 1][1] == 'P'))
	{
		result = true;
	}
	//black pawn check
	if ((board[kPosRow - 1][kPosCol + 1][0] == color && board[kPosRow - 1][kPosCol + 1][1] == 'P') || \
		(board[kPosRow - 1][kPosCol - 1][0] == color && board[kPosRow - 1][kPosCol - 1][1] == 'P'))
	{
		result = true;
	}

	// rook and queen
	bool blockBelow = false; // if there is a piece blocking the king from check from below
	bool blockRight = false; // if there is a piece blocking the king from check from right
	bool blockAbove = false; // if there is a piece blocking the king from check from above
	bool blockLeft = false; // if there is a piece blocking the king from check from left

	for (int distance = 1; distance < 8; distance++)
	{
		// below king
		pieceColor = board[kPosRow + distance][kPosCol][0];
		pieceType = board[kPosRow + distance][kPosCol][1];
		if (!(pieceColor == ' ') && !(pieceColor == color && (pieceType == 'R' || pieceType == 'Q')))
		{
			blockBelow = true;
		}
		if (!blockBelow && (pieceColor == color && (pieceType == 'R' || pieceType == 'Q')))
		{
			result = true;
		}

		// to the right of king
		pieceColor = board[kPosRow][kPosCol + distance][0];
		pieceType = board[kPosRow][kPosCol + distance][1];
		if (!(pieceColor == ' ') && !(pieceColor == color && (pieceType == 'R' || pieceType == 'Q')))
		{
			blockRight = true;
		}
		if (!blockRight && (pieceColor == color && (pieceType == 'R' || pieceType == 'Q')))
		{
			result = true;
		}

		// above king
		pieceColor = board[kPosRow - distance][kPosCol][0];
		pieceType = board[kPosRow - distance][kPosCol][1];
		if (!(pieceColor == ' ') && !(pieceColor == color && (pieceType == 'R' || pieceType == 'Q')))
		{
			blockAbove = true;
		}
		if (!blockAbove && (pieceColor == color && (pieceType == 'R' || pieceType == 'Q')))
		{
			result = true;
		}
		
		// to the left of king
		pieceColor = board[kPosRow][kPosCol - distance][0];
		pieceType = board[kPosRow][kPosCol - distance][1];
		if (!(pieceColor == ' ') && !(pieceColor == color && (pieceType == 'R' || pieceType == 'Q')))
		{
			blockLeft = true;
		}
		if (!blockLeft && (pieceColor == color && (pieceType == 'R' || pieceType == 'Q')))
		{
			result = true;
		}
	}

	// bishop and queen
	bool blockTopRight = false; // if there is a piece blocking the king from the top right
	bool blockTopLeft = false; // if there is a piece blocking the king from the top left
	bool blockBotRight = false; // if there is a piece blocking the king from the bottom right
	bool blockBotLeft = false; // if there is a piece blocking the king from the bottom left

	for (int distance = 1; distance < 8; distance++)
	{
		// top right of king
		pieceColor = board[kPosRow - distance][kPosCol + distance][0];
		pieceType = board[kPosRow - distance][kPosCol + distance][1];
		if (!(pieceColor == ' ') && !(pieceColor == color && (pieceType == 'B' || pieceType == 'Q')))
		{
			blockTopRight = true;
		}
		if (!blockTopRight && (pieceColor == color && (pieceType == 'B' || pieceType == 'Q')))
		{
			result = true;
		}

		// top left of king
		pieceColor = board[kPosRow - distance][kPosCol - distance][0];
		pieceType = board[kPosRow - distance][kPosCol - distance][1];
		if (!(pieceColor == ' ') && !(pieceColor == color && (pieceType == 'B' || pieceType == 'Q')))
		{
			blockTopLeft = true;
		}
		if (!blockTopLeft && (pieceColor == color && (pieceType == 'B' || pieceType == 'Q')))
		{
			result = true;
		}

		// bottom right of king
		pieceColor = board[kPosRow + distance][kPosCol + distance][0];
		pieceType = board[kPosRow + distance][kPosCol + distance][1];
		if (!(pieceColor == ' ') && !(pieceColor == color && (pieceType == 'B' || pieceType == 'Q')))
		{
			blockBotRight = true;
		}
		if (!blockBotRight && (pieceColor == color && (pieceType == 'B' || pieceType == 'Q')))
		{
			result = true;
		}
		
		// bottom left of king
		pieceColor = board[kPosRow + distance][kPosCol - distance][0];
		pieceType = board[kPosRow + distance][kPosCol - distance][1];
		if (!(pieceColor == ' ') && !(pieceColor == color && (pieceType == 'B' || pieceType == 'Q')))
		{
			blockBotLeft = true;
		}
		if (!blockBotLeft && (pieceColor == color && (pieceType == 'B' || pieceType == 'Q')))
		{
			result = true;
		}
	}

	// knight
	// first case
	pieceColor = board[kPosRow + 2][kPosCol - 1][0];
	pieceType = board[kPosRow + 2][kPosCol - 1][1];
	if (pieceColor == color && pieceType == 'N') {
		result = true;
	}
	// second case
	pieceColor = board[kPosRow + 1][kPosCol - 2][0];
	pieceType = board[kPosRow + 1][kPosCol - 2][1];
	if (pieceColor == color && pieceType == 'N') {
		result = true;
	}
	
	// third case
	pieceColor = board[kPosRow - 1][kPosCol - 2][0];
	pieceType = board[kPosRow - 1][kPosCol - 2][1];
	if (pieceColor == color && pieceType == 'N') {
		result = true;
	}
	// fourth case
	pieceColor = board[kPosRow - 2][kPosCol - 1][0];
	pieceType = board[kPosRow - 2][kPosCol - 1][1];
	if (pieceColor == color && pieceType == 'N') {
		result = true;
	}
	// fifth case
	pieceColor = board[kPosRow - 2][kPosCol + 1][0];
	pieceType = board[kPosRow - 2][kPosCol + 1][1];
	if (pieceColor == color && pieceType == 'N') {
		result = true;
	}
	// sixth case
	pieceColor = board[kPosRow - 1][kPosCol + 2][0];
	pieceType = board[kPosRow - 1][kPosCol + 2][1];
	if (pieceColor == color && pieceType == 'N') {
		result = true;
	}
	// seventh case
	pieceColor = board[kPosRow + 1][kPosCol + 2][0];
	pieceType = board[kPosRow + 1][kPosCol + 2][1];
	if (pieceColor == color && pieceType == 'N') {
		result = true;
	}
	// eight case
	pieceColor = board[kPosRow + 2][kPosCol + 1][0];
	pieceType = board[kPosRow + 2][kPosCol + 1][1];
	if (pieceColor == color && pieceType == 'N') {
		result = true;
	}

	return result;
}

/* EOF */
