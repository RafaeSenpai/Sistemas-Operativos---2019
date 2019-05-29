#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/unistd.h>


int main(){
int canal = mkfifo("./canais/firstFifo",0666);

	if(canal<0){
		perror("Ocorreu um erro na criação do canal de comunicação!\n");
		return 1;
	}
	
return 0;
}
