#include <unistd.h>/* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
	pid_t pid = fork();
	int status;

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

	if(pid<0){
		perror("Não consegui gerar o filho!\n");
		return 1;
	}
	if(pid==0){
		execlp("wc","wc",NULL);/*<<<----execlp porque sabe-se que a função wc predefinida do sistema, 
									  	logo não há necessidade de inidicar o caminho para a esta 
									 	função o execlp "já sabe esse caminho"*/
		_exit(0);
	}else{
		pid = wait(&status);
		return status;
	}

	close(fdInput);
	close(fdOutput);
	close(fdErrors);


	return 0;
}