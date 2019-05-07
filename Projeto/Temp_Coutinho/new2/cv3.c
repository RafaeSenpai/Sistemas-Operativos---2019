#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char const *argv[]){

  int client_to_server;
  char *myfifo = "/tmp/client_to_server_fifo";

  int server_to_client;
  char *myfifo2 = "/tmp/server_to_client_fifo";

  client_to_server = open(myfifo, O_WRONLY);// ESCREVER O CLIENTE

  char* str = malloc(100*sizeof(char));
  char* str1 = NULL;
  char* myfifo_final = NULL;

  while(1){
     int n;

     while((n=read(0,str,101))>0){
       str1 = malloc(100*sizeof(char));
       myfifo_final = malloc(200*sizeof(char));
       sprintf(str1,"%d",getppid());
       strcpy(myfifo_final,myfifo2);
       strcat(myfifo_final,str1);
       printf("%s\n",myfifo_final);
       printf("---------------\n");
       printf("%s\n",str1);
       strcat(str1," ");
       strcat(str1,str);
       strcpy(str,str1);
       write(1,"\ncmd message to serwer: \n",25);
       write(1,str,strlen(str)-1);
       write(client_to_server, str,strlen(str));
       write(1,"\n",1);
       perror("Write:");
       printf("%s\n",myfifo_final);
       server_to_client = open(myfifo_final, O_RDONLY); // LER O QUE O SERVER MANDA.REPARA QUE UM LÊ E OUTRO ESCREVE(NOS 2 FICHEIROS E SÃO ALTERNADOS)
       printf("%s\n",myfifo_final);
       read(server_to_client,str,2048);
       perror("Read:");
       write(1,"----------\n",11);
       write(1,str,strlen(str));
       printf("-------------\n");
       printf("%s\n",str1);
       printf("---------------\n");
       printf("%s\n",myfifo_final);
       free(str);
       str = malloc(100*sizeof(char));
       free(str1);
       free(myfifo_final);
       close(server_to_client);
     }
  }
      close(client_to_server);
    return 0;
}
