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
	// CRIAR os ficheiros primeiro com as permissões corretas
	int fsaida = open("saida1.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IWUSR | S_IRUSR );
	int ferros = open("erros1.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IWUSR | S_IRUSR );
	int fabrir = open("/etc/passwd", O_RDONLY);// aqui tu só queres ler portanto nao meets as outras permissões
	//Crias cópias para o stdin,portanto 0 na 2º variável do dup2(eu agora meti 2,0,1 mas deve estar mal.pus porque 2 é error,1 é output e 0 input.Mas é pra confirmar
	if(dup2(ferros,2)<0){
		printf("Erro ao riderecionar ficheiro de sderr\n");
	}
	if(dup2(fabrir,0)<0){
		write(ferros,"Erro ao riderecionar ficheiro de stdin\n",40);
		//printf("Erro ao riderecionar ficheiro de stdin\n");
	}
	if(dup2(fsaida,1)<0){
		write(ferros,"Erro ao riderecionar ficheiro de stdout\n",41);
		//printf("Erro ao riderecionar ficheiro de stdout\n");
	}
	
	// aqui tu só queres mandar para fsaida os dados de fabrir para escrever a fsaida
	// o n vai ficar com o resultado de ler(read) o ficheiro fabrir e metendo o "char" em c
	// a primeira variável é 0,1,2 que se refere ao standar input,output e error;
	// tu queres ler do ficheiro fabrir
	while((n=read(fabrir,&c,1))>0){
		write(fsaida,&c,n);
	}
	// no final tens que fechar so ficheiros todos

	close(fsaida);
	close(ferros);
	close(fabrir);

	return 0;
}
