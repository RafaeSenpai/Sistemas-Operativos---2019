#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
	pid_t pid;
	int canal[2];/* <<-- array utilizado para criar o pipe 
					   - dados[0] - permite ler dados do pipe 
					   - dados[1] - permite escrever dados no pipe */

	if(pipe(canal)>-1){

		pid=fork();

		if(pid<0){
			perror("Não consegui gerar o filho!\n");
			return 1;
		}

		if(pid == 0){
			close(canal[1]);//fecha a escrita do canal
			dup2(canal[0],0);
			close(canal[0]);
			execlp("wc","wc","-l",NULL);
			_exit(0);

		}else{
			close(canal[0]);//fecha o canal de leitura
			dup2(canal[1],1);
			close(canal[1]);
			execlp("ls","ls","/etc",NULL);

		}
	}else{
		perror("Erro ao criar o canal de comunicação!\n");
		return 1;
	}

	return 0;
}