#include "API.h"

int main(int argc, char const *argv[]){

   int client_to_server;
   char *myfifo = "/tmp/client_to_server_fifo";

   int server_to_client;
   char *myfifo2 = "/tmp/server_to_client_fifo";

   char buf[1024] = "";
   char str[1024];

   mkfifo(myfifo, 0666);
   mkfifo(myfifo2, 0666);
   int* ptr;

   client_to_server = open(myfifo, O_RDONLY);
   server_to_client = open(myfifo2, O_WRONLY);

   write(1,"Server ON.\n",11);

   while (1){

     if(argc == 1){
       int n=read(client_to_server,buf,2048); // LER O QUE O CLIENTE ESCREVE
       if (strcmp("exit\n",buf)==0){
         break;
       }
       else if (strcmp("",buf)!=0){
         menuComandosCV(buf);
       }
         memset(buf, 0, n);
     }

     else{

       char* path = malloc(100*sizeof(char));
       strcat(path, argv[1]);

       int fd = open(path, O_RDONLY, 0777);

       char* line = NULL;

       while(1){

         line = malloc(100 * sizeof(char));
         line = fileReadLine(fd);

         if(line == NULL){
           free(path);
           free(line);
           break;
         }
       }
     }
   }

   close(client_to_server);
   close(server_to_client);

   unlink(myfifo);
   unlink(myfifo2);
   return 0;
}
