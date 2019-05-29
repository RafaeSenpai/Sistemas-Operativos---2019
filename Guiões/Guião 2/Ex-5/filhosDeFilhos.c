#include <unistd.h>//fork/getpid()/getppid()
#include <sys/wait.h>//fork/getpid()/getppid()
#include <stdio.h>//printf()
#include <string.h>//strlen()
#include <stdlib.h>//system()


int main(int argc, char** argv){
int i = 0;
pid_t pid;

	do{
		pid = fork();
		if(pid<0){
			perror("Não consegui gerar um filho!\n");
			return 1;
		}

		i++;
		
		if(pid == 0){/*<<-- caso de ser filho*/
			printf("\n%dº Filho\n",i);
			printf("PID deste filho: %d\nPID do pai deste filho: %d\n",getpid(),getppid());
		}else{/*<<-- caso de ser pai*/
			wait(NULL);/*<<-- Espera que os filhos terminem*/
			_exit(0);/*<<--termina o processo pai*/
		}
	}while(i<10);

return 0;
}