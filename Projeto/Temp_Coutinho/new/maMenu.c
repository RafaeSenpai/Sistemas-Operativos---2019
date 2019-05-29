#include "maMenu.h"

void menuComandos(char* buffer){

	/*
		takeInstBuff: Função responsavel pela leitura e da instrução constida na leitura do terminal
	*/

char* param1 = strtok(buffer," ");
char* param2 = strtok(NULL," ");
char* param3 = strtok(NULL," ");
/*
printf("1º valor devolvido pelo strtok:%s\n",param1);
printf("2º valor devolvido pelo strtok:%s\n",param2);
printf("3º valor devolvido pelo strtok:%s\n\n\n",param3);
*/
	switch(*param1){
		case 'i':
/*			printf("2º valor devolvido pelo strtok no case: i:%s\n",param2);
			printf("3º valor devolvido pelo strtok no case: i:%s\n\n\n",param3);
*/			insereArtigo(param2,param3);
			printf("\n");
			break;
		case 'n':
/*			printf("2º valor devolvido pelo strtok no case: n:%s\n",param2);
			printf("3º valor devolvido pelo strtok no case: n:%s\n\n\n",param3);
*/			/*n <código> <novo nome> --> altera nome do artigo*/
			editaNome(param2,param3);
			printf("\n");
			break;
		case 'p':
			/*p <código> <novo preço>   --> altera preço do artigo*/
			editaPreco(param2, param3);
			break;
		case 't':
			/*ESTE MENU 't' É APENAS PARA TESTAR FUNÇÕES, SERÁ REMOVIDO DE FUTURO*/
//			printf("2º valor devolvido pelo strtok no case: t:%s\n",param2);
			getArtigo(param2);
			printf("\n");
		break;
		default:
			printf("Opção inválida!\n");
	}

}
