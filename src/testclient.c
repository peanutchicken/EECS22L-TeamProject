#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

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
    int l, n;
    int SocketFD;	/* socket file descriptor */
    struct sockaddr_in ServerAddress;	/* server address we connect with */
    struct hostent *Server;	/* server host */
    char SendBuf[256];	/* message buffer for sending a message */
    char RecvBuf[256];	/* message buffer for receiving a response */
    SendBuf[0]=0;
    char username[20];

    short port = 10300;
    int recvBufSize;
    
    Server = gethostbyname("crystalcove.eecs.uci.edu");

    ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = htons(port);
	ServerAddress.sin_addr = *(struct in_addr *)Server->h_addr_list[0];
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
        printf("send buffer = %s\n",SendBuf);
        int connectRet=connect(SocketFD, (struct sockaddr *)&ServerAddress,sizeof(ServerAddress)); //connect to the server
        printf("connectRet=%d\n",connectRet);
        write(SocketFD, SendBuf, l); //write to the socket

        recvBufSize = read(SocketFD, RecvBuf, sizeof(RecvBuf) - 1); //read server response
        RecvBuf[recvBufSize] = 0; //sets the last last char of the recieve buffer to null to allow us to use it as a string

        printf("Received response: %s\n",  RecvBuf);
 
    } while(atoi(RecvBuf)!=1); //wait for server to respond with 1 for succesful login, atoi() converts string number inputs to an integer value. ie: converts "1" to integer number 1

    printf("Succesful Login!\n"); //if the loop breaks then the login was successful


    //this is where the menu for client would go, will need a way for server to know game started, possibly start as soon as both players are ready. Maybe send a specific flag for readying?

    //basic input and recieve loop
    while(1)
    {
        SocketFD = socket(AF_INET, SOCK_STREAM, 0);

        printf("Enter a command to send to the server:\n");
        printf("-l for login, -m for message, -q to close server\n");

        fgets(SendBuf, sizeof(SendBuf), stdin); //takes input

		l = strlen(SendBuf); //length of the sendbuffer

        connect(SocketFD, (struct sockaddr *)&ServerAddress,sizeof(ServerAddress)); //connect to the server

        write(SocketFD, SendBuf, l); //write to the socket

        n = read(SocketFD, RecvBuf, sizeof(RecvBuf) - 1); //server respnse data


        RecvBuf[n] = 0; //sets the last last char of the recieve buffer to null to allow us to use it as a string


		printf("Received response: %s\n",  RecvBuf); 
        
        if(SendBuf[0]=='-'&&SendBuf[1]=='q')
        {
            printf("quitting client\n");
            close(SocketFD);
            return 0;
        }

    }
    
    // //game loop for receiving and sending data, just for reference, commented out for whoever implements the game loop
    // while(1)
    // {
    //     SocketFD = socket(AF_INET, SOCK_STREAM, 0); //setup socket

    //     connect(SocketFD, (struct sockaddr *)&ServerAddress,sizeof(ServerAddress)); //connect to the server


    //     n = read(SocketFD, RecvBuf, sizeof(RecvBuf) - 1); //server respnse data


    //     RecvBuf[n] = 0; //sets the last last char of the recieve buffer to null to allow us to use it as a string


	// 	printf("Received response: %s\n",  RecvBuf); 
        
    //     fgets(SendBuf, sizeof(SendBuf), stdin); //takes input

	// 	l = strlen(SendBuf); //length of the sendbuffer
        
    //     write(SocketFD, SendBuf, l); //write to the socket

    // }
    
    close(SocketFD);

    return 0;
}

