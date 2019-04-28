#include "cvMenu.h"

char* remSpc (char* buffer){ 
int l,e;
l=0;
e=0;

	while(buffer[l]!='\0'){

	  if ((buffer[l])==' ' && buffer[e-1]== ' '){
	  	l++;
	  }else{
	  	buffer[e]=buffer[l]; l++; e++;
	  }
	}

	buffer[e]='\0';

	if(buffer[0]== ' '){
		buffer=&(buffer[1]);
	}

	return buffer;  
}



void menuComandos(char* buffer){

	/*
		takeInstBuff: Função responsavel pela leitura e da instrução constida na leitura do terminal
	*/
char* param1 = strtok(buffer," ");
char* param2 = strtok(NULL," ");

int countParams = 0;
	while(countParams==0){
		if(param1 && param2){
			countParams = 2;
		}else if(param1 || param2){
			countParams = 1;
		}

	}
/*
printf("1º valor devolvido pelo strtok:%s\n",param1);
printf("2º valor devolvido pelo strtok:%s\n",param2);
printf("3º valor devolvido pelo strtok:%s\n\n\n",param3);
*/
	switch(countParams){
		case 1:
//			<código_numérico> --> mostra no stdout stock e preço
			getStock(param1);
			//getStockAndPrice(param1);
			printf("\n"); 
			break;
		case 2:
//			<código_numérico> <quantidade> --> actualiza stock e mostra novo stock
			atualizaStock(param1,param2);
			printf("\n");
			break;
		default:
			system("clear");
			write(1,"Opção inválida!\nInsira novo comando:\n",41);
	}

}