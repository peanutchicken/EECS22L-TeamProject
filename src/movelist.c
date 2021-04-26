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



//creates a new entry and returns it
entry *newMoveEntry(moveList *m, char gb[8][8][2]){
    entry* temp = malloc(sizeof(entry));
    temp->next=NULL;
    temp->last=NULL;
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
void deleteMoveEntry(moveList *m,entry *a){
    if(a->next==NULL&&a->last==NULL){ //next and last are null (only entry in list)
        free(a);
        a=NULL;
        m->first = NULL;
        m->last = NULL;
    }
    else if(a->next==NULL&&a->last!=NULL){ //next is null and last is valid pointer (last entry in list)
        m->last = a->last;
        (a->last)->next=NULL;
        free(a);
        a=NULL;
    }
    else if(a->next!=NULL&&a->last==NULL){ //next is valid pointer and last is null (first entry in list)
        m->first = a->next;
        (a->next)->last=NULL;
        free(a);
        a=NULL;
    }
    else if(a->next!=NULL&&a->last!=NULL){ //next and last are both valid pointers (entry in the middle of the list)
        (a->last)->next=a->next;
        (a->next)->last=a->last;
        a->next=NULL;
        a->last=NULL;
        free(a);
        a=NULL;
    }


}

//creates new entry and adds it to the end of the movelist
void append(moveList *m,char gameBoard[8][8][2]){
    entry* newEntry = newMoveEntry(m,gameBoard);
    (m->last)->next = newEntry;
    m->last = newEntry;
}

//deletes list and frees it
void deleteList(moveList *m){
    entry* current = m->first;
    entry* next;
    while(current!=NULL){
        next = current->next;
        free(current);
        current = next;
    }
    free(m);
}

//deletes n entries from the end of the list
void deleteNFromEnd(moveList *m, int n){
    entry* current = m->last;
    entry* last;
    for(int i=0;i<n;i++){
        last = current->last;
        deleteMoveEntry(m,current);
        current = last;
    }
    m->last = current;
}

//returns the move made between board 1 and 2, can't use string functions since the board char arrays don't end in null characters
char* moveDifference(char gameBoard1[8][8][2], char gameBoard2[8][8][2]){
    char* retVal=malloc(sizeof(char)*5);
    char from[2];
    char to[2];
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            
            if((gameBoard1[i][j][0]!=gameBoard2[i][j][0])&&(gameBoard1[i][j][1]!=gameBoard2[i][j][1])){ //finds where the two boards are different, should be 2 positions
                if(gameBoard1[i][j][0]=='\0'){
                    sprintf(to,"%d%c", i+1 , (char)(104-j));
                }
                if(gameBoard2[i][j][0]=='\0'){
                    sprintf(from,"%d%c", i+1, (char)(104-j));
                }
            }

        }
    }
    strcat(retVal,from);
    strcat(retVal,",");
    strcat(retVal,to);
    return retVal;
}

/* EOF */
