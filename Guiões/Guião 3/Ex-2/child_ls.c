#include <unistd.h>//fork/getpid()/getppid()
#include <stdio.h>//printf
#include <sys/wait.h>//fork/getpid()/getppid()/wait()
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"

int main(int argc, char** argv){
	pid_t pid;
	pid = fork();

	if(pid<0){
		printf("Não consegui gerar o filho!\n");
		return 1;
	}

	if(pid==0){//processo filho
		printf(ANSI_COLOR_GREEN"Sou o filho e vou fazer o ls!\n\n");
		sleep(3);
		execlp("ls","nome_do_executavel","-l",NULL);	
		/*O printf a baixo só ocorre caso o execlp dê erro!*/
		printf(ANSI_COLOR_RED"\nOcorreu um erro na chamada do execlp()!\n"ANSI_COLOR_RESET);
		_exit(0);/*<<--termina o processo filho*/
	
	}else{//processo pai
	
		wait(NULL);/*<<-- espera que o filho termine*/
		sleep(1);
		printf(ANSI_COLOR_GREEN"\n\nSou o processo pai e estive á espera que o meu filho termina-se! Agora vou terminar também!\n"ANSI_COLOR_RESET);
		sleep(5);
		_exit(0);/*<<--termina o processo pai*/
	
	}

	return 0;
}

