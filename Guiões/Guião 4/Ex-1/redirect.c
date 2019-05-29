#include <unistd.h>/* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>
#include <stdlib.h>

int main(){
	
	int fdInput = open("/etc/passwd", O_RDONLY,0777);
	/*
		- open(...):

		Devolve o descritor de ficheiros para o novo ficheiro. O descritor de ficheiros é 
		sempre o inteiro mais pequeno e maior que zero disponivel. Se for um valor negativo, 
		entao é porque ocorreu um erro ao abrir o ficheiro.
	*/
	if(fdInput>0){
		/*redirecionar o STDIN*/
		if(dup2(fdInput,0)<0){
			close(fdInput);
			return 1;
		}
	}

	/*As permissões 0777 são necessárias para aceder ao conteudo dos ficheiros!*/
	int fdOutput = open("./DataFiles/saida.txt",O_CREAT | O_APPEND | O_WRONLY,0777);
	if(fdOutput>0){
		/*redirecionaro STDOUT*/
		if(dup2(fdOutput,1)<0){
			close(fdOutput);
			return 1;
		}
	}
	

	int fdErrors = open("./DataFiles/erros.txt",O_CREAT | O_APPEND | O_WRONLY,0777);
	if(fdErrors>0){
		/*redirecionar o STDERR*/
		if(dup2(fdErrors,2)<0){
			close(fdErrors);
			return 1;
		}
	}

	char buf[1024];
	int n = 0;
	/*Vai ler de /etc/password e escrever em saida.txt e erros.txt*/
	if(n>=0){
		/* 	read:

			Devolve o numero de bytes lidos
		*/
		n = read(0,buf,1024);
		write(1,buf,n);
		write(2,buf,n);
		/*	close(...)

			O descritor a ser copiado deve ser fechado (função close()) depois de ser 
			realizado o comando dup() caso já não seja necessário.
		*/
		close(fdInput);
		close(fdOutput);
		close(fdErrors);
	}

	return 0;
}