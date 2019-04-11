#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 250
int main(){
char nomeProduto[MAX];
char linhaProduto[MAX];
float preco = 0.0;
int id_Linha=0;
char array[10]; //array que será usado para guardarr a string correspondente ao preço do artigo
FILE* ficheiro; //identificador de fluxo

																	/*Abrindo ficheiro
																	FILE *open(char *nomeFicheiro, char modo_de_acesso);

																	O modo de acesso é uma string que contém uma seqüência de caracteres que dizem se o arquivo será aberto para gravação ou leitura. 
																	Depois de aberto o arquivo, você só poderá executar os tipos de ação previstos pelo modo de acesso: não poderá ler de um arquivo 
																	que foi aberto somente para escrita, por exemplo. Os modos de acesso estão descritos na tabela a seguir:

																	r	Abre o arquivo somente para leitura. O arquivo deve existir. (O r vem do inglês read, ler)
																	r+	Abre o arquivo para leitura e escrita. O arquivo deve existir.
																	w	Abre o arquivo somente para escrita no início do arquivo. Apagará o conteúdo do arquivo se ele já existir, criará um arquivo novo se não existir. (O w vem do inglês write, escrever)
																	w+	Abre o arquivo para escrita e leitura, apagando o conteúdo pré-existente.
																	a	Abre o arquivo para escrita no final do arquivo. Não apaga o conteúdo pré-existente. (O a vem do inglês append, adicionar, apender)
																	a+	Abre o arquivo para escrita no final do arquivo e leitura.
																	*/





																	/*
																	Ao terminar de usar um arquivo, você deve fechá-lo. Isso é feito pela função fclose()
																	int fclose (FILE *fluxo);
																	*/

																	/*
																	A função exit() fecha todos os arquivos que um programa tiver aberto.
																	A função fflush() força a gravação de todos os caracteres que estão no buffer para o arquivo.
																	*/

	if((ficheiro = fopen("ARTIGOS.txt", "a+")) == NULL) /* Abre arquivo binário para escrita */
	    {
	          printf("Erro na abertura do arquivo");
	          exit(1);    
	    }
	
	printf("Insira o nome do produto:");
																	/*
																	A função fflush serve para limpar um fluxo de dados, no caso o fluxo stdin, que é o fluxo 
																	do qual você quer ler os dados necessários para o funcionamento do programa.
																	*/
	fflush(stdin);	
																	/*
																	Em alternativa á função gets() peca nesse quesito, de tamanho da string, pois podemos digitar 
																	mais caracteres do que a string alocou de memória, e "quebraríamos" o programa por conta de um overflow.
																	A função fget(), que é mais segura. Ela recebe três dados: a string que vai armazenar o que 
																	vai ser digitado ( no nosso caso é a variável "str"), o tamanho da string e de onde vai ler 
																	(ela pode ler de um arquivo de texto, por exemplo). Para ler do teclado, usamos stdin.
																	*/
																	//fgets(nomeProduto, 10, stdin);
																	/*
																	alternativ ao fgets sem que o nome a ser gravado para ficheiro contenha lixo no final
																	scanf ( "%256[^\n]", str);
																	*/



																	/*
																	1º LE A PALAVRA COM O scanf
																	2º calcula o tamanho da palavra sem o \n
																	3º guarda a palavra no ficheiro atravez do fwrite em que o parametro do tamanho a guardar é o valor calculado pelo tamanho obtido no passo anterior
																	*/
																	/*
																	Vamos dizer para a scanf() parar de pegar nossa string somente quando encontrar um caractere de NEW LINE (um enter). Para isso, usamos o operador: [^\n]
																	Logo, nosso código da scanf() para ler strings com espaços e armazenar na variável "nomeProduto" é:
																	*/
	scanf ( "%[^\n]", nomeProduto);

	printf("Preço do produto: ");
	scanf("%f",&preco);
																	/*sprintf - Para converter o float do preço num char para que este possa ser adicionado á linha do produto.
																	  The snprintf() function formats and stores a series of characters and values in the array buffer. 
																	  The snprintf() function with the addition of the n argument,
																	  which indicates the maximum number of characters (including at the end of null character) to be 
																	  written to buffer.
																	*/
	sprintf(array, "%.2f", preco);

	strcat(linhaProduto,strcat(strcat(strcat(nomeProduto, " "),array),"\n"));

	if(fwrite(linhaProduto, (strlen(nomeProduto))*sizeof(char), 1,ficheiro) != 1)
		   /* Escreve a variável o nome do arquivo */
	       printf("Erro na escrita do arquivo");
	fclose(ficheiro); 

	return 0;
}

