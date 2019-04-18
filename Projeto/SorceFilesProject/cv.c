#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main(int argc, char const *argv[])
{
   int client_to_server;
   char *myfifo = "/tmp/client_to_server_fifo";

   int server_to_client;
   char *myfifo2 = "/tmp/server_to_client_fifo";

   client_to_server = open(myfifo, O_WRONLY);// ESCREVER O CLIENTE
   server_to_client = open(myfifo2, O_RDONLY); // LER O QUE O SERVER MANDA.REPARA QUE UM LÊ E OUTRO ESCREVE(NOS 2 FICHEIROS E SÃO ALTERNADOS)
   
   /* write str to the FIFO */
   while(1){

   			 char str[BUFSIZ];
   			printf("Input message to serwer: ");
   			scanf("%s", str);

		   write(client_to_server, str, sizeof(str));

		   perror("Write:"); //Very crude error check

		   read(server_to_client,str,sizeof(str));

		   perror("Read:"); // Very crude error check

		   printf("...received from the server: %s\n",str);
		   //close(client_to_server);
		   //close(server_to_client);

		   /* remove the FIFO */
	}
 	  return 0;
}