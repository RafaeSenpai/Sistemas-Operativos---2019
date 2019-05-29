#include <unistd.h>/* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc, char** argv){
	int estado;
	int canal[2];/* <<-- array utilizado para criar o pipe 
					   - dados[0] - permite ler dados do pipe 
					   - dados[1] - permite escrever dados no pipe */
	pid_t pid;

	if(pipe(canal)>-1){
		pid = fork();

		if(pid<0){
			perror("Não consegui gerar o filho!\n");
		}

		if(pid==0){//<<---processo filho
			char stringRecebida[44];
			sleep(1);
			printf(ANSI_COLOR_YELLOW"Processo filho á espera do pai!\n"ANSI_COLOR_RESET);

			sleep(2);
			close(canal[1]);//fecha a escrita
			read(canal[0],stringRecebida,44);
			printf(ANSI_COLOR_GREEN"%s\n"ANSI_COLOR_RESET,stringRecebida);

			close(canal[1]);//<<-- acabada a leitura do conteudo do canal fecha também o canal de leitura
			_exit(0);
		}else{//<<---prcesso pai
			char stringToSend[44] = "Esta string foi escrita pelo processo pai!\n";
			close(canal[0]);//fecha leitura			

			printf("Processo pai está escrever!\n");
			sleep(5);
			write(canal[1],stringToSend,strlen(stringToSend)+1);
			close(canal[0]);//<<-- acabada a escrita no canal fecha o canal de escrita
			wait(&estado);
		}
	}else{
		perror("Ocorreu um erro na criação do canal de comunicação!\n");
		return 1;
	}

	return 0;
}