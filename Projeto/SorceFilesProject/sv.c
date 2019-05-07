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

/*
void cvGetStock(char* id,char *msg1){ //-------------------------------------------------------FUNCIONAL
int fdStK = open("STOCKS.txt", O_RDONLY);
char* msg = malloc(100*sizeof(char));
int stk;

   if(fdStK){
      //printf("Vai te feoder\n");
      lseek(fdStK,atoi(id)*sizeof(int),SEEK_SET);
      printf("Vai te feoder\n");
      read(fdStK,&stk,sizeof(int));
      close(fdStK);
      if(msg){
         printf("Vai te feoder\n");
         sprintf(msg,"Stock: %d\n",stk); 
         strcpy(msg1,msg); 
         //write(1, msg, strlen(msg));
         free(msg);
      }else{
         printf("Erro na funcao\n");
      }
   }else{
      printf("Erro no stock.txt\n");
   }
}
*/







/*
int main(int argc, char const *argv[])
{
   int client_to_server;
   char *myfifo = "/tmp/client_to_server_fifo";

   int server_to_client;
   char *myfifo2 = "/tmp/server_to_client_fifo";

   char buf[1024] = "";
   char str[1024];

   int status;
   /* create the FIFO (named pipe) 
   mkfifo(myfifo, 0666);
   mkfifo(myfifo2, 0666);

  int pd[2];
  pipe(pd);
  
  // if failed
  
   /* open, read, and display the message from the FIFO 
   client_to_server = open(myfifo, O_RDONLY);
   server_to_client = open(strfinal, O_WRONLY);

   

   write(1,"Server ON.\n",11);
    write(1,"Server ON.\n",11);
   while (1)

   {  
         int n=read(client_to_server,buf,2048);
         printf("kjsnanjsanjsan");


      if(fork()==0){
         int n=read(client_to_server,buf,2048);
         printf("kjsnanjsanjsan");

          // LER O QUE O CLIENTE ESCREVE
         if (strcmp("exit\n",buf)==0){
         write(1,"Server OFF.\n",10);
         break;
         }

         else if (strcmp(" ",buf)!=0)
         {
            char* str = malloc(100*sizeof(char));
            char* str1 = malloc(100*sizeof(char));
            char* strfinal = malloc(200*sizeof(char));
            

         char *myfifo2 = "/tmp/server_to_client_fifo";
        // strcat(strfinal,myfifo2);
         printf("kjsnanjsanjsan");
         str1=strtok(str," ");
         strcat(strfinal,str1);
      
         printf("%s\n",strfinal);
         server_to_client = open(strfinal, O_WRONLY);


         //pid_t pid=fork();
         char s[2]=" ";
         
         write(1,"Received: \n",10);
         write(1,buf,n);
         printf(".------------------------\n");
         write(server_to_client, "vai te foder", 13); // por causa do espaço adicionamos mais 1 


         //write(0,"Sending: %s\n", n);
         //write(server_to_client,buf,n);
         //memset(buf, 0, n);
         //cvGetStock(strtok(buf,s),str);
         //write(server_to_client,buf,n);   
         //write(server_to_client,getpid(),sizeof(pid_t)); 
         //strcat(myfifo2,strtok(buf," "));
         strtok(buf," ");
         printf("%s\n",buf);
         //printf("%c\n",myfifo2);
         //mkfifo(myfifo2, 0666);
            //write(1,myfifo2,strlen(myfifo2));
           

            //close(pd1[1]);// o pai nao escreve,
            //close(pd2[0]);
            //funcao que se através do switch
            // resultado

            //write(pd2[1],, ); //filho escreve para o pai 

            //close(pd1[0]);// o pai nao escreve,
            //close(pd2[1]);

            //server_to_client = open(myfifo2, O_WRONLY);
            //write(server_to_client,buf,n);

         }
      }

         else{

            
               wait(&status);

         }

         
         
      
         //memset(buf, 0, n);

       //clean buf from any data
      //memset(buf, 0, sizeof(buf-1));
   }


   close(client_to_server);
   //close(server_to_client);

   unlink(myfifo);
  // unlink(myfifo2);
   return 0;

}
*/

int main(int argc, char const *argv[])
{
   int client_to_server;
   char *myfifo = "/tmp/client_to_server_fifo";

   int server_to_client;
   char *myfifo2 = "/tmp/server_to_client_fifo";

   char buf[1024] = "";
   char str[1024];
   char buf1[1024] = "";

   int status;

   /* create the FIFO (named pipe) */
   mkfifo(myfifo, 0666);
   //mkfifo(myfifo2, 0666);

   /* open, read, and display the message from the FIFO */
   client_to_server = open(myfifo, O_RDONLY);
   //server_to_client = open(myfifo2, O_WRONLY);


   write(1,"Server ON.\n",11);



   while (1)
   {
      //printf("kjsnanjsanjsan");


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

     // int n=read(client_to_server,buf,1024); // LER O QUE O CLIENTE ESCREVE
      if (strcmp("exit\n",buf)==0)
      {
         write(1,"Server OFF.\n",10);
         break;
      }



      else if (strcmp(" ",buf)!=0)
      {
         //if(fork()==0){
                  //printf("kjsnanjsanjsan");
      	                  //memset(buf, 0, n);

      			if(fork()==0){

                  mkfifo(myfifo_final, 0666);
                  server_to_client = open(myfifo_final, O_WRONLY);
                  printf("%s\n",myfifo_final);
                  printf("%s",buf );
                  printf("---------------\n");
                  write(1,"Received: ",11);
                  write(1,buf,2*n);
                  //write(0,"Sending: %s\n", n);
                  write(server_to_client,buf,n);
                  perror("Write:");   
                  close(server_to_client);
                  
               }
               else
               		{
            		 wait(&status);
            		 //close(server_to_client);

            		}
            

               }
         //else{
          //    wait(&status);
               memset(buf, 0, n);
         //}
      }
         

       //clean buf from any data
      //memset(buf, 0, sizeof(buf-1));
   


   close(client_to_server);
   //close(server_to_client);

   unlink(myfifo);
   unlink(myfifo2);
   return 0;
}