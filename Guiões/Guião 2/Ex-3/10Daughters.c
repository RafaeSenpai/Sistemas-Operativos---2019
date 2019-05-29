#include <unistd.h>//fork/getpid()/getppid()
#include <sys/wait.h>//fork/getpid()/getppid()
#include <stdio.h>//printf()
#include <string.h>//strlen()
#include <stdlib.h>//system()
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc, char** argv){
pid_t pid;
int i=0;
int status;
	
	
	do{
		pid = fork();
		i++;
		if(pid<0){
			perror("Não consegui gerar o filho!\n");
		}
		if(pid==0){
			printf(ANSI_COLOR_GREEN"\nSON!\n"ANSI_COLOR_RESET);
			printf(ANSI_COLOR_GREEN"PID deste processo filho é: %d\n"ANSI_COLOR_RESET,getpid());
			printf(ANSI_COLOR_GREEN"PID do processo pai deste filho é: %d\n"ANSI_COLOR_RESET,getppid());
			printf(ANSI_COLOR_RED"Enviando para o pai->\n"ANSI_COLOR_RESET);
			sleep(1);
			printf(ANSI_COLOR_RED"Enviando para o pai-->\n"ANSI_COLOR_RESET);
			sleep(2);
			printf(ANSI_COLOR_RED"Enviando para o pai--->\n"ANSI_COLOR_RESET);
			sleep(2);
			printf(ANSI_COLOR_RED"Enviando para o pai---->DONE!\n"ANSI_COLOR_RESET);
			sleep(1);
			_exit(i);/*<<---para terminar a sua execução com um valor de saı́da igual ao seu número de ordem (e.g.: primeiro filho criado 
							termina com o valor 1). Só pode imprimir o código de saı́da de um filho se este tiver terminado com a invocação 
							(implı́cita ou explı́cita) da chamada ao sistema exit().*/
		}else{
			pid = wait(&status);//A chamada wait() suspende a execução do processo até que um dos seus filhos termine.

			printf(ANSI_COLOR_YELLOW"\nFATHER! - RECEBIDO DO FILHO!\n"ANSI_COLOR_RESET);
			printf("CÓDIGO DE SAIDA ENVIADO PELO FILHO E RECEBIDO PELO PAI: %d(pid) e %d(WEXITSTATUS)\n",pid,WEXITSTATUS(status));//WEXITSTATUS(status) retorna o status de saída do processo-filho.
			printf(ANSI_COLOR_YELLOW"PID deste processo pai é: %d\n"ANSI_COLOR_RESET,getpid());
			printf(ANSI_COLOR_YELLOW"PID do filho deste processo pai é: %d\n"ANSI_COLOR_RESET,pid);
		}
	}while(i<10);

	return 0;
}

/*
Function: _exit()

	Description:
		- The function _exit() terminates the calling process "immediately". Any open file descriptors belonging to the process are closed; any children 
		  of the process are inherited by process 1, init, and the process's parent is sent a SIGCHLD signal.
		- The value status is returned to the parent process as the process's exit status, and can be collected using one of the wait(2) family of calls.
		- The function _Exit() is equivalent to _exit().

	Return Value:
		These functions do not return.

Mais: http://www.uniriotec.br/~morganna/guia/libc/cs_wait.html
*/