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

int main(int argc, char const *argv[]) {

  int n;

  int public;
  char *myfifo = "/tmp/client_to_server_fifo";
  if((n=mkfifo(myfifo,0777))==-1) perror("MKFIFO 1:");
  printf("n: %d\n", n);
  if((public = open(myfifo, O_RDONLY,0777)) == -1) perror("OPEN 1:");

  int client_to_server;
  char *myfifo1 = malloc(50*sizeof(char));

  int server_to_client;
  char *myfifo2 = malloc(50*sizeof(char));

  char *buf = malloc(1024*sizeof(char));
  char *str = malloc(1024*sizeof(char));
  char *buf1 = malloc(50*sizeof(char));

  int status;

  write(1,"Server ON.\n",11);

  while (1){

    printf("here\n");
    if((n=read(public,buf,1024))==-1) perror("READ 1:");
    printf("here\n");

    printf("cenas lidas do public:%s\n",buf);

    char* cenas  = strtok(buf," ");
    char* cenas2 = strtok(NULL," ");

    printf("conteudo do cenas: %s\n",cenas);
    printf("conteudo do cenas: %s\n",cenas2);

    strcpy(myfifo1,"/tmp/W");

    printf("myfifo: %s\n",myfifo1);

    strcat(myfifo1,cenas2);

    printf("myfifo: %s\n",myfifo1);

    strcpy(myfifo2,"/tmp/R");

    printf("myfifo2: %s\n",myfifo2);

    strcat(myfifo2,cenas2);

    printf("myfifo2: %s\n",myfifo2);
    printf("conteudo do canal de comunicaçao:%s\n",buf);
    printf("%s\n",buf1);

    if(strcmp(buf,"cliente")==0){

      printf("2222222\n");
      printf("333333333333\n");
      printf("44444444444\n");

      if((server_to_client = open(myfifo2, O_WRONLY,0777))==-1) perror("OPEN 1:");
      printf("here\n");
      write(server_to_client, "qualquer coisa\n", strlen("qualquer coisa\n"));
      if((client_to_server = open(myfifo1, O_RDONLY,0777))==-1) perror("OPEN 2:");

      strcpy(buf1,"cenas com 50 posicoes\n\n\n");
      printf("%s\n",buf1);
      printf("mesmo antesd do write suposto de erro!\n");

      if((n = write(server_to_client,buf1,strlen(buf1)))==-1) perror("WRITE 1:");

      printf("ola\n");
      close(client_to_server);
      close(server_to_client);
    }
  }

  close(public);
  unlink(myfifo);
  unlink(myfifo2);
  return 0;
}

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
  create the FIFO (named pipe)
  mkfifo(myfifo, 0666);
  mkfifo(myfifo2, 0666);

  int pd[2];
  pipe(pd);

  // if failed

  open, read, and display the message from the FIFO
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
