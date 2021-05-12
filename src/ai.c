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
void makeMove(moveList *m, char gameBoard[8][8][2], char player)
{
    srand(time(0));
    //row/column values variables for original value
    int fromRow;
    int fromCol;

    //row/column values variables for destination value
    int toRow;
    int toCol;

    //char values for passing to legalMove()
    char from[2];
    char to[2];
    //int array used to add move to linkedlist
    int lastMove[4];

    int tempValue;

    bool moveFound = false;
    //loop until a legal move is found completely
    while(!moveFound)
    {
        //row/column values variables for original value
        fromRow = 65;
        fromCol = 65;

        //row/column values variables for destination value
        toRow = 65;
        toCol = 65;


        tempValue=65;
        

        if(player=='b')
        {
            while(fromCol==65)
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
            while(fromCol==65)
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
                    moveFound = true;
                    break;
                }
            }

            if(legalMove(from,to,gameBoard)){
                    break;
            }
        }
    }
    

    lastMove[0] = fromRow;
    lastMove[1] = fromCol;
    lastMove[2] = toRow;
    lastMove[3] = toCol;

    append(m, gameBoard, lastMove);

    //in passing to this, only the move[4] values are used to add it in; from[2] and to[2]
    //are only for legacy support

    //move piece
    gameBoard[toRow][toCol][0] = gameBoard[fromRow][fromCol][0];
	gameBoard[toRow][toCol][1] = gameBoard[fromRow][fromCol][1];
	gameBoard[fromRow][fromCol][0] = ' ';
	gameBoard[fromRow][fromCol][1] = ' ';
    
    return;
}


/* EOF */
