#include "maMenu.h"

void menuComandos(char* buffer){
char instrucao;
	
	/*
		takeInstBuff: Função responsavel pela leitura e da instrução constida na leitura do terminal
	*/
	instrucao = takeInstBuff(buffer);
	
	switch(instrucao){
		case 'i':
			insereArtigo( takeNomeBuffI(buffer), takePrecoBuff(buffer));
			printf("\n"); 
			break;
		case 'n':
			/*n <código> <novo nome> --> altera nome do artigo*/
			editaNome(takeIDBuff(buffer),takeNomeBuffN(buffer));
			printf("\n");
			break;
		case 'p':
			/*p <código> <novo preço>   --> altera preço do artigo*/
			//editaPreco(takeIDBuff(buffer));
			break;
		case 't':	
			/*ESTE MENU 't' É APENAS PARA TESTAR FUNÇÕES, SERÁ REMOVIDO DE FUTURO*/
			getArtigo(takeIDBuff(buffer));
			printf("\n");
		break;
		default:
			printf("Opção inválida!\n");
	}

}