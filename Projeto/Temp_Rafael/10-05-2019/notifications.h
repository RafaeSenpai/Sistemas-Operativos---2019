#ifndef nOTIFICATIONS_h
#define nOTIFICATIONS_h
#include "api.h"


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
#define ERROR_35 "Erro de descritor de ficheiro na função ag -> main()!\nNão pode ser feita a agregação porque o ficheiro VENDAS.txt ainda nao se encontra criado!\n\n"
#define ERROR_36 "Erro de alocação de memória!\nNa função ag -> gerarLogFile()\nErro ao gerar a estrutura de log.\nnewLog\n\n"
#define ERROR_37 "Erro de descritor de ficheiro na função ag -> gerarLogFile()!\nAo abrir o ficheiro log\n\n"
#define ERROR_38 "Erro de descritor de ficheiro na função ag -> getAggregationFileName()!\nAo abrir o ficheiro log\n\n"
#define ERROR_39 "Erro de alocação de memória!\nNa função ag -> getAggregationFileName()\nnomeFicheiro\n\n"
#define ERROR_40 "Erro de descritor de ficheiro na função ag -> getLogStatus()!\nAo abrir o ficheiro log\n\n"
#define ERROR_41 "Erro de descritor de ficheiro na função ag -> getLogLastAggregateSale()!\nAo abrir o ficheiro log\n\n"
#define ERROR_42 "Erro de descritor de ficheiro na função ag -> setLogNewAggregationFileName()!\nAo abrir o ficheiro log\n\n"
#define ERROR_43 "Erro de alocação de memória!\nNa função ag -> setLogNewAggregationFileName()\n LogFile new\n\n"
#define ERROR_44 "Erro de descritor de ficheiro na função ag -> setNewStatus()!\nAo abrir o ficheiro log\n\n"
#define ERROR_45 "Erro de descritor de ficheiro na função ag -> setLastAggregateSale()!\nAo abrir o ficheiro log\n\n"
#define ERROR_46 "Erro de descritor de ficheiro recebido na função ag -> getNumVendas()!\nAo aceder ao conteudo do ficheiro fdVendas\n\n"
#define ERROR_47 "Erro de descritor de ficheiro na função ag -> runAggregation()!\nAo abrir o ficheiro de agregação recebido como parametro\naggFileName\n\n"
#define ERROR_48 "Erro de descritor de ficheiro na função ag -> runAggregation()!\nAo abrir o ficheiro vendas\n\n"
#define ERROR_49 "Erro de alocação de memória!\nNa função ag -> runAggregation()\nVenda sale\n\n"
#define ERROR_50 "Erro de descritor de ficheiro na função ag -> seeContentLog()\nAo abrir o ficheiro log\nNão existe ficheiro log\n\n"
#define ERROR_51 "Erro de alocação de memória!\nNa função ag -> seeContentLog()\nLogFile log\n\n"
#define ERROR_52 "Erro de alocação de memória!\nNa função ag -> seeContentLog()\nChar* msg\n\n"


#define MSG_1 "O ID do artigo inserido não existe!\n\n"
#define MSG_2 "O ID do artigo do qual quer fazer alteração do stock não existe!\n\n"
#define MSG_3 "Não existe a venda pedida!\n\n"
#define MSG_4 "Opção inválida!\nInsira novo comando:\n\n"
#define MSG_5 "STOCK: O ID do artigo inserido não existe!\n\n"
#define MSG_6 "PRECO: O ID do artigo inserido não existe!\n\n"
#define MSG_7 "Artigo alterado com sucesso!\n\n"
#define MSG_8 "NOME: O ID do artigo inserido não existe!\n\n"
#define MSG_9 "Deixou de ter stock deste artigo!\n\n"
#define MSG_10 "Não existe nenhum ficheiro de vendas para agregar!\n\n"


void catchMessage(char *msg);
#endif