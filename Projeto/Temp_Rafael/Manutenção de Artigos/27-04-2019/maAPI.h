#ifndef maAPI_h
#define maAPI_h

#define ERROR_1 "Erro de descritor de ficheiro na função ma -> inserArtigo(...)!\nAo abrir o ficheiro STRINGS.txt\n"
#define ERROR_2 "Erro de descritor de ficheiro na função ma -> inserArtigo(...)!\nAo abrir o ficheiro ARTIGOS.txt\n"
#define ERROR_3 "Erro de descritor de ficheiro na função ma -> inserArtigo(...)!\nAo abrir o ficheiro STOCKS.txt\n"
#define ERROR_4 "Erro de descritor de ficheiro na função ma -> getNome(...)!\nAo abrir o ficheiro STRINGS.txt\n"
#define ERROR_5 "Erro de descritor de ficheiro na função ma -> getStock(...)!\nAo abrir o ficheiro STOCKS.txt\n"
#define ERROR_6 "Erro de descritor de ficheiro na função ma -> getArtigo(...)!\nAo abrir o ficheiro ARTIGOS.txt\n"
#define ERROR_7 "Erro de descritor de ficheiro na função ma -> editaNome(...)!\nAo abrir o ficheiro ARTIGOS.txt ou STRINGS.txt\n"
#define ERROR_8 "Erro de descritor de ficheiro na função ma -> editaPreco(...)!\nAo abrir o ficheiro ARTIGOS.txt\n"
#define ERROR_9 "Erro de descritor de ficheiro na função cv -> atualizaStock(...)!\nAo abrir o ficheiro STOCKS.txt\n"
#define ERROR_10 "Erro de descritor de ficheiro na função cv -> getStock(...)!\nAo abrir o ficheiro STOCKS.txt\n"
#define ERROR_11 "Erro de descritor de ficheiro na função cv -> getPreco(...)!\nAo abrir o ficheiro ARTIGOS.txt\n"
#define ERROR_12 "Erro de alocação de memória!\nNa função cv -> atualizaStock(...)\nchar* msg\n"
#define ERROR_13 "Erro de alocação de memória!\nNa função cv -> getStock(...)\nchar* msg\n"
#define ERROR_14 "Erro de alocação de memória!\nNa função cv -> getPreco(...)\nchar* msg\n"
#define ERROR_15 "Erro de alocação de memória!\nNa função cv -> atualizaStock(...)\nchar* msg\n"
#define ERROR_16 "Erro de alocação de memória!\nNa função ma -> criaStructArtigo(...)\nArtigoFile new\n"
#define ERROR_17 "Erro de alocação de memória!\nNa função ma -> insereArtigo(...)\nArtigoFile newArt\n"
#define ERROR_18 "Erro de alocação de memória!\nNa função ma -> insereArtigo(...)\nchar* id\n"
#define ERROR_19 "Erro de alocação de memória!\nNa função ma -> getNome(...)\nchar* nome\n"
#define ERROR_20 "Erro de alocação de memória!\nNa função ma -> viewArtigo(...)\nchar* msg\n"
#define ERROR_21 "Erro de alocação de memória!\nNa função ma -> getArtigo(...)\nArtigoFile newArtF\n"
#define ERROR_22 "Erro de alocação de memória!\nNa função ma -> menuComandos(...)\nchar* msg\n"
#define ERROR_23 "Erro de alocação de memória!\nNa função ma -> getArtigo(...)\nArtigoFile art\n"

#include <string.h> //strlen - strcpy - strtok
#include <unistd.h> //system calls
#include <fcntl.h> //file descriptor
#include <stdlib.h> //atof
#include <stdio.h>	// sprintf



/*
	Responsavel por encaminhar as mensagens de erro para as devidas funções.
	Foi criado a pensar em facilitar a deteção de algum erro durante os testes com varios clientes em simultaneo
*/
void errors(char *msg);

/*
	Estrutura do artigo que é guardada no ficheiro artigos
*/

typedef struct ArtigoF *ArtigoFile;


/*
	Estrutura generica do artigo.
	É constituida por todos os atributos de um artigo sem ser por qualquer tipo de referenciação.
*/
typedef struct Artigo *Artigo;



/*
	Faz a leitura, caracter a caracter, de um descritor de ficheiros e para a leitura quando deteta um '\n'
*/
ssize_t readln(int fildes, void *buf, size_t nbyte);




/*
	Dado o nome e o preço de artigo, é adicionada a informação do mesmo no ficheiro ARTIGOS.txt, nomeadamente 
	os atributos, ID, nome e preço (guardados numa struct). Também é criado um ficheiro STRINGS.txt com o 
	respetivo nome do produto e outro ficheiro com o respetivo stock do mesmo.
	Os atributos da estrutura guardada em ARTIGOS.txt:
	-ID
	-edr_nome
	-preco
*/
void insereArtigo(char* nome,char* preco);


/*
	Dado a posição do nome de um artigo no ficheiro STRINGS.txt, vai buscar o nome (string) desse artigo ao ficheiro STRINGS.txt
*/
char* getNome(int id);


/*
	Dado o ID de uma artigo devolve o stock do mesmo.
	Se não existir o ID inserido retorna 0.
*/
int getStock(int id);


/*
	Dado o ID de um artigo, devolve uma estrutura (generica) do artigo, isto é devolve 
	uma estrutura com os seguintes atributos:
	-ID;
	-Nome;
	-Preço
	-Stock.
	
	A justificação do porquê devolver uma estrutura generica do artigo é porque esta torna possivel ao utilizador, que não esteja contextualizado 
	com a estrutura de dados ARTIGO que é guardada em ficheiro, uma facil leitura de todas as caracteristicas do produto.
*/
Artigo getArtigo(char* id);


void editaNome(char* id, char* nome);


void menuComandos(char* buffer);

#endif