#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>


int main()
{
	int soc;
		
	soc = socket(AF_INET, SOCK_STREAM, 0);
	
	if(soc == -1)
	{
		printf("Socket creation failed.....\n");
		exit(0);
	}
	else
	{
		printf("Socket successfully created...\n");
	}
}
