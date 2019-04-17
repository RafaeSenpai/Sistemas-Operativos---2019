/*CODIGO FUNIONAL*/


#include <unistd.h>  //definições e declarações de chamadas
#include <fcntl.h> //definição modos de abertura de ficheiro
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "api.h"

int main(){
char buffer[1024];
int counter = 0;

	/*
		- Leitura do teclado para uma array
		- O que é lido para o arrray está dividido em 2 partes que são o nome do artigo e o preço do mesmo.
	*/
	if(read(0, buffer, 1024) < 0){
			/*
				Caso ocorra erro na leitura do stdin, é enviado para o stdout (terminal) uma notificação de 
				que não foi possivel proceder á gravação do conteudo no "buffer"
			*/
    		write(2, "Ocorreu um erro de leitura do artigo\n", 23);
	    	exit(0);
	}else{
		/*
			Verifica o tamanho do conteudo relevante da string
			Necessário por causa de estar a usar-se um buffer com um tamanho razoavel e haver a probabilidade 
			de não ser completamente utilizado
		*/
		for(counter=0;buffer[counter]!='\n';counter++);

		if(counter==0){
			main();
		}else{

			if(addArtigo(buffer)<0){
				write(2,"Erro na gravação do artigo no ficheiro ARTIGOS.txt!\n",51);
			}else if(addArtigo(buffer)==0){
				write(2,"Erro na gravação do nome do artigo no ficheiro STRINGS.txt!\n",51);	
			}
		}
	return *buffer;

	}	
}

/*
ARRANJAR FORMA DE SE POSICIONAR NA ULTIMA LINHA DO FICHEIRO PARA ESTA SER LIDA E OBTER-SE DA 
MESMA LINHA OS COD DE ARTIGO, DE FORMA A QUE SE POSSA INCREMENTAR O ID NA PROXIMA INSERÇÃO DE 
ARTIGOS
*/