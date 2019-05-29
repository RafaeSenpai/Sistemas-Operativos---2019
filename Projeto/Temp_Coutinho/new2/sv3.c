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

int main(int argc, char const *argv[]){
  int client_to_server;
  char *myfifo = "/tmp/client_to_server_fifo";

  int server_to_client;
  char *myfifo2 = "/tmp/server_to_client_fifo";

  char* buf = malloc(100*sizeof(char));
  char* str = malloc(100*sizeof(char));
  char* buf1 = malloc(100*sizeof(char));

  int status;

  mkfifo(myfifo, 0666);

  client_to_server = open(myfifo, O_RDONLY);

  write(1,"Server ON.\n",11);

  while (1){

    int n=read(client_to_server,buf,1024); // LER O QUE O CLIENTE ESCREVE
    strcpy(buf1,buf);
    printf("%s\n",buf);
    char* myfifo_final = malloc(200*sizeof(char));
    strtok(buf1, " ");
    strcat(myfifo_final,myfifo2);
    strcat(myfifo_final,buf1);
    printf("%s",buf);
    printf("-----------\n");
    printf("%s\n",buf1);
    printf("-----------\n");

    if (strcmp("exit\n",buf)==0){
      write(1,"Server OFF.\n",10);
      break;
    }
    else if (strcmp(" ",buf)!=0){
      mkfifo(myfifo_final, 0666);
      server_to_client = open(myfifo_final, O_WRONLY);
      printf("%s\n",myfifo_final);
      printf("%s",buf );
      printf("---------------\n");
      write(1,"Received: ",11);
      write(1,buf,2*n);
      write(server_to_client,buf,n);
      perror("Write:");
      close(server_to_client);
    }

    buf = calloc(100,sizeof(char));
    str = calloc(100,sizeof(char));
    buf1 = calloc(100,sizeof(char));
  }
  close(client_to_server);

  unlink(myfifo);
  unlink(myfifo2);
  return 0;
}
