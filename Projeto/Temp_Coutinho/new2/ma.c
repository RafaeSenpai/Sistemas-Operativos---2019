#include "api.h"
#include <fcntl.h> //file descriptor
#include <unistd.h> //system calls
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

int main(){

	char* buf = malloc(100*sizeof(char));
	char* pid = malloc(sizeof(char));
	char* iden = malloc(20*sizeof(char));
	char* myfifo1 = malloc(50*sizeof(char));
	char* myfifo2 = malloc(50*sizeof(char));
	char* publicFifo = "./fifos/publicFifo";

	while(readln(0,buf,1024)){

		if(strcmp(buf, "ag") != 0){
			maMenuComandos(buf);
		}

		else{

			int n, fdPublic, ma_to_server, server_to_ma;

			strcpy(iden,"ma ");
			sprintf(pid,"%d", getppid());
			strcat(iden,pid);
			strcpy(myfifo1,"./fifos/W");
			strcat(myfifo1,pid);
			strcpy(myfifo2,"./fifos/R");
			strcat(myfifo2,pid);

			if((n=mkfifo(myfifo1, 0777))==-1) perror("MKFIFO 1:");
			if((n=mkfifo(myfifo2, 0777))==-1) perror("MKFIFO 2:");

			if((fdPublic = open(publicFifo, O_WRONLY, 0777)) == -1) perror("OPEN 1:");

			if((n = write(fdPublic, iden,strlen(iden)))==-1) perror("WRITE 1:");

			if((ma_to_server = open(myfifo1, O_WRONLY,0777))==-1) perror("OPEN 2:");
			if((server_to_ma = open(myfifo2, O_RDONLY,0777))==-1) perror("OPEN 3:");

			if((n = read(server_to_ma, buf, 100))==-1) perror("READ 1:");

			if((n = write(ma_to_server, "ag", strlen("ag")))==-1) perror("WRITE 2:");

			buf = calloc(100, sizeof(char));
			iden = calloc(100, sizeof(char));
			pid = calloc(100, sizeof(char));
			myfifo1 = calloc(50, sizeof(char));
			myfifo2 = calloc(50, sizeof(char));
		}
	}

	return 0;
}
