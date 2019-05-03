#include "cv.h"

int main(){
char buffer[1024];

	/*
		Instrucao readln fica com o conteudo da linha lida do terminal até encontrar um \n
	*/
	while(cvReadln(0,buffer,1024)){
		cvMenuComandos(buffer);
	}

return 0;
}