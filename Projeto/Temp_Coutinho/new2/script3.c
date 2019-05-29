#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){

  int i; float x;
  int fd = open("script_p.txt", O_RDWR | O_CREAT, 0777);

  char* insercao = NULL;

  for(i = 0; i < 75000; i++){
    insercao = malloc(50*sizeof(char));
    x = i * sqrt(3);
    sprintf(insercao, "p %d %f\n", i, x);
    write(fd, insercao, strlen(insercao));
    free(insercao);
  }
  close(fd);
  return 0;
}
