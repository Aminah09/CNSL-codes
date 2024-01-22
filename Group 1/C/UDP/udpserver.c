//UDP SERVER PROGRAM

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	struct data
	{
		float x;
		float y;	
	}gdata;
	int sock;
	int addr_len,bytes_read;
	char recv_data[1024];
	float sum ;
	struct sockaddr_in server_addr,client_addr;
	if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		perror("Socket");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(6666);
	server_addr.sin_addr.s_addr=INADDR_ANY;
	bzero(&(server_addr.sin_zero),8);
	if(bind(sock,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))==-1)
	{
		perror("Bind");
		exit(1);
	}
	addr_len=sizeof(struct sockaddr);
	printf("\n UDPServer waiting for client on port no 6666 \n");
	fflush(stdout);
	while(1)
	{
		recvfrom(sock,&gdata,sizeof(struct data),0,(struct sockaddr *)&client_addr,&addr_len);
		printf("First value is %f \n",gdata.x);
		printf("Second value is %f \n",gdata.y);
		sum = gdata.x + gdata.y;
		printf ("Addition is %f \n",sum);
		sendto(sock,&sum,sizeof(sum),0,(struct sockaddr *)&client_addr,addr_len);
		fflush(stdout);
	}
	return 0;
}
 
