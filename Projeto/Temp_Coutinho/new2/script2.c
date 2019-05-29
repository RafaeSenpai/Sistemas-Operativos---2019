#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(){

  int i; int n = 99999;
  int fd = open("script_n.txt", O_RDWR | O_CREAT, 0777);

  char* insercao = NULL;

  for(i = 0; i < 50000; i++){
    insercao = malloc(50*sizeof(char));
    n--;
    sprintf(insercao, "n %d ART#%d\n", i, n);
    write(fd, insercao, strlen(insercao));
    free(insercao);
  }
  close(fd);
  return 0;
}
