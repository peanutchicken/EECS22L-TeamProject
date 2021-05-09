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
#include "legalityCheck.h"

//makes a legal move for the specified player
void makeMove(char gameBoard[8][8][2], char player)
{

    //row/column values variables for original value
    int fromRow = 0;
    int fromCol = 0;

    //row/column values variables for destination value
    int toRow = 0;
    int toCol = 0;

    //char values for passing to legalMove()
    char from[2];
    char to[2];

    if(player=='b')
    {
        for(int row = 7; row>0; row--)
        {
            for(int col = 0; col<7; col++)
            {
                if(gameBoard[row][col][0]==player){
                    fromRow = row;
                    fromCol = col;
                    break;
                }
            }
        }
    }
    else if(player=='w')
    {
        for(int row = 0; row<7; row--)
        {
            for(int col = 0; col<7; col++)
            {
                if(gameBoard[row][col][0]==player){
                    fromRow = row;
                    fromCol = col;
                    break;
                }
            }
        }
    }

    from[0] = fromRow;
    from[1] = fromCol;

    printf("from = %d,%d\n",fromRow,fromCol);
    for(int row = 0;row<8; row++)
    {
        for(int col = 0; col<8; col++)
        {
            toRow=row;
            toCol=col;
            to[0]=row;
            to[1]=col;
            printf("to = %d,%d\n",toRow,toCol);
            
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
