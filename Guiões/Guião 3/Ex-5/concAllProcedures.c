#include <unistd.h>//fork/getpid()/getppid()
#include <stdio.h>//printf
#include <sys/wait.h>//fork/getpid()/getppid()/wait()
#include <stdlib.h>//malloc
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"

int main(int argc, char** argv){
	pid_t pid;
	int numCommand = 0;

	if(argc>2){

		do{
			pid = fork();
			numCommand++;
			if(pid<0){
				perror("Não consegui gerar o filho!\n");
			}

			if(pid == 0){//processo filho
				char* msg = malloc(10*sizeof(char)); 
				sprintf(msg,"PROCESS_%d",numCommand);
				printf("Resultado do %dº filho!\n",numCommand);			
				execlp(argv[numCommand],msg,NULL);
				printf(ANSI_COLOR_RED"Ocorreu um erro na chamada do execlp()!"ANSI_COLOR_RESET"\n");
				_exit(0);
			}else{//processo pai
				wait(NULL);//<<--para esperar pelo resultado de todos os filhos					
			}	

		}while(numCommand<argc-1); //argc-1 para nao contar com o executavel como argumento
	
	}else{
		printf("Não possui argumentos associados!\n");
		getchar();
	}
	return 0;
}