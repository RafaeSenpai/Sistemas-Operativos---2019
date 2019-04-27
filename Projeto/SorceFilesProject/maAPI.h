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


/*
	Faz a leitura, caracter a caracter, de um descritor de ficheiros e para a leitura quando deteta um '\n'
*/
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
	Cria estrutura de Artigo a ser guardada no ficheiro ARTIGOS.txt
	.nbArt: numero de bytes lidos até ao final do ficheiro ARTIGOS.txt
	.nbStr: numero de bytes lidos até ao final do ficheiro STOCKS.txt
*/
ArtigoFile criaStructArtigo(int nbArt, int nbStr, char* price);


/*
	Cria estrutura que armazena a informação relativa ao Stock de um determinado Artigo
	.nbArt: numero de bytes lidos até ao final do ficheiro ARTIGOS.txt
	        (posição, no momento da gravação do novo artigo, no ficheiro ARTIGOS.txt onde
	        se encontra a referencia ao nome do artigo no ficheiro STRINGS.txt)
	Os atributos desta estrutura são:
		- id_Artg (nbArt);
		- stock;
*/
Stock criaStructStock(int nbArt, int quantidade);


/*
	Dado o nome e o preço de artigo, é adicionada a informação do mesmo no ficheiro ARTIGOS.txt, nomeadamente
	os atributos, ID, nome e preço (guardados numa struct). Também é criado um ficheiro STRINGS.txt com o
	respetivo nome do produto e outro ficheiro com o respetivo stock do mesmo(este ultimo é guardado também
	na forma de uma struct).
	Os atributos da estrutura guardada em ARTIGOS.txt:
	-ID
	-edr_nome
	-preco

	Os atributos da estrutura guardada em STOCKS.txt:
	-id_Artigo
	-Stock
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
  Dado o código de um artigo e um preço edita o preço do artigo
*/
void editaPreco(char* cod, char* preco);


/*
	Dado o ID de um artigo, devolve uma estrutura (generica) do artigo, isto é devolve
	uma estrutura com os seguintes atributos:
	-ID;
	-Nome;
	-Preço
	-Stock.
*/
Artigo getArtigo(char* id);


void editaNome(char* id, char* nome);



#endif
