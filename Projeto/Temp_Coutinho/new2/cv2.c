#include "api.h"

int main(int argc, char const *argv[]){

  char* filename = malloc(100*sizeof(char));
	char* line = malloc(100*sizeof(char));

  int n;

  while(read(0,filename,1024)){

		if(strcmp(filename, "end\n") == 0) break;

		strtok(filename, "\n");
		int fd = open(filename, O_RDONLY, 0777);

		printf("LOADING...\n");

		while((n = readln(fd, line, 1024)) > 0) menuComandos(line);

		printf("LOADED\n");
	}

  return 0;
}
