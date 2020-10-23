#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>

int main(void)
{
  int listenfd = 0,connfd = 0; 
  
  struct sockaddr_in serv_addr;
  struct hostent *hen;

  char sendBuff[1025];  
  char recvBuff[1025]; 
  int numrv;  

  
  hen = gethostbyname("server.justin.cs164");
  

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("socket retrieve success\n");
  
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));
  memset(recvBuff, '0', sizeof(recvBuff));
      
  serv_addr.sin_family = AF_INET;    
  serv_addr.sin_port = htons(5000);    
  bcopy((char *)hen->h_addr,(char *)&serv_addr.sin_addr.s_addr,hen->h_length);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
  
  if(listen(listenfd, 10) == -1){
      printf("Failed to listen\n");
      return -1;
  }
     
  
  while(1)
    {
      printf("TEST0!\n");
      connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
      printf("TEST2!\n");
      read(listenfd, recvBuff, sizeof(recvBuff)-1);
      if(strcmp(recvBuff,"Hi")) {
        strcpy(sendBuff, "Bye");
      }
      else if(strcmp(recvBuff,"Bye")) {
        strcpy(sendBuff, "Hi");
      }
      write(connfd, recvBuff, strlen(sendBuff));
 
      close(connfd);    
      sleep(1);
    }
 
 
  return 0;
}
