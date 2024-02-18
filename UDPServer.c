// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT	 8081
#define MAXLINE 1024
	
// Driver code
int main() {
	int sockfd,i;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("\nSocket created successfully");
	}
		
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
		
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("\nBind failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("\nSuccessfully binded");
	}
		
	int len, n;
	
	len = sizeof(cliaddr); //len is value/result
	
	for(;;)
	{
		bzero(buffer,MAXLINE);
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,
					MSG_WAITALL, ( struct sockaddr *) &cliaddr,
					&len);
		buffer[n] = '\0';
		printf("\nFrom Client : %s\n", buffer);
		
		bzero(buffer,MAXLINE);
		printf("\nTo Client : ");
		i=0;
		
		while((buffer[i++] = getchar()) != '\n')
			;
		
		sendto(sockfd, (const char *)buffer, sizeof(buffer),
			MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
				len);
		if(strncmp("exit",buffer,4)==0)
		{
			printf("\nServer exit...\n");
			break;
		}
	
	}	
	return 0;
}

