#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char c;
	int n;
	int status;

	int fsaida = open("saida2.txt",O_CREAT | O_TRUNC | O_WRONLY, S_IWUSR | S_IRUSR );
	int ferros = open("erros2.txt",O_CREAT | O_TRUNC | O_WRONLY, S_IWUSR | S_IRUSR );
	int fabrir = open("/etc/passwd", O_RDONLY);

	if(dup2(ferros,0)<0){
		printf("Erro ao riderecionar ficheiro de sderr\n");
	}
	if(dup2(fabrir,0)<0){
		write(ferros,"Erro ao riderecionar ficheiro de stdin\n",40);
		//printf("Erro ao riderecionar ficheiro de stdin\n");
	}
	if(dup2(fsaida,0)<0){
		write(ferros,"Erro ao riderecionar ficheiro de stdout\n",41);
		//printf("Erro ao riderecionar ficheiro de stdout\n");
	}
	// Estás a criar o filho 
	if(fork()==0){// estando no filho fazes a leitura e escrita no ficheiro que queres

		while((n=read(fabrir,&c,1))>0){
			write(fsaida,&c,n);
		}
	}
	// o pai vai esperar

	wait(&status);
	// fechas os ficheiros
	close(fsaida);
	close(ferros);
	close(fabrir);

	return 0;
}
