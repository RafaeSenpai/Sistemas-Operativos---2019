#include "api.h"

int main(){
char buffer[1024];

	/*
		Instrucao readln fica com o conteudo da linha lida do terminal até encontrar um \n
	*/
	while(readln(0,buffer,1024)){
		maMenuComandos(buffer);
	}

return 0;
}