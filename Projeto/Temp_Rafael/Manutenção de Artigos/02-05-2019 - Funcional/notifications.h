#ifndef nOTIFICATIONS_h
#define nOTIFICATIONS_h

#define ERROR_1 "Erro de descritor de ficheiro na função ma -> inserArtigo(...)!\nAo abrir o ficheiro STRINGS.txt\n\n"
#define ERROR_2 "Erro de descritor de ficheiro na função ma -> inserArtigo(...)!\nAo abrir o ficheiro ARTIGOS.txt\n\n"
#define ERROR_3 "Erro de descritor de ficheiro na função ma -> inserArtigo(...)!\nAo abrir o ficheiro STOCKS.txt\n\n"
#define ERROR_4 "Erro de descritor de ficheiro na função ma -> getNome(...)!\nAo abrir o ficheiro STRINGS.txt\n\n"
#define ERROR_5 "Erro de descritor de ficheiro na função ma -> getStock(...)!\nAo abrir o ficheiro STOCKS.txt\n\n"
#define ERROR_6 "Erro de descritor de ficheiro na função ma -> getArtigo(...)!\nAo abrir o ficheiro ARTIGOS.txt\n\n"
#define ERROR_7 "Erro de descritor de ficheiro na função ma -> editaNome(...)!\nAo abrir o ficheiro STRINGS.txt\n\n"
#define ERROR_8 "Erro de descritor de ficheiro na função ma -> editaPreco(...)!\nAo abrir o ficheiro ARTIGOS.txt\n\n"
#define ERROR_9 "Erro de descritor de ficheiro na função cv -> atualizaStock(...)!\nAo abrir o ficheiro STOCKS.txt\n\n"
#define ERROR_10 "Erro de descritor de ficheiro na função cv -> getStock(...)!\nAo abrir o ficheiro STOCKS.txt\n\n"
#define ERROR_11 "Erro de descritor de ficheiro na função cv -> getPreco(...)!\nAo abrir o ficheiro ARTIGOS.txt\n\n"
#define ERROR_12 "Erro de alocação de memória!\nNa função cv -> atualizaStock(...)\nchar* msg\n\n"
#define ERROR_13 "Erro de alocação de memória!\nNa função cv -> getStock(...)\nchar* msg\n\n"
#define ERROR_14 "Erro de descritor de ficheiro na função ma -> editaNome(...)!\nAo abrir o ficheiro ARTIGOS.txt\n\n"
#define ERROR_15 "Erro de alocação de memória!\nNa função cv -> atualizaStock(...)\nchar* msg\n\n"
#define ERROR_16 "Erro de alocação de memória!\nNa função ma -> criaStructArtigo(...)\nArtigoFile new\n\n"
#define ERROR_17 "Erro de alocação de memória!\nNa função ma -> insereArtigo(...)\nArtigoFile newArt\n\n"
#define ERROR_18 "Erro de alocação de memória!\nNa função ma -> insereArtigo(...)\nchar* id\n\n"
#define ERROR_19 "Erro de alocação de memória!\nNa função ma -> getNome(...)\nchar* nome\n\n"
#define ERROR_20 "Erro de alocação de memória!\nNa função ma -> viewArtigo(...)\nchar* msg\n\n"
#define ERROR_21 "Erro de alocação de memória!\nNa função ma -> getArtigo(...)\nArtigoFile newArtF\n\n"
#define ERROR_22 "Erro de alocação de memória!\nNa função ma -> menuComandos(...)\nchar* msg\n\n"
#define ERROR_23 "Erro de alocação de memória!\nNa função ma -> getArtigo(...)\nArtigoFile art\n\n"
#define ERROR_24 "Erro de descritor de ficheiro na função cv -> atualizaStock(...)!\nAo abrir o ficheiro VENDAS.txt\n\n"
#define ERROR_25 "Erro de alocação de memória!\nNa função ma -> criaStructVenda(...)\nVenda newSale\n\n"
#define ERROR_26 "Erro de descritor de ficheiro na função cv -> getVenda(...)!\nAo abrir o ficheiro VENDAS.txt\n\n"
#define ERROR_27 "Erro de alocação de memória!\nNa função cv -> getVenda(...)\nVenda sale\n\n"
#define ERROR_28 "Erro de alocação de memória!\nNa função cv -> viewVenda(...)\nchar* msg\n\n"
#define ERROR_29 "Erro de alocação de memória!\nNa função ag -> agCriaStructVenda(...)\nVenda new\n\n"
#define ERROR_30 "Erro de descritor de ficheiro na função ag -> atualizaStock(...)!\nAo abrir o ficheiro VENDAS.txt\n\n"
#define ERROR_31 "Erro de alocação de memória!\nNa função ag -> nameFileAgregation()\nErro a gerar a string do nome para o ficheiro de agregação!\nchar* nametoAgregationFile\n\n"
#define ERROR_32 "Erro de descritor de ficheiro na função ag -> geraAgregacao(...)!\nAo abrir o ficheiro VENDAS.txt\n\n"
#define ERROR_33 "Erro de descritor de ficheiro na função ag -> geraAgregacao(...)!\nAo abrir o ficheiro de agregação, ''aggregationFile''.txt\n\n"
#define ERROR_34 "Erro de alocação de memória!\nNa função ag -> seeAllAggregation(...)\nVenda aux\n\n"


#define MSG_1 "O ID do artigo inserido não existe!\n"
#define MSG_2 "O ID do artigo do qual quer fazer alteração do stock não existe!\n"
#define MSG_3 "Não existe a venda pedida!\n"
#define MSG_4 "Opção inválida!\nInsira novo comando:\n"
#define MSG_5 "STOCK: O ID do artigo inserido não existe!\n"
#define MSG_6 "PRECO: O ID do artigo inserido não existe!\n"
#define MSG_7 "Artigo alterado com sucesso!\n"
#define MSG_8 "NOME: O ID do artigo inserido não existe!\n"
#define MSG_9 "Deixou de ter stock deste artigo!\n"

#include <unistd.h> //system calls
#include <string.h> //strlen - strcpy - strtok
#include <stdlib.h> //exit()



/*
	Responsavel por encaminhar as mensagens de erro para as devidas funções.
	Foi criado a pensar em facilitar a deteção de algum erro durante os testes com varios clientes em simultaneo
*/
void catchMessage(char *msg);

#endif