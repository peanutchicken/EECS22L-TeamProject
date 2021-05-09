//header file for movelist.c
#pragma once
#ifndef MOVELIST_H
#define MOVELIST_h



typedef struct moveEntry {
	struct moveList* list;
	char gameBoard[8][8][2];
	struct moveEntry *next;
	struct moveEntry *last;
} entry;

typedef struct moveList{
	entry* first;
	entry* last;
} moveList;


//creates a new entry and returns it
entry *newMoveEntry(moveList *m, char gb[8][8][2]);

//deletes an entry and correctly reassigns the next and last entry's pointers
void deleteMoveEntry(moveList *m,entry *a);

//creates new entry and adds it to the end of the movelist
void append(moveList *m,char gameBoard[8][8][2]);

//creates a list and returns it
moveList *createList();

//deletes list and frees it
void deleteList(moveList *m);

//deletes n entries from the end of the list
void deleteNFromEnd(moveList *m, int n);

//returns the move made between board 1 and 2
void moveDifference(char out[5],char gameBoard1[8][8][2], char gameBoard2[8][8][2]);

//prints out every board state in the list
//for debugging
void printList(moveList *m);



#endif
