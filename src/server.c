#include "server.h"

int serverInit(short port, int backlog)
{
    int serverSocket;
    // int addressSize;

    sockaddr_in serverAddress;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    bind(serverSocket, (sockaddr *)&serverAddress, sizeof(serverAddress));

    listen(serverSocket, backlog);

    return serverSocket;
}

int acceptConnection(int serverSocket)
{
    int addressSize;
    sockaddr_in clientAddress;

    addressSize = sizeof(sockaddr_in);

    return accept(serverSocket, (sockaddr *)&clientAddress, (socklen_t *)&addressSize);
}

/*
int doStuff(int clientSocket,accountList *list)
{
    int echo=1; //if echo is 0, send the sendBuffer to the opponent socket of the account attached to the client socket
    int readRet;
    // int sendBuffLen;
    char recvBuffer[256];
    char sendBuffer[256];

    
    readRet = read(clientSocket,recvBuffer,sizeof(recvBuffer-1)); //readRet now contains the length of the data sent by the client

    recvBuffer[readRet]=0; //setting the last n'th value of recvBuffer to NULL so that we can use string functions on it and print it as a string

    printf("%s",recvBuffer); //print out the sent data

    if(recvBuffer[0]=='-') //checks for command denoted by -
    {
        switch(recvBuffer[1]) //switch case for all the commands
        {
            case 'm':
                strcpy(sendBuffer,"Server received a message");
                printf("Server received a message\n");
                break;

            case 'l':
                //sendBuffer = usernameCheck(clientSocket,recvBuffer, list);
                strcpy(sendBuffer,"Server received a login request");
                printf("Server received a login request\n");
                break;

            default:
                strcpy(sendBuffer,"Server received an invalid command");
                printf("Server received an invalid command\n");
                break;
        }
    }
    else
    {
        //server recieved a move
    }

    if(echo != 0)
    {
        write(clientSocket,sendBuffer,strlen(sendBuffer)); //sends the sendBuffer back to the client that sent data
    }
    else
    {
        //receieved a move, and send to opponent
    }

    return 0;
}
*/

// int usernameCheck(int socket, char* data, accountList list)
// {
//     char* input = strtok(data," "); //removes the -l
//     //grabs the username and password, and splits it into seperate strings
//     char* username = strtok(NULL," ");
//     char* password = strtok(NULL," ");
//     account* current = list.first;
//     while(current!=NULL)
//     {
//         if(strcmp(username,current.username)&&strcmp(password,current.password))
//         {
//             current.socket = socket;
//             return 1;
//         }
//         current = current.next;
//     }
//     return 0;
// }
