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

#include "constants.h"
#include "board.h"
#include "movelist.h"
#include "ai.h"
#include "legalityCheck.h"
#include "fileio.h"
#include "server.h"
#include "account.h"

/* declare printMenu function below */
void PrintMenu();

int main()
{
	// int n;

    // //set up file to write output to
    // FILE *file;
    // file = fopen("chessGameReplay.txt", "w+");
	
	// PrintMenu();
	// scanf("%d", &n);
	// while(n != 3) {
	// 	char gameBoard[8][8][2] = {
	// 			{"bR", "bN", "bB", "bQ", "bK", "bB", "bN", "bR"},
	// 			{"bP", "bP", "bP", "bP", "bP", "bP", "bP", "bP"},
	// 			{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	// 			{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	// 			{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	// 			{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	// 			{"wP", "wP", "wP", "wP", "wP", "wP", "wP", "wP"},
	// 			{"wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"}};
	// 	switch (n) {
    //         case 1:
    //             printf("player Vs Player is loading...\n");
    //             playerVsPlayer(gameBoard, file);
    //             break;
    //         case 2:
    //             printf("player Vs AI is loading...\n");
    //             playerVsAI(gameBoard, file);
    //             break;
    //         default :
    //             printf("Invalid option!\n" );
	// 	}
	// 	PrintMenu();
	// 	scanf("%d", &n);
	// }	
    // fclose(file);
	
    //commented out p1 code for new multiplayer code
    //menus will be clientside
    //currently the two testing usernames are test1 and test2




    int readRet;

    int running = 1;

    int serverSocket = serverInit(SERVERPORT, 5);
    fd_set availableSockets;
    fd_set readySockets;

    FD_ZERO(&availableSockets);
    FD_SET(serverSocket, &availableSockets);
    printf("\nserver initialized, beginning running loop\n");
    //server running loop
    while (running==1)
    {
        readySockets = availableSockets;
        printf("waiting for select\n");
        select(FD_SETSIZE, &readySockets, NULL, NULL, NULL);
        printf("Select returned\n");
        for (int i = 0; i < FD_SETSIZE; i++)
        {
            if (FD_ISSET(i, &readySockets))
            {
                if(i == serverSocket) //new connection
                {
                    printf("\n New Connection \n");
                    int tempSocket = acceptConnection(serverSocket);
                    FD_SET(tempSocket, &availableSockets);
                }
                else //client is ready to send data
                {
                    char recvBuffer[256];
                    char sendBuffer[256];
                    sendBuffer[0] = 0;
                    
                    readRet = read(i,recvBuffer,sizeof(recvBuffer)-1); //readRet now contains the length of the data sent by the client

                    recvBuffer[readRet]=0; //setting the last n'th value of recvBuffer to NULL so that we can use string functions on it and print it as a string

                    printf("recvBuffer = %s\n",recvBuffer); //print out the sent data

                    if(recvBuffer[0]=='-') //checks for command denoted by -
                    {
                        switch(recvBuffer[1]) //switch case for all the commands
                        {
                            case 'm': //message

                                printf("Server received a message\n");
                                strcpy(sendBuffer, "message recieved\n");
                                write(i,sendBuffer,strlen(sendBuffer));
                                break;

                            case 'l': //login request
                                printf("Server received a login request\n");

                                //checks the username against the two test accounts, will need to implement a working account system
                                //compiler whines about this??
                                //char* input = 
                                strtok(recvBuffer," "); //removes the -l
                                //grabs the username
                                char* username = strtok(NULL," ");
			
                                if((strcmp(username,"test1") == 10) || (strcmp(username,"test2") == 10)) //checking against the testing usernames
                                {
                                    strcpy(sendBuffer,"1");
                                }
                                else
                                {
                                    strcpy(sendBuffer,"0");
                                }
                                write(i,sendBuffer,strlen(sendBuffer)); //sends the sendBuffer back to the client that sent data
                                break;
                            case 'y': //test case for client testing
                                fflush(stdout);
                                printf("Testing client printing\n");
                                strcpy(sendBuffer, "Testing1");
                                write(i,"Testing1",strlen(sendBuffer));
                                sleep(1);
                                
                                strcpy(sendBuffer, "Testing2");
                                write(i,"Testing2",strlen(sendBuffer));
                                sleep(1);    

                                strcpy(sendBuffer, "Asking for input");
                                printf("Asking for input\n");
                                write(i,"Asking for input",strlen(sendBuffer));
                                sleep(1);

                                strcpy(sendBuffer, "-i");
                                write(i,"-i",strlen(sendBuffer));
                                sleep(1);

                                printf("Waiting for input\n");
                                readRet = read(i,recvBuffer,sizeof(recvBuffer)-1); //readRet now contains the length of the data sent by the client
                                recvBuffer[readRet]=0; //setting the last n'th value of recvBuffer to NULL so that we can use string functions on it and print it as a string

                                printf("Recieved input: %s \n",recvBuffer);
                                break;
                            case 'q': //quits the server
                                printf("Quitting the server\n");
                                strcpy(sendBuffer, "Quitting server");
                                write(i,sendBuffer,strlen(sendBuffer));
                                running = 0;
                                break;
                            case 'a':
                                printf("Received valid move from client.\n");
                                break;
                            
                            default:
                                printf("unrecognized command\n");
                                strcpy(sendBuffer, "unknown command");
                                write(i,sendBuffer,strlen(sendBuffer));
                                break;
                        }
                    }

                    FD_CLR(i,&availableSockets);
                }
            }
        }
    }
    close(serverSocket);
	return 0;
}

/* Menu */
void PrintMenu()
{
    printf("\n-------------------------\n");
    printf(" 1: Player vs player\n");
    printf(" 2: Player vs AI\n");
    printf(" 3: Exit Program\n");
    printf("\n-------------------------\n");
    printf("Please make your choice: ");
}

/* EOF */
