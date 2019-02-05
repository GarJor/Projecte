#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 5500

int main (int argc, char *argv[]) {

	int clientSocketDescriptor,socketDescriptor;

	struct sockaddr_in serverAddress,clientAddress;
	socklen_t clientLength;

	//char recvBuffer[1000],sendBuffer[1000];

	
	bzero(&serverAddress,sizeof(serverAddress));
	/*Socket address structure*/
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr=INADDR_ANY;
	serverAddress.sin_port=htons(PORT);
	/*TCP socket is created, an Internet socket address structure is filled with
	 * wildcard address & server’s well known port*/
	socketDescriptor=socket(AF_INET,SOCK_STREAM,0);
	/*Bind function assigns a local protocol address to the socket*/
	bind(socketDescriptor,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
	/*Listen function specifies the maximum number of connections that kernel should queue
	 * for this socket*/
	listen(socketDescriptor,5);
	printf("%s%d\n","Server is running on port ",PORT);

	/*The server to return the next completed connection from the front of the
	 * completed connection Queue calls it*/
	clientLength = sizeof(serverAddress);
	
	while(1) {		
	
		clientSocketDescriptor=accept(socketDescriptor,(struct sockaddr*)&clientAddress,&clientLength);
		char recvBuffer[1025];
		bzero(&recvBuffer,sizeof(recvBuffer));
		
		/*Receiving the request from client*/
		int valread = recv(clientSocketDescriptor,recvBuffer,sizeof(recvBuffer),0);
		
		printf("\nCliAssist : %s\n",recvBuffer);
		char command[4000];
		sprintf(command, "python parser.py %s",recvBuffer);
		system(command);
	}

}
