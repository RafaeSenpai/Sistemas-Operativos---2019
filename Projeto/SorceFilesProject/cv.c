#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/*
void eliminate_spaces(char *cmd){

   int i = 0,j,n = 0;
    while ((cmd[n] = getchar()) != '\n') {
        n++;
    }
    cmd[n] = '\0';
    while (i < n)
    {
        if(cmd[i]==' ' && (cmd[i+1]==' ' || cmd[i-1]==' '))
        {
            for(j=i;j<n;j++)
            cmd[j]=cmd[j+1];
            n--;
        }
        else
        {
            i++;
        }
    }
    printf("%s\n",cmd);
    printf("\n");

}
*/




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
            int n;
            write(0,"cmd message to serwer: \n",25);
            char str[1024];
           // str=malloc(sizeof(BUFSIZ));
            while((n=read(0,str,1024))>0){
                  write(1,str,n);
                   write(client_to_server, str,n);
            }
            //eliminate_spaces(str);


   			

		   //write(client_to_server, &str, sizeof(*str));

		   perror("Write:"); //Very crude error check

		   read(server_to_client,str,sizeof(*str));

		   perror("Read:"); // Very crude error check

		   printf("...received from the server: %s\n",&str);
		   //close(client_to_server);
		   //close(server_to_client);

		   /* remove the FIFO */

	}
 	  return 0;
}