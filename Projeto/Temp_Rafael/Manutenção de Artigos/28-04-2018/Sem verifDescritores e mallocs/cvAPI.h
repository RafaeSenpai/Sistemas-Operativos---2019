#ifndef cvAPI_h
#define cvAPI_h

#include <string.h> //strlen - strcpy - strtok
#include <unistd.h> //system calls
#include <fcntl.h> //file descriptor
#include <stdlib.h> //atof
#include <stdio.h>	//sprintf

/*
	Estrutura do artigo no ficheiro artigos
*/
typedef struct ArtigoF *ArtigoFile;


/*
	Estrutura generica do artigo
*/
typedef struct Artigo *Artigo;




/*
	Faz a leitura, caracter a caracter, de um descritor de ficheiros e para a leitura quando deteta um '\n'
*/
ssize_t readln(int fildes, void *buf, size_t nbyte);
void atualizaStock(char* cod, char* qt);
void getStock(char* id);
void getPrice(char* id);
void getStockAndPrice(char* id);
void menuComandos(char* buffer);

#endif
