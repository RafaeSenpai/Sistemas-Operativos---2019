#ifndef cvAPI_h
#define cvAPI_h

#include <string.h> //strlen - strcpy
#include <unistd.h> //system calls
#include <fcntl.h> //file descriptor
#include <stdlib.h> //atof
#include <stdio.h>	//printfs

/*
	Estrutura do artigo no ficheiro artigos
*/
typedef struct ArtigoF
{
    int id;
    int edr_nome; 
    float preco;
} *ArtigoFile;


/*
	Estrutura generica do artigo
*/
typedef struct Artigo{
	int id;
	char* nome;
	float preco;
	int stock;
} *Artigo;


/*
	Estrutura da informação relativa ao stock de um Artigo
	.id_Artigo: ID do artigo
	.stock: Stock relativo ao artigo
*/
typedef struct Stock{
	int id_Artg;
	int stock;
} *Stock;



ssize_t readln(int fildes, void *buf, size_t nbyte);
void atualizaStock(char* cod, char* qt);
int getStock(char* id);
void getStockAndPrice(char* id);

#endif
