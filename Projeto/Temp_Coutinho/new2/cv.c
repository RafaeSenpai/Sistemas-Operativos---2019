#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char const *argv[]){

  int n;

  char* pid = malloc(sizeof(char));
  char* cv = malloc(20*sizeof(char));
  strcpy(cv,"cliente ");
  sprintf(pid,"%d",getppid());
  strcat(cv,pid);

  int public;
  char *publicfifo = "/tmp/client_to_server_fifo";

  int client_to_server;
  char *myfifo1 = malloc(50*sizeof(char));

  int server_to_client;
  char *myfifo2 = malloc(50*sizeof(char));

  char* buf = malloc(100*sizeof(char));
  char* buf1 = malloc(100*sizeof(char));

  strcpy(myfifo1,"/tmp/W");
  strcat(myfifo1,pid);
  strcpy(myfifo2,"/tmp/R");
  strcat(myfifo2,pid);

  if((n=mkfifo(myfifo1, 0777))==-1) perror("myfifo1:");
  if((n=mkfifo(myfifo2, 0777))==-1) perror("myfifo2:");

  if((public = open(publicfifo, O_WRONLY, 0777)) == -1) perror("OPEN 1:");
  if((n = write(public, cv,strlen(cv)))==-1) perror("WRITE 1:");
  printf("cv:%s\n", cv);
  printf("here\n");
  printf("%d------\n",client_to_server );
  if((client_to_server = open(myfifo1, O_WRONLY,0777))==-1) perror("OPEN 2:");
  printf("client %d\n", client_to_server);
  if((server_to_client = open(myfifo2, O_RDONLY,0777))==-1) perror("OPEN 3:");

  while(1){

    while((n=read(0,buf,1024))>0){

      printf("here\n");

      //if(strcmp(buf, " ") != 0 && strcmp(buf, "\n") == 0 ){
        printf("buf: %s\n",buf);
        if((n=write(client_to_server,buf, strlen(buf)))==-1) perror("WRITE 2:");
        if((n=read(server_to_client,buf1,100))==-1) perror("READ 1:");
        printf("resposta: %s\n",buf1);

        buf1 = calloc(100, sizeof(char));
      //}
      buf = calloc(100, sizeof(char));
    }
  }
  unlink(myfifo1);
  unlink(myfifo2);
  return 0;
}

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
    write str to the FIFO
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
