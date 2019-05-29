#ifndef apiERRORS_h
#define apiERRORS_h

#define ERROR_1 "Erro de descritor de ficheiro na função ma -> inserArtigo(...)!\nAo abrir o ficheiro STRINGS.txt\n\n"
#define ERROR_2 "Erro de descritor de ficheiro na função ma -> inserArtigo(...)!\nAo abrir o ficheiro ARTIGOS.txt\n\n"
#define ERROR_3 "Erro de descritor de ficheiro na função ma -> inserArtigo(...)!\nAo abrir o ficheiro STOCKS.txt\n\n"
#define ERROR_4 "Erro de descritor de ficheiro na função ma -> getNome(...)!\nAo abrir o ficheiro STRINGS.txt\n\n"
#define ERROR_5 "Erro de descritor de ficheiro na função ma -> getStock(...)!\nAo abrir o ficheiro STOCKS.txt\n\n"
#define ERROR_6 "Erro de descritor de ficheiro na função ma -> getArtigo(...)!\nAo abrir o ficheiro ARTIGOS.txt\n\n"
#define ERROR_7 "Erro de descritor de ficheiro na função ma -> editaNome(...)!\nAo abrir o ficheiro ARTIGOS.txt ou STRINGS.txt\n\n"
#define ERROR_8 "Erro de descritor de ficheiro na função ma -> editaPreco(...)!\nAo abrir o ficheiro ARTIGOS.txt\n\n"
#define ERROR_9 "Erro de descritor de ficheiro na função cv -> atualizaStock(...)!\nAo abrir o ficheiro STOCKS.txt\n\n"
#define ERROR_10 "Erro de descritor de ficheiro na função cv -> getStock(...)!\nAo abrir o ficheiro STOCKS.txt\n\n"
#define ERROR_11 "Erro de descritor de ficheiro na função cv -> getPreco(...)!\nAo abrir o ficheiro ARTIGOS.txt\n\n"
#define ERROR_12 "Erro de alocação de memória!\nNa função cv -> atualizaStock(...)\nchar* msg\n\n"
#define ERROR_13 "Erro de alocação de memória!\nNa função cv -> getStock(...)\nchar* msg\n\n"
#define ERROR_14 "Erro de alocação de memória!\nNa função cv -> getPreco(...)\nchar* msg\n\n"
#define ERROR_15 "Erro de alocação de memória!\nNa função cv -> atualizaStock(...)\nchar* msg\n\n"
#define ERROR_16 "Erro de alocação de memória!\nNa função ma -> criaStructArtigo(...)\nArtigoFile new\n\n"
#define ERROR_17 "Erro de alocação de memória!\nNa função ma -> insereArtigo(...)\nArtigoFile newArt\n\n"
#define ERROR_18 "Erro de alocação de memória!\nNa função ma -> insereArtigo(...)\nchar* id\n\n"
#define ERROR_19 "Erro de alocação de memória!\nNa função ma -> getNome(...)\nchar* nome\n\n"
#define ERROR_20 "Erro de alocação de memória!\nNa função ma -> viewArtigo(...)\nchar* msg\n\n"
#define ERROR_21 "Erro de alocação de memória!\nNa função ma -> getArtigo(...)\nArtigoFile newArtF\n\n"
#define ERROR_22 "Erro de alocação de memória!\nNa função ma -> menuComandos(...)\nchar* msg\n\n"
#define ERROR_23 "Erro de alocação de memória!\nNa função ma -> getArtigo(...)\nArtigoFile art\n\n"

#include <unistd.h> //system calls
#include <string.h> //strlen - strcpy - strtok
#include <stdlib.h> //exit()



/*
	Responsavel por encaminhar as mensagens de erro para as devidas funções.
	Foi criado a pensar em facilitar a deteção de algum erro durante os testes com varios clientes em simultaneo
*/
void catchError(char *msg);

#endif