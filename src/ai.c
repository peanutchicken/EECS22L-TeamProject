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
#include <stdbool.h>

#include "ai.h"

//makes a legal move for the specified player
void makeMove(char gameBoard[8][8][2], char player)
{
    srand(time(0));
    //row/column values variables for original value
    int fromRow = 999;
    int fromCol = 999;

    //row/column values variables for destination value
    int toRow = 999;
    int toCol = 999;

    //char values for passing to legalMove()
    char from[2];
    char to[2];

    int tempValue=100;

    if(player=='b')
    {
        while(fromCol==999)
        {
            tempValue = (rand() %(8));
            for(int row = 7; row>0; row--)
            {
                if((gameBoard[row][tempValue][0])=='b'){
                    fromRow = row;
                    fromCol = tempValue;
                    break;
                }
            }
        }
    }
    else if(player=='w')
    {
        while(fromCol==999)
        {
            tempValue = (rand() %(8));
            for(int row = 0; row<7; row++)
            {
                if((gameBoard[row][tempValue][0])=='w'){
                    fromRow = row;
                    fromCol = tempValue;
                    break;
                }
            }
        }
    }

    from[0] = fromRow;
    from[1] = fromCol;

    //printf("from = %d,%d\n",fromRow,fromCol);
    for(int row = 0;row<8; row++)
    {
        for(int col = 0; col<8; col++)
        {
            toRow=row;
            toCol=col;
            to[0]=row;
            to[1]=col;
            //printf("to = %d,%d\n",toRow,toCol);
            
            if(legalMove(from,to,gameBoard)){
                break;
            }
        }

        if(legalMove(from,to,gameBoard)){
                break;
        }
    }

    

    
    


    //code from the end of player input to maintain consistancy
    gameBoard[toRow][toCol][0] = gameBoard[fromRow][fromCol][0];
	gameBoard[toRow][toCol][1] = gameBoard[fromRow][fromCol][1];
	gameBoard[fromRow][fromCol][0] = ' ';
	gameBoard[fromRow][fromCol][1] = ' ';
    
    return;
}


/* EOF */
