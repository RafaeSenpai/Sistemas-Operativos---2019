#include "mArtigosAPI.h"

int main(){
char buffer[1024];
//char* buff;


	/*
		- Leitura do teclado para uma array
		- O que é lido para o arrray está dividido em 2 partes que são o nome do artigo e o preço do mesmo.
	*/
	if(read(0, buffer, 1024) < 0){
    		write(2, "Ocorreu um erro de leitura do stdin (teclado) para o buffer!\n", 60);
	    	exit(0);
	}else{
		callCommands(buffer);
		free(buffer);
		
	}
return 0;
}