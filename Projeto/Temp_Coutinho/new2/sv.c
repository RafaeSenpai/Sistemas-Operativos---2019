#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define tam 6

int main(int argc, char const *argv[]) {

  int n, status;

  int public;
  char *myfifo = "/tmp/client_to_server_fifo";
  if((n=mkfifo(myfifo,0777))==-1) perror("MKFIFO 1:");
  if((public = open(myfifo, O_RDONLY,0777)) == -1) perror("OPEN 1:");
  printf("public: %d\n", public);

  int client_to_server;
  char *myfifo1 = malloc(50*sizeof(char));

  int server_to_client;
  char *myfifo2 = malloc(50*sizeof(char));

  char *buf = malloc(100*sizeof(char));
  char *str = malloc(100*sizeof(char));

  write(1,"Server ON.\n",11);

  while(1){
    if((n=read(public,buf,100))==-1) perror("READ 1:");

  printf("%s\n",buf);

  while (1){

    char* cenas  = strtok(buf," ");
    char* cenas2 = strtok(NULL," ");

    strcpy(myfifo1,"/tmp/W");
    strcat(myfifo1,cenas2);
    printf("myfifo1: %s\n", myfifo1);
    strcpy(myfifo2,"/tmp/R");
    strcat(myfifo2,cenas2);
    printf("myfifo2: %s\n", myfifo2);

    printf("buf: %s\n", buf);

    if((client_to_server = open(myfifo1, O_RDONLY,0777))==-1) perror("OPEN 1:");
    printf("fd client_to_server: %d\n", client_to_server);
    if((server_to_client = open(myfifo2, O_WRONLY,0777))==-1) perror("OPEN 2:");
    printf("fd server_to_client: %d\n", server_to_client);

    buf = calloc(100, sizeof(char));

    while(n=read(client_to_server, buf, 100)>0){

      if(fork()==0){

        printf("here\n");

        printf("here\n");

        if(n==-1) perror("READ 2:");

        printf("buf: %s\n", buf);
        if((n=write(server_to_client, "OK\n", 20))==-1) perror("WRITE 1:");
        printf("OK\n");

        buf = calloc(100, sizeof(char));
        _exit(0);
      }
 	break;
   	
       	//  wait(&status);
    }
  }
}
  close(public);
  return 0;
}
