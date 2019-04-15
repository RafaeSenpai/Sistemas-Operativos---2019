#include <unistd.h>  //definições e declarações de chamadas
#include <fcntl.h> //definição modos de abertura de ficheiro
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>


int removeInitialSpaces(char* string){
int i,j;
char tmp[1024];
i = 0;
j = 0;
	/*
		Avança na string enquanto esta ainda contiver espaços em branco e não for o seu fim
	*/
	for(i = 0; string[i] == ' ' || string[i]!='\n' ; i++)
	/*
		Encontrando finalmente caracteres validos inicia a copia da string para uma string 
		temporaria
	*/
	while(string[i] != '\n'){
		tmp[j] = string[i];
		j++;
		i++;
	}
	tmp[j]='\n';
	/*
		Caso não se trate de uma string que apenas contenha espaços em branco volta a copiar 
		o seu conteudo para dentro da string passada como parametro
	*/
	if(j>0){
		for(j = 0; tmp[j]!='\n'; j++){
			string[j] = tmp[j];
		}
		//j++; //????????????????
		string[j] = '\n';
		//return *string;

		for(i=0; string[i]!='\n';i++){
			printf("%c",string[i]);
		}
		printf("\n\n\n");
	}

return 1;
}


int main(){
char string[1014];


printf("insisra a string\n");

removeInitialSpaces(" 123    456");


return 0;
}
