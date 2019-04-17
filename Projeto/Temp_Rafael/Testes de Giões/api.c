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
	Variaveis globais
*/
char linhaArtigo[1024];
char nomeArtigo[1024];
char preco[1024];


/*
	Conta numero de linhas no ficheiro STRINGS.txt
*/
int numLinesSTRINGS(char *ficheiro){
int numLinhas = 0;
char c;
FILE *ficheiroSTRINGS;

	ficheiroSTRINGS = fopen(ficheiro,"r");

	if(ficheiroSTRINGS!=NULL){
		while(c!=EOF){
			c = fgetc(ficheiroSTRINGS);
			if(c == '\n'){
				numLinhas++;
			}
		}

		fclose(ficheiroSTRINGS);
	}
return numLinhas;
}



/*
	Extrair do buffer o nome do artigo para que este seja adicionado ao ficheiro STRINGS.txt

	NOTA: Este metodo de captura do nome do artigo terá que ser alterado completamente para 
	passar a obter o preço atravez do numero da posição de argumentos passados á função
*/
char* extractNome(char* buffer){

int j, i;
	
	for(j=0,i=0; buffer[i]!='\n'; i++){
		if( isalpha(buffer[i]) || buffer[i]<=' '){
			nomeArtigo[j]=buffer[i];
			j++;
		}
	}
	nomeArtigo[j-1]='\n';

return nomeArtigo;
}


/*
	Captura do buffer o preço do artigo para uma string, para essa mesma variavel 
	ser adicionada á linha do artigo
	
	NOTA: Este metodo de captura do preço terá que ser alterado completamente para passar a 
	obter o preço atravez do numero da posição de argumentos passados á função
*/
char* extractPreco(char* buffer){
int i,j;

	for(j=0,i=0; buffer[i]!='\n'; i++){
		if((buffer[i]>='0' && buffer[i]<='9') || (buffer[i]=='$' || buffer[i]==',')){
			preco[j]=buffer[i];
			j++;
		}
	}
	preco[j]='\n';
return preco;
}


char* createLineArtigo(char* buffer){
char numLinha[1024];
linhaArtigo[0]='\0';

	/*
		Converte para string o inteiro referente ao numero da ultima linha no ficheiro STRINGS.txt
	*/
	sprintf(numLinha, "%d", numLinesSTRINGS("STRINGS.txt"));

	/*
		(*)
		Underscore nada mais é que um delimitador da identificação com o resto integrante do ID do artigo 
		strcat(dest,sorce);
	*/
	strcat(numLinha,"_");
	strcat(linhaArtigo,numLinha); 

	/*
		data_atual será usada como parte constituinte do ID que identificará o artigo
	*/
	time_t data_atual = time(&data_atual);

	//*******************************
	/*
		Criar um formato mais curto da data atual para ser adicionada ao ID do artigo
	*/
	//CODIGO
	//CODIGO
	//CODIGO

	/*
		ctime: converte a data atual numa string (string de tamanho fixo) 

		OBS: adiciona '\n' no final da string gerada
	*/
	strcat(linhaArtigo,ctime(&data_atual));
	/*
		Para forçar a NÃO mudança de linha por causa do anterior '\n'
	*/
	linhaArtigo[strlen(linhaArtigo)-1]='\0';

	/*
		Separador '-->' é usado para fazer a distinção do ID do produto com o numero da linha onde se 
		encontra o nome do produto(no ficheiro STRINGS.txt)

		Neste caso o numero da linha onde se encontra o nome do produto é a referencia usada como "nome"
		do artigo em questão
	*/
	strcat(linhaArtigo,"-->");

	/*
		Para retirar da string da linha do artigo o underscore adicionado anteriormente(*)
	*/
	numLinha[strlen(numLinha)-1]='\0';


	strcat(linhaArtigo,numLinha);
	strcat(linhaArtigo,"-->");
	/*
		Adiciona á linha do artigo o respetivo preço
	*/
	strcat(linhaArtigo,extractPreco(buffer));

return linhaArtigo;	
}




/*
	Adicionar artigos ao ficheiro ARTIGOS.txt e respectiva indexação ao ficheiro STRINGS.txt
*/
int addArtigo(char* buffer){
int ficheiroARTIGOS;
int ficheiroSTRINGS;

	/*
		Abrir ficheiros
	*/
	ficheiroSTRINGS = open("STRINGS.txt", O_CREAT | O_APPEND | O_RDWR, 0777);
	ficheiroARTIGOS = open("ARTIGOS.txt", O_CREAT | O_APPEND | O_RDWR, 0777);
	
	/*
		Verifica a integridade da ligação aos ficheiros
	*/
	if(ficheiroARTIGOS < 0){
		return -1;
	}else if(ficheiroSTRINGS < 0){
		return -2;
	}

	/*
		Guarda no ficheiro ARTIGOS.txt todo o conteudo da linhaArtigo
	*/
	write(ficheiroARTIGOS, createLineArtigo(buffer), strlen(createLineArtigo(buffer)));
	close(ficheiroARTIGOS);

	/*
		Guarda no ficheiro STRINGS.txt o nome do artigo
	*/
	write(ficheiroSTRINGS, extractNome(buffer), strlen(extractNome(buffer))); 		
	close(ficheiroSTRINGS);
	
return 0;
}	

