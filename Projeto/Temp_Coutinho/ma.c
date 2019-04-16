#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

void insere(char* nome, char* preco);

void altera_nome(char* codigo, char* nome);

void altera_preco(char* codigo, char* preco);

int main(int argc, char* argv[]){

  char *acao, *nome, *codigo, *preco;

  acao = strdup("i");
  nome = strdup("badjoras");
  codigo = strdup("42069");
  preco = strdup("1.23");

  insere(nome, preco);

/* falta ler input e chamar funções correspondentes*/

  return 0;

}

void insere(char* nome, char* preco){

  int fd, id = 0, aux = 0, count = 0;
  char *buf, *iden, *count_s;

  fd = open("ARTIGOS", O_CREAT | O_TRUNC | O_WRONLY, 0777);

/*
  read(fd, buf, 1);

  while(strcmp(buf, "\0") != 0){
    if(strcmp(buf, "\n") == 0) id++;
    read(fd, buf, 1);
  }

  printf("here\n");

  aux = id;
  while(aux != 0){
    aux /= 10;
    ++count;
  }

  aux = count;
  while(count > 0){
    strcat(iden, "0");
    count--;
  }

  sprintf(count_s, "%d ", aux);
  strcat(iden, count_s);
  strcat(iden, count_s);
  strcat(iden, preco);
  */

  iden = strdup("1 1 4.20\n2 2 3.50\n3 3 0.69\n");
  write(fd, iden, strlen(iden));

  iden = strdup("4 4 4.20\n5 5 3.50\n6 6 0.69\n");
  write(fd, iden, strlen(iden));
  close(fd);

}
