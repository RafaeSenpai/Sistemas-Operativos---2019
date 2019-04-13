#include <unistd.h>  //definições e declarações de chamadas
#include <fcntl.h> //definição modos de abertura de ficheiro

int main(){

FILE *ficheiro;
/*
O_RDONLY	| Open the file so that it is read only.
O_WRONLY	| Open the file so that it is write only.
O_RDWR		| Open the file so that it can be read from and written to.
O_APPEND	| Append new information to the end of the file.
O_TRUNC		| Initially clear all data from the file.
O_CREAT		| If the file does not exist, create it. If the O_CREAT option is used, then you must include the third parameter.
O_EXCL		| Combined with the O_CREAT option, it ensures that the caller must create the file. If the file already exists, the call will fail.

fonte: http://codewiki.wikidot.com/c:system-calls:open
*/

	ficheiro = open("dados.txt",O_CREAT,O_RDWR);

	return ficheiro;

}