#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

#define MULT 100000000

int here;

void insere(char* nome, char* preco);

void altera_nome(char* codigo, char* nome);

void altera_preco(char* codigo, char* preco);

int main(int argc, char* argv[]){

  char buf[128], buf2[128], *nome, *acao, *codigo, *preco, *token;
  int len1, len2;

  here = 0;

  while(1){

    /*scanf("%s[^\n]", buf);
    strcpy(buf2, buf);
    acao = strtok(buf, " ");*/

    

/*
    if(strcmp(acao, "i") == 0){

      printf("here %d\n", here); here++;

      preco = strrchr(buf2, ' ');
      //strtok(preco, " ");
      printf("%s\n", preco);
      nome = strchr(buf2, ' ');
      //strtok(nome, " ");
      printf("%s\n", nome);

      printf("Comando: i, %s, %s\n", nome, preco);

      //insere(nome, preco);
    }
/*
    else if(strcmp(acao, "n") == 0){

      nome = strrchr(buf2, ' ');
      strtok(nome, " ");
      printf("%s\n", nome);
      codigo = strchr(buf2, ' ');
      strtok(codigo, " ");

      printf("Comando: n, %s, %s\n", codigo, nome);

      //altera_nome(codigo_int, nome);

    }

    else if(strcmp(acao, "p") == 0){

      preco = strrchr(buf2, ' ');
      strtok(preco, " ");
      codigo = strchr(buf2, ' ');
      strtok(codigo, " ");

      printf("Comando: i, %s, %s\n", codigo, preco);

      //altera_preco(codigo_int, preco_f)

    }

    else if(strcmp(acao, "q") == 0) break;
    else{

      printf("Input inválido, insira novo input\n");

    }
*/
  }

  return 0;

}
/*
void insere(char* nome, char* preco){

  int fd, ref, id;
  char* buf;
  sprintf(buf, "%s %s\n", nome, preco);

  fd = open("ARTIGOS", O_CREAT | O_TRUNC | O_WRONLY, 0777);
  write(fd, buf, strlen(buf));
  close(fd);
}
*/
