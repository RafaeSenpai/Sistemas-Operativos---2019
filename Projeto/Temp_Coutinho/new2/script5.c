#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){

  int i; int sign = 1; int venda; int limit = 1000;
  int fd = open("script_vendas.txt", O_RDWR | O_CREAT, 0777);

  time_t t;
  srand((unsigned) time(&t));

  char* insercao = NULL;

  for(i = 0; i < 50000; i++){
    venda = rand() % limit * sign;
    insercao = malloc(50*sizeof(char));
    sprintf(insercao, "%d %d\n", i, venda);
    write(fd, insercao, strlen(insercao));
    free(insercao);
    sign = -sign;
  }

  sign = -sign;

  for(i = 0; i < 50000; i++){
    venda = rand() % limit * sign;
    insercao = malloc(50*sizeof(char));
    sprintf(insercao, "%d %d\n", i, venda);
    write(fd, insercao, strlen(insercao));
    free(insercao);
    sign = -sign;
  }

  sign = -sign;

  for(i = 0; i < 50000; i++){
    venda = rand() % limit * sign;
    insercao = malloc(50*sizeof(char));
    sprintf(insercao, "%d %d\n", i, venda);
    write(fd, insercao, strlen(insercao));
    free(insercao);
    sign = -sign;
  }

  sign = -sign;

  for(i = 0; i < 50000; i++){
    venda = rand() % limit * sign;
    insercao = malloc(50*sizeof(char));
    sprintf(insercao, "%d %d\n", i, venda);
    write(fd, insercao, strlen(insercao));
    free(insercao);
    sign = -sign;
  }

  sign = -sign;

  for(i = 0; i < 50000; i++){
    venda = rand() % limit * sign;
    insercao = malloc(50*sizeof(char));
    sprintf(insercao, "%d %d\n", i, venda);
    write(fd, insercao, strlen(insercao));
    free(insercao);
    sign = -sign;
  }

  close(fd);
  return 0;
}
