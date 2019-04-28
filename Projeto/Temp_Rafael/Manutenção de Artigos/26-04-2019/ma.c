#include "maMenu.h"

int main(){
char buffer[1024];

	/*
		- Leitura do teclado para uma array;
		- O que é lido para o arrray está dividido em 3 partes que são a instrução, o nome do artigo e o preço do mesmo;
		- Instrucao readln fica com o conteudo da linha lida do terminal. Se a linha capturada do terminal
		contiver espaços a mais entre os diversos parametros, tais espaços serão previamente 
		reduzidos a um só espaço pela função remSpc, desta forma torna-se mais facil a interpretação dos diversos 
		comandos.
	*/
	while(readln(0,buffer,1024)){
		menuComandos(remSpc(buffer));
	}

return 0;
}