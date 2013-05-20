#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include "pcbnAPI.h"

void clean_buffer(char *buffer,int size){
	int i;
	for(i=0;i<size;i++)
		buffer[i]='\0';

	return;
}
void* server_answer(void* arg){
	int *sock = (int*)arg;
	char buffer[255];
	char aux[255];
	char *buffer_it = buffer;
	int n,part,i=0,tam;
	command_header cmmd;
	while(1){
		clean_buffer(buffer,sizeof(buffer));
		//fgets(buffer, sizeof(buffer), fp);
		//printf("%c \n",buffer[0]);
		
		tam = n = recv(sock[0],&cmmd,sizeof(command_header) ,0);

		printf("server_answer:Number of bytes received: %d\n",n);
		printf("command:%d\nsize:%d\nmessage:%d\n",cmmd.command,cmmd.size,cmmd.p);

	}
	
}

void receive_answer(int *sock)
{
	void* arg = (void*)sock;
	pthread_t new_thread;
	pthread_create( &new_thread, NULL, &server_answer, sock);
	return;
}

int main(int argc, char **argv) {

  struct sockaddr_in servaddr;
  int *sock;
  int size;
  int size_sent;
  sock = (int*)malloc(sizeof(int));
  sock[0] = socket(AF_INET, SOCK_STREAM, 0);

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(6791);
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  connect(sock[0], (struct sockaddr *)&servaddr, sizeof(servaddr));
  receive_answer(sock);
  command_header cmmd;
  size = status_command_answer(&cmmd);
  while(1) {
    	
    //char message[161];
    //fgets(message, 161, stdin);
    printf("%ld \n", sizeof(cmmd));

		/* Replacing '\n' with '\0' */
    //char *tmp = strchr(message, '\n');
    //if (tmp) *tmp = '\0';

		//scanf(" %s", message);
    if(size_sent = send(sock[0], &cmmd, size, 0)>0)
      printf("Sent %d bytes correctly\n",size_sent);
    sleep(10);
  }

    //close(sock);
}
