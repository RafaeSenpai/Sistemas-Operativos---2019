#ifndef header_h
#define header_h

#include <string.h> //strlen - strcpy - strtok - strcmp
#include <unistd.h> //system calls
#include <fcntl.h> //file descriptor
#include <stdlib.h> //atof
#include <stdio.h>	//sprintf
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "notifications.h"

typedef struct ArtigoF *ArtigoFile;

typedef struct Artigo *Artigo;

typedef struct Vendas *Venda;

char* fileReadLine(int fildes);

ssize_t readLine(int fildes, void *buf, size_t nbyte);

void atualizaStock(char* cod, char* qt);

Artigo getArtigo(char* id);

char* getNome(int edr_nome);

int getStockC(char* id);

int getStockI(int id);

float getPreco(char* id);

Venda criaStructVenda(char* idArt, char* quant);

Venda getVenda(char* x);

void viewArtigo(Artigo art);

void viewVenda(Venda x);

void getStockAndPrice(char* id);

void menuComandosMA(char* buffer);

void menuComandosCV(char* buffer);

#endif
