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
	int Serfd,conn,len;
	struct sockaddr_in servaddr,cli;
		
	Serfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(Serfd == -1)
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
	
	if(bind(Serfd,(SA*)&servaddr,sizeof(servaddr))!=0)
	{
		printf("Socket bind failed....\n");
		exit(0);
	}
	else
	{
		printf("Socket successfully binded...\n");
	}
	
	if(listen(Serfd,5) != 0)
	{
		printf("Listen failed....\n");
		exit(0);
	}
	else
	{
		printf("Server listening...\n");
	}
	len = sizeof(cli);
	conn = accept(Serfd,(SA*)&cli,&len);
	
	if(conn<0)
	{
		printf("Server accept failed....\n");
		exit(0);
	}
	else
	{
		printf("Server accept the client....\n");
	}
	char buff[MAX];
	int n;
	
	for(;;)
	{
		bzero(buff,MAX);
		int r = read(conn,buff,sizeof(buff));
		if(r<0)
		{
			perror("read failed");
		}
		printf("From client: %s\n To client: ",buff);
		bzero(buff,MAX);
		n=0;
		
		while((buff[n++] = getchar()) != '\n')
			;
		
		write(conn,buff,sizeof(buff));
		
		if(strncmp("exit",buff,4)==0)
		{
			printf("Server exit...\n");
			break;
		}
	}
	close(Serfd);
}
