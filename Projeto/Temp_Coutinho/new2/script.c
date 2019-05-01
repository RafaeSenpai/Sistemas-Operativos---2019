#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#import <math.h>

char* randstring(size_t length) {
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *randomString = NULL;
    if (length) {
        randomString = malloc(sizeof(char) * (length +1));
        if (randomString) {
            for (int n = 0;n < length;n++) {
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }
        }
    }
    return randomString;
}

int main(){

  int i;
  int fd = open("ARTIGOS.txt", O_RDWR | O_CREAT, 0777);
  float x;

  char* nome = NULL;
  char* insercao = NULL;
  char* preco = malloc(50*sizeof(char));

  for(i = 0; i < 100000; i++){
    printf("i: %d\n", i);
    nome = malloc(20*sizeof(char));
    insercao = malloc(50*sizeof(char));
    strcat(insercao, "i ");
    nome = randstring(8);
    x = i * sqrt(2);
    strcat(insercao, nome);
    strcat(insercao, " ");
    sprintf(preco, "%f\n", x);
    strcat(insercao, preco);
    write(fd, insercao, strlen(insercao));
    free(nome);
    free(insercao);
  }

  close(fd);
  return 0;
}
