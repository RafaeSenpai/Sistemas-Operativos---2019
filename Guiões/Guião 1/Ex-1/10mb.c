#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "10mb.h"


void gera10MB(char* nome){
	int fd = open(nome,O_CREAT | O_RDWR,0777);
	char* x = "a";

	for(int i= 0; i<10204000;i++){
		write(fd,x,sizeof(char));
	}
	close(fd);
}

void call_gera10MB(){
	char* name = malloc(50*sizeof(char));

	printf("Insira o nome para o ficheiro: ");
	scanf("%s",name);
	gera10MB(name);
	free(name);
	getchar();
}