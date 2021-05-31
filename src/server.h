#ifndef SERVER
#define SERVER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/select.h>

#define SERVERPORT 10300

struct accountList{
    struct account* first;
    struct account* last;
};

struct account{
    char username[10];
    char password[10];
    int socket;
    int opponentSocket;
    struct account* next;
    struct account* prev;
    
};

typedef struct account account;
typedef struct accountList accountList;
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;



//does the inital server setup, and returns the server socket
int serverInit(short port, int backlog);

//accepts the connection and returns the client socket
int acceptConnection(int serverSocket);

//handles the parsing of the data sent, and also sends data to other client
int doStuff(int clientSocket, accountList list);

//handles login. data comes in form -l <username> <password>.
//returns 1 if successful login
//returns 0 if unsuccessful
int usernameCheck(int socket, char* data, accountList list);

//returns pointer to account with a specified socket
account* findAccount(int socket, accountList list);

#endif /* SERVER */
