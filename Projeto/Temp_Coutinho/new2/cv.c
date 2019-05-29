#include "api.h"
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){

  int n, fdPublic, fdVendas, client_to_server, server_to_client;

  char* pid = malloc(sizeof(char));
  char* cv = malloc(20*sizeof(char));
  char* buf = malloc(100*sizeof(char));
  char* buf2 = malloc(100*sizeof(char));
  char* param1 = malloc(100*sizeof(char));
  char* param2 = malloc(100*sizeof(char));
  char* lixo = malloc(100*sizeof(char));
  char* myfifo1 = malloc(50*sizeof(char));
  char* myfifo2 = malloc(50*sizeof(char));
  char* publicFifo = "./fifos/publicFifo";
  char* fifoVendas = "./fifos/fifoVendas";

  strcpy(cv,"cliente ");
  sprintf(pid,"%d",getppid());
  strcat(cv,pid);
  printf("cv: %s\n", cv);
  strcpy(myfifo1,"./fifos/W");
  strcat(myfifo1,pid);
  printf("myfifo1: %s\n", myfifo1);
  strcpy(myfifo2,"./fifos/R");
  strcat(myfifo2,pid);
  printf("myfifo2: %s\n", myfifo2);

  if((n=mkfifo(myfifo1, 0777))==-1) perror("MKFIFO 1:");
  printf("here\n");
  if((n=mkfifo(myfifo2, 0777))==-1) perror("MKFIFO 2:");
  printf("here\n");

  if((fdPublic = open(publicFifo, O_WRONLY, 0777)) == -1) perror("OPEN 1:");
  printf("fdPublic: %d\n", fdPublic);
  if((fdVendas = open(fifoVendas, O_WRONLY, 0777)) == -1) perror("OPEN 2:");
  printf("fdVendas: %d\n", fdVendas);

  if((n = write(fdPublic, cv,strlen(cv)))==-1) perror("WRITE 1:");

  if((client_to_server = open(myfifo1, O_WRONLY,0777))==-1) perror("OPEN 3:");
  if((server_to_client = open(myfifo2, O_RDONLY,0777))==-1) perror("OPEN 4:");

  while(1){

    printf("CLIENT ON\n");

    while((n=read(0,buf,1024))>0){ if (n == -1) perror("READ 1:");

      if((strcmp(buf, " ") != 0 && strcmp(buf, "\n") != 0)) {

        strtok(buf, "\n");

        param1 = strtok(buf, " ");
        buf2 = strtok(NULL, "\n");
        param2 = strtok(buf2, " ");
        lixo = strtok(NULL, " ");

        /*if(strcmp(param1, "exit\n") == 0){
          if((n=write(client_to_server,param1, strlen(param1)))==-1) perror("WRITE 2:");
          param1 = calloc(100, sizeof(char));
          break;
        }*/

        buf = calloc(100, sizeof(char));

        if(!buf2){
          printf("caso 1\n");

          printf("param1: %s\n", param1);
          sprintf(buf, "%s", param1);
          printf("buf: %s\n", buf);

          if((n=write(client_to_server,buf, strlen(buf)))==-1) perror("WRITE 2:");

          // param1 = calloc(100, sizeof(char));
          // param2 = calloc(100, sizeof(char));
          // lixo = calloc(100, sizeof(char));
        }

        else if(!lixo){
          printf("caso 2\n");

          printf("param1: %s\n",param1);
          printf("param2: %s\n",param2);

          printf("buf: %s\n",param2);
          buf = calloc(100, sizeof(char));

          sprintf(buf, "%s %s", param1, param2);
          printf("buf: %s\n", buf);

          if((n=write(fdVendas,buf, strlen(buf)))==-1) perror("WRITE 2:");
          if((n=read(server_to_client,buf,100))==-1) perror("READ 1:");
        }

        else{
      			system("clear"); //perguntar ao rafa
      			write(1,"Comando inválido!\nInsira novo comando:\n",41);
        }

        buf = calloc(100, sizeof(char));
        buf2 = calloc(100, sizeof(char));
        param1 = calloc(100, sizeof(char));
        param2 = calloc(100, sizeof(char));
        lixo = calloc(100, sizeof(char));
      }


      printf("END\n");
    }
  }

  close(client_to_server);
  close(server_to_client);
  unlink(myfifo1);
  unlink(myfifo2);
  unlink(publicFifo);
  return 0;
}
