#include <unistd.h>  //definições e declarações de chamadas
#include <fcntl.h> //definição modos de abertura de ficheiro
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>


int main(){
int tam;
char buffer[60];
/*
O_RDONLY	| Open the file so that it is read only.
O_WRONLY	| Open the file so that it is write only.
O_RDWR		| Open the file so that it can be read from and written to.
O_APPEND	| Append new information to the end of the file.
O_TRUNC		| Initially clear all data from the file.
O_CREAT		| If the file does not exist, create it. If the O_CREAT option is used, then you must include the third parameter.
O_EXCL		| Combined with the O_CREAT option, it ensures that the caller must create the file. If the file already exists, the call will fail.

fonte: http://codewiki.wikidot.com/c:system-calls:open
Exemplos de aplicação de system calls:
http://www.qnx.com/developers/docs/6.5.0/index.jsp?topic=%2Fcom.qnx.doc.neutrino_lib_ref%2Fr%2Fread.html
*/

	/*Abrir o ficheiro*/
	int ficheiro = open("dados.txt", O_RDWR,0777);

	if(ficheiro < 0){
        	return -1;
	}else{
	/*
		int fildes			| The file descriptor of where to write the output. You can either use a file descriptor obtained from the open system call, or you can use 0, 1, or 2, to refer to standard input, standard output, or standard error, respectively.
		const void *buf		| A pointer to a buffer of at least nbytes bytes, which will be written to the file.
		size_t nbytes		| The number of bytes to write. If smaller than the provided buffer, the output is truncated.
		return value		| Returns the number of bytes that were written. If value is negative, then the system call returned an error.
	*/

		if( write(ficheiro,"Foi escrito este conteudo no ficheiro dados.txt\n", 48)!=48){
	      /*write(0-stdin;1-stdou;2-stderr, Mensagem de erro!)*/
      	       write(2, "Ocorreu um erro a gravar a mensagem no ficheiro dados.txt\n", 48);
	               return 1;
		}
	close(ficheiro);
	}



	/*Lê do teclado para um buffer,neste caso data[128]

	read(int fildes, void *buf, size_t nbytes);

		int fildes			| The file descriptor of where to read the input. You can either use a file descriptor obtained from the open 
							  system call, or you can use 0, 1, or 2, to refer to standard input, standard output, or standard error, respectively.
		const void *buf		| A character array where the read content will be stored.
		size_t nbytes		| The number of bytes to read before truncating the data. If the data to be read is smaller than nbytes, all data is saved in the buffer.
		return value		| Returns the number of bytes that were read. If value is negative, then the system call returned an error.  
	*/
    char data[128];
	if(read(0, data, 128) < 0){
    		write(2, "An error occurred in the read.\n", 31);
	    	exit(0);
	}

	/*Imprime o conteudo do buffer*/
	for(int x=0; data[x]!='\n';x++){
		printf("%c",data[x]);
	}
	printf("\n\n");




/*Programa que lê 1 linha do ficheiro e para a leitura quando encontra um espaço (fim da referencia ID do artigo) e apresenta no ecra esse ID*/
/*Passado o ID de um artigo, ler a linha do ficheiro para uma variavel - */















	/*Ler o texto o tamanho do ficheiro
	 *
	tam = read(descritor de ficheiro, buffer para onde é lido o conteudo, nº de bytes a ler);*/
	tam = read(ficheiro,buffer, 60);
	

	/* Testa caso de erro*/
    	if( tam == -1 ) {
        	perror( "--->Erro ao ler o ficheiro dados.txt" );
        	return EXIT_FAILURE;
   	}
	

	/*Devolve a quantidade de bytes lido*/
	printf("Numero de bytes lidos: %d\n",tam);



	printf("\n\n\nPINTOU!\n");
	return EXIT_SUCCESS;

}
