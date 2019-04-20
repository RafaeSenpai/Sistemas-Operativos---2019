#include "maAPI.h"
#include "maPARSERS.h"

int main(){
char buffer[1024];

	/*
		- Leitura do teclado para uma array
		- O que é lido para o arrray está dividido em 2 partes que são o nome do artigo e o preço do mesmo.
	*/
	while(readln(0,buffer,1024)){
		callCommands(remSpc(buffer));
	}
return 0;
}