#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
   int client_to_server;
   char *myfifo = "/tmp/client_to_server_fifo";

   int server_to_client;
   char *myfifo2 = "/tmp/server_to_client_fifo";

   char buf[1024] = "";
   char str[1024];

   /* create the FIFO (named pipe) */
   mkfifo(myfifo, 0666);
   mkfifo(myfifo2, 0666);

   /* open, read, and display the message from the FIFO */
   client_to_server = open(myfifo, O_RDONLY);
   server_to_client = open(myfifo2, O_WRONLY);

   write(1,"Server ON.\n",11);



   while (1)
   {
      int n=read(client_to_server,buf,1024); // LER O QUE O CLIENTE ESCREVE
      if (strcmp("exit\n",buf)==0)
      {
         write(1,"Server OFF.\n",10);
         break;
      }



      else if (strcmp(" ",buf)!=0)
      {
         write(1,"Received: \n",10);
         write(1,buf,n);

         //write(0,"Sending: %s\n", n);
         write(server_to_client,buf,n);
      }
         memset(buf, 0, n);

       //clean buf from any data
      //memset(buf, 0, sizeof(buf-1));
   }


   close(client_to_server);
   close(server_to_client);

   unlink(myfifo);
   unlink(myfifo2);
   return 0;
}
