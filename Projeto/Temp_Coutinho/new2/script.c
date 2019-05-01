#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#import <math.h>

int main(){

  int i;
  int fd = open("ARTIGOS.txt", O_RDWR | O_CREAT, 0777);
  float x;

  char* insercao = NULL;

  for(i = 0; i < 100000; i++){
    insercao = malloc(50*sizeof(char));
    x = i * sqrt(2);
    sprintf(insercao, "i ART#%d %f\n", i, x);
    write(fd, insercao, strlen(insercao));
    free(insercao);
  }
  close(fd);
  return 0;
}
