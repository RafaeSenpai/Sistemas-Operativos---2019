#include "api.h"

void main(){//-------------------------------------FUNCIONAL

	int n;

	char* filename = malloc(100*sizeof(char));
	char* line = malloc(100*sizeof(char));

	while(read(0,filename,100)){

		if(strcmp(filename, "quit\n") == 0) break;

		strtok(filename, "\n");
		int fd = open(filename, O_RDONLY, 0777);

		printf("LOADING...\n");

		while((n = readln(fd, line, 100)) > 0){
			maMenuComandos(line);
			line = calloc(100, sizeof(char));
		}

		filename = calloc(100, sizeof(char));

		printf("LOADED\n");
	}

	printf("LOADED ALL\n");

	free(filename);
	free(line);
}
