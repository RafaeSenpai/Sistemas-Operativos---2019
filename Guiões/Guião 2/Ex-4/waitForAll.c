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
	int status,i;
	pid_t pid;
	i=0;

	do{
		pid = fork();

		if(pid<0){
			perror("Não consegui gerar o filho!\n");
			return 1;
		}
		
		if(pid==0){
			printf(ANSI_COLOR_YELLOW"Filho com pid (%d) devolveu o codigo de saida: %d\n"ANSI_COLOR_RESET,getpid(),i);
			sleep(2);/*<<--- Este sleep é para obrigar todos os filhos já criados a 
							 esperar tempo suficiente para que os restantes "irmãos" 
							 se criem e façam coisas(podia ser 1 segundo)*/
			_exit(i);/*<<--termina o processo atual com o codigo 'i' passado por argumento*/
		}		
		i++;

	}while(i<10);

	/*O ciclo for abaixo, já é da responsabilidade do processo pai*/
	for(int x = 0; x < 10; x++){
		pid = wait(&status);/*<<--- - A chamada wait() suspende a execução do processo até que um dos seus filhos termine.
									- A variável status é atualizada com o código passado na chamada da função _exit()
									- wait() bloqueia o processo-pai até um processo-filho terminar. Retorna PID do processo-filho que terminou.*/

		printf(ANSI_COLOR_GREEN"Recebido do filho (código de terminação): %d\n"ANSI_COLOR_RESET,WEXITSTATUS(status));/*<<-- WEXITSTATUS(status) retorna o status de saída do processo-filho.*/
		printf(ANSI_COLOR_GREEN"Valor de verificação de se o processo filho terminou sem erros (1-True/0-False): %d\n"ANSI_COLOR_RESET,WIFEXITED(status));
		//sleep(1);
	}

	return 0;
}

/*
Função: wait()

	Bloqueia a execução do processo até um processo-filho terminar.
	
	Retorna, em caso de sucesso:
		○ O identificador de processo (PID) do processo-filho que terminou
		○ O valor do apontador status é atualizado com o código de terminação do processo-filho
*/