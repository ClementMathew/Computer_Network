#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>   
#include <sys/socket.h>
#include <unistd.h>

#define MAX 100
#define PORT 8082
#define SA struct sockaddr


int main()
{
	int Clifd,conn;
	struct sockaddr_in servaddr,cli;
		
	Clifd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(Clifd == -1)
	{
		printf("Socket creation failed.....\n");
		exit(0);
	}
	else
	{
		printf("Socket successfully created...\n");
	}
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	
	if(connect(Clifd,(SA*)&servaddr,sizeof(servaddr))!=0)
	{
		printf("Connection with the server failed....\n");
		exit(0);
	}
	else
	{
		printf("Connected to the server...\n");
	}
	char buff[MAX];
	int n;
	
	for(;;)
	{
		bzero(buff,sizeof(buff));
		printf("Enter the string : ");
		n=0;
		
		while((buff[n++] = getchar())!='\n')
			;
		
		write(Clifd,buff,sizeof(buff));
		bzero(buff,sizeof(buff));
		read(Clifd,buff,sizeof(buff));
		
		printf("From server : %s",buff);
		
		if(strncmp("exit",buff,4) == 0)
		{
			printf("Client Exit....\n");
			break;
		}
	}
	close(Clifd);
}
