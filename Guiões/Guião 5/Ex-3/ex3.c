#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
	int canal[2];/* <<-- array utilizado para criar o pipe 
					   - dados[0] - permite ler dados do pipe 
					   - dados[1] - permite escrever dados no pipe */
	pid_t pid;
	char buff[1024];

	if(pipe(canal)>-1){
	
		pid = fork();
		if(pid<0){
			perror("Não consegui gerar o filho!\n");
			return 1;
		}

		if(pid == 0){
			close(canal[1]);
			
			dup2(canal[0],0);/*<<--associar o standard input do processo filho ao descritor
								   de leitura do pipe anónimo criado pelo pai*/
			close(canal[0]);
			execlp("wc","wc",NULL);
			_exit(0);
		}else{
			close(canal[0]);
			int n = read(0,buff,1024);
			write(canal[1],buff,n);
			close(canal[1]);
		}
	}else{
		perror("Erro na criação do canal de comunicação!\n");
		return 1;
	}
	return 0;
}