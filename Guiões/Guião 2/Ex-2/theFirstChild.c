#include <unistd.h>//fork/getpid()/getppid()
#include <sys/wait.h>//fork/getpid()/getppid()
#include <stdio.h>//printf()
#include <string.h>//strlen()
#include <stdlib.h>//system()

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define MSG "Resultado do comando 'ps' antes deste programa terminar!\nDÊ ENTER...\n"

int main(int argc, char**argv){
pid_t pid;
int status=-1;
	pid = fork();

	if(pid<0){ /*<<--Em caso de falha no fork(), este retorna um valor negativo*/
		perror("Não consegui gerar um filho!\n");
		return 1;
	}

	if(pid == 0){/*	<<--caso o fork() retorne seja igual a zero (isto é, 
						trata-se do processo filho), entao irá
						fazer o processos imediatamente a baixo*/

		sleep(3);//<- para o filho permanecer ativo e obter o seu pid
		printf(ANSI_COLOR_GREEN"PROCESSO FILHO!\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_GREEN"PID deste processo filho: %d\n"ANSI_COLOR_RESET,getpid());
		printf(ANSI_COLOR_GREEN"PID do processo pai deste filho: %d\n"ANSI_COLOR_RESET,getppid());
		system("ps -l");
		_exit(0);

	}else{/*<<--caso o fork() retorne um valor diferente de zero(partindo do principio 
				que nao occoreu nenhum erro na criação do filho) então é porque se trata
				do processo pai*/


		/*
			A situação em que o processo filho é assinalado como estando num estado Z ou 	<defunct>,
			designado por zombie. Este caso ocorre quando um processo termina e o seu pai não recolheu ainda a
			correspondente informação (através da invocação da chamada wait()).
		*/
		
		wait(&status);	/*<<<---caso queira que o pai aguarde pela resposta do filho. 
									Para tal o filho tem que finalizar as suas tarefas e 
									só depois é que o pai prossegue. O que quer dizer que 
									o primeiro resultado a ser visualizado será o do processo 
									filho e só depois o resultado do processo pai*/
		printf("Valor guardado na variavel status (variavel que contem o estado transmitido pelo filho): %d\n",status);
		printf(ANSI_COLOR_YELLOW"PROCESSO PAI!\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_YELLOW"PID deste processo pai: %d\n"ANSI_COLOR_RESET,getpid());
		printf(ANSI_COLOR_YELLOW"PID do filho deste pai: %d\n"ANSI_COLOR_RESET,pid);


		/*
			A baixo um pequeno comando que permite ao utilizador visualizar os processos a correr, 
			antes deste programa terminar, e desta forma conseguir confirmar os PIDs do processo pai 
			e o processo filho, de outra forma não seria possivel cofirmar o PID do processo filho 
			porque para executar o comando de visualização de processos primeiro teria que terminal 
			o processo filho, e ao terminar primeiramente o processo filho, este já nao iria aparecer 
			na lista de processos invocada
		*/
		//write(1,MSG,strlen(MSG));
		//getchar();
		system("ps -l");

		getchar(); //para não terminar o programa. Não tão util quanto isso!

	}

	return 0;
}