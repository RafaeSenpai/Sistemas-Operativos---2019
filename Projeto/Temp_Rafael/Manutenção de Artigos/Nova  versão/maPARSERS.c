#include "maPARSERS.h"



/*
	Variaveis locais
*/
char nomeArtigo[128];
char pr[1014];
char id[10];


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




char* takeNomeBuff(char* buffer){
int j, i, max;

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
int i,j;
i = strlen(buffer)-1;

	/*
		Parte do final da string do buffer e vai andando para trás até encontrar 1 espaço. 
		Nesta altura é suposto estarmos no inicio do preço do artigo na string
	*/
	for(; buffer[i]!=' ';i--);

	/*
		Procede á captura da parte da string referente ao preço
	*/
	for(j=0; buffer[i]!='\0'; i++){
		if((buffer[i]>='0' && buffer[i]<='9') || buffer[i]==',' || buffer[i]=='.'){
			pr[j]=buffer[i];
			j++;
		}
	}
	pr[j]='\0';

return pr;
}


/*
	Usado para buscar o artigo no qual se quer alterar o preço
*/
char* takeIDBuff(char* buff){
int j;
int i = strlen(buff)-1;
//char id[i]; //<---- tive que declarar esta variavel como publica snão dava warning

	/*O while imediatamente a baixo é a solução alternativa ao bug da função que remove espaços, menos 
	os espaços do final da string(fica sempre um espaço no final da string)*/
	while(buff[i]==' '){
		i--;
	}

	while(isdigit(buff[i]) || isalpha(buff[i]) || buff[i]!=' '){
		i--;
	}
	
	i++;

	for(j=0; buff[i]!='\0';i++,j++){
		id[j]=buff[i];
	}
	
	id[j]='\0';

return id;
}