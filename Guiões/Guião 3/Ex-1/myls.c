#include <unistd.h>//fork/getpid()/getppid()
#include <stdio.h>//printf
#include <sys/wait.h>//fork/getpid()/getppid()/wait()
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"

int main(int argc, char** argv){

		execlp("ls","nome_do_executavel","-l",NULL);	
		/*O printf a baixo só ocorre caso o execlp dê erro!*/
		printf(ANSI_COLOR_RED"\nOcorreu um erro na chamada do execlp()!\n"ANSI_COLOR_RESET);
		
	return 0;
}

