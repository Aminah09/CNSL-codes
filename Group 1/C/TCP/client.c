//TCPCLIENT PROGRAM

#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#define MAX 30

typedef struct message
{
	float input[2];
	float output;
	int ch;
}message;

void main()
{
	int ssfd;
	int len;
	int msgLen;
	struct sockaddr_in address;
	int result;
	FILE *fp;
	char ch='A';
	message *msg;
	message *reply;
	msg=(message*)malloc(sizeof(message));
	reply=(message*)malloc(sizeof(message));
	msgLen=sizeof(message);
	ssfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=9734;
	len=sizeof(address);
	result=connect(ssfd,(struct sockaddr*)&address,len);
	if(result==-1){
	perror("Server not found");
	printf("\nError Result:%d",result);
}
printf("\nConnection successful");
do{
	printf("\n\nSELECT Appropriate Option:\n");
	printf("\n1.\tAddition");
	printf("\n2.\tDisconnect And Exit");
	scanf("%d",&msg->ch);
	printf("Your Choice:%d",msg->ch);
	switch(msg->ch)
	{
		case 1:
		printf("\nEnter any First value:");
		scanf("%f",&msg->input[0]);
		printf("\nEnter any Second value:");
		scanf("%f",&msg->input[1]);
		write(ssfd,msg,msgLen);
		read(ssfd,reply,msgLen);
		printf("Output from server:%f",reply->output);
		break;

		default:
		printf("Invalid Choice....Select Another");
		break;
	}
}while(msg->ch!=2);
close(ssfd);
}


