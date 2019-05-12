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

int pids[tam], pidServer;

void handlerSIGUSR1(int signal){
  int i;
  for(i = 0; i < tam; i++){
    if(pids[i] != pidServer && pids[i] != 0){
      kill(pids[i], SIGSTOP);
    }
  }
}

void resumeClients(){
  printf("resume clientes\n");
  int i;
  for(i = 0; i < tam; i++) kill(pids[i], SIGCONT);
}

int main(){

  signal(SIGUSR1, handlerSIGUSR1);

  int i, n, status, fdPublic, fdVendas, param1, param2, op, client_to_server, server_to_client, fdBUF;

  pidServer = getpid();

  char *myfifo1 = malloc(50*sizeof(char));
  char *myfifo2 = malloc(50*sizeof(char));
  char *buf = malloc(100*sizeof(char));
  char* tipo = malloc(100*sizeof(char));
  char* pidFifo = malloc(100*sizeof(char));
  char *fifoVendas = "./fifos/fifoVendas";
  char *publicFifo = "./fifos/publicFifo";

  i = 0;

  if((n=mkfifo(publicFifo,0777))==-1) perror("MKFIFO 1:");
  if((n=mkfifo(fifoVendas,0777))==-1) perror("MKFIFO 2:");

  if((fdPublic = open(publicFifo, O_RDONLY,0777)) == -1) perror("OPEN 1:");
  if((fdVendas = open(fifoVendas, O_RDONLY,0777)) == -1) perror("OPEN 2:");

  while(1){

    write(1,"SERVER ON.\n",11);

    buf = calloc(100, sizeof(char));

    while (1){

      //if((n=read(fdVendas, buf, 100))==-1){

        if((n = read(fdPublic, buf, 100))==-1) perror("READ 1:");

        tipo  = strtok(buf," ");
        pidFifo = strtok(NULL," ");
        strcpy(myfifo1,"./fifos/W");
        strcat(myfifo1,pidFifo);
        strcpy(myfifo2,"./fifos/R");
        strcat(myfifo2,pidFifo);

        if(i<tam){
          pids[i] = atoi(pidFifo); //guardar pids em array para concorrencia
          i++;
        }

        if((client_to_server = open(myfifo1, O_RDONLY,0777))==-1) perror("OPEN 3:");
        if((server_to_client = open(myfifo2, O_WRONLY,0777))==-1) perror("OPEN 4:");

        buf = calloc(100, sizeof(char));
        sprintf(buf, "%d", pidServer);

        if((n=write(server_to_client, buf, strlen(buf))) == -1) perror("WRITE 1:");

        if(fork()==0){

          buf = calloc(100, sizeof(char));
          printf("tipo: %s\n", tipo);

          if(strcmp(tipo, "cliente") == 0){

            while(n=read(client_to_server, buf, 100)>0){

              if(n==-1) perror("READ 2:");

              //dup redirecionar terminal para server_to_client

              fdBUF = dup(1);

              dup2(server_to_client, 1);
              menuComandos(buf);
              dup2(fdBUF, 1);
              // dup redirecionar server_to_client para terminal

              resumeClients();
              buf = calloc(100, sizeof(char));
            }
          }
          else{
            // agregador
          }/*
          free(buf);
          free(tipo);
          free(pidFifo);
          close(client_to_server);
          close(server_to_client);
          close(fdVendas);
          unlink(myfifo1);
          unlink(myfifo2);
          unlink(fifoVendas);*/
          _exit(0);
        }
    //}
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
