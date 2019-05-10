#include "API.h"
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

  int i, n, status, fdPublic, fdVendas, param1, param2, op, pids[tam];
  i = 0;

  char *publicFifo = "./fifos/publicFifo";
  if((n=mkfifo(publicFifo,0777))==-1) perror("MKFIFO 1:");
  printf("here\n");
  if((fdPublic = open(publicFifo, O_RDONLY,0777)) == -1) perror("OPEN 1:");
  printf("here\n");
  printf("fdPublic: %d\n", fdPublic);

  char *fifoVendas = "./fifos/fifoVendas";
  if((n=mkfifo(fifoVendas,0777))==-1) perror("MKFIFO 2:");
  if((fdVendas = open(fifoVendas, O_RDONLY,0777)) == -1) perror("OPEN 2:");
  printf("fdVendas: %d\n", fdVendas);

  while(1){

    int client_to_server;
    char *myfifo1 = malloc(50*sizeof(char));

    int server_to_client;
    char *myfifo2 = malloc(50*sizeof(char));

    char *buf = malloc(100*sizeof(char));

    write(1,"Server ON.\n",11);

    if((n = read(fdPublic, buf, 100))==-1) perror("READ 1:");

    char* cenas  = strtok(buf," ");
    char* cenas2 = strtok(NULL," ");
    strcpy(myfifo1,"./fifos/W");
    strcat(myfifo1,cenas2);
    printf("myfifo1: %s\n", myfifo1);
    strcpy(myfifo2,"./fifos/R");
    strcat(myfifo2,cenas2);
    printf("myfifo2: %s\n", myfifo2);

    if(i<tam){
      pids[i] = atoi(cenas2); //guardar pids em array para concorrencia
      i++;
    }

    sleep(1);

    if((client_to_server = open(myfifo1, O_RDONLY,0777))==-1) perror("OPEN 2:");
    if((server_to_client = open(myfifo2, O_WRONLY,0777))==-1) perror("OPEN 3:");

    buf = calloc(100, sizeof(char));

    while (1){



      if(fork()==0){

        while(n=read(client_to_server, buf, 100)>0){ if(n==-1) perror("READ 2:");

          printf("buf: %s\n", buf);

          menuComandosCV(buf); //usar DUP ou DUP2 para mandar para stdout do CV

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
  close(fdPublic);
  unlink(publicFifo);
  return 0;
}
