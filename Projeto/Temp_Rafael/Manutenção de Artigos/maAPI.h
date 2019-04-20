#ifndef maAPI_h
#define maAPI_h
#include <ctype.h> //isdigit
#include <stdlib.h> //atof
#include <string.h> //strlen
#include <unistd.h> //system calls
#include <stdio.h>
#include "maPARSERS.h"

/*
Estrutura de artigo 
*/
struct Artigo
{
    int id;
    char *nome;
    float preco;
    float stock;
} Artigo;



/*
	Estrutura do artigo no ficheiro artigos
*/
typedef struct ArtigoF
{
    int id;
    int ind_nome; 
    float preco;
} *ArtigoFile;


/*
	EStrutura de uma venda
*/
struct Venda
{
	char idArt;
	float quantidade;
	float totalVenda;
} Venda;



ssize_t readln(int fildes, void *buf, size_t nbyte);
int verifDescrt(int descArtig, int descStr);
char* getNome(int *ficheiro, int idArtigo);
float getStock(int *ficheiro,int idArtigo);
float getPrice(int *ficheiro, int idArtigo);
void insereArtigo(char* nome,char* preco);
void editName(char* id, char* nome);
void editPrice(char* id, char* preco);
void callCommands(char* buffer);
#endif
