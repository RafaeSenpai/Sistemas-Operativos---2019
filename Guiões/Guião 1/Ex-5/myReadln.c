#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

ssize_t readln(int fildes, void *buf, size_t nbyte){
ssize_t i=0;
int n;
char tmp;
char *buffer = (char *)buf;
	
	while((n = (read(fildes,&tmp,1)>0)) && i<nbyte){
		buffer[i]=tmp;
		i++;
		if(tmp == '\n'){//quando o caracter adicionado ao buffer for \n é porque jáleu até ao final da linha e entao termina o while (processo de leitura da linha)
			break;
		}
	}

	if(i<nbyte){
		buffer[i] = '\0';
	}else{//caso seja igual (caso em que esgotou o numero de bytes que podiam ser lidos - este parametro é o parametro que é dado pela variavel nbytes)
		buffer[i-1] = '\0';
	}
	//printf("Retorno do readln: %d\n",);
	return i;
}




int main(int argc, char **argv){
	int fd;
	char buf[1024];
	
	// Se nao for especificado o ficheiro lê do STDIN senao le do ficheiro
	if( argc < 2 )
		fd = 0;
	else
		fd = open(argv[1], O_RDONLY);
	
	// Le a linha do STDIN ou de um ficheiro
	ssize_t n = readln(fd,buf,1024);
	
	// Escreve a linha no STDOUT (n := nr de caracteres da primeira linha)
	write(0,buf,n);
}