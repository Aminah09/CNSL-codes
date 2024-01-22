//UDP CLIENT PROGRAM

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

int main()
{
   int sock; 
   int add_len;
   struct sockaddr_in server_addr;
   struct hostent *host;
   char send_data[1024];
   struct data
   {
	float x;
	float y;
   }sdata;
   float sum;
   host=(struct hostent *)gethostbyname((char*)"127.0.0.1");
   if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1)
   {
     perror("socket ");
     exit(1);
   }
   server_addr.sin_family=AF_INET;
   server_addr.sin_port=htons(6666);
   server_addr.sin_addr=*((struct in_addr*)host->h_addr);
   bzero(&(server_addr.sin_zero),8);
   add_len = sizeof(struct sockaddr);

   while(1)
   {
      printf("\n Enter First Value :");
      scanf("%f",&sdata.x);
      printf("\n Enter Second value:");
      scanf("%f",&sdata.y);
      sendto(sock,&sdata,sizeof(struct data),0,(struct sockaddr *)&server_addr,sizeof(struct sockaddr));
      recvfrom(sock,&sum,sizeof(sum),0,(struct sockaddr *)&server_addr,&add_len);
      printf("\n Addition is %f",sum);
   }
}

