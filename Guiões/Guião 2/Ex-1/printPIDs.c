#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MSG "Resultado do comando 'ps' antes deste programa terminar!\nDÊ ENTER...\n"

int main(int argc, char** argv){
	char* msg = malloc(100*sizeof(char));
	pid_t pidProcesso = getpid();
	pid_t pidProcessoPai = getppid();

	sprintf(msg,"PID do pai: %d\nPID do processo filho: %d\n\n",pidProcessoPai,pidProcesso);
	write(1,msg,strlen(msg));

	/*A baixo um pequeno comando que permite ao utilizador visualizar os processos a correr, 
	antes deste programa terminar, e desta forma conseguir confirmar os PIDs do processo pai 
	e o processo filho, de outra forma não seria possivel cofirmar o PID do processo filho 
	porque para executar o comando de visualização de processos primeiro teria que terminal 
	o processo filho, e ao terminar primeiramente o processo filho, este já nao iria aparecer 
	na lista de processos invocada*/
	write(1,MSG,strlen(MSG));
	getchar();
	system("ps");

	getchar(); //para não terminar o programa. Não tão util quanto isso!
	return 0;
}