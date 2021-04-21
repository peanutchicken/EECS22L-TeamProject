//header file for board

#ifndef BOARD_H
#define BOARD_H

typedef struct Board BOARD;
typedef struct BoardList BLIST;
typedef struct BoardEntry BENTRY;

//individual board struct
struct Board
{
    //actual gameboard itself
    char gameBoard[8][8][2];

    unsigned int player;
};

//list of boardentries structure
struct BoardList
{
    int Length;
    BENTRY *First;
    BENTRY *Last;
};

//struct for board entry, allows navigation between boards, contained inside boardlist
struct BoardEntry
{
    BLIST *List;
    BENTRY *Next;
    BENTRY *Prev;
    BOARD *Board;
}; 

BOARD *NewBoard(char gameBoard[8][8][2], unsigned int player);

BOARD *NewBlankBoard(char gameBoard[8][8][2]);

void DeleteBoard(BOARD *b);

void PrintBoard(BOARD *b);

//allocate new board list
BLIST *NewBoardList();

//delete board list
void DeleteBoardList(BLIST *l);

//append board at end of the list
void AppendBoard(BLIST *l, BOARD *b);

//print board list
void PrintBoardList(BLIST *b);


#endif 

