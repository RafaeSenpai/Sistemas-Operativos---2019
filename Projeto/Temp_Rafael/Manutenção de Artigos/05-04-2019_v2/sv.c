#include "sv.h"
#include "cv.h"



int main(){

//esta main ira ler do pipe a ordem enviada pelo cliente de vendas e manda-la para o cvMenuComandos para que seja interpretada a devida funcionalidade pedida pelo cliente de vendas
//,logo o codigo qu se encontra a baixo não servirá de nada
	

char buffer[1024];

	/*
		Instrucao readln fica com o conteudo da linha lida do terminal até encontrar um \n
	*/
	while(cvReadln(0,buffer,1024)){
		cvMenuComandos(buffer);
	}

return 0;
}