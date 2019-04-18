#include "maAPI.h"
#include "maPARSERS.h"

/*
	Verifica integridade dos descritores dos ficheiros e caso algum deles falhe 
	é devolvido um inteiro que identifica o respetivo descritor, porporcionando 
	desta forma a identificação do descritor que falhou!
	
	NOTA: Devolve 0 no caso de estar tudo conforme com os descritores

		exit(0) - indicates successful program termination & it is fully portable, While
		exit(1) - (usually) indicates unsucessful termination. However, it's usage is non-portable.
*/
int verifDescrt(int *descArtig, int *descStr){

	if(descArtig <0){
		write(2, "Erro na gravação do artigo no ficheiro ARTIGOS.txt!\n", 51);
		exit(0);
	}else if (descStr <0){
		write(2, "Erro na gravação do nome do artigo no ficheiro STRINGS.txt!\n", 61);
		exit(0);
	}
	return 0;
}





char* insereArtigo(char* nome,char* preco){
int fileARTGS = open("STRINGS.txt", O_CREAT | O_APPEND | O_RDWR, 0777);
int fileSTRS = open("ARTIGOS.txt", O_CREAT | O_APPEND | O_RDWR, 0777);

	if(verifDescrt(fileARTGS,fileSTRS) == 0){
		//COLOCAR AQUI O CODIGO DE INSERÇAO DO ARTIGO




	}else{
		exit(0);
	}

return 'x';
}


/*
	Vai buscar ao ficheiro STRINGS.txt o nome de um artigo
*/
char* getNome(int *ficheiro, int idArtigo){

return 'x';
}


/*
	Vai buscar ao ficheiro STOCKS.txt o stock de um artigo
*/
int getStock(int *ficheiro,int idArtigo){

return 0;
}








void callCommands(char* buffer){

buff = malloc(strlen(buffer)*sizeof(char));
strcat(buff,remSpc(buffer));
char inst = takeInstBuff(buff);
	//colocar aqui uma função que identifica a instrução, o nome de artigo e o preço do mesmo
	switch(inst){
		case 'i':
			//insereArtigo( takeNomeBuff(buff), takePrecoBuff(buff)); 
			/*funcção que lê do buffer os restantes parametros guardados no buffer e aplica-os 
			á função de inserção:  i <nome> <preço>  --> insere novo artigo, mostra o código */
			break;
		case 'n':
			/*n <código> <novo nome> --> altera nome do artigo*/
			break;
		case 'p':
			/*p <código> <novo preço>   --> altera preço do artigo*/
			break;
		default:
			printf("Opção inválida!\n");
	}

}