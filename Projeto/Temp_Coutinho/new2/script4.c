#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){

  int i; int n = 25001;
  int fd = open("script_stocks.txt", O_RDWR | O_CREAT, 0777);

  char* insercao = NULL;

  for(i = 0; i < 25000; i++){
    insercao = malloc(50*sizeof(char));
    sprintf(insercao, "%d %d\n", i, n);
    n--;
    write(fd, insercao, strlen(insercao));
    free(insercao);
  }
  close(fd);
  return 0;
}
