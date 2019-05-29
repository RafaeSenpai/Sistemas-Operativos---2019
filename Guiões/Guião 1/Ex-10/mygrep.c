#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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


int main(int argc, char **argv){ //NOTA/BUG: Dá os resultados corretos mas continua a iterar sobre o ficheiro!
	char* linha = malloc(2048*sizeof(char));
	int fd = open(argv[2],O_RDONLY);
	char* msg = malloc(1024*sizeof(char));

	printf("Numero de argumentos: argc: %d\n",argc);
	printf("argv[0]: %s\n",argv[0]);
	printf("argv[1]: %s\n",argv[1]);
	printf("argv[2]: %s\n",argv[2]);
	printf("argv[3]: %s\n\nRESULTADO:",argv[3]);
	getchar();


	while((readln(fd,linha,1024))>0){
		if(strstr(linha,argv[1])>0){
			/*https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c*/
			sprintf(msg, ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, linha);
			write(1,msg,strlen(msg));
		}

	}
	return 0;

}