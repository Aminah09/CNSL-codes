//TCP SERVER PROGRAM 

#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX 30

int ssfd;
int ccfd,res;
int serverlen,clientlen;
struct sockaddr_in serveraddr;
struct sockaddr_in clientaddr;
char result[MAX];
float addition (float a, float b);

typedef struct message
{
	float input[2];
	float output;
	int ch;
}message;

void main()
{	
	int msgLen;
	char *ch;
	ssfd=socket(AF_INET,SOCK_STREAM,0);
	message *msg;
	message *reply;
	msg=(message*)malloc(sizeof(message));
	reply=(message*)malloc(sizeof(message));

	printf("\nWaiting for connection \n SSFD Value:%d",ssfd);
	msgLen=sizeof(message);

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	serveraddr.sin_port=9734;
	serverlen=sizeof(serveraddr);
	bind(ssfd,(struct sockaddr*)&serveraddr,serverlen);
	printf("\nConnected to socket");
	listen(ssfd,5);

	ccfd=accept(ssfd,(struct sockaddr*)&clientaddr,&clientlen);
	printf("\nConnection accepted successfully \n");
	while(1)
	{
		read(ccfd,reply,msgLen);
		switch(reply->ch)
		{
			case 1: 
			printf("First Value is %f \n",reply->input[0]);
			printf("Second Value is %f \n",reply->input[1]);
			printf("Addition is %f",addition((float)reply->input[0], (float)reply->input[1]));
			fflush(stdout);
			reply->output = addition((float)reply->input[0], (float)reply->input[1]) ;
			write(ccfd,reply,msgLen);
			break;
		}

	}

}
float addition (float a, float b)
{
	float result;
	result = a + b	;
	return result;
}


