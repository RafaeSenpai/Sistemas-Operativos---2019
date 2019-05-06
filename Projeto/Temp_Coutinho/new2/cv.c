#include "API.h"

int main(int argc, char const *argv[]){

  int client_to_server;
  char *myfifo = "/tmp/client_to_server_fifo";

  int server_to_client;
  char *myfifo2 = "/tmp/server_to_client_fifo";

  client_to_server = open(myfifo, O_WRONLY);
  server_to_client = open(myfifo2, O_RDONLY);

  while(1){

    int n;

    char str[2048];
    char* str_pointer = malloc(100*sizeof(char));
    char* str1 = malloc(100*sizeof(char));
    char* myfifo_final = malloc(200*sizeof(char));

    str_pointer=&str[0];

    sprintf(str1,"%d",getppid());
    strcat(myfifo_final,myfifo2);
    strcat(myfifo_final,str1);
    //printf("%s\n",myfifo_final);

    while((n=read(0,str,sizeof(str)))>0){

      //printf("---------------\n%s\n", str1);

      strcat(str1," ");
      strcat(str1,str);
      strcpy(str,str1);

      //write(1,"\ncmd message to serwer: \n",25);
      //write(1,str,strlen(str));
      write(client_to_server, str,strlen(str));

      perror("Write:");

      //printf("%s\n",myfifo_final);

      server_to_client = open(myfifo_final, O_RDONLY); // LER O QUE O SERVER MANDA.REPARA QUE UM LÊ E OUTRO ESCREVE(NOS 2 FICHEIROS E SÃO ALTERNADOS)
      //printf("%s\n",myfifo_final);
      read(server_to_client,str,2048);
      perror("Read:"); // Very crude error check
      //write(1,"----------\n",11);
      //write(1,str,strlen(str));
      memset(str, 0, sizeof(str));
    }
  }

  close(client_to_server);
  close(server_to_client);
  return 0;
}
