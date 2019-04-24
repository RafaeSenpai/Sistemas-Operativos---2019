#ifndef maAPI_h
#define maAPI_h

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



/*
	Verifica integridade dos descritores dos ficheiros e caso algum deles falhe 
	é devolvido um inteiro que identifica o respetivo descritor, porporcionando 
	desta forma a identificação do descritor que falhou!
	
	NOTA: Devolve 0 no caso de estar tudo conforme com os descritores

		exit(0) - indicates successful program termination & it is fully portable, While
		exit(1) - (usually) indicates unsucessful termination. However, it's usage is non-portable.
*/
int verifDescrt(int descArtig, int descStr);


/*
	Estrutura de Artigo a ser guardada no ficheiro ARTIGOS.txt
*/
ArtigoFile criaStructArtigo(int nbArt, int nbStr, char* name,char* price);



/*
	Dado o nome e o preço de artigo, é adicionada a informação do mesmo e 
	gerado o respetivo ID do produto no ficheiro ARTIGOS.txt e a string 
	correspondente ao nome do artigo é adicionada ao final do ficheiro STRINGS.txt 
*/
void insereArtigo(char* nome,char* preco);


/*
	Dado o ID de um artigo, vai buscar o nome desse artigo ao ficheiro STRINGS.txt
*/
char* getNome(int id);

/*
	Dado o ID de uma artigo devolve o stock do mesmo.
	Se existir o ID inserido não existir retorna 0.
*/
int getStock(int id);


/*
	Dado o ID de um artigo, devolve uma estrutura (generica) do artigo
*/
Artigo getArtigo(char* id);




#endif