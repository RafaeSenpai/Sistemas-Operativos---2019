#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

	return i;
}


int main(int argc, char **argv){
	int fd1,fd2;
	char buf[1024];
	int i;
	char* msg = malloc(2048*sizeof(char));
	
	printf("Numero de argumentos: argc: %d\n",argc);
	printf("argv[0]: %s\n",argv[0]);
	printf("argv[1]: %d\n",atoi(argv[1]));
	printf("argv[2]: %s\n",argv[2]);
	printf("argv[3]: %s\n\n",argv[3]);
	getchar();
	


	// Se nao for especificado o ficheiro lê do STDIN senao le do ficheiro
	
	if( argc < 2 )//se o numero de parametros passados ao terminal for menor que 2 argumentos entao o comando em questão será algo do genero: ./myhead <nº linhas a ler>
		fd1 = 0; //entao o numero de linhas a ler serão as linhas escritas do teclado
	else if(argc == 3){//caso tenha mais que 2 parametro entao é porque existe um terceiro parametro e esse será o ficheiro a ser lidas o numero de linhas passadas. Será algo do genero: ./myhead <nº linhas> <ficheiro>
		fd1 = open(argv[2], O_RDONLY); 
		i=1;
		sprintf(msg,"===> %s <===\n",argv[2]);
		write(0,msg,strlen(msg));
		while(readln(fd1,buf,1024)>0 && i<=((-1)*atoi(argv[1]))){
		//	printf("argv[1]:%d\n",(-1)*(atoi(argv[1])));
		//	printf("i:%d\n",i);
			sprintf(msg,"   %s\n",buf);
			write(0,msg,strlen(msg));
			i++;
		}

	}else{
		fd1 = open(argv[2], O_RDONLY); 
		fd2 = open(argv[3], O_RDONLY); 
		i=1;

		sprintf(msg,"===> %s <===\n",argv[2]);
		write(0,msg,strlen(msg));
		while(readln(fd1,buf,1024)>0 && i<=((-1)*atoi(argv[1]))){
			sprintf(msg,"   %s",buf);
			write(0,msg,strlen(msg));
			i++;
		}

		i=1;//para começar novamento do inicio o contador das linhas lidas no 2º parametro, ficheiro
		
		sprintf(msg,"\n===> %s <===\n",argv[3]);
		write(0,msg,strlen(msg));
		while(readln(fd2,buf,1024)>0 && i<=((-1)*atoi(argv[1]))){
			sprintf(msg,"   %s",buf);
			write(0,msg,strlen(msg));
		i++;
		}
	}

	//ssize_t n = readln(fd,buf,1024);


	free(msg);
	close(fd1);
	close(fd2);
}
