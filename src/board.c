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
#include <unistd.h>

#include "board.h"

// game runner that loops through human vs human chess game
void playerVsPlayer(char gameBoard[8][8][2], FILE *file) 
{
	moveList* list = createList();

	bool playerExit = false;

	printf("\nWelcome to Player vs Player Chess Game!\n");
	printBoard(gameBoard);

    // adds the starting board state
    int latestMove[4] = {0,0,0,0};      //blank move to pass to first append
	append(list,gameBoard, latestMove); 

	// main loop
	while (!winCheck(gameBoard) && !playerExit) {
		playerExit = playerInput(list, gameBoard, 'w');

		if (!playerExit) {
			printBoard(gameBoard);
		}

		if (winCheck(gameBoard) || playerExit) {
			break;
		}
		playerExit = playerInput(list, gameBoard, 'b');

		if (!playerExit) {
			printBoard(gameBoard);
		}
	}


    replayGame(file, list, 0);

	deleteList(list);
	list = NULL;
}

// game runner that loops through human vs AI chess game
void playerVsAI(char gameBoard[8][8][2], FILE *file) {
	moveList* list = createList();
	bool playerExit = false;
	char playerColor;
    int gameOpponent = 0;       //used to record what color ai is

	printf("\nWelcome to Player vs AI chess game!\n");
	printf("Choose White('w') or Black('b'): ");
	scanf(" %c", &playerColor);

	while (!(playerColor == 'w' || playerColor == 'b')) {
		printf("Invalid color. White('w') or Black('b'): ");
		scanf(" %c", &playerColor);
	}
	printBoard(gameBoard);

    //blank move for first position in board list
    int latestMove[4] = {0,0,0,0};
	append(list, gameBoard, latestMove);

	// main loop
	while (!winCheck(gameBoard) && !playerExit) {
		if (playerColor == 'w') {
            gameOpponent = 1;
			playerExit = playerInput(list, gameBoard, 'w');
			if (!playerExit) {
				printBoard(gameBoard);
			}

			if (winCheck(gameBoard) || playerExit) {
				break;
			}

			// here is where AI makes its move
			makeMove(list, gameBoard,'b');
			printBoard(gameBoard);

			//takeBackMove(gameBoard,list);
		} 
        else if (playerColor == 'b') {
            gameOpponent = 2;
			// here is where AI makes its move
			makeMove(list, gameBoard,'w');
			printBoard(gameBoard);

			if (winCheck(gameBoard)) 
				break;
			

            //here's where the player makes their move
			playerExit = playerInput(list, gameBoard, 'b');

			if (!playerExit) 
				printBoard(gameBoard);

			//takeBackMove(gameBoard,list);
		}
	}

    //save game to file
    replayGame(file, list, gameOpponent);

	deleteList(list);
	list = NULL;
}

// old print board
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

// new print board for server to write to client
// print current state of the chess board and its pieces
void writeBoard(int sock, char gameBoard[8][8][2]) {
	char tempPiece[2];
	char num[1];

	for (int i = 0; i< 8; i++) 
        {
		if (i == 0) 
        	{
			write(sock, "\n    +----+----+----+----+----+----+----+----+\n", 47);
		}
		num[0] = (char) (56 - i);
		write(sock, num, 1);
		write(sock, "   |", 4);
		for (int j = 0; j < 8; j++)
        	{
			tempPiece[0] = gameBoard[i][j][0];
			tempPiece[1] = gameBoard[i][j][1];
			write(sock, " ", 1);
			write(sock, tempPiece, 2);
			write(sock, " |", 2);
		}
		write(sock, "\n    +----+----+----+----+----+----+----+----+\n", 47);
		if (i == 7) 
        	{
				write(sock, "      A    B    C    D    E    F    G    H", 42);
		}
	}
	write(sock, "\n", 1);
}

// update the chess board accordingly from player user input and returns if the user has exited the game or not
bool playerInput(moveList *m, char gameBoard[8][8][2], char player) {
	char move[4];       // 2 coordinates that the user wants to move the chess piece to
	char from[2];       // start coordinate to pass into legalMove
	char to[2];         // end coordinate to pass into legalMove
    int lastMove[4] = {0,0,0,0};    //last move made in int arr format
	bool playerExit = false; // if the player chooses to exit the game or not


    //move suggestion
	suggestedMove(gameBoard,player);

	// choosing white piece
	if (player == 'w') {
		printf("White - Please choose your move(or \"exit\" to exit current game): ");
		scanf("%s", move);

		// exit
		if (move[0] == 'e' && move[1] == 'x' && move[2] == 'i' && move[3] == 't') {
			playerExit = true;
		}

        lastMoveConvert(move, from, to, lastMove);

		while((!legalMove(from, to, gameBoard) || \
                gameBoard[lastMove[0]][lastMove[1]][0] == 'b' || \
                gameBoard[lastMove[0]][lastMove[1]][0] == ' ') && !playerExit) 
        {
			printf("Invalid move. Please enter again(or \"exit\" to exit current game): ");
			scanf("%s", move);

			// exit
			if (move[0] == 'e' && move[1] == 'x' && move[2] == 'i' && move[3] == 't') {
				playerExit = true;
			}

        lastMoveConvert(move, from, to, lastMove);
		}
			
	}
		
	// choosing black piece

    else if (player == 'b') 
    {
		printf("Black - Please choose your move(or \"exit\" to exit current game): ");
		scanf("%s", move);

		// exit
		if (move[0] == 'e' && move[1] == 'x' && move[2] == 'i' && move[3] == 't') {
			playerExit = true;
		}

        //convert char input values to ascii
        lastMoveConvert(move, from, to, lastMove);

		while((!legalMove(from, to, gameBoard) || \
                gameBoard[lastMove[0]][lastMove[1]][0] == 'w' || \
                gameBoard[lastMove[0]][lastMove[1]][0] == ' ') && !playerExit) 
        {
			printf("Invalid move. Please enter again(or \"exit\" to exit current game): ");
			scanf("%s", move);

			// exit
			if (move[0] == 'e' && move[1] == 'x' && move[2] == 'i' && move[3] == 't') {
				playerExit = true;
			}

            lastMoveConvert(move, from, to, lastMove);
		}

	}

    //append gameboard to moveList
    append(m, gameBoard, lastMove);
	
	if (!playerExit)
	{
		gameBoard[lastMove[2]][lastMove[3]][0] = gameBoard[lastMove[0]][lastMove[1]][0];
		gameBoard[lastMove[2]][lastMove[3]][1] = gameBoard[lastMove[0]][lastMove[1]][1];
		gameBoard[lastMove[0]][lastMove[1]][0] = ' ';
		gameBoard[lastMove[0]][lastMove[1]][1] = ' ';
	}

	return playerExit;
}

