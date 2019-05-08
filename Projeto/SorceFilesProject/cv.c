#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

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

  int public;
  char *myfifo = "/tmp/client_to_server_fifo";

  public = open(myfifo, O_WRONLY);


   char* pid=malloc(sizeof(char));
   char* cv=malloc(20*sizeof(char));
   strcpy(cv,"cliente ");
   sprintf(pid,"%d",getppid());
   strcat(cv,pid);
   write(public, cv,strlen(cv));
   printf("%s\n",cv);

   int client_to_server;
   char *myfifo1 = malloc(15*sizeof(char));

   int server_to_client;
   char *myfifo2 = malloc(15*sizeof(char));
   
   strcpy(myfifo1,"/tmp/W");
   strcat(myfifo1,pid);
   strcpy(myfifo2,"/tmp/R");
   strcat(myfifo2,pid);

   mkfifo(myfifo1, 0777);
   mkfifo(myfifo2, 0777);

   printf("%s\n",myfifo2);
   printf("%s\n",myfifo1);

  
  client_to_server = open(myfifo1, O_WRONLY,0777);
  server_to_client = open(myfifo2, O_RDONLY,0777);

  char buf[1024];

    int n;
    printf("-------\n");
    while((n=read(server_to_client,buf,1024))>0){
            perror("Read:");
            printf("%s\n",buf);
    }

    close(server_to_client);
    close(client_to_server);
    close(public);

  return 0;


}






   // ESCREVER O CLIENTE
   //server_to_client = open(myfifo2, O_RDONLY); // LER O QUE O SERVER MANDA.REPARA QUE UM LÊ E OUTRO ESCREVE(NOS 2 FICHEIROS E SÃO ALTERNADOS)
   
   /* write str to the FIFO 
   while(1){
            int n;
            char str[2048]; // +para o user escrever
            //char* str_pointer = malloc(100*sizeof(char)); //para concat as strings
            //str_pointer=&str[0];
            char* str1 = malloc(100*sizeof(char));
            char* myfifo_final = malloc(200*sizeof(char));
            // str=malloc(sizeof(BUFSIZ));
            //sprintf(str1,"%d",getppid());
            //strcat(myfifo_final,myfifo2);
            //strcat(myfifo_final,str1);
            //printf("%s\n",myfifo_final);
            while((n=read(0,str,sizeof(str)))>0){
              sprintf(str1,"%d",getppid());
              strcpy(myfifo_final,myfifo2);
              strcat(myfifo_final,str1);
              printf("%s\n",myfifo_final);
                //n=0;
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
                // strcat(myfifo2,);
                //printf("%s\n",myfifo2); //Very crude error check
                server_to_client = open(myfifo_final, O_RDONLY); // LER O QUE O SERVER MANDA.REPARA QUE UM LÊ E OUTRO ESCREVE(NOS 2 FICHEIROS E SÃO ALTERNADOS)
                printf("%s\n",myfifo_final);
                read(server_to_client,str,2048);
                perror("Read:"); // Very crude error check
                write(1,"----------\n",11);
                write(1,str,strlen(str));  
                memset(str, 0, strlen(str));
                free(str1);
                free(myfifo_final); 
                printf("-------------\n");
                printf("%s\n",str1);
                printf("---------------\n");
                printf("%s\n",myfifo_final);
                char* str1 = malloc(100*sizeof(char));
                char* myfifo_final = malloc(200*sizeof(char));  
                close(server_to_client);    

       /* remove the FIFO 
     }
     memset(str, 0, sizeof(str));
      
  }
      close(client_to_server);
      //close(server_to_client);
    return 0;
}
*/






/*
int main(int argc, char const *argv[])
{
   int client_to_server;
   char *myfifo = "/tmp/client_to_server_fifo";

   int server_to_client;
   char *myfifo2= "/tmp/server_to_client_fifo";

   //pid_t pid=getpid();// saber o pid para saber que sao clientes diferente


   client_to_server = open(myfifo, O_WRONLY);// ESCREVER O CLIENTE
   server_to_client = open(myfifo2, O_RDONLY); // LER O QUE O SERVER MANDA.REPARA QUE UM LÊ E OUTRO ESCREVE(NOS 2 FICHEIROS E SÃO ALTERNADOS)
   // meter os nomes iguais logo metes myfifo+ pid para ser igual ao server
   /* write str to the FIFO 
   while(1){



            int n;
            pid_t pid;// saber o pid para saber que sao clientes diferente

            char* str = malloc(100*sizeof(char));
            char* str1 = malloc(100*sizeof(char));
            char* strfinal = malloc(200*sizeof(char));
            strcat(strfinal,myfifo2);
            strcat(strfinal,str1);
            //server_to_client = open(myfifo, O_RDONLY);


            // str=malloc(sizeof(BUFSIZ));
            while((n=read(0,str,sizeof(str)))>0){
               				//printf("....................\n");
            			  sprintf(str1,"%d",getppid());
            			  //printf("....................\n");
            			  printf("%s\n", str1);
            			  //printf("....................\n");

            			  //sprintf(myfifo2,"/%s",str1);
            			  

            			  //printf("....................\n");
            			  
            			  printf("%s\n",strfinal);
            			  
            			  //server_to_client = open(myfifo2, O_RDONLY);
                          write(1,"----------\n",11);
                          strcat(str1," ");
                          strcat(str1,str);
                          strcpy(str,str1);
                          write(1,"cmd message to serwer: \n",25);
		                  //strcat(str," ");// a tasqueiro mas é para adiconar um espaço
		                  //strcat(str,str1);
		                  printf("%s",str);
		                  printf("%s\n",myfifo);
		                  write(client_to_server, str, strlen(str)); // por causa do espaço adicionamos mais 1 
		          		    perror("Write:"); //Very crude error check
		          		    read(server_to_client,str,strlen(str));
		          		    perror("Read:"); // Very crude error check
		                  write(1,"----------\n",11);
		                  write(1,str,strlen(str));
		                  memset(str, 0, sizeof(str));
	                
            	}
                //write(client_to_server,&pid,sizeof(pid_t));
                
                

               // memset(str, 0, sizeof(str-1));

		  

		   /* remove the FIFO 
     
      
	}
      close(client_to_server);
      close(server_to_client);
 	  return 0;
}
*/