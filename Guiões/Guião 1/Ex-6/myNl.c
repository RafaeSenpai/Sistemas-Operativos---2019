#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


ssize_t readln(int fildes, void *buf, size_t nbyte){
int n,i=0;
char tmp;
char *buffer = (char *)buf;
	
	while(n = (read(fildes,&tmp,1)>0) && i<nbyte){
		i++;
		buffer[i]=tmp;
	
		if(tmp=='\n'){
			break;
		}	
	}

	if(n<0){
		buffer[i]='\0';
	}

	if(i<nbyte){
		buffer[i]='\0';
	}else{
		buffer[i-1]='\0';
	}

	return i;
}


int main(int argc, char **argv){
	int fd;
	char buf[1024];
	int i=1;
	// Se nao for especificado o ficheiro lê do STDIN senao le do ficheiro
	if( argc < 2 )
		fd = 0;
	else
		fd = open(argv[1], O_RDONLY);
	
	// Le a linha do STDIN ou de um ficheiro
	//ssize_t n = readln(fd,buf,1024);
	
	char* msg = malloc(2048*sizeof(char));

	while(readln(fd,buf,1024)>0){
		sprintf(msg,"    %d  %s\n",i,buf);
		write(0,msg,strlen(msg));
		i++;
	}
	
	free(msg);
	close(fd);
}