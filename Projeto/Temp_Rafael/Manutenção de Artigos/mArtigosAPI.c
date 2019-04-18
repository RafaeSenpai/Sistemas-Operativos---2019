#include "mArtigosAPI.h"

/*
	Variaveis locais
*/
char nomeArtigo[1024];
char pr[1014];




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




/*
	Remove do buffer todos os espaços a mais
*/
char* remSpc(char* buffer) {

    int j = 1;
    for (int i = 1; buffer[i]; i++) {
        if (buffer[i] != ' ' || (buffer[i - 1] != ' ')) {
           buffer[j] = buffer[i];
           j++;
        }
    }
    buffer[j-1] = '\0';
return buffer;
}


/*
	Captura o primeiro char que encontrar e considera-o como o comando a executar

	OBS: Esta função foi criada com o objetivo de, caso o buffer tenha espaços 
	logo no inicio (a função remSpc não resolve) a função irá ignorar todos os espaços
	e apenas pegar o primeiro caracter que lhe aparecer á frente considerando este 
	o comando a executar. Salvaguarda também a possibilidade de o 1º caracter ser um 
	caracter para uma instrução, mas não poder ser interpretado por este fazer parte 
	de uma palavra
*/
char takeInstBuff(char* buffer){
int i = 0;

	if(buffer[i]==' '){
		while(buffer[i]==' '){
			i++;
		}
		if(buffer[i+1]!=' '){
			//apenas um comando não interpretavel
			return 'w';		
		}
		return buffer[i];
	}else if(buffer[i]!=' ' && buffer[i+1]==' '){
		return buffer[i];
	}
	return 'w';
}


/*
	Retirar do buffer o nome do artigo
*/
char* takeNomeBuff(char* buffer){
int j, i,min, max;

	for(max=strlen(buffer)-1; buffer[max]!=' '; max--);//coloca-se na posição onde começa o preço

	for(j=0,i=2; i<=max; i++){
		if( isalpha(buffer[i]) || buffer[i]<=' '){
			nomeArtigo[j]=buffer[i];
			j++;
		}
	}
	nomeArtigo[j-1]='\n';

return nomeArtigo;
}




/*
	Retirar do buffer o preço do artigo

	IMPORTANTE: A função não consegue capturar o preço quando a seguir deste tem espaços
*/
char* takePrecoBuff(char* buffer){
float preco;
int i,j;
i = strlen(buffer)-1;

	/*
		Parte do final da string do buffer e vai andando para trás até encontrar 1 espaço. 
		Nesta altura é suposto estarmos no inicio do preço do artigo na string
	*/
	for(i; buffer[i]!=' ';i--);

	/*
		Procede á captura da parte da string referente ao preço
	*/
	for(j=0,i; buffer[i]!='\0'; i++){
		if((buffer[i]>='0' && buffer[i]<='9') || buffer[i]==',' || buffer[i]=='.'){
			pr[j]=buffer[i];
			j++;
		}
	}
	pr[j]='\0';

return pr;
}






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


/*


char* insereArtigo(char* nome,char* preco){
int fileARTGS = open("STRINGS.txt", O_CREAT | O_APPEND | O_RDWR, 0777);
int fileSTRS = open("ARTIGOS.txt", O_CREAT | O_APPEND | O_RDWR, 0777);

	if(verifDescrt(fileARTGS,fileSTRS) == 0){
		//COLOCAR AQUI O CODIGO DE INSERÇAO DO ARTIGO




	}else{
		exit(0);
	}
}

*/
/*
	Vai buscar ao ficheiro STRINGS.txt o nome de um artigo
*/
//char* getNome(int *ficheiro, int idArtigo){

//}


/*
	Vai buscar ao ficheiro STOCKS.txt o stock de um artigo
*/
//int getStock(int *ficheiro,int idArtigo){

//}


