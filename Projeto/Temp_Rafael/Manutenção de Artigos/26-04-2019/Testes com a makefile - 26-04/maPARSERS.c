#include "maPARSERS.h"
#include <stdio.h> //<---------------------------------------PARA ELIMINAR DEPOIS DOS TESTES

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
			//w: apenas um comando não interpretavel
			return 'w';		
		}
		return buffer[i];
	}else if(buffer[i]!=' ' && buffer[i+1]==' '){
		return buffer[i];
	}
	return 'w';
}




char* takeNomeBuffI(char* buffer){
char* nomeArtigo = malloc(128*sizeof(char));
int j, i, max;

	for(max=strlen(buffer)-1; buffer[max]!=' '; max--);

	for(j=0,i=2; i<=max; i++){
		if( isalpha(buffer[i]) || buffer[i]!=' '){
			nomeArtigo[j]=buffer[i];
			j++;
		}
	}
	nomeArtigo[j-1]='\n';

return nomeArtigo;
}



/*


	for(j=0,i=2; i<=max; i++){
		if( isalpha(buffer[i]) || buffer[i]==' '){
			nomeArtigo[j]=buffer[i];
			j++;
		}
	}
	nomeArtigo[j-1]='\n';
	printf("Output  no takeNomeBuff:%s\n",nomeArtigo);//---------------------------------------PARA ELIMINAR DEPOIS DOS TESTES

return nomeArtigo;
}

*/


/*
	Retirar do buffer o preço do artigo

	IMPORTANTE: A função não consegue capturar o preço quando a seguir deste tem espaços
*/
char* takePrecoBuff(char* buffer){
int i,j;
i = strlen(buffer)-1;
char* pr = malloc(128*sizeof(char));
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
char* id = malloc(10*sizeof(char));
printf("Conteudo do buffer no takeIDBuff:%s\n",buff);//---------------------------------------PARA ELIMINAR DEPOIS DOS TESTES
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
printf("Output  no takeIDBuff:%s\n",id);//---------------------------------------PARA ELIMINAR DEPOIS DOS TESTES
return id;
}



