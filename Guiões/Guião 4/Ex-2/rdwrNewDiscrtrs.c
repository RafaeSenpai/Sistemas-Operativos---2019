#include <unistd.h>/* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#define msg "Isto é o resultado de um printf 'Mensagem de teste para o output!'\n\n\n"


int main(){
pid_t pid;
int status;	
	/*
	- open(...):

		Devolve o descritor de ficheiros para o novo ficheiro. O descritor de ficheiros é 
		sempre o inteiro mais pequeno e maior que zero disponivel. Se for um valor negativo, 
		entao é porque ocorreu um erro ao abrir o ficheiro.
	*/
	int fdInput = open("./DataFiles/input.txt", O_RDONLY,0777);

	if(fdInput>0){
		/*redirecionar o STDIN*/
		if(dup2(fdInput,0)<0){
			close(fdInput);
			return 1;
		}
	}

	/*As permissões 0777 são necessárias para aceder ao conteudo dos ficheiros!*/
	int fdOutput = open("./DataFiles/saida.txt", O_CREAT | O_APPEND | O_WRONLY,0777);
	if(fdOutput>0){
		/*redirecionaro STDOUT*/
		if(dup2(fdOutput,1)<0){
			close(fdOutput);
			return 1;
		}
	}
	

	int fdErrors = open("./DataFiles/erros.txt", O_CREAT | O_APPEND | O_WRONLY,0777);
	if(fdErrors>0){
		/*redirecionar o STDERR*/
		if(dup2(fdErrors,2)<0){
			close(fdErrors);
			return 1;
		}
	}

	pid = fork();
	
	if(pid<0){
		perror("Não consegui gerar o filho!\n");
		return 1;
	}

	if(pid==0){
		/*Escreve no descritor de ficheiros, 1, (que já não é o terminal) que foi 
		anteriormente redefinido para o ficheiro "saida.txt"*/
		write(1,msg,strlen(msg));

		/*Lê do stdin, 0, (que já não é o teclado) que foi anteriormente redefinido
		para o ficheiro input.txt e vai gravar o seu conteudo para uma variavel e 
		posteriormente visualizada para prova*/
		char buff[1024];
		/*lê do stdin(agora o conteudo do ficheiro stdin.txt e lê-o e faz o seu print*/
		read(0,&buff,1024);

		/*Os resultados a baixo (obtido pelo comando do "system" e o printf não serão 
		impresso no ecra mas sim no ficheiro saida.txt*/
		printf("%s\n",buff);
		system("ls");
		system("tree");/*<<--este comando pode retornar erro caso a aplicação nao esteja 
							 instalada, logo o erro ficará registado no ficheiro erros.txt*/

		/*O comando a baixo é não existe logo vai dar erro, como tal este erro será guardado
		no ficheiro erros.txt*/
		system("./invocação_função_invalida");

		/*	
		- close(...)

			O descritor a ser copiado deve ser fechado (função close()) depois de ser 
			realizado o comando dup() caso já não seja necessário.
		*/
		close(fdInput);
		close(fdOutput);
		close(fdErrors);

		_exit(0);
	}else{
		pid = wait(&status);
		return status;
	}

	return 0;
}