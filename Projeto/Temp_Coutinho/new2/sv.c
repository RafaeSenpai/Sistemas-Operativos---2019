#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){

  int n, status, public;

  char *publicfifo = "/tmp/publicfifo";
  if((n=mkfifo(publicfifo,0777))==-1) perror("MKFIFO 1:");
  if((public = open(publicfifo, O_RDONLY,0777)) == -1) perror("OPEN 1:");
  printf("public: %d\n", public);

  while(1){

    int client_to_server;
    char *myfifo1 = malloc(50*sizeof(char));

    int server_to_client;
    char *myfifo2 = malloc(50*sizeof(char));

    char *buf = malloc(100*sizeof(char));

    write(1,"Server ON.\n",11);

    if((n = read(public, buf, 100))==-1) perror("READ 1:");

    char* cenas  = strtok(buf," ");
    char* cenas2 = strtok(NULL," ");
    strcpy(myfifo1,"/tmp/W");
    strcat(myfifo1,cenas2);
    printf("myfifo1: %s\n", myfifo1);
    strcpy(myfifo2,"/tmp/R");
    strcat(myfifo2,cenas2);
    printf("myfifo2: %s\n", myfifo2);

    if((client_to_server = open(myfifo1, O_RDONLY,0777))==-1) perror("OPEN 2:");
    if((server_to_client = open(myfifo2, O_WRONLY,0777))==-1) perror("OPEN 3:");

    buf = calloc(100, sizeof(char));

    while (1){

      if(fork()==0){

        while(n=read(client_to_server, buf, 100)>0){

          if(n==-1) perror("READ 2:");
          printf("buf: %s\n", buf);
          if((n=write(server_to_client, "OK\n", 20))==-1) perror("WRITE 1:");
          printf("OK\n");

          buf = calloc(100, sizeof(char));
        }

        _exit(0);
      }

      else break;
    }
    // close(client_to_server);
    // close(server_to_client);
    // unlink(myfifo1);
    // unlink(myfifo2);
  }
  close(public);
  unlink(publicfifo);
  return 0;
}
