#include <unistd.h>  //definições e declarações de chamadas
#include <fcntl.h> //definição modos de abertura de ficheiro
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

/*
Conta numero de linhas no ficheiro STRINGS.txt
*/
int contLinesSTRINGS(){
int numLinhas = 0;
char c;
FILE *ficheiroSTRINGS;

	ficheiroSTRINGS = fopen("STRINGS.txt","r");

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

int main(){
	printf("%d",contLinesSTRINGS());
	return 0;
}