#include "maParsers.h"
/*
	Variaveis locais
*/
char nomeArtigo[1024];
char pr[1014];

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

