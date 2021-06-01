#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
 
void printBoard(char gameBoard[8][8][2]);

int printMenu();


int main()
{
    // int l, n;
    // int SocketFD;	/* socket file descriptor */
    // struct sockaddr_in ServerAddress;	/* server address we connect with */
    // struct hostent *Server;	/* server host */
    // char SendBuf[256];	/* message buffer for sending a message */
    // char RecvBuf[256];	/* message buffer for receiving a response */

    // short port = 10300;

    
    // Server = gethostbyname("crystalcove.eecs.uci.edu");

    // ServerAddress.sin_family = AF_INET;
	// ServerAddress.sin_port = htons(port);
	// ServerAddress.sin_addr = *(struct in_addr *)Server->h_addr_list[0];

    // while(1)
    // {
    //     SocketFD = socket(AF_INET, SOCK_STREAM, 0); //setup socket


    //     printf("Enter a command to send to the server:\n");
    //     printf("-l for login, -m for message\n");

    //     fgets(SendBuf, sizeof(SendBuf), stdin); //takes input

	// 	l = strlen(SendBuf); //length of the sendbuffer

    //     connect(SocketFD, (struct sockaddr *)&ServerAddress,sizeof(ServerAddress)); //connect to the server

    //     write(SocketFD, SendBuf, l); //write to the socket

    //     n = read(SocketFD, RecvBuf, sizeof(RecvBuf) - 1); //server respnse data


    //     RecvBuf[n] = 0; //sets the last last char of the recieve buffer to null to allow us to use it as a string


	// 	printf("Received response: %s\n",  RecvBuf); 
        

    // }
    
    // close(SocketFD);

    //below is the new version of the client

    //Below is a modified version of the test client
    int l;
    int SocketFD;	/* socket file descriptor */
    struct sockaddr_in ServerAddress;	/* server address we connect with */
    struct hostent *Server;	/* server host */
    char SendBuf[256];	/* message buffer for sending a message */
    char RecvBuf[256];	/* message buffer for receiving a response */
    SendBuf[0]=0;
    char username[20];
    //char message[256];  
    short port = 10300;
    int recvBufSize;
    
    Server = gethostbyname("crystalcove.eecs.uci.edu");

    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(port);
    ServerAddress.sin_addr = *(struct in_addr *)Server->h_addr_list[0];

   // int input = printMenu();//this take the input for user's option
//if(input == 1)
//{ 
    do
    {
        //initial login
        SocketFD = socket(AF_INET, SOCK_STREAM, 0); //setup socket
        printf("Enter a username\n");

        fgets(username, sizeof(username), stdin); //takes input

        //formats the username login as "-l <username>"
        strcat(SendBuf, "-l ");
        strcat(SendBuf,username);
        l = strlen(SendBuf);
        printf("send buffer = %s",SendBuf);
        int connectRet=connect(SocketFD, (struct sockaddr *)&ServerAddress,sizeof(ServerAddress)); //connect to the server
        printf("connectRet=%d\n",connectRet);
        write(SocketFD, SendBuf, l); //write to the socket

        recvBufSize = read(SocketFD, RecvBuf, sizeof(RecvBuf)- 1); //read server response
        RecvBuf[recvBufSize] = 0; //sets the last last char of the recieve buffer to null to allow us to use it as a string

        printf("Received response: %s\n",  RecvBuf); 

    } while(atoi(RecvBuf)!=1); //wait for server to respond with 1 for succesful login, atoi() converts string number inputs to an integer value. ie: converts "1" to integer number 1

    printf("Succesful Login!\n"); //if the loop breaks then the login was successful


    //this is where the menu for client would go, will need a way for server to know game started, possibly start as soon as both players are ready. Maybe send a specific flag for readying?
    printf("\nPlayer vs. Player Game Start\n");
  char gameBoard[8][8][2] = {
                                    {"bR", "bN", "bB", "bQ", "bK", "bB", "bN", "bR"},
                                    {"bP", "bP", "bP", "bP", "bP", "bP", "bP", "bP"},
 		                    {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
                                    {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
          	                    {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
         	                    {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
          		            {"wP", "wP", "wP", "wP", "wP", "wP", "wP", "wP"},
          		            {"wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"}};  
  
     
  printBoard(gameBoard);
    //game loop for receiving and sending data
    
    /*
    while(1)
    {
        SocketFD = socket(AF_INET, SOCK_STREAM, 0); //setup socket

        connect(SocketFD, (struct sockaddr *)&ServerAddress,sizeof(ServerAddress)); //connect to the server

	//printf("Sending message to the server: ");
	//fgets(SendBuf, sizeof(SendBuf), stdin);
	
	//format the message as "-m <message>"
	//strcat(SendBuf, "-m");
        //l = strlen(SendBuf);
	//n = write(SocketFD, SendBuf, l);
        
       
        n = read(SocketFD, RecvBuf, sizeof(RecvBuf) - 1); //server respnse data


        RecvBuf[n] = 0; //sets the last last char of the recieve buffer to null to allow us to use it as a string


	printf("Received response: %s\n",  RecvBuf); 
        
        fgets(SendBuf, sizeof(SendBuf), stdin); //takes input

	l = strlen(SendBuf); //length of the sendbuffer
        
        write(SocketFD, SendBuf, l); //write to the socket

    }*/
	
//}
/*
else if (input == 2)
{
        SocketFD = socket(AF_INET, SOCK_STREAM, 0); //setup socket
        printf("Enter your message: ");

        fgets(message, sizeof(message), stdin); //takes input

        //formats the username login as "-m <message>"
        strcat(SendBuf, "-m ");
        strcat(SendBuf,message);
        l = strlen(SendBuf);
        printf("send buffer = %s",SendBuf);
        int connectRet=connect(SocketFD, (struct sockaddr *)&ServerAddress,sizeof(ServerAddress)); //connect to the server
        printf("connectRet=%d\n",connectRet);
        write(SocketFD, SendBuf, l); //write to the socket

        recvBufSize = read(SocketFD, RecvBuf, sizeof(RecvBuf)- 1); //read server response
        RecvBuf[recvBufSize] = 0; //sets the last last char of the recieve buffer to null to allow us to use it as a string
}*/
    
    close(SocketFD);
//}
}

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


int printMenu()
{
  int n;
  do
  {
	printf("1.Login\n");
	printf("2.Send a message to the server\n");
	printf("Please select the option: ");
	scanf("%i",&n);
  } while(n < 1 || n > 2);
  return n;
}



