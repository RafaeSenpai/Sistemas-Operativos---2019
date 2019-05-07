#include "API.h"

int main(int argc, char const *argv[]){
  int client_to_server;
  char *myfifo = "/tmp/client_to_server_fifo";

  int server_to_client;
  char *myfifo2 = "/tmp/server_to_client_fifo";

  char buf[1024] = "";
  char str[1024];
  char buf1[1024] = "";

  int status;

  mkfifo(myfifo, 0666);
  mkfifo(myfifo2, 0666);

   /* open, read, and display the message from the FIFO */
  client_to_server = open(myfifo, O_RDONLY);
  server_to_client = open(myfifo2, O_WRONLY);

  write(1,"Server ON.\n",11);

  while (1){

    int n=read(client_to_server,buf,1024); // LER O QUE O CLIENTE ESCREVE
    strcpy(buf1,buf);
    char* myfifo_final = malloc(200*sizeof(char));
    strtok(buf1, " ");
    strcat(myfifo_final,myfifo2);
    strcat(myfifo_final,buf1);
    //printf("%s\n",buf1);
    //printf("-----------\n");

    if (strcmp("exit\n",buf)==0){
      write(1,"Server OFF.\n",10);
      break;
    }

    else if (strcmp(" ",buf)!=0){

      if(fork()==0){
        mkfifo(myfifo_final, 0666);
        server_to_client = open(myfifo_final, O_WRONLY);
        //printf("%s\n",myfifo_final);
        write(1,"Received: ",11);
        write(1,buf,n);
        write(server_to_client,buf,n);
        perror("Write:");
        memset(buf, 0, n);
      }
      else{
        wait(&status);
      }
    }

    memset(buf, 0, sizeof(buf-1));
  }

   close(client_to_server);
   close(server_to_client);

   unlink(myfifo);
   unlink(myfifo2);
   return 0;
}
