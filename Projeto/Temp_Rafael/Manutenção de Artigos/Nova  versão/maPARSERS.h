#ifndef maPARSERS_h
#define maPARSERS_h
#include <string.h>
#include <ctype.h>
#include <stdlib.h> //mallocs
/*
	Remove do buffer todos os espaços a mais no inicio, no final e entre 
	as palavras ou caracters.

	NOTA: Sempre que uma string tem varios espaços no seu final, a função remove todos
	deixando apenas 1. Supostamente no final da string não devia de ficar nenhum espaço, 
	mas até ao momento não se resolveu este caso. Tendo em conta esta limitação, todos 
	os inputs dados ao programa funcionam corretamente, podendo apenas haver erros no 
	caso em que os inputs contenham 1 ou mais espaços no seu final. Mais precisamente 
	na função takeIDBuff.
*/
char* remSpc (char* buffer);

  /*
	Captura o primeiro char que encontrar e considera-o como o comando a executar

	OBS: Esta função foi criada com o objetivo de, caso o buffer tenha espaços 
	logo no inicio (a função remSpc não resolve) a função irá ignorar todos os espaços
	e apenas pegar o primeiro caracter que lhe aparecer á frente considerando este 
	o comando a executar. Salvaguarda também a possibilidade de o 1º caracter ser um 
	caracter para uma instrução, mas não poder ser interpretado por este fazer parte 
	de uma palavra
*/
char takeInstBuff(char* buffer);

/*
	Retirar do buffer o nome do artigo
*/
char* takeNomeBuffI(char* buffer);

/*
	Retira do buffer o preço do artigo
*/
char* takePrecoBuff(char* buffer);

/*
	Retira do buffer o ID do artigo
*/
char* takeIDBuff(char* buff);


#endif
