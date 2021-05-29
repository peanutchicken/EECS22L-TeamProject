#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

int main()
{
    int l, n;
    int SocketFD;	/* socket file descriptor */
    struct sockaddr_in ServerAddress;	/* server address we connect with */
    struct hostent *Server;	/* server host */
    char SendBuf[256];	/* message buffer for sending a message */
    char RecvBuf[256];	/* message buffer for receiving a response */

    short port = 10300;

    Server = gethostbyname("crystalcove.eecs.uci.edu");

    ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = htons(port);
	ServerAddress.sin_addr = *(struct in_addr *)Server->h_addr_list[0];

    while(1)
    {
        SocketFD = socket(AF_INET, SOCK_STREAM, 0);
        printf("Enter a command to send to the server:\n");
        printf("-l for login, -m for message\n");
        fgets(SendBuf, sizeof(SendBuf), stdin);
		l = strlen(SendBuf);
        connect(SocketFD, (struct sockaddr *)&ServerAddress,sizeof(ServerAddress));
        write(SocketFD, SendBuf, l);
        n = read(SocketFD, RecvBuf, sizeof(RecvBuf) - 1);
        RecvBuf[n] = 0;
		printf("Received response: %s\n",  RecvBuf);
        close(SocketFD);

    }

}