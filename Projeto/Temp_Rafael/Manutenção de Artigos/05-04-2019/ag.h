#ifndef agAPI_h
#define agAPI_h
#include "notifications.h"
#include <fcntl.h>
#include <unistd.h> //system calls
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*
	Estrutura de uma Venda no ficheiro Vendas
*/
typedef struct Vendas *Venda;


/*
	Dado um descritor de ficheiro, neste caso, do ficheiro VENDAS.txt, devolve o numero de vendas existente nesse ficheiro
*/
int getNumVendas(int fd);


/*
	Esta função devolve uma string que apresenta a data e hora f cinalizada com ".txt"
	A string devolvida será usada para criar o nome do ficheiro a ser usado para o descritor
*/
char* nameFileAgregation();


/*
	Cria uma estrutura de venda com o id do artigo, a soma de todas as quantidades vendidas desse artigo e o resultado obtido da soma de todos os totais de venda de todas as vendas desse artigo.
	A obtenção destes resultados a serem guardados na estrutura é feita sobre o ficheiro VENDAS.txt
*/
Venda agCriaStructVenda(int idArtigo, float qtdTotalVendas, float totalVendas);


/*
	Cria uma venda com os valores totais do artigo após a procura de todas as suas vendas no ficheiro VENDAS.txt
	A venda devolvida por esta função será guardada no ficheiro de agregação.

	A função recebe o id do artigo a agregar e o numero de vendas existente no ficheiro VENDAS.txt, este ultimo valor será calculado na função que a chamar.
*/
Venda saleToAgregation(int idArt, int numVendas);


/*
	Dado um ID de artigo, um descritor de ficheiro e o numero de vendas(previamente calculado, de forma a não exigir muito trabalho computacional) 
	verificar se nesse descritor existe o artigo com o dado ID. 
	--------É passado como parametro o descrior de ficheiro porque desta forma posso usar esta a mesma função quer para procurar a existencia de um artigo 
	--------quer nas vendas registadas no ficheiro VENDAS.txt, quer no ficheiro de agregação.

	OBS: - O ficheiro de agregação terá que ser previamente criado
		 - Ao passar os parametros para esta função, o parametro id, deve ser previamente convertido para inteiro, atoi()
		 - A prcura é feita no ficheiro de agregações.
		 - devolve 1 caso o artigo exista ou zero caso não exista.
*/
int existArtInAggregation(int fd, int id, int numArtig);




/*
	EM principio nao sera passado nenhum parametro a esta função
*/
void geraAgregacao();


/*
	Imprimir toda a agregação atual
*/
void viewVendaAggregation(Venda sale);



/*
	Imprimir toda a agregação no ecra
*/
void seeAllAggregation(int fd);



#endif