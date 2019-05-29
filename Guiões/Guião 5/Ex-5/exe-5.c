#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


/*
	NOTA: Esta função está a imprimir nada no output!
*/
int main(){
	pid_t pid;
	int canal[2];/* <<-- array utilizado para criar o pipe 
					   - dados[0] - permite ler dados do pipe 
					   - dados[1] - permite escrever dados no pipe */
	pid = fork();

	if(pipe(canal)>-1){
		if(pid<0){
			perror("Não consegui gerar o filho!\n");
			return 1;
		}

		if(pid == 0){
			close(canal[1]);//fecha o canal de escrita
			dup2(canal[0],0);//redireciona o canal de leitura
			close(canal[0]);//fecha o canal de leitura
			execlp("cut","cut","-f7","-d:",NULL);
			_exit(0);
		}else{
			close(canal[0]);//fecha o canal de leitura
			dup2(canal[1],1);//redireciona o canal de escrita
			close(canal[1]);
			execlp("grep","-v","^#","/etc/passwd",NULL);
		}
	}else{
		perror("Erro ao criar o canal de comunicação!\n");
		return 1;
	}
	return 0;
}