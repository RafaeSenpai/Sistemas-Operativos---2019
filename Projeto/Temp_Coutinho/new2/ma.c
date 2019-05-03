#include "API.h"

int main(){
char buffer[1024];

	/*
		Instrucao readln fica com o conteudo da linha lida do terminal até encontrar um \n
	*/
	while(readLine(0,buffer,1024)){
		menuComandosMA(buffer);
	}

return 0;
}
