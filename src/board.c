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

#include "board.h"
#include "legalityCheck.h"
#include "movelist.h"
#include "ai.h"

// game runner that loops through human vs human chess game
void playerVsPlayer(char gameBoard[8][8][2]) 
{
	moveList* list = createList();
	printf("\nWelcome to Player vs Player Chess Game!\n");
	printBoard(gameBoard);
	append(list,gameBoard); // adds the starting board state
	// main loop
	while (!winCheck(gameBoard)) {
		playerInput(gameBoard, 'w');
		printBoard(gameBoard);
		if (winCheck(gameBoard)) {
			break;
		}
		// append the move list here
		append(list,gameBoard);
		playerInput(gameBoard, 'b');
		printBoard(gameBoard);
		append(list,gameBoard);
	}
	deleteList(list);
	list = NULL;
}

// game runner that loops through human vs AI chess game
void playerVsAI(char gameBoard[8][8][2]) {
	moveList* list = createList();
	char playerColor;
	printf("\nWelcome to Player vs AI chess game!\n");
	printf("Choose White('w') or Black('b'): ");
	scanf(" %c", &playerColor);
	while (!(playerColor == 'w' || playerColor == 'b')) {
		printf("Invalid color. White('w') or Black('b'): ");
		scanf(" %c", &playerColor);
	}
	printBoard(gameBoard);
	append(list,gameBoard);
	// main loop
	while (!winCheck(gameBoard)) {
		if (playerColor == 'w') {
			playerInput(gameBoard, 'w');
			printBoard(gameBoard);
			if (winCheck(gameBoard)) {
				break;
			}
			// append the move list here
			append(list,gameBoard);
			// here is where AI makes its move
			makeMove(gameBoard,'b');
			printBoard(gameBoard);
			append(list,gameBoard);
		} else if (playerColor == 'b') {
			// here is where AI makes its move
			makeMove(gameBoard,'w');
			if (winCheck(gameBoard)) {
				break;
			}
			append(list,gameBoard);
			printBoard(gameBoard);
			playerInput(gameBoard, 'b');
			printBoard(gameBoard);
			// append the move list here
			append(list,gameBoard);
		}
	}

	deleteList(list);
	list = NULL;
	
}

// print current state of the chess board and its pieces
void printBoard(char gameBoard[8][8][2]) {

	for (int i = 0; i< 8; i++) 
        {
		if (i == 0) 
        	{
			printf("\n    +----+----+----+----+----+----+----+----+\n");
		}
		printf("%d   |", 8 - i);
		for (int j = 0; j < 8; j++)
        	{
			printf(" %c%c |", gameBoard[i][j][0], gameBoard[i][j][1]);
		}
		printf("\n    +----+----+----+----+----+----+----+----+\n");
		if (i == 7) 
        	{
				printf("      A    B    C    D    E    F    G    H");
		}
	}
	printf("\n");
}

// update the chess board accordingly from player user input
void playerInput(char gameBoard[8][8][2], char player) {
	char move[4]; // 2 coordinates that the user wants to move the chess piece to
	char from[2]; // start coordinate to pass into legalMove
	char to[2]; // end coordinate to pass into legalMove
	int fromRow; // row number in board array of the chess piece the user wants to move
	int fromCol; // column number in board array of the chess piece the user wants to move
	int toRow; // row number in board array of the new location
	int toCol; // column number in board array of the new location


	// choosing white piece
	if (player == 'w') {
		printf("White - Please choose your move: ");
		scanf("%s", move);

		// assign from and to variables
		from[0] = move[0];
		from[1] = move[1];
		to[0] = move[2];
		to[1] = move[3];

		// conversion from ASCII
		fromRow = 8 - (move[1] - 48);
		fromCol = move[0] - 65;
		toRow = 8 - (move[3] - 48);
		toCol = move[2] - 65;

        	//assign converted ascii values back to from and to
	        from[0] = fromRow;
	        from[1] = fromCol;
	        to[0] = toRow;
	        to[1] = toCol;

		while(!legalMove(from, to, gameBoard) || \
              gameBoard[fromRow][fromCol][0] == 'b' || \
              gameBoard[fromRow][fromCol][0] == ' ') 
        {
			printf("Invalid move. Please enter again: ");
			scanf("%s", move);

			// assign from and to variables
			from[0] = move[0];
			from[1] = move[1];
			to[0] = move[2];
			to[1] = move[3];

			// conversion from ASCII
			fromRow = 8 - (move[1] - 48);
			fromCol = move[0] - 65;
			toRow = 8 - (move[3] - 48);
			toCol = move[2] - 65;

	        	//assign converted ascii values back to from and to
		        from[0] = fromRow;
	        	from[1] = fromCol;
		        to[0] = toRow;
		        to[1] = toCol;
		}
			
	}
		
	// choosing black piece

    else if (player == 'b') 
    {
		printf("Black - Please choose your move: ");
		scanf("%s", move);

		// assign from and to variables
		from[0] = move[0];
		from[1] = move[1];
		to[0] = move[2];
		to[1] = move[3];

		// conversion from ASCII
		fromRow = 8 - (move[1] - 48);
		fromCol = move[0] - 65;
		toRow = 8 - (move[3] - 48);
		toCol = move[2] - 65;
		
		
               //assign converted ascii values back to from and to
               from[0] = fromRow;
               from[1] = fromCol;
               to[0] = toRow;
               to[1] = toCol;

        	//assign converted ascii values back to from and to
	        from[0] = fromRow;
	        from[1] = fromCol;
	        to[0] = toRow;
	        to[1] = toCol;

		while(!legalMove(from, to, gameBoard) || gameBoard[fromRow][fromCol][0] == 'w' || gameBoard[fromRow][fromCol][0] == ' ') 
        {
			printf("Invalid move. Please enter again: ");
			scanf("%s", move);

			// assign from and to variables
			from[0] = move[0];
			from[1] = move[1];
			to[0] = move[2];
			to[1] = move[3];

			// conversion from ASCII
			fromRow = 8 - (move[1] - 48);
			fromCol = move[0] - 65;
			toRow = 8- (move[3] - 48);
			toCol = move[2] - 65;
			
        		//assign converted ascii values back to from and to
        		from[0] = fromRow;
        		from[1] = fromCol;
        		to[0] = toRow;
        		to[1] = toCol;
		}
	}
	
	gameBoard[toRow][toCol][0] = gameBoard[fromRow][fromCol][0];
	gameBoard[toRow][toCol][1] = gameBoard[fromRow][fromCol][1];
	gameBoard[fromRow][fromCol][0] = ' ';
	gameBoard[fromRow][fromCol][1] = ' ';

}

/* EOF */
