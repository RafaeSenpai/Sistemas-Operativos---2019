#include "API.h"

int main(int argc, char const *argv[]){

  char* filename = malloc(100*sizeof(char));
	char* line = malloc(100*sizeof(char));

  int n;

  while(read(0,filename,1024)){

		if(strcmp(filename, "end\n") == 0) break;

		strtok(filename, "\n");
		int fd = open(filename, O_RDONLY, 0777);

		printf("LOADING...\n");

		while((n = readLine(fd, line, 1024)) > 0) menuComandosCV(line);

		printf("LOADED\n");
	}

  return 0;
}
