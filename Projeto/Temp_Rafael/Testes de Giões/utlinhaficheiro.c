/*CODIGO FUNIONAL*/


#include <unistd.h>  //definições e declarações de chamadas
#include <fcntl.h> //definição modos de abertura de ficheiro
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
/*	
FUNÇÃO: 1
	- Remove todos os espaços a mais existentes na string inserida;
	- Devolve o tamanho da string e caso esse mesmo tamanho seja igual a zero a string será 
	  considerada invalida
*/


/*
FUNÇÃO: 2
	Verifica se se trata de uma linha valida (verifica se se trata de uma string apenas com 
	caracteres de 'A' a 'Z' e de 'a' a 'z' e espaços entre as palavras)
*/

int main(){
int ficheiroARTIGOS;
int counter = 0;
char strDate[24];
strDate[0]='\0';
	/*
		Abrir ficheiro
	*/
	ficheiroARTIGOS = open("ARTIGOS.txt", O_CREAT | O_APPEND | O_RDWR, 0777);

	/*
		Verifica a integridado do ficheiro e sua ligação
	*/
	if(ficheiroARTIGOS < 0){
        	return -1;
	}



	/*
		Leitura do teclado para uma array
	*/
	char buffer[1024];
	if(read(0, buffer, 1024) < 0){
			/*
				Envia para o stdou uma notificação de que não foi possivel proceder á gravação 
				do conteudo do stdin no "buffer"
			*/
    		write(2, "Ocorreu um erro de leitura do artigo\n", 23);
	    	exit(0);
	}else{
		/*
			Verifica o tamanho do conteudo relevante da string
		*/
		for(counter=0;buffer[counter]!='\n';counter++);
		/*
			- Escrita do conteudo relevante do array no ficheiro, i é, tudo até ao \n pois a partir
			  daí é "lixo" da memória;
			- countTemp + 1: Para capturar o \n e assim já mudar de linha no ficheiro automaticamente
		*/
		if(counter==0){
			main();
		}else{
			time_t data_atual = time(&data_atual);
			
			/*
				Colocar aqui mesmo uma função de contagem de linhas no ficheiro artigos e o 
				resultado devolvido será incrmentado em 1 unidade e usado como ID do artigo a inserir
			*/


			/*
				ctime: converte a data atual numa string
			*/
			//concatenar a string da data com um ifen para mais tarde concatenar tb com o ID do artigo
		

			strcat(strDate,ctime(&data_atual));//<-ctime: converte a data atual para string
			strDate[strlen(strDate)-1]='\0';
			strcat(strDate,"--->");
			write(ficheiroARTIGOS, strDate, 28);// <---28 = strlen(strDate) + strlen("-->")
			write(ficheiroARTIGOS, buffer, counter + 1); /* <--counter + 1: para que adicione o '\n' e 
																			o proximo artigo seja 
																			escrito na proxima linha! */
			/*
				Termina a ligação com o ficheiro
			*/
			close(ficheiroARTIGOS);
		}
		return *buffer;

	}	
}

/*
ARRANJAR FORMA DE SE POSICIONAR NA ULTIMA LINHA DO FICHEIRO PARA ESTA SER LIDA E OBTER-SE DA 
MESMA LINHA OS COD DE ARTIGO, DE FORMA A QUE SE POSSA INCREMENTAR O ID NA PROXIMA INSERÇÃO DE 
ARTIGOS
*/
