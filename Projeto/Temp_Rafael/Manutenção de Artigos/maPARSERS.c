#include "maPARSERS.h"


/*
	Variaveis locais
*/
char nomeArtigo[1024];
char pr[1014];
char id[1024];


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
char* remSpc (char* buffer){ 

    int l,e;
    l=e=0;

    while(buffer[l]!='\0') {

      if ((buffer[l])==' ' && buffer[e-1]== ' ') l++;
      else {buffer[e]=buffer[l]; l++; e++;}
    }
    
    buffer[e]='\0';

    if(buffer[0]== ' '){
    	buffer=&(buffer[1]);
    }

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