// for new multiplayer... 0 for VALID input. 1 for INVALID input.
// update the chess board accordingly from player user input and returns if the user has exited the game or not
int clientInput(int sock, char move[4], char gameBoard[8][8][2], char player) {
	char from[2];       // start coordinate to pass into legalMove
	char to[2];         // end coordinate to pass into legalMove
	int lastMove[4] = {0,0,0,0};    //last move made in int arr format


	// choosing white piece
	if (player == 'w') {

	        lastMoveConvert(move, from, to, lastMove);

		// invalid move
		while((!legalMove(from, to, gameBoard) || \
        	        gameBoard[lastMove[0]][lastMove[1]][0] == 'b' || \
	                gameBoard[lastMove[0]][lastMove[1]][0] == ' ')) 
	       	{
			write(sock, "Invalid move\n", 13);
			return 1;
		}
	}				
	// choosing black piece
	else if (player == 'b') 
	{
        	//convert char input values to ascii
	        lastMoveConvert(move, from, to, lastMove);

		while((!legalMove(from, to, gameBoard) || \
                gameBoard[lastMove[0]][lastMove[1]][0] == 'w' || \
                gameBoard[lastMove[0]][lastMove[1]][0] == ' ')) 
        	{
			write(sock, "Invalid move\n", 13);
			return 1;
		}

	}

	
	gameBoard[lastMove[2]][lastMove[3]][0] = gameBoard[lastMove[0]][lastMove[1]][0];
	gameBoard[lastMove[2]][lastMove[3]][1] = gameBoard[lastMove[0]][lastMove[1]][1];
	gameBoard[lastMove[0]][lastMove[1]][0] = ' ';
	gameBoard[lastMove[0]][lastMove[1]][1] = ' ';

	return 0;
}

//converts ascii input of last move made into int values for chessboard
int lastMoveConvert(char move[4], char from[2], char to[2], int lastMove[4])
{
    //lastMove contains the int board values of the last move made in the format:
    //lastMove[from_Row, from_Col, to_Row, to_Col];

    // conversion from ASCII
    // looks backwards because values come in in col, row format but
    // we want them in row,col
    lastMove[0] = 8 - (move[1] - 48);
    lastMove[1] = move[0] - 65;
    lastMove[2] = 8- (move[3] - 48);
    lastMove[3] = move[2] - 65;

    //this is legacy garbage but it's how values are passed to legality check so i guess it stays
    from[0] = lastMove[0];
    from[1] = lastMove[1];
    to[0] = lastMove[2];
    to[1] = lastMove[3];
 
    return 0;
}

//prints a suggested move for the respective player
void suggestedMove(char gameBoard[8][8][2], char player)
{

	//temporary gameboard
	char tempGameBoard[8][8][2];
    //temporary linkedlist
	moveList* list = createList();

	//suggested move output
	char suggestedOut[5];

	//copys the existing gameboard into a temporary gameboard

	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			tempGameBoard[i][j][0] = gameBoard[i][j][0];
			tempGameBoard[i][j][1] = gameBoard[i][j][1];
		}
	}


    //use temporary moveList to that the suggested move doesn't get added to the real one

	makeMove(list, tempGameBoard,player);

	//printf("made Move in suggestedMove");

	moveDifference(suggestedOut, gameBoard, tempGameBoard);
	//printf("found move difference in suggestedMove");
	printf("\nPsssst... try %s.\n", suggestedOut);

	deleteList(list);
	list = NULL;
}

void takeBackMove(char gameBoard[8][8][2], moveList* list)
{
	int choice;

	printf("Would you like to restart the turn? \n");
	printf("1. Yes \n");
	printf("2. No \n");
	printf("Enter the number of your choice: ");
	scanf("%d",&choice);


	switch(choice)
	{
		case 1:
			deleteNFromEnd(list,2);
			for(int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
				{
					gameBoard[i][j][0]=((list->last)->gameBoard)[i][j][0];
					gameBoard[i][j][1]=((list->last)->gameBoard)[i][j][0];
				}
			}
			return;
			break;

		default:
			return;
			break;

	}
	
	
}
/* EOF */
