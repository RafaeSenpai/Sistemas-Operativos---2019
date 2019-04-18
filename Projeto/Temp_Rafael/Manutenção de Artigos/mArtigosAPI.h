#ifndef maArtigosAPI_h
#define maArtigosAPI_h
#include <ctype.h> //isdigit
#include <stdlib.h> //atof
#include <string.h> //strlen
#include <unistd.h> //system calls
#include <stdio.h>

struct Artigo
{
    char id;
    char *nome;
    float preco;
    float stock;
    int ref_nome;
} Artigo;

struct Venda
{
	char idArt;
	float quantidade;
	float totalVenda;
} Venda;





//char* getNome(int *ficheiro, int idArtigo);
//int getStock(int *ficheiro,int idArtigo);
int verifDescrt(int *descArtig, int *descStr);
char* takePrecoBuff(char* buffer);
char* takeNomeBuff(char* buffer);
char* remSpc(char* buffer);
char* insereArtigo(char* nome,char* preco);
char takeInstBuff(char* buffer);


#endif
