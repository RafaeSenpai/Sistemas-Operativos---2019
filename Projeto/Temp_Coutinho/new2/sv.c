#include "api.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define tam 100

int main(){

  int i, n, status, fdPublic, fdVendas, param1, param2, op, pids[tam], client_to_server, server_to_client;

  char *myfifo1 = malloc(50*sizeof(char));
  char *myfifo2 = malloc(50*sizeof(char));
  char *buf = malloc(100*sizeof(char));
  char* tipo = malloc(100*sizeof(char));
  char* pidFifo = malloc(100*sizeof(char));
  char *fifoVendas = "./fifos/fifoVendas";
  char *publicFifo = "./fifos/publicFifo";

  i = 0;

  if((n=mkfifo(publicFifo,0777))==-1) perror("MKFIFO 1:");
  printf("here\n");
  if((n=mkfifo(fifoVendas,0777))==-1) perror("MKFIFO 2:");
  printf("here\n");

  if((fdPublic = open(publicFifo, O_RDONLY,0777)) == -1) perror("OPEN 1:");
  printf("fdPublic: %d\n", fdPublic);
  if((fdVendas = open(fifoVendas, O_RDONLY,0777)) == -1) perror("OPEN 2:");
  printf("fdVendas: %d\n", fdVendas);


  if(i<tam){
    pids[i] = atoi(pidFifo); //guardar pids em array para concorrencia
    i++;
  }

  while(1){

    write(1,"SERVER ON.\n",11);

    buf = calloc(100, sizeof(char));

    while (1){

      if((n = read(fdPublic, buf, 100))==-1) perror("READ 1:");

      tipo  = strtok(buf," ");
      pidFifo = strtok(NULL," ");
      strcpy(myfifo1,"./fifos/W");
      strcat(myfifo1,pidFifo);
      printf("myfifo1: %s\n", myfifo1);
      strcpy(myfifo2,"./fifos/R");
      strcat(myfifo2,pidFifo);
      printf("myfifo2: %s\n", myfifo2);

      if((client_to_server = open(myfifo1, O_RDONLY,0777))==-1) perror("OPEN 3:");
      if((server_to_client = open(myfifo2, O_WRONLY,0777))==-1) perror("OPEN 4:");

      if(fork()==0){

        buf = calloc(100, sizeof(char));

        while(n=read(client_to_server, buf, 100)>0){
          if(n==-1) perror("READ 2:");

          printf("buf: %s\n", buf);

          //dup redirecionar terminal para server_to_client
          menuComandos(buf);
          //dup redirecionar server_to_client para terminal

          buf = calloc(100, sizeof(char));
        }/*
        free(buf);
        free(tipo);
        free(pidFifo);
        close(client_to_server);
        close(server_to_client);
        close(fdPublic);
        close(fdVendas);
        unlink(myfifo1);
        unlink(myfifo2);
        unlink(publicFifo);
        unlink(fifoVendas);*/
        _exit(0);
      }
    }
  }
  free(buf);
  free(tipo);
  free(pidFifo);
  close(client_to_server);
  close(server_to_client);
  close(fdPublic);
  close(fdVendas);
  unlink(myfifo1);
  unlink(myfifo2);
  unlink(publicFifo);
  unlink(fifoVendas);
  return 0;
}
