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
int ficheiroSTRINGS;
int counter = 0;
char linhaArtigo[24];
linhaArtigo[0]='\0';
	/*
		Abrir ficheiro
	*/
	ficheiroARTIGOS = open("ARTIGOS.txt", O_CREAT | O_APPEND | O_RDWR, 0777);
	ficheiroSTRINGS = open("STRINGS.txt", O_CREAT | O_APPEND | O_RDWR, 0777);
	/*
		Verifica a integridado do ficheiro e sua ligação
	*/
	if(ficheiroARTIGOS < 0 && ficheiroSTRINGS < 0){
        	return -1;
	}



	/*
		Leitura do teclado para uma array

		o que é lido para o arrray está dividido em 2 partes que são o nome do artigo e o preço do mesmo.

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

		if(counter==0){
			main();
		}else{
			char preco[1024];
			char nomeArtigo[1024];
			int j;
			int i;
			
			for(j=0,i=0; buffer[i]!='\n'; i++){
				if( isalpha(buffer[i]) || buffer[i]<=' '){
					nomeArtigo[j]=buffer[i];
					j++;
				}
			}
			nomeArtigo[j-1]='\n';


			write(ficheiroSTRINGS, nomeArtigo, strlen(nomeArtigo)); /* <--- counter + 1: para que adicione o '\n' e 
																				o proximo artigo seja 
																				escrito na proxima linha! */
			
			


			/*
				Captura do buffer o preço do artigo para uma variavel, para mais terde essa mesma variavel 
				ser adicionada á linha do artigo
				
				NOTA: Este metodo de captura do preço terá que ser alterado completamente para passar a obter
				o preço atravez do numero da posição de argumentos passados á função
			*/
			
			for(j=0,i=0; buffer[i]!='\n'; i++){
				if((buffer[i]>='0' && buffer[i]<='9') || (buffer[i]=='$' || buffer[i]==',')){
					preco[j]=buffer[i];
					j++;
				}
			}
			preco[j]='\n';

			/*
				- Escrita do conteudo relevante do buffer no ficheiro, i é, tudo até ao \n pois a partir
				  daí é "lixo" da memória, salvaguarda-se assim a gravação correta do nome do artigo 
				  independentemente do seu tamanho (até 1024 caracteres);
				- countTemp + 1: Para capturar o \n e assim já mudar de linha no ficheiro automaticamente
			*/
				time_t data_atual = time(&data_atual);
				
			/*
				Colocar aqui mesmo uma função de contagem de linhas no ficheiro artigos e o 
				resultado devolvido será incrmentado em 1 unidade e usado como ID do artigo a inserir
			*/


			/*
				ctime: converte a data atual numa string
			*/
		
			char numLinha[1024];
			
			sprintf(numLinha, "%d", numLinesSTRINGS("STRINGS.txt"));/* <-- converte o inteiro que representa 
																				  o numero da linha com nome do artigo para string */
			strcat(numLinha,"_");
			strcat(linhaArtigo,numLinha); /* <-- Adiciona o numero da linha como parte da referencia do artigo*/
			//formatar a data para um formato mais pequeno
			strcat(linhaArtigo,ctime(&data_atual));/* <------------- ctime: converte a data atual para string 
																	 		(string de tamanho fixo) OBS: adiciona '\n' no final da 
																	 		string gerada*/
			linhaArtigo[strlen(linhaArtigo)-1]='\0';/* <---------------- para forçar a NÃO mudança de linha */
			strcat(linhaArtigo,"-->"); /* <-----Separador '-->' é usado para distinção do ID do produto com o numero da linha onde se 
												encontra o nome do produto(no ficheiro STRINGS.txt)*/
			numLinha[strlen(numLinha)-1]='\0';/* <--------- Para retirar da string da linha do artigo o underscore adicionado anteriormente*/
			strcat(linhaArtigo,numLinha);
			strcat(linhaArtigo,"-->");/* <-------------------------------para ocorrer a mudança de linha*/
			strcat(linhaArtigo,preco);
			write(ficheiroARTIGOS, linhaArtigo, strlen(linhaArtigo));/* <------------ guarda no ficheiro ARTIGOS todo o conteudo da linhaArtigo*/
			



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

/*Contador de linhas no ficheiro STRINGS para que o mesmo numero de linha seja usado no ficheiro 
ARTIGOS.txt como nome do artigo*/
