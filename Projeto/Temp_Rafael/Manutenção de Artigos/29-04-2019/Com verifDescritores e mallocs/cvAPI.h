#ifndef cvAPI_h
#define cvAPI_h

#include <string.h> //strlen - strcpy - strtok - strcmp
#include <unistd.h> //system calls
#include <fcntl.h> //file descriptor
#include <stdlib.h> //atof
#include <stdio.h>	//sprintf
#include "errors.h"

/*
	Estrutura do artigo no ficheiro artigos
*/
typedef struct ArtigoF *ArtigoFile;


/*
	Estrutura generica do artigo
*/
typedef struct Artigo *Artigo;


/*
	Estrutura de uma Venda no ficheiro Vendas
*/
typedef struct Vendas *Venda;

/*
	Faz a leitura, caracter a caracter, de um descritor de ficheiros e para a leitura quando deteta um '\n'
*/
ssize_t cvReadln(int fildes, void *buf, size_t nbyte);

void atualizaStock(char* cod, char* qt);

int cvGetStock(char* id);

float getPreco(char* id);

Venda criaStructVenda(char* idArt, char* quant);

/*
	Vai buscar uma venda numa determinada posição
	O objetivo desta função não é explorar a necessidade 
	de buscar uma venda pela sua posição do ficheiro. 
	A necessidade desta função é apenas para confirmar, 
	durante os testes á função, se esta está a guardar corretamente os dados
*/
Venda getVenda(char* x);

void viewVenda(Venda x);

void getStockAndPrice(char* id);

void cvMenuComandos(char* buffer);

#endif
