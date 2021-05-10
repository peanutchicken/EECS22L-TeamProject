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
#include <string.h>

#include "movelist.h"
#include "board.h"



//creates a new entry and returns it
entry *newMoveEntry(moveList *m, char gb[8][8][2]){
    entry* temp = malloc(sizeof(entry));
    temp->next=NULL;
    temp->last=NULL;

    for(int i=0; i<4; i++) 
    {
        temp->latestMove[i] = 0;
    }

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            for(int k=0;k<2;k++){
                temp->gameBoard[i][j][k]=gb[i][j][k];
            }
        }
    }
    temp->list=m;
    return temp;
}

//deletes an entry and correctly reassigns the next and last entry's pointers
void deleteMoveEntry(moveList *m,entry *a)
{
    if(a->next==NULL&&a->last==NULL)
    { //next and last are null (only entry in list)
        free(a);
        a=NULL;
        m->first = NULL;
        m->last = NULL;
    }
    else if(a->next==NULL&&a->last!=NULL)
    { //next is null and last is valid pointer (last entry in list)
        m->last = a->last;
        (a->last)->next=NULL;
        free(a);
        a=NULL;
    }
    else if(a->next!=NULL&&a->last==NULL)
    { //next is valid pointer and last is null (first entry in list)
        m->first = a->next;
        (a->next)->last=NULL;
        free(a);
        a=NULL;
    }
    else if(a->next!=NULL&&a->last!=NULL)
    { //next and last are both valid pointers (entry in the middle of the list)
        (a->last)->next=a->next;
        (a->next)->last=a->last;
        a->next=NULL;
        a->last=NULL;
        free(a);
        a=NULL;
    }


}

//creates new entry and adds it to the end of the movelist
void append(moveList *m,char gameBoard[8][8][2], int latestMove[4])
{
    entry* newEntry = newMoveEntry(m,gameBoard);
    if(m->first == NULL&&m->last==NULL) //if the list is empty
    {
        m->first = newEntry;
        m->last = newEntry;
    }
    else
    {
        newEntry->last = m->last; //assign old last to last of the newEntry
        (m->last)->next = newEntry; //reassign the old last's next to newEntry
        m->last = newEntry; //reassign last of the list to newEntry
        
    }
}

//creates new moveList and returns it
moveList *createList()
{
    moveList *temp = malloc(sizeof(moveList));
    temp->first = NULL;
    temp->last = NULL;
    return temp;
}

//deletes list and frees it
void deleteList(moveList *m)
{
    entry* current = m->first;
    entry* next;
    while(current!=NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    m->first = NULL;
    m->last = NULL;
    free(m);
}

//deletes n entries from the end of the list
void deleteNFromEnd(moveList *m, int n)
{
    entry* current = m->last;
    entry* last;
    for(int i=0;i<n;i++)
    {
        last = current->last;
        deleteMoveEntry(m,current);
        current = last;
    }
}

//stores the move made between board 1 and 2 in out[5]
//can't use string functions since the board char arrays don't end in null characters
//output is formatted as "A2,A3"
void moveDifference(char out[5],char gameBoard1[8][8][2], char gameBoard2[8][8][2])
{
    char retVal[5]="     ";
    char from[2];
    char to[2];
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++)
        {
            
            //finds where the two boards are different, should be 2 positions
            if((gameBoard1[i][j][0]!=gameBoard2[i][j][0])&&(gameBoard1[i][j][1]!=gameBoard2[i][j][1])) 
            { 
                if(gameBoard1[i][j][0]==' ')
                {
                    to[0] = 'A'+j;
                    to[1] = '8'-i;
                    to[2] = '\0';
                }
                if(gameBoard2[i][j][0]==' ')
                {
                    from[0] = 'A'+j;
                    from[1] = '8'-i;
                    from[2] = '\0';
                }
            }

        }
    }
    strcat(retVal,from);
    strcat(retVal,",");
    strcat(retVal,to);
    strcpy(out,retVal);
}

//prints every board state in the list
//used for debugging
void printList(moveList *m)
{
    entry* current=m->first;
    do
    {
        printBoard(current->gameBoard);
        current=current->next;
    }
    while(current->next!=NULL);
    printBoard((m->last)->gameBoard);
    
}

/* EOF */
