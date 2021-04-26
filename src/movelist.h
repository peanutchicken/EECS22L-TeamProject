//header file for movelist.c

#ifndef MOVELIST_H
#define MOVELIST_h



typedef struct moveEntry {
	struct moveList* list;
	char gameBoard[8][8][2];
	entry *next;
	entry *last;
} entry;

typedef struct moveList{
	entry* first;
	entry* last;
} moveList;


//creates a new entry and returns it
entry *newMoveEntry(char gameBoard[8][8][2]);

//deletes an entry and correctly reassigns the next and last entry's pointers
void deleteMoveEntry(entry *e);

//allocates memory for new moveList
moveList* createList();

//creates new entry and adds it to the end of the movelist
void append(moveList *m,char gameBoard[8][8][2]);

//deletes list and frees it
void deleteList(moveList *m);

//deletes n entries from the end of the list
void deleteNFromEnd(moveList *m, entry *e, int n);

//returns the move made between board 1 and 2
char[5] moveDifference(char gameBoard1[8][8][2], char gameBoard2[8][8][2]);



#endif
